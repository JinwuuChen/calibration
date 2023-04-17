#ifndef EXTERNAL_CAMERA_H
#define EXTERNAL_CAMERA_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <QFileDialog>
#include <QButtonGroup>
#include "imagebox.h"
#include "newcamerproject.h"
#include "savecamerresult.h"
#include<qdesktopwidget.h>
namespace Ui
{
    class external_camera;
}

class external_camera : public QWidget
{
    Q_OBJECT

public:
    explicit external_camera(QWidget *parent = 0);
    ~external_camera();
    void Calculatepnp();
    void openresultneican_click();
    void appendtw(int a, int b, int c, int d, int e);
    void addcoordinateclick();
    void ActImageClick(int x, int y);
    void imgaddclick();
    void deleteimgclick();
    void external_camera_help_click();
    void saveresult_xml_click();
    void saveprojectclick();
    void openprojectclick();
    void showImg(int item);
    void newprojectclick();
    void receiveprojectdata(QString a);
    void onRadiobuttonClicked();
    void receiveresultdata(QString a);
    void savecoordinateclick();
    QString savereultPath_biaoding;
    bool open_xml_flag = 0;
    QString savereultPath;
    newcamerproject *newp = new newcamerproject;
    savecamerresult *result_xml = new savecamerresult;
    QStringList Imgpath;
    std::vector<std::string> imagePaths;
    std::vector<cv::Point3f> point3s;
    std::vector<cv::Point2f> point2s;
    cv::Mat mtx;
    cv::Mat dist;
    cv::Mat rvecs;
    cv::Mat tvecs;
    ImageBox m_imageBox;
    int imgshow_flag;
    void clear();

private:
    Ui::external_camera *ui;
    QButtonGroup *mbtngroup;
};

#endif // EXTERNAL_CAMERA_H
