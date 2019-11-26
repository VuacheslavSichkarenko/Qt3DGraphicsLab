#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>
#include <QImage>
#include "graphics/components/worldobject.h"
#include "graphics/components/camera.h"
#include "graphics/components/vertex.h"
#include "graphics/projections/projection.h"
#include "graphics/components/zbuffer.h"
#include "math/Vector2D.h"
#include <mutex>

class WorldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldWidget(QWidget *parent = nullptr);
    ~WorldWidget() override;

    enum DrawModel
    {
        WIREFRAME,
        SURFACE
    };

    WorldObject& GetWorldObject();
    void SetProjection(Projection* projection);

public slots:
    void SetDrawModel(const DrawModel& drawModel);
    void SetLight(const Vector3D& light);
    void redraw();

private:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void fillTriangle(const Vertex& vert1, const Vertex& vert2, const Vertex& vert3, const QColor& color);
    void fillRect(const int& x, const int& y, const int& width, const int& height, const QColor& color);
    void drawLine(const int& x1, const int& y1, const int& x2, const int& y2, const QColor& color);
    void drawPixel(const int& x, const int& y, const QColor& color);

    void drawObjectSurface();
    void drawObjectWireframe();
    void drawMisc();
    void redrawThread();

    QList<Vertex> VerticesToCoordSystem(const QList<Vertex>& vertices);
    QList<Vertex> transformVertices(const QList<Vertex>& vertices);
    void recalculateNormals(const QList<Vertex>& vertices);

private:
    WorldObject* m_worldObject;
    Projection* m_projection;
    ZBuffer* m_zBuffer;
    Vector2D m_coordSysCenter;
    Vector3D m_light;
    DrawModel m_drawModel;
    QImage* m_renderBuffer;
    QImage* m_drawBuffer;
    std::mutex m_drawMutex;
};

#endif // WORLDWIDGET_H
