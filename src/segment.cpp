#include "../includes/libpack.h"
#include <cmath>
#include <iostream>

Segment::Segment(Segment* target, float dist, float lerp) : target(target), dist(dist), lerp(lerp) {}
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
    
    x = lerp * (target->getX() - (distDif == 0 ? 0 : xDif/distDif * dist)) + (1 - lerp) * x;
    y = lerp * (target->getY() - (distDif == 0 ? 0 : yDif/distDif * dist)) + (1 - lerp) * y;
    z = lerp * (target->getZ() - (distDif == 0 ? 0 : zDif/distDif * dist)) + (1 - lerp) * z;

    rotY = atan2(xDif, zDif) * (180.0 / M_PI);
    rotXZ = -asin(distDif == 0 ? 0 : yDif/distDif) * (180.0 / M_PI);
}

void Segment::translate(float x, float y, float z) 
{
    this->x += x; 
    this->y += y; 
    this->z += z;
}

float Segment::getX() { return x; }
float Segment::getY() { return y; }
float Segment::getZ() { return z; }

void Segment::clampX(float min, float max) { x = x < min ? min : x > max ? max : x; }
void Segment::clampY(float min, float max) { y = y < min ? min : y > max ? max : y; }
void Segment::clampZ(float min, float max) { z = z < min ? min : z > max ? max : z; }

float Segment::getRotationY() { return rotY; }
float Segment::getRotationXZ() { return rotXZ; }