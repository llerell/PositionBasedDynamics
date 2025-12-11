#include "drawarea.h"
#include <QOpenGLWidget>

DrawArea::DrawArea(QWidget *parent)
    : QOpenGLWidget{parent}
{
    this->setFixedSize(QSize(500,200));
    context = Context();
}

void DrawArea::paintEvent(QPaintEvent *event)  {
    QPainter p(this);
    this->show(&p, event, context);
}

void DrawArea::initializeGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0,0.0,0.0,0.0);
}

void DrawArea::paintGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
}

// Affichage des éléments de la sphère
void DrawArea::show(QPainter *painter, QPaintEvent *event, Context& context) {
    this->paintGL();    // I don't know how to clear out of paintGL()
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::red));
    std::vector<Particle> particles = context.getParticles();
    for(int i=0; i<context.getNbParticles(); i++) {
        Particle part = particles[i];
        float ellipseWidth = this->width()/5;
        float ellipseHeight = this->height()/5;
        QRectF target(part.getX() - ellipseWidth/2, part.getY() - ellipseHeight/2, ellipseWidth, ellipseHeight);
        painter->drawEllipse(target);
    }
}

// Takes the mouse position when there is a double click
// Then calls the paintEvent method (with update)
void DrawArea::mouseDoubleClickEvent(QMouseEvent *event) {
    Vec2 pos = Vec2(event->x(), event->y());
    Particle particle = Particle(pos, Vec2(0,0), 1, 10);
    context.addParticle(particle);
    this->update();
}

// Redraw another ellipse below the precedent
void DrawArea::animate() {
    context.updatePhysicalSystem(1);
    this->update();
}


void worldToView(Vec2& world_pos) {
    // How?
}

void viewToWorld(Vec2& view_pos) {
    // How?
}


