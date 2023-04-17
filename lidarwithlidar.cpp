#include "lidarwithlidar.h"
#include "ui_lidarwithlidar.h"
#include <QtCore>

lidarwithlidar::lidarwithlidar(QWidget *parent) : QWidget(parent),
    ui(new Ui::lidarwithlidar)
{
    ui->setupUi(this);
    setWindowTitle("激光雷达-激光雷达标定工具");
    lidarthread=new mythread(this);
    connect(this,&lidarwithlidar::send_cloud,lidarthread,&mythread::lidarthread_slot);
    connect(this,&lidarwithlidar::stopflag,lidarthread,&mythread::stop_thread);
    timer=new QTimer(this);
    timer_transform_init=new QTimer(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&lidarwithlidar::new_project_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&lidarwithlidar::save_project_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&lidarwithlidar::open_project_clicked);
    connect(timer_transform_init,SIGNAL(timeout()),this,SLOT(view_timer_update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Time_Update()));
    connect(ui->pushButton_4, &QPushButton::clicked, this, &lidarwithlidar::add_child_path_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &lidarwithlidar::add_parent_path_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &lidarwithlidar::update_path_clicked);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&lidarwithlidar::calculateclicked);
    connect(ui->ListWidget_imgs, &QListWidget::currentRowChanged, this, &lidarwithlidar::onitemclicked);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&lidarwithlidar::stop_calculate_clicked);
    connect(ui->pushButton_10,&QPushButton::clicked,this,&lidarwithlidar::save_result_clicked);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&lidarwithlidar::help_clicked);
    vtkwidget = new QVTKWidget(this, QFlag(0));
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    parent_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>{});
    child_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>{});
    child_filtered_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>{});
    output_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>{});
    output_double_cloud.reset(new pcl::PointCloud<pcl::PointXYZI>{});
    viewer->setBackgroundColor(0, 0, 0);
    ui->verticalLayout->addWidget(vtkwidget);
    ui->verticalLayout->update();
    vtkwidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(vtkwidget->GetInteractor(), vtkwidget->GetRenderWindow());
    vtkwidget->update();
    timer_transform_init->start(10);
    connect(lidarthread, &mythread::threadSignal1,this, &lidarwithlidar::mySlot1);
    ui->doubleSpinBox->setRange(-100,100);
    ui->doubleSpinBox_2->setRange(-100,100);
    ui->doubleSpinBox_3->setRange(-100,100);
    ui->doubleSpinBox_4->setRange(-6.3,6.3);
    ui->doubleSpinBox_5->setRange(-6.3,6.3);
    ui->doubleSpinBox_6->setRange(-6.3,6.3);
    ui->doubleSpinBox->setSingleStep(0.5);
    ui->doubleSpinBox_2->setSingleStep(0.5);
    ui->doubleSpinBox_3->setSingleStep(0.5);
    ui->doubleSpinBox_4->setSingleStep(0.05);
    ui->doubleSpinBox_5->setSingleStep(0.05);
    ui->doubleSpinBox_6->setSingleStep(0.05);
    ui->doubleSpinBox->setDecimals(3);
    ui->doubleSpinBox_2->setDecimals(3);
    ui->doubleSpinBox_3->setDecimals(3);
    ui->doubleSpinBox_4->setDecimals(3);
    ui->doubleSpinBox_5->setDecimals(3);
    ui->doubleSpinBox_6->setDecimals(3);
    ui->doubleSpinBox_4->setWrapping(true);
    ui->doubleSpinBox_5->setWrapping(true);
    ui->doubleSpinBox_6->setWrapping(true);
}

lidarwithlidar::~lidarwithlidar()
{
    delete ui;
}

void lidarwithlidar::new_project_clicked()
{
    newprojectwidget->show();
    newprojectwidget->move(this->geometry().center().x()-newprojectwidget->width()/2,this->geometry().center().y()-newprojectwidget->height()/2);
    connect(newprojectwidget, &newcamerproject::sendData, this, &lidarwithlidar::receiveprojectdata);
}

