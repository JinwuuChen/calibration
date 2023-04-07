#include "newcamerproject.h"
#include "ui_newcamerproject.h"
newcamerproject::newcamerproject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newcamerproject)
{
    ui->setupUi(this);
    setWindowTitle("新建项目");
    connect(ui->pushButton,&QPushButton::clicked,this,&newcamerproject::newclick);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&newcamerproject::addprojectdir);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&newcamerproject::closenewproject);
}

newcamerproject::~newcamerproject()
{
    delete ui;
}

void newcamerproject::newclick()
{
    QString originaPath = this->ui->lineEdit_2->text();
    QString dirPath = QFileDialog::getExistingDirectory(this, "新建项目", this->ui->lineEdit_2->text());
    if(dirPath.isEmpty())
        this->ui->lineEdit_2->setText(originaPath);
    else
        this->ui->lineEdit_2->setText(dirPath);
//     QString projectdir;
//    QString projectname=this->ui->lineEdit->text();
//    projectdir=this->ui->lineEdit_2->text()+"/"+projectname;
}

void newcamerproject::addprojectdir()
{
    emit sendData(ui->lineEdit_2->text()+"/"+ui->lineEdit->text());
    this->close();
}

void newcamerproject::closenewproject()
{
    this->close();
}
