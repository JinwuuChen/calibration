#include "imagebox.h"
#include "graphicsview.h"

ImageBox::ImageBox():
    m_widget(nullptr)
{
}

ImageBox::~ImageBox()
{
    if(m_widget)
        m_widget->deleteLater();
}


QString ImageBox::Version()
{
    return "ImageBox V1.0.21724";
}


void ImageBox::Init(QBoxLayout *panel)
{
    if(m_widget!=nullptr)
        return;
    m_widget = new GraphicsView(nullptr);
    if(panel)
        panel->addWidget(m_widget);
    m_widget->Init(this);
}

void ImageBox::SetImage(const QImage &image)
{
    m_image = image;
    m_widget->SetImage(image);
}

void ImageBox::SetImage(const QString &image)
{
    QImage img = QImage(image);
    if(!img.isNull())
    {
        m_image = img;
        m_widget->SetImage(img);
    }
}