void lidarwithlidar::save_project_clicked()
{
    cv::FileStorage yml_project_file(saveprojectpath.toStdString(), cv::FileStorage::WRITE);
    yml_project_file << "project" << 4;
    yml_project_file << "child_pcd_path"<<child_pcd_path.toStdString();
    yml_project_file << "parent_pcd_path" << parent_pcd_path.toStdString();
    yml_project_file<< "x" << x;
    yml_project_file<< "y" << y;
    yml_project_file<< "z" << z;
    yml_project_file << "qx" << qx;
    yml_project_file << "qy" << qy;
    yml_project_file << "qz" << qz;
    yml_project_file<<"iter"<<iter;
}

void lidarwithlidar::open_project_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), ".", tr("project files (*.project)"));
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadfile(filename.toStdString(), cv::FileStorage::READ);
        if (int(ymlreadfile["project"]) != 4)
        {
            QWidget *itemw = new QWidget;
            QLabel *wl = new QLabel(itemw);
            wl->setText("请打开激光雷达-激光雷达标定项目");
            wl->resize(500, 200);
            itemw->show();
            itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
            itemw->setWindowTitle("错误");
            return;
        }
        else
        {
            child_pcd_path.clear();
            parent_pcd_path.clear();
//            ui->lineEdit->clear();
//            ui->lineEdit_2->clear();
//            ui->lineEdit_3->clear();
//            ui->lineEdit_4->clear();
//            ui->lineEdit_5->clear();
//            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->doubleSpinBox->clear();
            ui->doubleSpinBox_2->clear();
            ui->doubleSpinBox_3->clear();
            ui->doubleSpinBox_4->clear();
            ui->doubleSpinBox_5->clear();
            ui->doubleSpinBox_6->clear();
            ui->ListWidget_imgs->clear();
            ui->result_show->clear();
            viewer->removeAllPointClouds();
            vtkwidget->update();
            child_pcd_path = QString::fromStdString(ymlreadfile["child_pcd_path"]);
            parent_pcd_path = QString::fromStdString(ymlreadfile["parent_pcd_path"]);
            ui->label_12->clear();
            ui->label_14->clear();
            ui->label_12->setText("子点云目录：" + child_pcd_path);
            ui->label_14->setText("父点云目录：" + parent_pcd_path);
            update_path_clicked();
            ymlreadfile["x"]>>x;
            ymlreadfile["y"]>>y;
            ymlreadfile["z"]>>z;
            ymlreadfile["qx"]>>qx;
            ymlreadfile["qy"]>>qy;
            ymlreadfile["qz"]>>qz;
            ymlreadfile["iter"]>>iter;
//            ui->lineEdit->setText(QString::number(x));
//            ui->lineEdit_2->setText(QString::number(y));
//            ui->lineEdit_3->setText(QString::number(z));
//            ui->lineEdit_4->setText(QString::number(qx));
//            ui->lineEdit_5->setText(QString::number(qy));
//            ui->lineEdit_6->setText(QString::number(qz));
          ui->lineEdit_7->setText(QString::number(iter));
            ui->doubleSpinBox->setValue(x);
            ui->doubleSpinBox_2->setValue(y);
            ui->doubleSpinBox_3->setValue(z);
            ui->doubleSpinBox_4->setValue(qx);
            ui->doubleSpinBox_5->setValue(qy);
            ui->doubleSpinBox_6->setValue(qz);
        }
    }
}
void lidarwithlidar::update_path_clicked()
{
    ui->ListWidget_imgs->clear();
    ui->result_show->clear();
    parent_cloud_files = getFileNames(parent_pcd_path);
    child_cloud_files = getFileNames(child_pcd_path);
    if (parent_cloud_files.size() == child_cloud_files.size())
    {
        for (int i = 0; i < parent_cloud_files.size(); i++)
        {
            ui->ListWidget_imgs->addItem("父点云：" + parent_cloud_files[i] + " 子点云:" + child_cloud_files[i]);
        }
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("子点云目录和父点云目录中点云文件数不一致");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
        return;
    }
}

void lidarwithlidar::result_clear()
{
    translation_x=0;
    translation_y=0;
    translation_z=0;
    rotation_x=0;
    rotation_y=0;
    rotation_z=0;
}

