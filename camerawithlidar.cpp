#include "camerawithlidar.h"
#include "ui_camerawithlidar.h"
using namespace std;
void camerawithlidar::getTheoreticalUVl(float* theoryUV, const vector<float> &intrinsic, const vector<float> &extrinsic, double x, double y, double z) {
    // set the intrinsic and extrinsic matrix
    double matrix1[3][3] = {{intrinsic[0], intrinsic[1], intrinsic[2]}, {intrinsic[3], intrinsic[4], intrinsic[5]}, {intrinsic[6], intrinsic[7], intrinsic[8]}};
    double matrix2[3][4] = {{extrinsic[0], extrinsic[1], extrinsic[2], extrinsic[3]}, {extrinsic[4], extrinsic[5], extrinsic[6], extrinsic[7]}, {extrinsic[8], extrinsic[9], extrinsic[10], extrinsic[11]}};
    double matrix3[4][1] = {x, y, z, 1};

    // transform into the opencv matrix
    cv::Mat matrixIn(3, 3, CV_64F, matrix1);
    cv::Mat matrixOut(3, 4, CV_64F, matrix2);
    cv::Mat coordinate(4, 1, CV_64F, matrix3);

    // calculate the result of u and v
    cv::Mat result = matrixIn*matrixOut*coordinate;
    float u = result.at<double>(0, 0);
    float v = result.at<double>(1, 0);
    float depth = result.at<double>(2, 0);

    theoryUV[0] = u / depth;
    theoryUV[1] = v / depth;
}
camerawithlidar::camerawithlidar(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::camerawithlidar)
{
    ui->setupUi(this);
    setWindowTitle("相机-激光雷达标定");
   //setFixedSize(this->width(), this->height());
    connect(ui->pushButton, &QPushButton::clicked, this, &camerawithlidar::newprojectclick);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &camerawithlidar::saveprojectclick);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &camerawithlidar::openprojectclick);
    connect(ui->pushButton_16, &QPushButton::clicked, this, &camerawithlidar::saveresultxmlclick);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &camerawithlidar::addimgclick);
    connect(ui->ListWidget_imgs, &QListWidget::currentRowChanged, this, &camerawithlidar::onitemclicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &camerawithlidar::addpcdpathclick);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &camerawithlidar::addimgpathclick);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &camerawithlidar::addcoordinateclick);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &camerawithlidar::openxmlclick);
    connect(ui->pushButton_15, &QPushButton::clicked, this, &camerawithlidar::calculateclick);
    connect(ui->pushButton_14, &QPushButton::clicked, this, &camerawithlidar::deletecoordinateclick);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &camerawithlidar::camerawithlidar_help_click);
   // connect(ui->pushButton_18,&QPushButton::clicked,this,&camerawithlidar::result_verify_clicked);
    vtkWidget = new QVTKWidget(this, QFlag(0));
    cloud.reset(new pcl::PointCloud<pcl::PointXYZI>);
    clicked_points_3d.reset(new pcl::PointCloud<pcl::PointXYZ>);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->setBackgroundColor(0, 0, 0);
    //    cloud->points.resize(200);
    //    for (size_t i = 0; i < cloud->points.size (); ++i)
    //    {
    //        cloud->points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    //        cloud->points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    //        cloud->points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
    //    }
    viewer->addPointCloud<pcl::PointXYZI>(cloud, "cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");
    viewer->resetCamera();
    ui->verticalLayout->addWidget(vtkWidget);
    ui->verticalLayout->update();
    vtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(vtkWidget->GetInteractor(), vtkWidget->GetRenderWindow());
    vtkWidget->update();
    viewer->registerPointPickingCallback(&camerawithlidar::point_pick_callback, *this);
    ui->twcoordinate->clear();
    ui->twcoordinate_3->clear();
    ui->twcoordinate->setColumnCount(2);
    ui->twcoordinate_3->setColumnCount(3);
    QStringList imglistname;
    imglistname << "二维坐标x";
    imglistname << "二维坐标y";
    QStringList pcdlistname;
    pcdlistname << "三维坐标x";
    pcdlistname << "三维坐标y";
    pcdlistname << "三维坐标z";
    ui->twcoordinate->setHorizontalHeaderLabels(imglistname);
    ui->twcoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twcoordinate_3->setHorizontalHeaderLabels(pcdlistname);
    ui->twcoordinate_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->twcoordinate->verticalHeader()->hide();
    //ui->twcoordinate_3->verticalHeader()->hide();
    ui->twcoordinate->setAlternatingRowColors(true);
    ui->twcoordinate_3->setAlternatingRowColors(true);
}

