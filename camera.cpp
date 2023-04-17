#include "camera.h"
#include "ui_camera.h"
#include <vector>
#include <QVector>
#include <nameimg.h>
#include <iostream>
#include <QDebug>
#include <QXmlStreamWriter>
using namespace std;
camera::camera(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::camera)
{
    ui->setupUi(this);
   // this->setStyleSheet("background:white;");
    calibrate_timer=new QTimer(this);
    find_corner_timer=new QTimer(this);
    connect(find_corner_timer,SIGNAL(timeout()),this,SLOT(Time_find_corner_update()));
    connect(calibrate_timer,SIGNAL(timeout()),this,SLOT(Time_calibrate_update()));
    setWindowTitle("相机内参标定");
    //setFixedSize(this->width(), this->height());
    //connect(ui->ListWidget_imgs,&QListWidget::currentRowChanged,this,&camera::showImg);
    this->camneican = make_unique<cam_neican>();
    mbtngroup = new QButtonGroup(this);
    mbtngroup->addButton(ui->radioButton, 0);
    mbtngroup->addButton(ui->radioButton_2, 1);
    mbtngroup->addButton(ui->radioButton_3, 2);
    connect(ui->radioButton, &QRadioButton::clicked, this, &camera::onRadiobuttonClicked);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &camera::onRadiobuttonClicked);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &camera::onRadiobuttonClicked);
    connect(ui->ListWidget_imgs, &QListWidget::itemClicked, this, &camera::onitemclicked);
    connect(ui->inputbuttonimg, &QAction::triggered, this, &camera::imgaddclick);
    connect(ui->actiondelet, &QAction::triggered, this, &camera::deleteimgclick);
    connect(ui->actionset, &QAction::triggered, this, &camera::setboardclick);
    connect(ui->action_3, &QAction::triggered, this, &camera::startcameraclick);
    connect(ui->action1, &QAction::triggered, this, &camera::startcalicamera);
    connect(ui->action_2, &QAction::triggered, this, &camera::saveresultcamera);
    connect(ui->action_4, &QAction::triggered, this, &camera::savecamera_xml);
    connect(ui->action_5, &QAction::triggered, this, &camera::readcamera_xml);
    connect(ui->action, &QAction::triggered, this, &camera::newproject);
    connect(ui->action_6, &QAction::triggered, this, &camera::helpclick);
}

camera::~camera()
{
    delete ui;
}

void camera::imgaddclick()
{
    ui->ListWidget_imgs->clear();
    camneican->imagePaths.clear();
    camneican->clear();
    passcal_flag = 0;
    Imgpath.append(QFileDialog::getOpenFileNames(this, "选择多张图片", QDir::currentPath(), "图片格式 (*.jpg *.png *.bmp)"));
    for (int i = 0; i < Imgpath.size(); i++)
        camneican->imagePaths.push_back(Imgpath[i].toStdString());
    Imgpath.clear();
    for (int i = 0; i < camneican->imagePaths.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(camneican->imagePaths[i]));
        ui->ListWidget_imgs->addItem(item);
        //    QListWidgetItem *item = new QListWidgetItem();
        //    QCheckBox *checkBox= new QCheckBox ();
        //    ui->ListWidget_imgs->addItem(item);//在ListWidget中添加一个条目
        //    ui->ListWidget_imgs->setItemWidget(item, checkBox);//在这个条目中放置CheckBox
        //    item->setText(QString::fromStdString(camneican->imagePaths[i]));
        //    std::cout<<camneican->imagePaths[i]<<std::endl;
    }
    ui->ListWidget_imgs->setCurrentRow(0);
}

