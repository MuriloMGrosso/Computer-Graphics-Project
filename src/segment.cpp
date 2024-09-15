#include "segment.h"
#include <math.h>

Segment::Segment(Segment* target, float dist) : target(target), dist(dist) {}

void Segment::updatePosition() 
{
    float distDif;
    float xDif, yDif, zDif;
    
    if(!target) return;

    xDif = target->getX() - x;
    yDif = target->getY() - y;
    zDif = target->getZ() - z;

    distDif = sqrt(
        pow(xDif, 2) + pow(yDif, 2) + pow(zDif, 2) 
    );

    x = target->getX() - (distDif == 0 ? 0 : xDif/distDif * dist);
    y = target->getY() - (distDif == 0 ? 0 : yDif/distDif * dist);
    z = target->getZ() - (distDif == 0 ? 0 : zDif/distDif * dist);

    rotX = atan(yDif == 0 ? 0 : zDif/yDif) * (180.0 / M_PI);
    rotY = atan(zDif == 0 ? 0 : xDif/zDif) * (180.0 / M_PI);
    rotZ = atan(xDif == 0 ? 0 : yDif/xDif) * (180.0 / M_PI);
}

void Segment::translate(float x, float y, float z) 
{
    this->x += x; this->y += y; this->z += z;
}

float Segment::getX() { return x; }
float Segment::getY() { return y; }
float Segment::getZ() { return z; }

float Segment::getRotationX() { return rotX; }
float Segment::getRotationY() { return rotY; }
float Segment::getRotationZ() { return rotZ; }

void Segment::updateDist(float dif, float minDist) { this->dist = this->dist < minDist ? minDist : this->dist > 3 * minDist ? 3 * minDist: this->dist * dif; }