camerawithlidar::~camerawithlidar()
{
    delete ui;
}

void camerawithlidar::deletecoordinateclick()
{
    while (ui->twcoordinate->selectedItems().count() > 0)
    {
        int rowidx = ui->twcoordinate->selectedItems()[0]->row();
        ui->twcoordinate->removeRow(rowidx);
        ui->twcoordinate_3->removeRow(rowidx);
    }
    while (ui->twcoordinate_3->selectedItems().count() > 0)
    {
        int rowidx_3 = ui->twcoordinate_3->selectedItems()[0]->row();
        ui->twcoordinate->removeRow(rowidx_3);
        ui->twcoordinate_3->removeRow(rowidx_3);
    }
}
void camerawithlidar::newprojectclick()
{
    newp->show();
    newp->move(this->geometry().center().x()-newp->width()/2,this->geometry().center().y()-newp->height()/2);
    connect(newp, &newcamerproject::sendData, this, &camerawithlidar::receiveprojectdata);
}
void camerawithlidar::receiveprojectdata(QString a)
{
    saveprojectpath = a;
}
void camerawithlidar::saveprojectclick()
{
    cv::FileStorage ymlFile(saveprojectpath.toStdString(), cv::FileStorage::WRITE);
    ymlFile << "project" << 3;
    ymlFile << "dirname" << dirname.toStdString();
    ymlFile << "dirimgname" << dirimgname.toStdString();
    // ymlFile << "lidar_files" << lidar_files;
    // ymlFile << "dirimgname" << dirimgname;
    // ymlFile << "lidar_imgfiles" << lidar_imgfiles;
    point2s.clear();
    point3s.clear();
    int tempnum = ui->twcoordinate->rowCount();
    QTableWidgetItem *item = new QTableWidgetItem;
    for (int i = 0; i < tempnum; i++)
    {
        point2s.push_back(cv::Point2f(ui->twcoordinate->item(i, 0)->text().toFloat(), ui->twcoordinate->item(i, 1)->text().toFloat()));
        point3s.push_back(cv::Point3f(ui->twcoordinate_3->item(i, 0)->text().toFloat(), ui->twcoordinate_3->item(i, 1)->text().toFloat(), ui->twcoordinate_3->item(i, 2)->text().toFloat()));
    }
    ymlFile << "point2s" << point2s;
    ymlFile << "point3s" << point3s;
    ymlFile << "open_xml_flag" << open_xml_flag;
    if (open_xml_flag)
    {
        ymlFile << "mtx" << mtx;
        ymlFile << "dist" << dist;
    }
    ymlFile << "rvecs" << rvecs;
    ymlFile << "tvecs" << tvecs;
}
void camerawithlidar::clear()
{
    dirname.clear();
    dirimgname.clear();
    point2s.clear();
    point3s.clear();
    mtx = cv::Mat();
    dist = cv::Mat();
    rvecs = cv::Mat();
    tvecs = cv::Mat();
}
void camerawithlidar::openprojectclick()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), ".", tr("project files (*.project)"));
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadfile(filename.toStdString(), cv::FileStorage::READ);
        if (int(ymlreadfile["project"]) != 3)
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("请打开相机-激光雷达标定项目");
            wl->resize(500, 200);
            itemw->show();
            itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
            itemw->setWindowTitle("错误");
            return;
        }
        else
        {
            clear();
            ui->ListWidget_imgs->clear();
            ui->result_show->clear();
            ui->textEdit->clear();
            ui->twcoordinate->clear();
            ui->twcoordinate_3->clear();
            ui->twcoordinate->setRowCount(0);
            ui->twcoordinate_3->setRowCount(0);
            ui->twcoordinate->setColumnCount(2);
            ui->twcoordinate_3->setColumnCount(3);
            QStringList imglistname;
            imglistname << "二维坐标x";
            imglistname << "二维坐标y";
            QStringList pcdlistname;
            pcdlistname << "三维坐标x";
            pcdlistname << "三维坐标y";
            pcdlistname << "三维坐标z";
            ui->twcoordinate->setHorizontalHeaderLabels(imglistname);
            ui->twcoordinate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->twcoordinate_3->setHorizontalHeaderLabels(pcdlistname);
            ui->twcoordinate_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //        ui->twcoordinate->verticalHeader()->hide();
            //        ui->twcoordinate_3->verticalHeader()->hide();
            ui->twcoordinate->setAlternatingRowColors(true);
            ui->twcoordinate_3->setAlternatingRowColors(true);

            dirname = QString::fromStdString(ymlreadfile["dirname"]);
            dirimgname = QString::fromStdString(ymlreadfile["dirimgname"]);
            ui->label_14->clear();
            ui->label_14->setText("点云目录：" + dirname);
            ui->label_12->clear();
            ui->label_12->setText("图片目录：" + dirimgname);
            if (!dirimgname.isEmpty() && !dirname.isEmpty())
            {
                lidar_files = getFileNames(dirname);
                lidar_imgfiles = getimgFileNames(dirimgname);
                if (lidar_files.size() == lidar_imgfiles.size())
                {
                    for (int i = 0; i < lidar_files.size(); i++)
                    {
                        ui->ListWidget_imgs->addItem("二维：" + lidar_imgfiles[i] + " 三维:" + lidar_files[i]);
                    }
                }
                else
                {
                    QWidget *itemw = new QWidget;
                    QLabel *wl = new QLabel(itemw);
                    wl->setText("项目中目录不正确或图片数量不一样");
                    wl->resize(500, 200);
                    itemw->show();
                    itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
                    itemw->setWindowTitle("错误");
                    return;
                }
            }
            point2s.clear();
            point3s.clear();
            ymlreadfile["point2s"] >> point2s;
            ymlreadfile["point3s"] >> point3s;
            for (int i = 0; i < point2s.size(); i++)
            {
                appendtw(point2s[i].x, point2s[i].y, point3s[i].x, point3s[i].y, point3s[i].z);
            }
            ymlreadfile["open_xml_flag"] >> open_xml_flag;
            if (int(ymlreadfile["open_xml_flag"]) == 1)
            {
                ymlreadfile["mtx"] >> mtx;
                ymlreadfile["dist"] >> dist;
                std::stringstream textStr;
                textStr << "mtx:" << mtx << std::endl;
                textStr << "dist:" << dist << std::endl;
                ui->textEdit->setText(QString(textStr.str().c_str()));
            }
            ymlreadfile["rvecs"] >> rvecs;
            ymlreadfile["tvecs"] >> tvecs;
            if (!rvecs.empty())
            {
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
void camerawithlidar::addimgclick()
{
    ui->ListWidget_imgs->clear();
    lidar_files = getFileNames(dirname);
    lidar_imgfiles = getimgFileNames(dirimgname);
    if (lidar_files.size() == lidar_imgfiles.size())
    {
        for (int i = 0; i < lidar_files.size(); i++)
        {
            ui->ListWidget_imgs->addItem("二维：" + lidar_imgfiles[i] + " 三维:" + lidar_files[i]);
        }
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("图片目录中的图片文件数和点云目录中的点云文件数不一致");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
        return;
    }
}

void camerawithlidar::result_verify_clicked()
{
cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
cameraMatrix.at<double>(0, 0) = mtx.at<double>(0, 0);
cameraMatrix.at<double>(0, 2) = mtx.at<double>(0, 2);
cameraMatrix.at<double>(1, 1) = mtx.at<double>(1, 1);
cameraMatrix.at<double>(1, 2) = mtx.at<double>(1, 2);
distCoeffs.at<double>(0,0)=dist.at<double>(0,0);
distCoeffs.at<double>(0,1)=dist.at<double>(0,1);
distCoeffs.at<double>(0,2)=dist.at<double>(0,2);
distCoeffs.at<double>(0,3)=dist.at<double>(0,3);
distCoeffs.at<double>(0,4)=dist.at<double>(0,4);
std::cout<<rvecs<<std::endl;
std::cout<<tvecs<<std::endl;
cv::Mat R;
cv::Rodrigues(rvecs, R);
Eigen::Matrix3d Rot;
Eigen::Vector3d trans;
cv::cv2eigen(R,Rot);
cv::cv2eigen(tvecs,trans);
std::cout<<"R = "<<R<<std::endl;
 std::cout<<"t = "<<tvecs<<std::endl;
 std::cout<<"R = "<<Rot<<std::endl;
 std::cout<<"t = "<<trans<<std::endl;
 Eigen::Quaterniond q(Rot);
 double ext[7]={q.x(),q.y(),q.z(),q.w(),0,0,0};
 Eigen::Map<Eigen::Quaterniond>  m_q = Eigen::Map<Eigen::Quaterniond>(ext);
 Eigen::Map<Eigen::Vector3d>     m_t = Eigen::Map<Eigen::Vector3d>(ext + 4);
 Eigen::Matrix3d rot = m_q.toRotationMatrix();
 vector<float> intrinsic{(float)mtx.at<double>(0, 0),(float)mtx.at<double>(0, 1),(float)mtx.at<double>(0, 2),(float)mtx.at<double>(1, 0),(float)mtx.at<double>(1, 1),(float)mtx.at<double>(1, 2),(float)mtx.at<double>(2, 0),(float)mtx.at<double>(2, 1),(float)mtx.at<double>(2, 2)};
 vector<float> extrinsic{(float)rot(0,0),(float)rot(0,1),(float)rot(0,2),(float)trans[0],
                                (float)rot(1,0),(float)rot(1,1),(float)rot(1,2),(float)trans[1],
                                (float)rot(2,0),(float)rot(2,1),(float)rot(2,2),(float)trans[2]};
for(int i=0;i<intrinsic.size();i++)
 std::cout<<intrinsic[i]<<std::endl;
float x,y,z;
float theoryUV[2]={0,0};
int myCount=0;
QDir dir(dirname);
QDir dirimg(dirimgname);
QString absFilePath = dir.absoluteFilePath(lidar_files[0]);
cloud.reset(new pcl::PointCloud<pcl::PointXYZI>);
if (pcl::io::loadPCDFile<pcl::PointXYZI>(absFilePath.toStdString(), *cloud) == -1) //* load the file
{
    PCL_ERROR("Couldn't read file test_pcd.pcd \n");
}
////T.create(4, 4, CV_64FC1);
////R.copyTo(T(cv::Rect(0, 0, 3, 3)));
////T.at<double>(0, 3) = tvecs.at<double>(0, 0);
////    T.at<double>(1, 3) = tvecs.at<double>(1, 0);
////    T.at<double>(2, 3) = tvecs.at<double>(2, 0);
////    T.at<double>(3, 0) = T.at<double>(3, 1) = T.at<double>(3, 2) = 0;
////    T.at<double>(3, 3) = 1;
std::vector<cv::Point2f> pointseq;
std::cout<<dirimg.absoluteFilePath(lidar_imgfiles[0]).toStdString()<<std::endl;
//QPixmap imgL = QPixmap(dirimg.absoluteFilePath(lidar_imgfiles[0]));
cv::Mat gray=cv::imread(dirimg.absoluteFilePath(lidar_imgfiles[0]).toStdString());
for(int i=0;i<cloud->size();i++)
{
    x=cloud->points[i].x;
    y=cloud->points[i].y;
    z=cloud->points[i].z;
     //std::cout<<x<<y<<std::endl;
    getTheoreticalUVl(theoryUV,intrinsic,extrinsic,x,y,z);
    int u = floor(theoryUV[0] + 0.5); // 四舍五入像素值
    int v = floor(theoryUV[1] + 0.5);
    std::cout<<u<<v<<std::endl;
    if(abs(u)<=gray.rows&&abs(v)<=gray.cols)
        {
        cv::Point p(u,v);
    pointseq.push_back(cv::Point2f(u,v));
    cv::circle(gray, p, 1,cv::Scalar(0, 0, 0),-1); // window上画点
    }

}

QWidget *itemw = new QWidget;
QLabel *wl = new QLabel(itemw);
wl->clear();
wl->resize(1000, 1000);
//imgL = imgL.scaled(wl->size(), Qt::KeepAspectRatio);
cv::cvtColor(gray, gray, cv::COLOR_BGR2RGB);
QImage img = QImage(gray.data, gray.cols, gray.rows, gray.cols * gray.channels(), QImage::Format_RGB888);
img = img.scaled(wl->size(), Qt::KeepAspectRatio);
wl->setPixmap(QPixmap::fromImage(img));
itemw->show();
itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
itemw->setWindowTitle("错误");

}

QStringList camerawithlidar::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.pcd";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}

QStringList camerawithlidar::getimgFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg";
    nameFilters << "*.png";
    nameFilters << "*.bmp";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}

void camerawithlidar::point_pick_callback(const pcl::visualization::PointPickingEvent &event, void *args)
{
    pcl::PointXYZ cur_point;
    event.getPoint(cur_point.x, cur_point.y, cur_point.z);
    clicked_points_3d->points.push_back(cur_point);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red(clicked_points_3d, 255, 0, 0);
    viewer->removePointCloud("clicked_points");
    viewer->addPointCloud(clicked_points_3d, red, "clicked_points");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "clicked_points");
    ui->label_2->setText(QString::number(cur_point.x));
    ui->label_3->setText(QString::number(cur_point.y));
    ui->label_5->setText(QString::number(cur_point.z));
    ui->lineEdit_5->setText(QString::number(float(cur_point.x)));
    ui->lineEdit_17->setText(QString::number(float(cur_point.y)));
    ui->lineEdit_18->setText(QString::number(float(cur_point.z)));
    vtkWidget->update();
}

