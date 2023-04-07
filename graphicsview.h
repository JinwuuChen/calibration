#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QBoxLayout>
#include <QGraphicsView>
#include <qevent.h>

class ImageBox;

class GraphicsView:public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QWidget *parent = 0);
    ~GraphicsView();

    void Init(ImageBox * imageBox){m_imageBox = imageBox;}
    void SetImage(const QImage & image);

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    void ZoomIn();
    void ZoomOut();
    void Zoom(float scaleFactor);
    void Translate(QPointF delta);

private:
    bool m_isTranslate;
    QPoint m_lastMousePos;
    ImageBox * m_imageBox;
    QGraphicsScene * m_scene;
    QGraphicsPixmapItem * m_imageItem;
};

#endif // GRAPHICSVIEW_H