void lidarwithlidar::help_clicked()
{
    QWidget *itemw = new QWidget;
    QLabel *wl = new QLabel(itemw);
    wl->setText("新建项目-分别选择文件数相同的子点云和父点云文件夹-更新目录-设置初始变换值和迭代次数-执行");
    wl->resize(1000, 200);
    itemw->show();
    itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
    itemw->setWindowTitle("帮助");
}
QStringList lidarwithlidar::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.pcd";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}

void lidarwithlidar::calculateclicked()
{
    if ((*parent_cloud).empty()==1||(*child_cloud).empty()==1)
    {
        PCL_ERROR("ERROR");
    }
    else
    {
        if(lidarthread->isRunning())
            return;
        else
        {
            ui->result_show->clear();
            DownsampleCloud(child_cloud, child_filtered_cloud, 0.1);
            emit send_cloud(child_filtered_cloud,parent_cloud,init_guess_,iter);
            lidarthread->start();
        }
    }
}

void lidarwithlidar::receiveprojectdata(QString a)
{
    saveprojectpath=a;
}

void lidarwithlidar::receiveresultdata(QString a)
{
    QString saveresultpath = a;
    cv::FileStorage ymlresultfile(saveresultpath.toStdString(), cv::FileStorage::WRITE);

    ymlresultfile << "xmlflag" << 4;
    ymlresultfile << "finaliter"<<numiteration;
    ymlresultfile << "score" << scorefitness;
    ymlresultfile<< "translation_x" << translation_x;
    ymlresultfile<< "translation_y" << translation_y;
    ymlresultfile<< "translation_z" << translation_z;
    ymlresultfile << "rotation_x" << rotation_x;
    ymlresultfile << "rotation_y" << rotation_y;
    ymlresultfile << "rotation_z" << rotation_z;
}

void lidarwithlidar::Time_Update(void)
{
}

