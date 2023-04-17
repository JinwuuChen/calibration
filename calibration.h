#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QMainWindow>
#include<list>
#include "camera.h"
#include "external_camera.h"
#include "camerawithlidar.h"
#include "lidarwithlidar.h"
#include <fstream>
#include <time.h>
#include <QHostInfo> // 计算机名
#include <QStandardPaths>  // 用户名(获取家目录，删除其它字段只保留用户名)
#include <QNetworkInterface>  // 网卡信息
#include <cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <rsa.h>
#include <hex.h>
#include <osrng.h>
#include <files.h>
#include <md5.h>
#include <pssr.h>
#include "cryptopputil.h"
#include<qdesktopwidget.h>
#include <QApplication>
static bool verifer_success_flag=0;
namespace Ui
{
    class calibration;
}

class calibration : public QMainWindow
{
    Q_OBJECT

public:
    explicit calibration(QWidget *parent = 0);
    ~calibration();
    void cameramode();
    void changecamera();
    void changeexternal_camera();
    void changecamerwithlidat();
    void change_lidarwithlidar_clicked();
    void verifer_license();
    void read_license();
    bool cameramode_flag = 0;
    time_t StringToDataTime(std::string datetime_str);
    std::string license_;
private:
    Ui::calibration *ui;
};

#endif // CALIBRATION_H
