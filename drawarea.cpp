#include "drawarea.h"
#include <QOpenGLWidget>
#include <QLine>

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

Vec2 DrawArea::worldToView(Vec2 world_pos){
    return Vec2 {world_pos.getX(), this->height()-world_pos.getY()};
}

Vec2 DrawArea::viewToWorld(Vec2 view_pos){
    return Vec2 {view_pos.getX(), this->height()-view_pos.getY()};
}

// Affichage des éléments de la sphère
void DrawArea::show(QPainter *painter, QPaintEvent *event, Context& context) {
    this->paintGL();    // I don't know how to clear out of paintGL()
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::red));
    std::vector<Particle> particles = context.getParticles();
    int width, height;
    Vec2 pixelPos = {0,0};
    width = this->width();
    height = this->height();
    for(int i=0; i<context.getColliders().size(); i++) {
        PlanCollider coll = context.getColliders()[i];
        Vec2 pc = worldToView(coll.getCenter());
        Vec2 p1 = Vec2(0,pc.getY());
        Vec2 p2 = Vec2(width, pc.getY());
        QLine line(p1.getX(), p1.getY(),p2.getX(), p2.getY());
        painter->drawLine(line);
    }
    for(int i=0; i<context.getNbParticles(); i++) {
        Particle part = particles[i];
        pixelPos=worldToView(part.getPos());
        QRectF target(pixelPos.getX()-width/10, pixelPos.getY()-height/10, width/5, height/5);
        painter->drawEllipse(target);
    }
}

// Takes the mouse position when there is a double click
// Then calls the paintEvent method (with update)
void DrawArea::mouseDoubleClickEvent(QMouseEvent *event) {
    Vec2 pixelPos = Vec2(event->x(), event->y());
    Vec2 worldPos = worldToView(pixelPos);
    Particle particle = Particle(worldPos, Vec2(20,50), 10, 1);
    context.addParticle(particle);
    this->update();
}

// Redraw another ellipse below the precedent
void DrawArea::animate() {
    context.updatePhysicalSystem(1);
    this->update();
}

