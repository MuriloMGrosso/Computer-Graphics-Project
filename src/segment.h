#ifndef FISH_SEGMENT_H
#define FISH_SEGMENT_H

class Segment{
private:
    Segment* target;
    float dist;

    float x;
    float y;
    float z;

    float rotX;
    float rotY;
    float rotZ;

public:
    Segment(Segment* target, float dist);

    void updatePosition();
    void translate(float x, float y, float z);

    float getX();
    float getY();
    float getZ();
    float getRotationX();
    float getRotationY();
    float getRotationZ();
};

#endif