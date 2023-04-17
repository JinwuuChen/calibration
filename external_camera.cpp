#include "external_camera.h"
#include "ui_external_camera.h"
external_camera::external_camera(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::external_camera)
{
    ui->setupUi(this);
    //  this->setStyleSheet("background:white;");
    setWindowTitle("相机外参标定");
    // setFixedSize(this->width(), this->height());
    //    m_imageBox.Init(ui->verticalLayout_2);
    //    connect(&m_imageBox,&ImageBox::ImageClick,this,&external_camera::ActImageClick);
    //    connect(ui->pushButton_4,&QPushButton::pressed,[this]{
    //        QString filename = QFileDialog::getOpenFileName();
    //        if(filename.isEmpty())
    //            return;
    //        m_imageBox.SetImage(filename);
    //    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, &external_camera::imgaddclick);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &external_camera::deleteimgclick);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &external_camera::Calculatepnp);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &external_camera::openresultneican_click);
    connect(ui->pushButton_14, &QPushButton::clicked, this, &external_camera::saveresult_xml_click);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &external_camera::addcoordinateclick);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &external_camera::savecoordinateclick);
    //    mbtngroup= new QButtonGroup(this);
    //    mbtngroup->addButton(ui->radioButton,0);
    //    mbtngroup->addButton(ui->radioButton_2,1);
    //    connect(ui->radioButton,&QRadioButton::clicked,this,&external_camera::onRadiobuttonClicked);
    //    connect(ui->radioButton_2,&QRadioButton::clicked,this,&external_camera::onRadiobuttonClicked);
    connect(ui->ListWidget_imgs, &QListWidget::currentRowChanged, this, &external_camera::showImg);
    connect(ui->pushButton, &QPushButton::clicked, this, &external_camera::newprojectclick);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &external_camera::external_camera_help_click);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &external_camera::saveprojectclick);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &external_camera::openprojectclick);
    ui->twcoordinate->clear();
    ui->twcoordinate->setColumnCount(5);
    QStringList coordinatelistname;
    coordinatelistname << "二维坐标x";
    coordinatelistname << "二维坐标y";
    coordinatelistname << "三维坐标x";
    coordinatelistname << "三维坐标y";
    coordinatelistname << "三维坐标z";
    ui->twcoordinate->setHorizontalHeaderLabels(coordinatelistname);
    ui->twcoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twcoordinate->verticalHeader()->hide();
    ui->twcoordinate->setAlternatingRowColors(true);
}

external_camera::~external_camera()
{
    delete ui;
}

void external_camera::appendtw(int a, int b, int c, int d, int e)
{
    int count = ui->twcoordinate->rowCount();
    ui->twcoordinate->setRowCount(count + 1);
    QTableWidgetItem *twitema = new QTableWidgetItem(QString::number(a));
    QTableWidgetItem *twitemb = new QTableWidgetItem(QString::number(b));
    QTableWidgetItem *twitemc = new QTableWidgetItem(QString::number(c));
    QTableWidgetItem *twitemd = new QTableWidgetItem(QString::number(d));
    QTableWidgetItem *twiteme = new QTableWidgetItem(QString::number(e));
    twitema->setTextAlignment(Qt::AlignCenter);
    twitemb->setTextAlignment(Qt::AlignCenter);
    twitemc->setTextAlignment(Qt::AlignCenter);
    twitemd->setTextAlignment(Qt::AlignCenter);
    twiteme->setTextAlignment(Qt::AlignCenter);
    ui->twcoordinate->setItem(count, 0, twitema);
    ui->twcoordinate->setItem(count, 1, twitemb);
    ui->twcoordinate->setItem(count, 2, twitemc);
    ui->twcoordinate->setItem(count, 3, twitemd);
    ui->twcoordinate->setItem(count, 4, twiteme);
}
void external_camera::savecoordinateclick()
{
//    point2s.clear();
//    point3s.clear();
//    int tempnum = ui->twcoordinate->rowCount();
//    if (!tempnum)
//    {
//        QWidget *itemw = new QWidget;
//        QLabel *wl = new QLabel(itemw);
//        wl->setText("没有输入坐标");
//        wl->resize(500, 200);
//        itemw->show();
//        itemw->setWindowTitle("错误");
//    }
//    else
//    {
//        QTableWidgetItem *item = new QTableWidgetItem;
//        for (int i = 0; i < tempnum; i++)
//        {
//            point2s.push_back(cv::Point2f(ui->twcoordinate->item(i, 0)->text().toInt(), ui->twcoordinate->item(i, 1)->text().toInt()));
//            point3s.push_back(cv::Point3f(ui->twcoordinate->item(i, 2)->text().toInt(), ui->twcoordinate->item(i, 3)->text().toInt(), ui->twcoordinate->item(i, 4)->text().toInt()));
//        }
//    }
    while (ui->twcoordinate->selectedItems().count() > 0)
    {
        int rowidx = ui->twcoordinate->selectedItems()[0]->row();
        ui->twcoordinate->removeRow(rowidx);
    }
}

