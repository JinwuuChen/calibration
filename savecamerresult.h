#ifndef SAVECAMERRESULT_H
#define SAVECAMERRESULT_H

#include <QWidget>
#include<QFileDialog>
namespace Ui {
class savecamerresult;
}

class savecamerresult : public QWidget
{
    Q_OBJECT

public:
    explicit savecamerresult(QWidget *parent = 0);
    ~savecamerresult();
    void newclick();
    void addprojectdir();
    void closenewproject();
signals:
    void sendData(QString data);
private:
    Ui::savecamerresult *ui;
};

#endif // SAVECAMERRESULT_H
