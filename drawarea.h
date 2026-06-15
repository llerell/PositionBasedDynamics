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

    /// show the objects on the stage
    void show(QPainter *painter, QPaintEvent *event, Context& context);


    /// select particles to link
    void mousePressEvent(QMouseEvent *event) override;

    /// call update to physical system multiple times before showing the result.
    void animate();

    /// reset context.
    void reset();

    /// active or desactive the random colors for the particles.
    void randomColor();


    /// active or desactive the destruction of the particles.
    void toggleCollisions();


    /// change the maximum health points of the particles.
    void setHealth(const int newHealth);

    void link();


private:
    Context context;

    /// height in meters
    const float m_height = 10;
    /// width in meters
    const float m_width = 15;

    /// whether the particles appear with a random color.
    bool is_random;
    /// maximum health points of the particles
    int healthPoints;

    /// number of times the physical system is updated betwteen two frames
    int nbUpdates = 10;

    /// default color for the collider (when context.collisions is false)
    QColor defaultColliderColor = Qt::black;
    /// default color for the particles (when is_random is false)
    QColor defaultPartColor = Qt::gray;


    /// translate physical system coordinates in pixel coordinates.
    const Vec2 worldToView(const Vec2 world_pos) const;

    /// translate pixel coordinates in physical system coordinates.
    const Vec2 viewToWorld(const Vec2 view_pos) const;

    /// draw a Plane collider.
    void drawCollider(QPainter *painter, const PlaneCollider PlaneCollider);

    /// draw a Spherical collider.
    void drawCollider(QPainter *painter, const SphereCollider sphereCollider);

    /// draw a rectangular collider.
    void drawCollider(QPainter *painter, const BoxCollider boxCollider);

    /// create a particle at every double click input.
    void mouseDoubleClickEvent(QMouseEvent *event) override;

};

#endif // DRAWAREA_H