void camera::deleteimgclick()
{
    QListWidgetItem *item = ui->ListWidget_imgs->currentItem();
    for (int i = 0; i < camneican->imagePaths.size(); i++)
    {
        if (camneican->imagePaths[i] == item->text().toStdString())
        {
            camneican->imagePaths.erase(camneican->imagePaths.begin() + i);
            if (passcal_flag)
            {
                camneican->imagePointsSeq.erase(camneican->imagePointsSeq.begin() + i);
                camneican->objectPointsSeq.erase(camneican->objectPointsSeq.begin() + i);
                camneican->conerfindseq.erase(camneican->conerfindseq.begin() + i);
            }
        }
    }
    ui->ListWidget_imgs->removeItemWidget(item);
    delete item;
}

void camera::startcameraclick()
{
    camneican->clear();
    if (camneican->boardSize.height <= 0 || camneican->boardSize.width <= 0 || camneican->squareSize <= 0)
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("请设置棋盘参数");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
         itemw->setWindowTitle("错误");
        itemw->setWindowTitle("错误");
        return;
    }
    showint();
    camneican->findCorners();
    timer_widget = new QWidget;
    timer_label = new QLabel(timer_widget);
    find_corner_timer->start(5);
    passcal_flag = 1;

}

void camera::onRadiobuttonClicked()
{

    int checkid = mbtngroup->checkedId();
    cout << "check" << checkid << endl;
    switch (checkid)
    {
    case 0:
        ui->imgshow->clear();
        imgshow_flag = 0;
        break;
    case 1:
        ui->imgshow->clear();
        imgshow_flag = 1;
        break;
    case 2:
        imgshow_flag = 2;
        break;
    }
}

void camera::onitemclicked(QListWidgetItem *item)
{
    showint();
    if (imgshow_flag == 0)
    {
        ui->imgshow->clear();
        QPixmap imgL = QPixmap(item->text());
        imgL = imgL.scaled(ui->imgshow->size(), Qt::KeepAspectRatio);
        ui->imgshow->setPixmap(imgL);
        cout << imgshow_flag << endl;
    }
    else if (imgshow_flag == 1 && passcal_flag)
    {
        ui->imgshow->clear();
        cv::Mat cvImg = camneican->drawChessboardCornersimg(item->text().toStdString());
        cv::cvtColor(cvImg, cvImg, cv::COLOR_BGR2RGB);
        QImage img = QImage(cvImg.data, cvImg.cols, cvImg.rows, cvImg.cols * cvImg.channels(), QImage::Format_RGB888);
        img = img.scaled(ui->imgshow->size(), Qt::KeepAspectRatio);
        ui->imgshow->setPixmap(QPixmap::fromImage(img));
    }
    else if (imgshow_flag == 2)
    {
        ui->imgshow->clear();
        stringstream textStr;
        if (!camneican->mtx.empty())
        {
            textStr << "ret:" << endl;
            textStr << camneican->ret << endl;
            textStr << "mtx:" << endl;
            textStr << camneican->mtx << endl;
            textStr << "dist畸变值:" << endl;
            textStr << camneican->dist << endl;
            ui->imgshow->clear();
            ui->imgshow->setText(QString(textStr.str().c_str()));
           // ui->imgshow->adjustSize();
        }
    }
    else
    {
        ui->imgshow->clear();
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        itemw->setWindowTitle("提示");
        wl->setText("请先执行检测，再查看结果图");
        wl->resize(500, 200);
        itemw->show();
         itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
    }
}

void camera::startcalicamera()
{
    if (passcal_flag)
    {
        camneican->setImageSize(cv::imread(camneican->imagePaths[0]).size());
        camneican->calicamera();
        timer_widget = new QWidget;
        timer_label = new QLabel(timer_widget);
        calibrate_timer->start(5);
//        timer_label->setText("标定完成，可查看结果，保存标定结果");
//        timer_label->setWordWrap(true);
//        QStringList not_calibrate_name_list;
//        timer_label->setText(timer_label->text()+"\n"+"以下路径图片因为角点未找到未进行计算：");
//        for (int i = 0; i < camneican->imagePaths.size(); i++)
//        {
//            if(camneican->conerfindseq[i]==0)
//            {
//             timer_label->setText(timer_label->text()+"\n"+QString::fromStdString(camneican->imagePaths[i]));
//            }
//        }
//        timer_label->adjustSize();
//        timer_widget->show();
    }
    else
    {
        //ui->textEdit->append("请先执行检测");
        //ui->textEdit->append("===");
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("请先执行检测");
        wl->resize(500, 200);
        itemw->show();
         itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("提示");
    }
}

