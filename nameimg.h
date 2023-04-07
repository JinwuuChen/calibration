#ifndef NAMEIMG_H
#define NAMEIMG_H

#include <QWidget>

namespace Ui {
class nameimg;
}

class nameimg : public QWidget
{
    Q_OBJECT

public:
    explicit nameimg(QWidget *parent = 0);
    ~nameimg();
    nameimg(QString filename);

private:
    Ui::nameimg *ui;
};

#endif // NAMEIMG_H
