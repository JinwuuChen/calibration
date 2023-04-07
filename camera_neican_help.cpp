#include "camera_neican_help.h"
#include "ui_camera_neican_help.h"

camera_neican_help::camera_neican_help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_neican_help)
{
    ui->setupUi(this);
    setWindowTitle("帮助");
}

camera_neican_help::~camera_neican_help()
{
    delete ui;
}
