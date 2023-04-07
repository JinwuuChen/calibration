#ifndef CAMERA_H
#define CAMERA_H
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QButtonGroup>
#include <QListWidget>
#include <iostream>
#include <memory>
#include "cam_neican.h"
#include "setboard.h"
#include <QXmlStreamReader>
#include "camera_neican_help.h"
#include "newcamerproject.h"
#include "savecamerresult.h"
#include <QCheckBox>
#include<QTimer>
#include<QLabel>
namespace Ui
{
    class camera;
}

class camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = 0);
    ~camera();
    QStringList Imgpath;
    int imgshow_flag = 0;
    bool passcal_flag = 0;
    void imgaddclick();
    void startcameraclick();
    void onRadiobuttonClicked();
    void onitemclicked(QListWidgetItem *item);
    void startcalicamera();
    void saveresultcamera();
    void deleteimgclick();
    void savecamera_xml();
    void readcamera_xml();
    void setboardclick();
    void receivedata(int a, int b, float c);
    void showint();
    void helpclick();
    void newproject();
    void receiveprojectdata(QString a);
    void receiveresultdata(QString a);
    //    void showImg(int item);
    //    bool loadImgsFistTime = true;
    std::unique_ptr<cam_neican> camneican;
    QString savereultPath;
    QString savereultPath_biaoding;
    setboard *board = new setboard;
    newcamerproject *newp = new newcamerproject;
    savecamerresult *redsult = new savecamerresult;
    static int a, b;
    bool xunhuan=1;
    static float c;
    QTimer* calibrate_timer;
    QTimer* find_corner_timer;
    QWidget *timer_widget;
    QLabel *timer_label;
private slots:
    void Time_calibrate_update(void);
    void Time_find_corner_update(void);
    //    void on_actioninput_triggered();

private:
    Ui::camera *ui;
    QButtonGroup *mbtngroup;
};

#endif // CAMERA_H