void external_camera::Calculatepnp()
{
    point2s.clear();
    point3s.clear();
    int tempnum = ui->twcoordinate->rowCount();
    if (!tempnum)
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("没有输入坐标");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
    }
    else
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        for (int i = 0; i < tempnum; i++)
        {
            point2s.push_back(cv::Point2f(ui->twcoordinate->item(i, 0)->text().toInt(), ui->twcoordinate->item(i, 1)->text().toInt()));
            point3s.push_back(cv::Point3f(ui->twcoordinate->item(i, 2)->text().toInt(), ui->twcoordinate->item(i, 3)->text().toInt(), ui->twcoordinate->item(i, 4)->text().toInt()));
        }
    }

    bool found;
    if (open_xml_flag)
    {
        if (point2s.size() <= 8)
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("坐标数小于9");
            wl->resize(500, 200);
            itemw->show();
            itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
            itemw->setWindowTitle("错误");
        }
        else
        {
            found = cv::solvePnP(point3s, point2s, mtx, dist, rvecs, tvecs);
            if (found == 0)
            {
                QWidget *itemw = new QWidget;
                QLabel *wl = new QLabel(itemw);
                wl->setText("没有找到标定结果");
                wl->resize(500, 200);
                itemw->show();
                itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
                itemw->setWindowTitle("错误");
                return;
            }
            else
            {
                std::cout << "solvePnP" << std::endl;
                ui->result_show->clear();
                std::stringstream textStr;
                textStr << "rvecs:" << std::endl;
                textStr << rvecs << std::endl;
                textStr << "tvecs:" << std::endl;
                textStr << tvecs << std::endl;
                ui->result_show->setText(QString(textStr.str().c_str()));
                found = 0;
            }
        }
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("没有打开内参标定结果");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
    }
}
void external_camera::saveprojectclick()
{
    cv::FileStorage ymlFile(this->savereultPath.toStdString(), cv::FileStorage::WRITE);
    ymlFile << "project" << 2;
    ymlFile << "imgpath" << imagePaths;
    ymlFile << "open_xml_flag" << open_xml_flag;
    if (open_xml_flag)
    {
        ymlFile << "mtx" << mtx;
        ymlFile << "dist" << dist;
    }
    ymlFile << "point2s" << point2s;
    ymlFile << "point3s" << point3s;
    ymlFile << "rvecs" << rvecs;
    ymlFile << "tvecs" << tvecs;
}
void external_camera::clear()
{
    Imgpath.clear();
    imagePaths.clear();
    point3s.clear();
    point2s.clear();
    mtx = cv::Mat();
    dist = cv::Mat();
    rvecs = cv::Mat();
    tvecs = cv::Mat();
};
void external_camera::openprojectclick()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), ".", tr("project files (*.project)"));
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadFile(filename.toStdString(), cv::FileStorage::READ);
        if (!ymlreadFile.isOpened())
            return;
        if (int(ymlreadFile["project"]) != 2)
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("请打开相机项目文件");
            wl->resize(500, 200);
            itemw->show();
            itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
            itemw->setWindowTitle("错误");
        }
        else
        {
            clear();
            ui->ListWidget_imgs->clear();
            imagePaths.clear();
            ui->result_show->clear();
            ui->twcoordinate->clear();
            ui->twcoordinate->setRowCount(0);
            ui->twcoordinate->setColumnCount(5);
            QStringList coordinatelistname;
            coordinatelistname << "二维坐标x";
            coordinatelistname << "二维坐标y";
            coordinatelistname << "三维坐标x";
            coordinatelistname << "三维坐标y";
            coordinatelistname << "三维坐标z";
            ui->twcoordinate->setHorizontalHeaderLabels(coordinatelistname);
            ui->twcoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->twcoordinate->verticalHeader()->hide();
            ui->twcoordinate->setAlternatingRowColors(true);
            ui->textEdit->clear();
            ymlreadFile["imgpath"] >> imagePaths;
            ymlreadFile["open_xml_flag"] >> open_xml_flag;
            if (open_xml_flag)
            {
                ymlreadFile["mtx"] >> mtx;
                ymlreadFile["dist"] >> dist;
                ui->textEdit->clear();
                std::stringstream textStr;
                textStr << "mtx:" << mtx << std::endl;
                textStr << "dist:" << dist << std::endl;
                ui->textEdit->setText(QString(textStr.str().c_str()));
            }
            ymlreadFile["point2s"] >> point2s;
            ymlreadFile["point3s"] >> point3s;
            ymlreadFile["rvecs"] >> rvecs;
            ymlreadFile["tvecs"] >> tvecs;
            for (int i = 0; i < point2s.size(); i++)
            {
                appendtw(point2s[i].x, point2s[i].y, point3s[i].x, point3s[i].y, point3s[i].z);
            }
            for (int i = 0; i < imagePaths.size(); i++)
            {
                QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(imagePaths[i]));
                ui->ListWidget_imgs->addItem(item);
            }
            if (!rvecs.empty())
            {
                ui->result_show->clear();
                std::stringstream textStr;
                textStr << "rvecs:" << std::endl;
                textStr << rvecs << std::endl;
                textStr << "tvecs:" << std::endl;
                textStr << tvecs << std::endl;
                ui->result_show->setText(QString(textStr.str().c_str()));
            }
        }
    }
}

