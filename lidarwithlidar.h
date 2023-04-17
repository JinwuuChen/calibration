#ifndef LIDARWITHLIDAR_H
#define LIDARWITHLIDAR_H

#include <QWidget>
#include <QFileDialog>
#include <pcl/visualization/pcl_visualizer.h>
#include <QVTKWidget.h>
#include <QThread>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <boost/thread/thread.hpp>
#include <pcl/visualization/cloud_viewer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOutputWindow.h>
#include <pcl/point_types.h>
#include <QVector>
#include <QVector3D>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/ndt.h>
#include <pcl/registration/icp.h>
#include<iostream>
#include<QTimer>
#include<QTime>
#include"savecamerresult.h"
#include"newcamerproject.h"
#include"result_verify.h"
#include<qdesktopwidget.h>
#include<Eigen/StdVector>
using namespace Eigen;
EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Eigen::Affine3d)//解决vector中Eigen对齐的问题
namespace Ui
{
    class lidarwithlidar;
}

class mythread : public QThread
        {
    Q_OBJECT
    public:
    mythread(QObject *parent=0);
    void run();
    int flag=0;
    int stop_thread_flag=0;
    int iter_thread;
    int num_iter_last;
    pcl::NormalDistributionsTransform<pcl::PointXYZI, pcl::PointXYZI> ndt_thread;
    pcl::PointCloud<pcl::PointXYZI>::Ptr out_cloud_thread;
    Eigen::Matrix4f init_guess_thread;
    Eigen::Vector3f t_xyz,r_xyz;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    float translation_x=0,translation_y=0,translation_z=0,rotation_x=0,rotation_y=0,rotation_z=0;
signals:
    void threadSignal1(int,float,float,float,float,float,float,float,float);
public slots:
    void lidarthread_slot(pcl::PointCloud<pcl::PointXYZI>::Ptr,pcl::PointCloud<pcl::PointXYZI>::Ptr,Eigen::Matrix4f,int);
    void stop_thread(int);
};

class lidarwithlidar : public QWidget
{
    Q_OBJECT

public:
    explicit lidarwithlidar(QWidget *parent = 0);
    ~lidarwithlidar();
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    void new_project_clicked();
    void save_project_clicked();
    void open_project_clicked();
    void add_child_path_clicked();
    void save_result_clicked();
    void onitemclicked(int item);
    void stop_calculate_clicked();
    Eigen::Matrix4f current_guess_;
    Eigen::Matrix4f guess_final;
    void add_parent_path_clicked();
    QString child_pcd_path;
    QString parent_pcd_path;
    void update_path_clicked();
    void result_clear();
    void help_clicked();
    pcl::visualization::PCLVisualizer::Ptr viewer;
    pcl::PointCloud<pcl::PointXYZI>::Ptr parent_cloud;
    pcl::PointCloud<pcl::PointXYZI>::Ptr child_cloud;
    pcl::PointCloud<pcl::PointXYZI>::Ptr child_filtered_cloud;
    pcl::PointCloud<pcl::PointXYZI>::Ptr output_cloud;
    pcl::PointCloud<pcl::PointXYZI>::Ptr output_double_cloud;
    pcl::NormalDistributionsTransform<pcl::PointXYZI, pcl::PointXYZI> ndt;
    //pcl::IterativeClosestPoint<pcl::PointXYZI, pcl::PointXYZI> ndt;
    void DownsampleCloud(pcl::PointCloud<pcl::PointXYZI>::ConstPtr in_cloud_ptr, pcl::PointCloud<pcl::PointXYZI>::Ptr out_cloud_Ptr, double in_leaf_size);
    QVTKWidget *vtkwidget;
    QTimer *timer;
    QTimer *timer_transform_init;
    QStringList getFileNames(const QString &path);
    QStringList parent_cloud_files;
    QStringList child_cloud_files;
    double x,y,z,qx,qy,qz;
    void calculateclicked();
    Eigen::Matrix4f init_guess_;
    int cnt,iter;
    int num_iter_;
    newcamerproject *newprojectwidget=new newcamerproject;
    void receiveprojectdata(QString a);
    QString saveprojectpath;
    savecamerresult *save_multi_result_xml = new savecamerresult;
    void receiveresultdata(QString a);
    int numiteration=0;
    float scorefitness=0;
    Eigen::Vector3f t_xyz,r_xyz;
    float translation_x=0,translation_y=0,translation_z=0,rotation_x=0,rotation_y=0,rotation_z=0;
    mythread* lidarthread;

signals:
    void send_cloud(pcl::PointCloud<pcl::PointXYZI>::Ptr,pcl::PointCloud<pcl::PointXYZI>::Ptr,Eigen::Matrix4f,int);
    void stopflag(int);
public slots:
    void Time_Update(void);
    void view_timer_update(void);
    void mySlot1(int,float,float,float,float,float,float,float,float);

private:
    Ui::lidarwithlidar *ui;
};


#endif // LIDARWITHLIDAR_H
