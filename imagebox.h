#ifndef IMAGEBOX_H
#define IMAGEBOX_H

#include <QtCore/qglobal.h>

#if defined(IMAGEBOX_LIBRARY)
#  define IMAGEBOX_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEBOX_EXPORT Q_DECL_IMPORT
#endif

#include <QImage>
#include <QBoxLayout>

class GraphicsView;

class IMAGEBOX_EXPORT ImageBox:public QObject
{
    Q_OBJECT

public:
    ImageBox();
    ~ImageBox();

    QString Version();
    void Init(QBoxLayout * panel);
    const QImage & GetImage(){return m_image;}
    void SetImage(const QImage & image);
    void SetImage(const QString & image);

signals:
    void ImageClick(int x,int y);

private:
    GraphicsView * m_widget;   /**< 用于操作绘图的控件*/
    QImage m_image;               /**< 当前显示图片*/
    friend class GraphicsView;
};

#endif
