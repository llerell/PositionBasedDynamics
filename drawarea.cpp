#include "drawarea.h"
#include "spherecollider.h"
#include <QOpenGLWidget>
#include <QLine>

DrawArea::DrawArea(QWidget *parent)
    : QOpenGLWidget{parent}
{
    const float ratio = m_width/m_height;
    const int height = 500;
    this->setFixedSize(QSize(height*ratio,height));
    context = Context();
    context.setNbUpdates(nbUpdates);
    std::srand(std::time({}));
    is_random = false;
    healthPoints = nbUpdates*50;
}

void DrawArea::paintEvent(QPaintEvent *event)  {
    QPainter p(this);
    this->show(&p, event, context);
}

void DrawArea::initializeGL(){
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0,0.0,0.0,0.0);
}

void DrawArea::show(QPainter *painter, QPaintEvent *event, Context& context) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);

    const int height = this->height();

    painter->fillRect(event->rect(), QBrush(Qt::white));
    std::vector<Particle> particles = context.getParticles();

    // draw colliders
    QColor colliderColor;
    for(int i=0; i<context.getColliders().size(); i++) {

        const std::variant<PlaneCollider, SphereCollider, BoxCollider> coll_var = context.getColliders()[i];
        if(context.getCollisionsToggle()) {
            colliderColor = std::visit([this](auto& arg) -> QColor {return arg.getColor();}, coll_var);
        }
        else {
            colliderColor = defaultColliderColor;
        }
        painter->setPen(colliderColor);
        painter->setBrush(QBrush(colliderColor));

        std::visit([painter, this](auto& arg) {drawCollider(painter, arg);}, coll_var);
    }

    // draw particles
    Vec2 viewPos;
    for(int i=0; i<context.getNbParticles(); i++) {
        const Particle part = particles[i];

        // translate in view coordinates
        viewPos=worldToView(part.getPos());
        const float rad = height*part.getRad()/m_height;

        painter->setPen(part.getColor());
        painter->setBrush(QBrush(part.getColor()));
        const QRectF target(viewPos.getX()-rad, viewPos.getY()-rad, rad*2, rad*2);
        painter->drawEllipse(target);

    }
}

void DrawArea::animate() {
    float dt = 0.01;
    float n = float(nbUpdates); // need a float to make a float division with dt/n
    for (int i=0; i<n; i++){
        context.updatePhysicalSystem(dt/n);
    }
    this->update();
}

void DrawArea::reset() {
    context.reset();
    this->update();
}

void DrawArea::randomColor() {
    is_random = !(is_random);
}

void DrawArea::toggleCollisions() {
    context.changeCollisions();
}

void DrawArea::setHealth(const int newHealth) {
    healthPoints = nbUpdates*newHealth;
}


const Vec2 DrawArea::worldToView(const Vec2 world_pos) const {
    const float py = (this->height())*(1-world_pos.getY()/m_height);
    return Vec2 {this->width()*world_pos.getX()/m_width, py};
}

const Vec2 DrawArea::viewToWorld(const Vec2 view_pos) const{
    const float y = m_height*(1-view_pos.getY()/(this->height()));
    return Vec2 {m_width*view_pos.getX()/this->width(), y};
}

void DrawArea::drawCollider(QPainter *painter, const PlaneCollider PlaneCollider) {
    const Vec2 pc = PlaneCollider.getPoint();
    const Vec2 nc = PlaneCollider.getNormal();
    Vec2 p1, p2;

    if (nc.getY()!=0){
        const float coeff = -nc.getX()/nc.getY();
        p1 = worldToView(Vec2(0,pc.getY()-coeff*pc.getX()));
        p2 = worldToView(Vec2(m_width, pc.getY()+coeff*(m_width - pc.getX())));
    } else { // vertical planes
        p1 = worldToView(Vec2(pc.getX(), 0));
        p2 = worldToView(Vec2(pc.getX(), m_height));
    }

    const QLine line(p1.getX(), p1.getY(),p2.getX(), p2.getY());
    painter->drawLine(line);
}

void DrawArea::drawCollider(QPainter *painter, const SphereCollider sphereCollider) {
    const Vec2 pc = worldToView(sphereCollider.getPoint());
    const float rc = this->height() * sphereCollider.getRadius()/m_height;
    const QRectF target(pc.getX()-rc, pc.getY()-rc, 2*rc, 2*rc);
    painter->drawEllipse(target);
}

void DrawArea::drawCollider(QPainter *painter, const BoxCollider boxCollider) {
    const Vec2 u = boxCollider.getU();
    const Vec2 v = boxCollider.getV();
    const float width = boxCollider.getWidth();
    const float height = boxCollider.getHeight();
    const Vec2 p1 = worldToView(boxCollider.getPoint() + (width/2 * u) + (height/2 * v));
    const Vec2 p2 = worldToView(boxCollider.getPoint() + (width/2 * u) - (height/2 * v));
    const Vec2 p3 = worldToView(boxCollider.getPoint() - (width/2 * u) + (height/2 * v));
    const Vec2 p4 = worldToView(boxCollider.getPoint() - (width/2 * u) - (height/2 * v));

    QList<QPoint> points;
    points.append(QPoint(p1.getX(), p1.getY()));
    points.append(QPoint(p2.getX(), p2.getY()));
    points.append(QPoint(p4.getX(), p4.getY()));
    points.append(QPoint(p3.getX(), p3.getY()));
    points.append(QPoint(p1.getX(), p1.getY()));
    const QPolygon polygon = QPolygon(points);
    painter->drawPolygon(polygon);
}

// Take the mouse position when there is a double click
// Then call the paintEvent method (with update)
void DrawArea::mouseDoubleClickEvent(QMouseEvent *event) {
    const QPointF position = event->position();
    const Vec2 viewPos = Vec2(position.x(), position.y());
    const Vec2 worldPos = viewToWorld(viewPos);
    QColor color;

    if(is_random) {
        // Random color: int between 0 and 254 to avoid white (which would not be seen)
        const int red = std::rand() % 255;
        const int green = std::rand() % 255;
        const int blue = std::rand() % 255;
        color = QColor(red,green,blue);
    }
    else {
        color = defaultPartColor;
    }

    Particle particle = Particle(worldPos, Vec2(), 0.5, 1, healthPoints, color);
    context.addParticle(particle);
    this->update();
}

void DrawArea::mousePressEvent(QMouseEvent *event){
    QPointF position = event->position();
    Vec2 viewPos = Vec2(position.x(), position.y());
    Vec2 worldPos = viewToWorld(viewPos);
    context.setSelectedParticle(worldPos);
}

void DrawArea::animate() {
    float dt = 0.01;
    float n = float(nbUpdates);
    for (int i=0; i<n; i++){
        context.updatePhysicalSystem(dt/n);
    }
    this->update();
}

void DrawArea::reset() {
    context.reset();
    this->update();
}

void DrawArea::randomColor() {
    is_random = !(is_random);
}

void DrawArea::activeCollisions() {
    context.changeCollisions();
}

void DrawArea::setHealth(int newHealth) {
    healthPoints = nbUpdates*newHealth;
}

void DrawArea::link(){
    context.linkSelectedParticles();
}
