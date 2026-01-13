#include "boxcollider.h"

BoxCollider::BoxCollider(Vec2 pc_, Vec2 u_, float width_, float height_):Collider(), pc(pc_), u(u_*(1.0/(u_.length()))), width(width_), height(height_), v(Vec2(-u.getY(), u.getX())), isKiller(false) {}


std::optional<StaticConstraint> BoxCollider::checkContact(Particle& collider) {
    Vec2 diff = collider.getExpPos()-this->getCenter();
    Vec2 u = this->getU();
    Vec2 v = this->getV();
    float height = this->getHeight();
    float width = this->getWidth();

    // côtés (hors coins)

    // (x,y) écriture de la position de la particule dans le repère (u,v) centré en P
    float x = u.dotProduct(diff);
    float y = v.dotProduct(diff);
    if ((x > 0)&&(x < collider.getRad()+width/2.0)  &&  (y>-height/2.0) && (y<height/2.0)){
        StaticConstraint sc;
        sc.nc = u;
        sc.pc = this->getCenter() + (width/2.0)*u;
        sc.part_ptr=&collider;
        return sc;

    } else if ((x<0) && (x > -collider.getRad()-width/2.0)&&  (y>-height/2.0) && (y<height/2.0)){
        StaticConstraint sc;
        sc.nc = -1*u;
        sc.pc = this->getCenter() - (width/2.0)*u;
        sc.part_ptr=&collider;
        return sc;
    }
    if ((y > 0)&&(y < collider.getRad()+height/2.0) &&  (x>-width/2.0) && (x<width/2.0)){
        StaticConstraint sc;
        sc.nc = v;
        sc.pc = this->getCenter() + (height/2.0)*v;
        sc.part_ptr=&collider;
        return sc;

    } else if (( y <0) && (y > -collider.getRad()-height/2.0)&&  (x>-width/2.0) && (x<width/2.0)){
        StaticConstraint sc;
        sc.nc = -1*v;
        sc.pc = this->getCenter() - (height/2.0)*v;
        sc.part_ptr=&collider;
        return sc;
    }

    // coins : contraintes linéarisées originant de chaque coin
    // les autres vérifications ont été réalisées précédemment

    Vec2 p1 = this->getCenter()+(width/2)*u+(height/2)*v;
    Vec2 p2 = this->getCenter()-(width/2)*u+(height/2)*v;
    Vec2 p3 = this->getCenter()-(width/2)*u-(height/2)*v;
    Vec2 p4 = this->getCenter()+(width/2)*u-(height/2)*v;

    Vec2 p[4] = {p1,p2,p3,p4};

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

Vec2 BoxCollider::getCenter() {
    return pc;
}

Vec2 BoxCollider::getU(){
    return u;
}
Vec2 BoxCollider::getV(){
    return v;
}

float BoxCollider::getWidth(){
    return width;
}

float BoxCollider::getHeight(){
    return height;
}

bool BoxCollider::canDestroy(){
    return isKiller;
}
