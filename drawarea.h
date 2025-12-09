#ifndef DRAWAREA_H
#define DRAWAREA_H

#include "context.h"
#include <QOpenGLWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QOpenGLFunctions>


class DrawArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void initializeGL() override;

    void paintGL() override;

    // Affichage des éléments de la sphère
    void show(QPainter *painter, QPaintEvent *event, Context& context);

    // Takes the mouse position when there is a double click
    // Then calls the paintEvent method (with update)
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    // Redraw another ellipse below the precedent
    void animate();

    // Transform the position (so modify the Vec2 object)
    void worldToView(Vec2& world_pos);
    void viewToWorld(Vec2& view_pos);

private:
    Context context;

signals:
};

#endif // DRAWAREA_H
