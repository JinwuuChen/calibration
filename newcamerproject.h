#ifndef NEWCAMERPROJECT_H
#define NEWCAMERPROJECT_H

#include <QWidget>
#include<QFileDialog>
namespace Ui {
class newcamerproject;
}

class newcamerproject : public QWidget
{
    Q_OBJECT

public:
    explicit newcamerproject(QWidget *parent = 0);
    ~newcamerproject();
    void newclick();
    void addprojectdir();
    void closenewproject();
signals:
    void sendData(QString data);
private:
    Ui::newcamerproject *ui;
};

#endif // NEWCAMERPROJECT_H
