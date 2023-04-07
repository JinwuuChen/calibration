#include "savecamerresult.h"
#include "ui_savecamerresult.h"

savecamerresult::savecamerresult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::savecamerresult)
{
    ui->setupUi(this);
    setWindowTitle("导出结果");
    connect(ui->pushButton,&QPushButton::clicked,this,&savecamerresult::newclick);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&savecamerresult::addprojectdir);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&savecamerresult::closenewproject);
}

savecamerresult::~savecamerresult()
{
    delete ui;
}

void savecamerresult::newclick()
{
    QString originaPath = this->ui->lineEdit_2->text();
    QString dirPath = QFileDialog::getExistingDirectory(this, "导出结果", this->ui->lineEdit_2->text());
    if(dirPath.isEmpty())
        this->ui->lineEdit_2->setText(originaPath);
    else
        this->ui->lineEdit_2->setText(dirPath);

}

void savecamerresult::addprojectdir()
{
    emit sendData(ui->lineEdit_2->text()+"/"+ui->lineEdit->text());
    this->close();
}

void savecamerresult::closenewproject()
{
  this->close();
}
