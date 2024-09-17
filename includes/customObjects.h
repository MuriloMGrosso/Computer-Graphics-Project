#ifndef CUSTOM_OBJECTS_H
#define CUSTOM_OBJECTS_H
#include <string>

void fishHeadModel(float s);
void fishDorsalModel(float s);
void fishTailModel(float s);
void castleModel(float x, float y, float z, float scale, float rotationX, float rotationY, float rotationZ);
void aquariumModel(float s);
void baitModel(float s, float x, float y, float z, float ceil);
void skyBox(std::string filepath);

#endif
