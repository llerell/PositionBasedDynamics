#include "drawarea.h"
#include <QOpenGLWidget>

DrawArea::DrawArea(QWidget *parent)
    : QOpenGLWidget{parent}
{
    this->setFixedSize(QSize(750,500));
    context = Context();
}

void DrawArea::paintEvent(QPaintEvent *event)  {
    QPainter p(this);
    this->show(&p, event, context);
}

void DrawArea::initializeGL(){
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0,0.0,0.0,0.0);
}

void DrawArea::paintGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
}

// The height of the screen is equivalent to 10m.
Vec2 DrawArea::worldToView(Vec2 world_pos){
    float py = (this->height())*(1-world_pos.getY()/m_height);
    return Vec2 {this->height()*world_pos.getX()/m_height, py};
}

Vec2 DrawArea::viewToWorld(Vec2 view_pos){
    float y = m_height*(1-view_pos.getY()/(this->height()));
    return Vec2 {m_height*view_pos.getX()/this->height(), y};
}
// Affichage des éléments de la sphère
void DrawArea::show(QPainter *painter, QPaintEvent *event, Context& context) {
    this->paintGL();    // I don't know how to clear out of paintGL()
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::red));
    std::vector<Particle> particles = context.getParticles();
    int height = this->height();
    Vec2 viewPos = Vec2(0,0);
    for(int i=0; i<context.getNbParticles(); i++) {
        Particle part = particles[i];
        viewPos=worldToView(part.getPos());
        float rad = height*part.getRad()/m_height;
        QRectF target(viewPos.getX()-rad/2, viewPos.getY()-rad/2, rad, rad);
        painter->drawEllipse(target);

    }
}

// Takes the mouse position when there is a double click
// Then calls the paintEvent method (with update)
void DrawArea::mouseDoubleClickEvent(QMouseEvent *event) {
    QPointF position = event->position();
    Vec2 pixelPos = Vec2(position.x(), position.y());
    Vec2 worldPos = viewToWorld(pixelPos);
    Particle particle = Particle(worldPos, Vec2(0,5), 1, 1);
    context.addParticle(particle);
    this->update();
}

// Redraw another ellipse below the precedent
void DrawArea::animate() {
    context.updatePhysicalSystem(0.1);
    this->update();
}