void camera::saveresultcamera()
{
    redsult->show();
    redsult->move(this->geometry().center().x()-redsult->width()/2,this->geometry().center().y()-redsult->height()/2);
    connect(redsult, &savecamerresult::sendData, this, &camera::receiveresultdata);
}

void camera::savecamera_xml()
{
    // QString savereultPath=QFileDialog::getSaveFileName(this,tr("Save Xml"),"untitled.project",tr("Xml files(*.xml)"));
    cv::FileStorage ymlFile(this->savereultPath.toStdString(), cv::FileStorage::WRITE);
    ymlFile << "project" << 1;
    ymlFile << "boardSize" << camneican->boardSize;
    ymlFile << "squareSize" << camneican->squareSize;
    ymlFile << "image" << camneican->imagePaths;
    ymlFile << "imagePointsSeq" << camneican->imagePointsSeq;
    ymlFile << "objectPointsSeq" << camneican->objectPointsSeq;
    ymlFile << "imageSize" << camneican->imageSize;
    ymlFile << "reprojectionError" << camneican->ret;
    ymlFile << "CameraMat" << camneican->mtx;
    ymlFile << "DistCoeff" << camneican->dist;
    ymlFile << "passcal_flag" << passcal_flag;
}

void camera::readcamera_xml()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), ".", tr("project files (*.project)"));
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadFile(filename.toStdString(), cv::FileStorage::READ);
        if (!ymlreadFile.isOpened())
            return;
        else
        {
            ui->ListWidget_imgs->clear();
            camneican->imagePaths.clear();
            camneican->clear();
        }
        if (int(ymlreadFile["project"]) != 1)
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("请打开内参项目文件");
            wl->resize(500, 200);
            itemw->show();
             itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
            itemw->setWindowTitle("错误");
        }
        else
        {
            ymlreadFile["boardSize"] >> camneican->boardSize;
            ymlreadFile["squareSize"] >> camneican->squareSize;
            ymlreadFile["image"] >> camneican->imagePaths;
            ymlreadFile["imagePointsSeq"] >> camneican->imagePointsSeq;
            ymlreadFile["objectPointsSeq"] >> camneican->objectPointsSeq;
            ymlreadFile["imageSize"] >> camneican->imageSize;
            ymlreadFile["reprojectionError"] >> camneican->ret;
            ymlreadFile["CameraMat"] >> camneican->mtx;
            ymlreadFile["DistCoeff"] >> camneican->dist;
            ymlreadFile["passcal_flag"] >> passcal_flag;
            if (camneican->imagePaths.size() <= 0)
                return;
            for (int i = 0; i < camneican->imagePaths.size(); i++)
            {
                QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(camneican->imagePaths[i]));
                ui->ListWidget_imgs->addItem(item);
                //camneican->imagePaths.push_back(camneican->imagePaths[i]);
            }
            showint();
        }
    }
}
void camera::setboardclick()
{
    camneican->clear();
    board->show();
    board->move(this->geometry().center().x()-board->width()/2,this->geometry().center().y()-board->height()/2);
    connect(board, &setboard::sendData, this, &camera::receivedata);
}

void camera::receivedata(int a, int b, float c)
{
    // camneican->boardSize.height=n;
    // camneican->boardSize.width=b;
    camneican->setBoardSize(a, b);
    camneican->setSquareSize(c);
    passcal_flag = 0;
    showint();
}

void camera::showint()
{
    ui->label->setText("列：" + QString::number(camneican->boardSize.width + 1));
    ui->label_2->setText("行：" + QString::number(camneican->boardSize.height + 1));
    ui->label_3->setText("大小：" + QString::number(camneican->squareSize) + "X" + QString::number(camneican->squareSize));
}

