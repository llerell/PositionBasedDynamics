#ifndef DRAWAREA_H
#define DRAWAREA_H

#include "context.h"
#include <QOpenGLWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include "planecollider.h"
#include "spherecollider.h"
#include "vec2.h"

class DrawArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void initializeGL() override;

    void show(QPainter *painter, QPaintEvent *event, Context& context);

    /// draw a Plane collider.
    void drawCollider(QPainter *painter, PlaneCollider PlaneCollider);

    /// draw a Spherical collider.
    void drawCollider(QPainter *painter, SphereCollider sphereCollider);

    /// draw a rectangular collider.
    void drawCollider(QPainter *painter, BoxCollider boxCollider);

    /// create a particle at every double click input.
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    /// call update to physical system multiple times before showing the result.
    void animate();

    /// reset context.
    void reset();

    void randomColor();

    void activeCollisions();

    void setHealth(int newHealth);


private:
    /// translate physical system coordinates in pixel coordinates.
    Vec2 worldToView(Vec2 world_pos);

    /// translate pixel coordinates in physical system coordinates.
    Vec2 viewToWorld(Vec2 view_pos);

    Context context;

    float m_height = 10;

    float m_width = 15;

    bool is_random;

    int healthPoints;

    int nbUpdates = 10;

    QColor defaultColliderColor = Qt::black;
    QColor defaultPartColor = Qt::gray;

};

#endif // DRAWAREA_H