void lidarwithlidar::view_timer_update()
{
    if(iter==ui->lineEdit_7->text().toInt()&&x==ui->doubleSpinBox->value()&&y==ui->doubleSpinBox_2->value()&&z==ui->doubleSpinBox_3->value()&&qx==ui->doubleSpinBox_4->value()&&qy==ui->doubleSpinBox_5->value()&&qz==ui->doubleSpinBox_6->value())
        return;
    else
    {
//        x=ui->lineEdit->text().toFloat();
//        y=ui->lineEdit_2->text().toFloat();
//        z=ui->lineEdit_3->text().toFloat();
//        qx=ui->lineEdit_4->text().toFloat();
//        qy=ui->lineEdit_5->text().toFloat();
//        qz=ui->lineEdit_6->text().toFloat();
        x=ui->doubleSpinBox->value();
        y=ui->doubleSpinBox_2->value();
        z=ui->doubleSpinBox_3->value();
        qx=ui->doubleSpinBox_4->value();
        qy=ui->doubleSpinBox_5->value();
        qz=ui->doubleSpinBox_6->value();
        iter=ui->lineEdit_7->text().toInt();
        Eigen::Translation3f init_translation(x, y, z);
        Eigen::AngleAxisf init_rotation_x(qx, Eigen::Vector3f::UnitX());
        Eigen::AngleAxisf init_rotation_y(qy, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf init_rotation_z(qz, Eigen::Vector3f::UnitZ());
        init_guess_ = (init_translation * init_rotation_z*init_rotation_y*init_rotation_x).matrix();
        pcl::transformPointCloud(*child_cloud,*output_double_cloud,init_guess_);
        viewer->resetCamera();
        viewer->removeAllPointClouds();
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZI> red(child_cloud, 255, 0, 0);
        viewer->addPointCloud<pcl::PointXYZI>(parent_cloud, red, "parent_cloud");
        // viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "parent_cloud");
        viewer->addPointCloud<pcl::PointXYZI>(output_double_cloud, "output_double_cloud");
        //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "output_double_cloud");
        viewer->resetCamera();
        vtkwidget->update();
    }
}

void lidarwithlidar::mySlot1(int a,float b,float c,float d,float e,float f,float g,float h,float i)
{
    ui->result_show->append(QString::number(a));
    std::stringstream textStr;
    textStr << "final iter:"<<a << std::endl;
    textStr << " score: " << b << " prob:" << c << std::endl;
    textStr << "translation(x,y,z):" << std::endl;
    textStr << d <<" "<<e<<" "<<f<< std::endl;
    textStr << "rotation(qx,qy,qz):" << std::endl;
    textStr << g <<" "<<h<<" "<<i<< std::endl;//弧度
    ui->result_show->append(QString(textStr.str().c_str()));
    numiteration=a;
    scorefitness=b;
    translation_x=d;
    translation_y=e;
    translation_z=f;
    rotation_x=g;
    rotation_y=h;
    rotation_z=i;
    Eigen::Translation3f init_translation(d, e, f);
    Eigen::AngleAxisf init_rotation_x(g, Eigen::Vector3f::UnitX());
    Eigen::AngleAxisf init_rotation_y(h, Eigen::Vector3f::UnitY());
    Eigen::AngleAxisf init_rotation_z(i, Eigen::Vector3f::UnitZ());
    guess_final = (init_translation * init_rotation_z*init_rotation_y*init_rotation_x).matrix();
    pcl::transformPointCloud(*child_cloud,*output_double_cloud,guess_final);
    viewer->resetCamera();
    viewer->removeAllPointClouds();
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZI> red(child_cloud, 255, 0, 0);
    viewer->addPointCloud<pcl::PointXYZI>(parent_cloud, red, "parent_cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "parent_cloud");
    viewer->addPointCloud<pcl::PointXYZI>(output_double_cloud, "output_double_cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "output_double_cloud");
    viewer->resetCamera();
    vtkwidget->update();
}


void lidarwithlidar::add_child_path_clicked()
{
    child_pcd_path = QFileDialog::getExistingDirectory(this, tr("选择子点云目录"));
    ui->label_12->clear();
    ui->label_12->setText("子点云目录：" + child_pcd_path);
}

void lidarwithlidar::save_result_clicked()
{
    save_multi_result_xml->show();
    save_multi_result_xml->move(this->geometry().center().x()-save_multi_result_xml->width()/2,this->geometry().center().y()-save_multi_result_xml->height()/2);
    connect(save_multi_result_xml, &savecamerresult::sendData, this, &lidarwithlidar::receiveresultdata);
}

void lidarwithlidar::onitemclicked(int item)
{
    if (item == -1)
    {
        return;
    }
    QDir dir_child(child_pcd_path);
    QString abs_child_FilePath = dir_child.absoluteFilePath(child_cloud_files[item]);
    QDir dir_parent(parent_pcd_path);
    QString abs_parent_FilePath = dir_parent.absoluteFilePath(parent_cloud_files[item]);
    if (pcl::io::loadPCDFile<pcl::PointXYZI>(abs_parent_FilePath.toStdString(), *parent_cloud) == -1 || pcl::io::loadPCDFile<pcl::PointXYZI>(abs_child_FilePath.toStdString(), *child_cloud) == -1)
    {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
    }
    else
    {
//        x=ui->lineEdit->text().toFloat();
//        y=ui->lineEdit_2->text().toFloat();
//        z=ui->lineEdit_3->text().toFloat();
//        qx=ui->lineEdit_4->text().toFloat();
//        qy=ui->lineEdit_5->text().toFloat();
//        qz=ui->lineEdit_6->text().toFloat();
        x=ui->doubleSpinBox->value();
        y=ui->doubleSpinBox_2->value();
        z=ui->doubleSpinBox_3->value();
        qx=ui->doubleSpinBox_4->value();
        qy=ui->doubleSpinBox_5->value();
        qz=ui->doubleSpinBox_6->value();
        iter=ui->lineEdit_7->text().toInt();
        Eigen::Translation3f init_translation(x, y, z);
        Eigen::AngleAxisf init_rotation_x(qx, Eigen::Vector3f::UnitX());
        Eigen::AngleAxisf init_rotation_y(qy, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf init_rotation_z(qz, Eigen::Vector3f::UnitZ());
        init_guess_ = (init_translation * init_rotation_z*init_rotation_y*init_rotation_x).matrix();
        pcl::transformPointCloud(*child_cloud,*output_double_cloud,init_guess_);
        //std::cout<<init_guess_<<std::endl;
        ui->result_show->clear();
        viewer->resetCamera();
        viewer->removeAllPointClouds();
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZI> red(parent_cloud, 255, 0, 0);
        viewer->addPointCloud<pcl::PointXYZI>(parent_cloud,red, "parent_cloud");
        //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "child_cloud");
        viewer->addPointCloud<pcl::PointXYZI>(output_double_cloud, "output_double_cloud");
        // viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "parent_cloud");
        viewer->resetCamera();
        vtkwidget->update();
    }
}

void lidarwithlidar::stop_calculate_clicked()
{
    //    lidarthread->quit();
    //    timer_transform_init->start(10);
    emit stopflag(1);
    ui->result_show->append("停止迭代");
}
void lidarwithlidar::add_parent_path_clicked()
{
    parent_pcd_path = QFileDialog::getExistingDirectory(this, tr("选择父点云目录"));
    ui->label_14->clear();
    ui->label_14->setText("父点云目录:" + parent_pcd_path);
}
void lidarwithlidar::DownsampleCloud(pcl::PointCloud<pcl::PointXYZI>::ConstPtr in_cloud_ptr, pcl::PointCloud<pcl::PointXYZI>::Ptr out_cloud_Ptr, double in_leaf_size)
{
    pcl::VoxelGrid<pcl::PointXYZI> voxelized;
    voxelized.setInputCloud(in_cloud_ptr);
    voxelized.setLeafSize((float)in_leaf_size, (float)in_leaf_size, (float)in_leaf_size);
    voxelized.filter(*out_cloud_Ptr);
}

mythread::mythread(QObject *parent)
    : QThread(parent)
{
    out_cloud_thread.reset(new pcl::PointCloud<pcl::PointXYZI>{});
}

void mythread::run()
{
    num_iter_last=-1;
//    if(flag)
//    {
        for(int i=-2;i<iter_thread;i=i+10)
        {
            ndt_thread.setMaximumIterations(i);
            ndt_thread.align(*out_cloud_thread,init_guess_thread);
            if(stop_thread_flag)
            {
                num_iter_last=-1;
                stop_thread_flag=0;
                break;
            }
            else
            {
                if(num_iter_last==ndt_thread.getFinalNumIteration())
                {
                    flag=0;
                    num_iter_last=-1;
                    break;
                }
                num_iter_last=ndt_thread.getFinalNumIteration();
                Eigen::Matrix4f init_guess_fan=ndt_thread.getFinalTransformation();
                Eigen::Vector3f transtation_matrix=ndt_thread.getFinalTransformation().block(0,3,3,1);
                Eigen::Matrix3f rotation_matrix=ndt_thread.getFinalTransformation().block(0,0,3,3);
                t_xyz=transtation_matrix.transpose();
                r_xyz=rotation_matrix.eulerAngles(2,1,0).transpose();
                translation_x=t_xyz(0);
                translation_y=t_xyz(1);
                translation_z=t_xyz(2);
                rotation_x=r_xyz(2);
                rotation_y=r_xyz(1);
                rotation_z=r_xyz(0);
                emit threadSignal1(ndt_thread.getFinalNumIteration(),ndt_thread.getFitnessScore(),ndt_thread.getTransformationProbability(),translation_x,translation_y,translation_z,rotation_x,rotation_y,rotation_z);
            }
        }
        //    }
}

void mythread::lidarthread_slot(pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_child,pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_parent,Eigen::Matrix4f init_guess_,int iter)
{
    ndt_thread.setTransformationEpsilon(0.01);
    ndt_thread.setStepSize(0.1);
    ndt_thread.setResolution(1.0);
    ndt_thread.setInputSource(cloud_child);
    ndt_thread.setInputTarget(cloud_parent);
    init_guess_thread=init_guess_;
    flag=1;
    iter_thread=iter;
}
void mythread::stop_thread(int a)
{
    stop_thread_flag=a;
}