void camera::helpclick()
{
    camera_neican_help *help = new camera_neican_help;
    help->show();
    help->move(this->geometry().center().x()-help->width()/2,this->geometry().center().y()-help->height()/2);
}

void camera::newproject()
{
    newp->show();
    newp->move(this->geometry().center().x()-newp->width()/2,this->geometry().center().y()-newp->height()/2);
    connect(newp, &newcamerproject::sendData, this, &camera::receiveprojectdata);
}

void camera::receiveprojectdata(QString a)
{
    savereultPath = a;
    cout << savereultPath.toStdString() << endl;
}

void camera::receiveresultdata(QString a)
{
    savereultPath_biaoding = a;
    cv::FileStorage ymlFile(savereultPath_biaoding.toStdString(), cv::FileStorage::WRITE);
    ymlFile << "xmlflag" << 1;
    ymlFile << "imageSize" << camneican->imageSize; // 图像尺寸
    ymlFile << "reprojectionError" << camneican->ret;
    ymlFile << "CameraMat" << camneican->mtx;
    ymlFile << "DistCoeff" << camneican->dist;
}

void camera::Time_calibrate_update()
{
    timer_label->setText("标定正在进行，请勿关闭");
    timer_label->setWordWrap(true);
    if(xunhuan)
         timer_label->setText(timer_label->text()+".");
    else
        timer_label->setText(timer_label->text()+"...");
    xunhuan=!xunhuan;
    this->hide();
    QStringList not_calibrate_name_list;
    timer_label->setText(timer_label->text()+"\n"+"以下图片中没有找到棋盘：");
    for (int i = 0; i < camneican->imagePaths.size(); i++)
    {
        if(camneican->conerfindseq[i]==0)
        {
         timer_label->setText(timer_label->text()+"\n"+QString::fromStdString(camneican->imagePaths[i]));
        }
    }
    timer_label->adjustSize();
    timer_widget->setFixedSize(timer_widget->width(), timer_widget->height());
    timer_widget->show();
    timer_widget->move(this->geometry().center().x()-timer_widget->width()/2,this->geometry().center().y()-timer_widget->height()/2);
    timer_widget->setWindowTitle("标定正在进行，请勿关闭");
    if(camneican->calibrate_flag)
    {
        this->show();
        timer_widget->close();
        calibrate_timer->stop();
    }
}

void camera::Time_find_corner_update()
{
    this->hide();
    timer_label->clear();
    timer_label->setText("检测正在进行，请勿关闭");
    timer_label->setWordWrap(true);
    if(xunhuan)
         timer_label->setText(timer_label->text()+".");
    else
        timer_label->setText(timer_label->text()+"...");
    xunhuan=!xunhuan;
    timer_label->setText(timer_label->text()+"\n"+"剩余待检测图片数："+QString::number(camneican->imagePaths.size()-camneican->conerfindseq.size()));
    //for(int i=0;i<camneican->conerfindseq.size();i++)
    //{
    //    if(camneican->conerfindseq[i]==0)
    //    {
    //     timer_label->setText(timer_label->text()+"\n"+QString::fromStdString(camneican->imagePaths[i])+"未找到角点");
    //    }
    //    else
    //    timer_label->setText(timer_label->text()+"\n"+QString::fromStdString(camneican->imagePaths[i])+"找到角点");
    //}
    //timer_label->adjustSize();
    timer_label->resize(500, 200);
    timer_widget->setFixedSize(timer_widget->width(), timer_widget->height());
    timer_widget->show();
    timer_widget->move(this->geometry().center().x()-timer_widget->width()/2,this->geometry().center().y()-timer_widget->height()/2);
    timer_widget->setWindowTitle("检测正在进行，请勿关闭");
    if(camneican->corner_flag)
    {
        timer_widget->close();
        this->show();
        find_corner_timer->stop();
    }
}