void external_camera::openresultneican_click()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), ".", tr("project files (*.xml)"));
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadFile;
        if (ymlreadFile.open(filename.toStdString(), cv::FileStorage::READ))
        {
            if (int(ymlreadFile["xmlflag"]) != 1)
            {
                QWidget *itemw = new QWidget;
                QLabel *wl = new QLabel(itemw);
                wl->setText("请打开相机内参标定结果文件");
                wl->resize(500, 200);
                itemw->show();
                itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
                itemw->setWindowTitle("错误");
            }
            else
            {
                ymlreadFile["CameraMat"] >> mtx;
                ymlreadFile["DistCoeff"] >> dist;
                open_xml_flag = 1;
                ui->textEdit->clear();
                std::stringstream textStr;
                textStr << "mtx:" << mtx << std::endl;
                textStr << "dist:" << dist << std::endl;
                ui->textEdit->setText(QString(textStr.str().c_str()));
            }
        }
        else
        {
            return;
        }
    }
}

void external_camera::addcoordinateclick()
{
    int cooa = ui->lineEdit->text().toInt();
    int coob = ui->lineEdit_2->text().toInt();
    int cooc = ui->lineEdit_13->text().toInt();
    int cood = ui->lineEdit_14->text().toInt();
    int cooe = 0;
    appendtw(cooa, coob, cooc, cood, cooe);
}

void external_camera::ActImageClick(int x, int y)
{
    ui->lineEdit->setText(QString::number(x));
    ui->lineEdit_2->setText(QString::number(y));
}

void external_camera::imgaddclick()
{
    ui->ListWidget_imgs->clear();
    Imgpath.clear();
    this->imagePaths.clear();
    Imgpath.append(QFileDialog::getOpenFileNames(this, "Select one or more files to open", QDir::currentPath(), "Images (*.jpg *.png *.bmp)"));
    for (int i = 0; i < Imgpath.size(); i++)
        this->imagePaths.push_back(Imgpath[i].toStdString());
    Imgpath.clear();
    for (int i = 0; i < this->imagePaths.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(this->imagePaths[i]));
        ui->ListWidget_imgs->addItem(item);
    }
    ui->ListWidget_imgs->setCurrentRow(0);
}

