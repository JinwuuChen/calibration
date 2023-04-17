#ifndef CAMERAWITHLIDAR_H
#define CAMERAWITHLIDAR_H

#include <QWidget>
#include <QFileDialog>
#include <QListWidgetItem>
#include <thread>
#include <imagebox.h>
#include <pcl/common/common_headers.h>
// #include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <boost/thread/thread.hpp>
// PCLVisualizer是PCL可视化3D点云的主要类。其内部实现了添加各种3D对象以及交互的实现等，比其他类实现的功能更齐全。
#include <pcl/visualization/cloud_viewer.h>
#include <QVTKWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOutputWindow.h>
#include <pcl/point_types.h>
#include <QVector>
#include <QVector3D>
#include<qdesktopwidget.h>
#include <memory>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include "newcamerproject.h"
#include "savecamerresult.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <opencv2/calib3d.hpp>
using namespace std;
namespace Ui
{
    class camerawithlidar;
}

class camerawithlidar : public QWidget
{
    Q_OBJECT

public:
    explicit camerawithlidar(QWidget *parent = 0);
    ~camerawithlidar();
    newcamerproject *newp = new newcamerproject;
    QString saveprojectpath;
    savecamerresult *result_xml = new savecamerresult;
    void newprojectclick();
    void saveprojectclick();
    void openprojectclick();
    void receiveprojectdata(QString a);
    void receiveresultdata(QString a);
    void deletecoordinateclick();
    void camerawithlidar_help_click();
    void clear();
    void saveresultxmlclick();
    void addimgclick();
    void result_verify_clicked();
    QStringList getFileNames(const QString &path);
    QStringList getimgFileNames(const QString &path);
    QStringList lidar_files;
    QStringList lidar_imgfiles;
    ImageBox m_imageBox;
    QString dirname;
    QString dirimgname;
    void onitemclicked(int item);
    QVTKWidget *vtkWidget;
    void point_pick_callback(const pcl::visualization::PointPickingEvent &event, void *args);
    pcl::PointCloud<pcl::PointXYZ>::Ptr clicked_points_3d;
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud;
    pcl::visualization::PCLVisualizer::Ptr viewer;
    void addpcdpathclick();
    void addimgpathclick();
    void ActImageClick(int x, int y);
    void addcoordinateclick();
    void appendtw(float a, float b, float c, float d, float e);
    void calculateclick();
    void openxmlclick();
    bool open_xml_flag = 0;
    cv::Mat mtx;
    cv::Mat dist;
    cv::Mat rvecs;
    cv::Mat tvecs;
    std::vector<cv::Point3f> point3s;
    std::vector<cv::Point2f> point2s;
    void getTheoreticalUVl(float* theoryUV, const vector<float> &intrinsic, const vector<float> &extrinsic, double x, double y, double z);

signals:
    void click_3d(QVector3D);

private:
    Ui::camerawithlidar *ui;
    static const std::string _clickID;
};
#endif // CAMERAWITHLIDAR_H
