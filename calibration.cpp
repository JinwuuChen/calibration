/*
 * _______________#########_______________________ 
 * ______________############_____________________ 
 * ______________#############____________________ 
 * _____________##__###########___________________ 
 * ____________###__######_#####__________________ 
 * ____________###_#######___####_________________ 
 * ___________###__##########_####________________ 
 * __________####__###########_####_______________ 
 * ________#####___###########__#####_____________ 
 * _______######___###_########___#####___________ 
 * _______#####___###___########___######_________ 
 * ______######___###__###########___######_______ 
 * _____######___####_##############__######______ 
 * ____#######__#####################_#######_____ 
 * ____#######__##############################____ 
 * ___#######__######_#################_#######___ 
 * ___#######__######_######_#########___######___ 
 * ___#######____##__######___######_____######___ 
 * ___#######________######____#####_____#####____ 
 * ____######________#####_____#####_____####_____ 
 * _____#####________####______#####_____###______ 
 * ______#####______;###________###______#________ 
 * ________##_______####________####______________ 
 */


#include "calibration.h"
#include "ui_calibration.h"
using namespace CryptoPP;
calibration::calibration(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::calibration)
{
    ui->setupUi(this);
    read_license();
    setWindowTitle("自动驾驶多传感器快速标定软件");
    connect(ui->pushButton_3, &QPushButton::clicked, this, &calibration::changecamera);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &calibration::changeexternal_camera);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &calibration::changecamerwithlidat);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &calibration::change_lidarwithlidar_clicked);
}

calibration::~calibration()
{
    delete ui;
}

void calibration::changecamera()
{
    if(verifer_success_flag)
    {
    camera *cam = new camera;
    cam->show();
    cam->move(this->geometry().center().x()-cam->width()/2,this->geometry().center().y()-cam->height()/2);
    this->close();
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("license不正确");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
     }
}

void calibration::changeexternal_camera()
{
    if(verifer_success_flag)
    {
    external_camera *m = new external_camera;
    m->show();
    m->move(this->geometry().center().x()-m->width()/2,this->geometry().center().y()-m->height()/2);
    this->close();
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("license不正确");
        wl->resize(500, 200);
        itemw->show();
       itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
    }
}
void calibration::changecamerwithlidat()
{
    if(verifer_success_flag)
    {
    camerawithlidar *k = new camerawithlidar;
    k->show();
     k->move(this->geometry().center().x()-k->width()/2,this->geometry().center().y()-k->height()/2);
    this->close();
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("license不正确");
        wl->resize(500, 200);
        itemw->show();
       itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
    }
}
void calibration::change_lidarwithlidar_clicked()
{
    if(verifer_success_flag)
    {
    lidarwithlidar *l = new lidarwithlidar;
    l->show();
    l->move(this->geometry().center().x()-l->width()/2,this->geometry().center().y()-l->height()/2);
    this->close();
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("license不正确");
        wl->resize(500, 200);
        itemw->show();
       itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
    }
}

void calibration::verifer_license()
{
    QString plain = QString::fromStdString(license_);
//    std::string filename = "license.license";
//    cv::FileStorage ymlFile(filename, cv::FileStorage::WRITE);
//    ymlFile << "license" << plain.toStdString();
    QString key = "cicv";
    QString result_license=CryptoPPUtil::DecryptString(plain, key);
    if(result_license.size()>0)
    {
    time_t tt;
    time(&tt);
    tt = tt + 8 * 3600;  // transform the time zone
    tm* t = gmtime(&tt);
    time_t sys_time = mktime(t);
    std::string mac_id=result_license.toStdString().substr(0,17);
    std::string time=result_license.toStdString().substr(18,19);
    std::list<std::string> mac_seq;
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();
    time_t  dead_line_time = StringToDataTime(time);
    for(int i=0;i<list.count();i++)
    {
    QNetworkInterface interface=list.at(i);
    std::cout << "HardwareAddress:" << interface.hardwareAddress().toStdString()<<std::endl;
    mac_seq.push_back(interface.hardwareAddress().toStdString());
    }
    std::list<string>::iterator find_mac_iter=std::find(mac_seq.begin(),mac_seq.end(),mac_id);
    if(find_mac_iter!=mac_seq.end())
    {
        double   diff_times = difftime(dead_line_time, sys_time);
        int iHour = diff_times / 60 / 60;
        int day=iHour/24;
        int iMin = (diff_times - iHour * 60 * 60) / 60;
        int iSec = diff_times - iHour * 60 * 60 - iMin * 60;
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("mac地址正确");
        wl->setWordWrap(true);
        if(iHour>0||iMin>0)
        {
        wl->setText(wl->text()+"\n"+"剩余时间："+QString::number(day)+"天"+QString::number(int(iHour-day*24))+"小时"+QString::number(iMin)+"分钟");
        verifer_success_flag=1;
        }
        else
        {
            wl->setText(wl->text()+"\n"+"许可证已过期，无法使用");
        }
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("提示");
        return;
    }
    else
    {
        QWidget *itemw = new QWidget;
        QLabel *wl = new QLabel(itemw);
        wl->setText("license与本机mac地址不匹配，无法使用");
        wl->resize(500, 200);
        itemw->show();
        itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
        itemw->setWindowTitle("错误");
        return;
    }
    }
    else
    {
       QWidget *itemw = new QWidget;
       QLabel *wl = new QLabel(itemw);
       wl->setText("license输入错误");
       wl->resize(500, 200);
       itemw->show();
      itemw->move(this->geometry().center().x()-itemw->width()/2,this->geometry().center().y()-itemw->height()/2);
       itemw->setWindowTitle("错误");
       return;
    }
}

void calibration::read_license()
{
    QString filename = "./license.license";
    if (!filename.isEmpty())
    {
        cv::FileStorage ymlreadFile(filename.toStdString(), cv::FileStorage::READ);
        ymlreadFile["license"] >> license_;
    }
}

time_t calibration::StringToDataTime(string datetime_str)
{
    const char* cha = datetime_str.c_str();
        tm tm_;
        int year = 0; int month = 0; int day = 0; int hour = 0; int minute = 0; int second = 0;
        sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
        tm_.tm_year = year - 1900;
        tm_.tm_mon = month - 1;
        tm_.tm_mday = day;
        tm_.tm_hour = hour;
        tm_.tm_min = minute;
        tm_.tm_sec = second;
        tm_.tm_isdst = 0;
        time_t t_ = mktime(&tm_);
        return t_;
}