void external_camera::deleteimgclick()
{
    QListWidgetItem *item = ui->ListWidget_imgs->currentItem();
    for (int i = 0; i < imagePaths.size(); i++)
    {
        if (imagePaths[i] == item->text().toStdString())
            imagePaths.erase(imagePaths.begin() + i);
    }
    // Imgpath.removeOne(item->text());
    ui->ListWidget_imgs->removeItemWidget(item);
    delete item;
}

void external_camera::external_camera_help_click()
{
    QWidget *itemw = new QWidget;
    QLabel *wl = new QLabel(itemw);
    wl->setText("新建项目-添加图片-添加坐标-打开内参-标定外参");
    wl->resize(1000, 200);
    itemw->show();
    itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
    itemw->setWindowTitle("帮助");
}

void external_camera::saveresult_xml_click()
{
    result_xml->show();
    result_xml->move(this->geometry().center().x()-result_xml->width()/2,this->geometry().center().y()-result_xml->height()/2);
    connect(result_xml, &savecamerresult::sendData, this, &external_camera::receiveresultdata);
}

void external_camera::showImg(int item)
{
    m_imageBox.Init(ui->verticalLayout_2);
    connect(&m_imageBox, &ImageBox::ImageClick, this, &external_camera::ActImageClick);
    if (item == -1)
    {
        return;
    }
    m_imageBox.SetImage(QString::fromStdString(imagePaths[item]));
    // ui->twcoordinate->clear();
    // ui->twcoordinate->setColumnCount(5);
    // QStringList coordinatelistname;
    // coordinatelistname << "二维坐标x";
    // coordinatelistname << "二维坐标y";
    // coordinatelistname << "三维坐标x";
    // coordinatelistname << "三维坐标y";
    // coordinatelistname << "三维坐标z";
    // ui->twcoordinate->setHorizontalHeaderLabels(coordinatelistname);
    // ui->twcoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // // 隐藏列表头
    // ui->twcoordinate->verticalHeader()->hide();
    // // 交替显示颜色
    // ui->twcoordinate->setAlternatingRowColors(true);
    // if (imagePaths[item] == "/home/chen/标定/相机标定/相机标定/外参/相机外参标定.jpg")
    // {
    //     appendtw(1053, 1035, 0, 3, 0);
    //     appendtw(1062, 756, 0, 6, 0);
    //     appendtw(1067, 638, 0, 9, 0);
    //     appendtw(1820, 1010, 3, 3, 0);
    //     appendtw(1554, 765, 3, 6, 0);
    //     appendtw(1427, 656, 3, 9, 0);
    //     appendtw(284, 930, -3, 3, 0);
    //     appendtw(565, 726, -3, 6, 0);
    //     appendtw(707, 627, -3, 9, 0);
    //     appendtw(903, 489, -3, 15, 0);
    //     appendtw(841, 531, -3, 15, 0);
    //     appendtw(1301, 550, 3, 15, 0);
    // }
}

void external_camera::newprojectclick()
{
    newp->show();
    newp->move(this->geometry().center().x()-newp->width()/2,this->geometry().center().y()-newp->height()/2);
    connect(newp, &newcamerproject::sendData, this, &external_camera::receiveprojectdata);
}

void external_camera::receiveprojectdata(QString a)
{
    savereultPath = a;
    // if(savereultPath==" ")
    //{
    //     QWidget *itemw=new QWidget;
    //              QLabel* wl=new QLabel(itemw);
    //              wl->setText("打开的文件错误");
    //              wl->resize(250,100);
    //              itemw->show();
    //              itemw->setWindowTitle("错误");
    // }
}

void external_camera::receiveresultdata(QString a)
{
    savereultPath_biaoding = a;
    cv::FileStorage ymlFile(savereultPath_biaoding.toStdString(), cv::FileStorage::WRITE);
    ymlFile << "xmlflag" << 2;
    ymlFile << "rvecs" << rvecs;
    ymlFile << "tvecs" << tvecs;
}

// void external_camera::onRadiobuttonClicked()
//{
//     int checkid= mbtngroup->checkedId();
//     switch (checkid) {
//     case 0:
//         ui->imgshow->clear();
//         imgshow_flag=0;
//         break;
//     case 1:
//         ui->imgshow->clear();
//         imgshow_flag=1;
//         break;
//     }
// }
