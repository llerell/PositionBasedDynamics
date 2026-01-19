#include "boxcollider.h"

BoxCollider::BoxCollider(const Vec2 pc_, const Vec2 u_, const float width_, const float height_):Collider(), pc(pc_), u(u_*(1.0/(u_.length()))), width(width_), height(height_), v(Vec2(-u.getY(), u.getX())) {}

BoxCollider::BoxCollider(const Vec2 pc_, const Vec2 u_, const float width_, const float height_, const int role_):Collider(role_), pc(pc_), u(u_*(1.0/(u_.length()))), width(width_), height(height_), v(Vec2(-u.getY(), u.getX())) {}


const std::optional<StaticConstraint> BoxCollider::checkContact(Particle& collider) {
    const Vec2 diff = collider.getExpPos()-this->getPoint();
    const Vec2 u = this->getU();
    const Vec2 v = this->getV();
    const float height = this->getHeight();
    const float width = this->getWidth();

    // côtés (hors coins)

    // (x,y) écriture de la position de la particule dans le repère (u,v) centré en P
    const float x = u.dotProduct(diff);
    const float y = v.dotProduct(diff);
    if ((y>-height/2.0) && (y<height/2.0)){
        if ((x > 0)&&(x < collider.getRad()+width/2.0)){
            StaticConstraint sc;
            sc.nc = u;
            sc.pc = this->getPoint() + (width/2.0)*u;
            sc.part_ptr= &collider;
            return sc;

        } else if ((x<0) && (x > -collider.getRad()-width/2.0)){
            StaticConstraint sc;
            sc.nc = -1*u;
            sc.pc = this->getPoint() - (width/2.0)*u;
            sc.part_ptr=&collider;
            return sc;
        }
    }
    if ((x>-width/2.0) && (x<width/2.0)){
        if ((y > 0)&&(y < collider.getRad()+height/2.0) ){
            StaticConstraint sc;
            sc.nc = v;
            sc.pc = this->getPoint() + (height/2.0)*v;
            sc.part_ptr = &collider;
            return sc;

        } else if (( y <0) && (y > -collider.getRad()-height/2.0)){
            StaticConstraint sc;
            sc.nc = -1*v;
            sc.pc = this->getPoint() - (height/2.0)*v;
            sc.part_ptr=&collider;
            return sc;
        }
    }

    // coins : contraintes linéarisées originant de chaque coin
    // les autres vérifications ont été réalisées précédemment, pas besoin d'ajouter ces conditions

    const Vec2 p1 = this->getPoint()+(width/2)*u+(height/2)*v;
    const Vec2 p2 = this->getPoint()-(width/2)*u+(height/2)*v;
    const Vec2 p3 = this->getPoint()-(width/2)*u-(height/2)*v;
    const Vec2 p4 = this->getPoint()+(width/2)*u-(height/2)*v;

    const Vec2 p[4] = {p1,p2,p3,p4};

    for (int i=0; i<4; i++){
        if((p[i]-collider.getExpPos()).length()<collider.getRad()){
            StaticConstraint sc;

            // normale : vecteur unité de la différence
            sc.nc = (1/(collider.getExpPos() - p[i]).length())*(collider.getExpPos() - p[i]);
            sc.pc = p[i];
            sc.part_ptr = &collider;
            return sc;
        }
    }
    return {};
}

const Vec2 BoxCollider::getPoint() const {
    return pc;
}

const Vec2 BoxCollider::getU() const{
    return u;
}
const Vec2 BoxCollider::getV() const{
    return v;
}

const float BoxCollider::getWidth() const{
    return width;
}

const float BoxCollider::getHeight() const{
    return height;
}
