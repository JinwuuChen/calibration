#include "calibration.h"
#include"camera.h"
#include <QApplication>
#include"cam_neican.h"
#include<qdesktopwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calibration w;
    QDesktopWidget *desktop=QApplication::desktop();
    w.move(( desktop->screen(1)->width()-w.width())/2,(desktop->screen(1)->height()-w.height())/2);
    w.show();
    w.verifer_license();
    return a.exec();
}
