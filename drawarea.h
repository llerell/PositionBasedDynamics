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

private:
    Context context;

signals:
};

#endif // DRAWAREA_H
