#ifndef SETBOARD_H
#define SETBOARD_H

#include <QWidget>

namespace Ui {
class setboard;
}

class setboard : public QWidget
{
    Q_OBJECT

public:
    explicit setboard(QWidget *parent = 0);
    ~setboard();
    void intboard();
    void exitboard();
signals:
    void sendData(int data,int data2,float data3);
private:
    Ui::setboard *ui;
};

#endif // SETBOARD_H