void camerawithlidar::addpcdpathclick()
{
    dirname = QFileDialog::getExistingDirectory(this, tr("选择pcd文件目录"));
    ui->label_14->clear();
    ui->label_14->setText("点云目录：" + dirname);
}

void camerawithlidar::addimgpathclick()
{
    dirimgname = QFileDialog::getExistingDirectory(this, tr("选择图片目录"));
    ui->label_12->clear();
    ui->label_12->setText("图片目录：" + dirimgname);
}

void camerawithlidar::ActImageClick(int x, int y)
{
    ui->label_8->setText(QString::number(x));
    ui->label_10->setText(QString::number(y));
    ui->lineEdit->setText(QString::number(x));
    ui->lineEdit_2->setText(QString::number(y));
}

void camerawithlidar::addcoordinateclick()
{
    float cooa = ui->lineEdit->text().toFloat();
    float coob = ui->lineEdit_2->text().toFloat();
    float cooc = ui->lineEdit_5->text().toFloat();
    float cood = ui->lineEdit_17->text().toFloat();
    float cooe = ui->lineEdit_18->text().toFloat();
    appendtw(cooa, coob, cooc, cood, cooe);
}

void camerawithlidar::appendtw(float a, float b, float c, float d, float e)
{
    int count2s = ui->twcoordinate->rowCount();
    int count3s = ui->twcoordinate_3->rowCount();
    ui->twcoordinate->setRowCount(count2s + 1);
    ui->twcoordinate_3->setRowCount(count3s + 1);
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
    ui->twcoordinate->setItem(count2s, 0, twitema);
    ui->twcoordinate->setItem(count2s, 1, twitemb);
    ui->twcoordinate_3->setItem(count3s, 0, twitemc);
    ui->twcoordinate_3->setItem(count3s, 1, twitemd);
    ui->twcoordinate_3->setItem(count3s, 2, twiteme);
}

