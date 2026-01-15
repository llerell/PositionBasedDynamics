#ifndef DRAWAREA_H
#define DRAWAREA_H

#include "context.h"
#include <QOpenGLWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include "plancollider.h"
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

    void drawCollider(QPainter *painter, PlanCollider plancollider);
    void drawCollider(QPainter *painter, SphereCollider spherCollider);

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void animate();

    void reset();

    void randomColor();


private:
    Vec2 worldToView(Vec2 world_pos);

    Vec2 viewToWorld(Vec2 view_pos);

    Context context;

    float m_height = 10;

    float m_width = 15;

    bool is_random;

    QColor colliderColor = Qt::black;
    QColor defaultPartColor = Qt::gray;
    std::vector<QColor> partColors = {Qt::darkGreen, Qt::darkBlue, QColor(230,200,0), Qt::gray, QColor(0,114,114), QColor(200,120,0), QColor(120,0,200)};

signals:
};

#endif // DRAWAREA_H
