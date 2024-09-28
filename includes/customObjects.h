/* 
 * Modelos de objetos customizados.
 */

#ifndef CUSTOM_OBJECTS_H
#define CUSTOM_OBJECTS_H

/*----------------------------------------------------------------------------------------*/
// DECLARACAO DAS FUNCOES

void fishHeadModel(float s);
void fishDorsalModel(float s);
void fishTailModel(float s);
void castleModel(float x, float y, float z, float scale, float rotationX, float rotationY, float rotationZ);
void aquariumModel(float s);
void baitModel(float s);
void kelpModel(int segments, float scale, float baseX, float baseY, float baseZ, float Bx[4], float By[4], float Bz[4]) ;

#endif
