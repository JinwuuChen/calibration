#ifndef CAMERA_NEICAN_HELP_H
#define CAMERA_NEICAN_HELP_H

#include <QWidget>

namespace Ui {
class camera_neican_help;
}

class camera_neican_help : public QWidget
{
    Q_OBJECT

public:
    explicit camera_neican_help(QWidget *parent = 0);
    ~camera_neican_help();

private:
    Ui::camera_neican_help *ui;
};

#endif // CAMERA_NEICAN_HELP_H
