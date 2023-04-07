#include "calibration.h"
#include"camera.h"
#include <QApplication>
#include"cam_neican.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    camera c;
    calibration w;
//    cam_neican k;
//    k.findCorners();
    w.show();
//    a.exec();
//    c.show();
    return a.exec();
}