void camerawithlidar::calculateclick()
{
    if (open_xml_flag)
    {
        point2s.clear();
        point3s.clear();
        bool found;
        int tempnum = ui->twcoordinate->rowCount();
        if (ui->twcoordinate->rowCount() != ui->twcoordinate_3->rowCount())
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("坐标输入不正确");
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
                point2s.push_back(cv::Point2f(ui->twcoordinate->item(i, 0)->text().toFloat(), ui->twcoordinate->item(i, 1)->text().toFloat()));
                point3s.push_back(cv::Point3f(ui->twcoordinate_3->item(i, 0)->text().toFloat(), ui->twcoordinate_3->item(i, 1)->text().toFloat(), ui->twcoordinate_3->item(i, 2)->text().toFloat()));
            }
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
                    wl->setText("请输入正确坐标");
                    wl->resize(500, 200);
                    itemw->show();
                    itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
                    itemw->setWindowTitle("错误");
                    return;
                }
                else
                {
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

void camerawithlidar::openxmlclick()
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

void camerawithlidar::onitemclicked(int item)
{
    m_imageBox.Init(ui->verticalLayout_2);
    connect(&m_imageBox, &ImageBox::ImageClick, this, &camerawithlidar::ActImageClick);
    if (item == -1)
    {
        return;
    }
    QDir dirimg(dirimgname);
    QString absimgFilePath = dirimg.absoluteFilePath(lidar_imgfiles[item]);
    m_imageBox.SetImage(absimgFilePath);
    QDir dir(dirname);
    QString absFilePath = dir.absoluteFilePath(lidar_files[item]);
    cloud.reset(new pcl::PointCloud<pcl::PointXYZI>);
    if (pcl::io::loadPCDFile<pcl::PointXYZI>(absFilePath.toStdString(), *cloud) == -1) //* load the file
    {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
    }
    else
    {
        viewer->resetCamera();
        viewer->removeAllPointClouds();
        // pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> fildColor(cloud, "intensity");//按照intensity字段进行渲染
        clicked_points_3d.reset(new pcl::PointCloud<pcl::PointXYZ>{});
        // --- 显示点云数据 ----
        // viewer->addPointCloud<pcl::PointXYZI>(cloud,fildColor,"sample cloud");
        viewer->addPointCloud<pcl::PointXYZI>(cloud, "sample cloud");
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3.0, "sample cloud");
        viewer->resetCamera();
        // ui->qvtkWidget->update ();
        // std::function<void(const pcl::visualization::PointPickingEvent&)> fun =
        // std::bind(&camerawithlidar::point_pick_callback, this, std::placeholders::_1);
        // viewer->registerPointPickingCallback(fun);
        viewer->getRenderWindow();
        vtkWidget->update();
        //  viewer->registerPointPickingCallback(&camerawithlidar::point_pick_callback,*this);
    }
}
void camerawithlidar::saveresultxmlclick()
{
    if (rvecs.empty() || tvecs.empty())
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("没有标定结果");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("保存标定结果错误");
        return;
    }
    result_xml->show();
    result_xml->move(this->geometry().center().x()-result_xml->width()/2,this->geometry().center().y()-result_xml->height()/2);
    connect(result_xml, &savecamerresult::sendData, this, &camerawithlidar::receiveresultdata);
}
void camerawithlidar::receiveresultdata(QString a)
{
    QString saveresultpath = a;
    cv::FileStorage ymlresultfile(saveresultpath.toStdString(), cv::FileStorage::WRITE);
    ymlresultfile << "xmlflag" << 3;
    ymlresultfile << "rvecs" << rvecs;
    ymlresultfile << "tvecs" << tvecs;
}
void camerawithlidar::camerawithlidar_help_click()
{
    QWidget *itemw = new QWidget;
    QLabel *wl = new QLabel(itemw);
    wl->setText("设置图片目录-设置点云目录-更新目录-在图片区域右键点击鼠标可选择像素点-点云区域shift加左键可选点-键盘O切换点云放大模式");
    wl->resize(1000, 200);
    itemw->show();
    itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
    itemw->setWindowTitle("帮助");
}
