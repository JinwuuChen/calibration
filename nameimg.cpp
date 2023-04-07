#include "nameimg.h"
#include "ui_nameimg.h"

nameimg::nameimg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nameimg)
{
    ui->setupUi(this);
}

nameimg::nameimg(QString filename)
{
ui->labelfilename->setText(filename);
}


nameimg::~nameimg()
{
    delete ui;
}
