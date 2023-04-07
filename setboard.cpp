#include "setboard.h"
#include "ui_setboard.h"
#include "camera.h"
setboard::setboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setboard)
{
    ui->setupUi(this);
    setWindowTitle("设置棋盘");
    connect(ui->pushButton,&QPushButton::clicked,this,&setboard::intboard);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&setboard::exitboard);
}

setboard::~setboard()
{
    delete ui;
}

void setboard::intboard()
{
    camera k;
    emit sendData(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toFloat());
    this->close();
}

void setboard::exitboard()
{
 //   emit sendData(0,0,0);
    this->close();
}


