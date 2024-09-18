/* 
 * Implementacao de um segmento com
 * Inverse Kinematics.
 */

#ifndef FISH_SEGMENT_H
#define FISH_SEGMENT_H

class Segment
{
	private:
		Segment* target;	// Segmento alvo
		float dist;		// Distancia ate o alvo

		float x, y, z;		// Coordenadas
		float rotY, rotXZ;		// Rotacoes (graus)
		float lerp;

	public:
    	Segment(Segment* target, float dist, float lerp);		// Construtor

		void updatePosition();		// Atualiza a posicao do segmento
		void translate(float x, float y, float z);		// Movimenta o segmento

		float getX();	// Retorna coordenada X
		float getY();	// Retorna coordenada Y
		float getZ();	// Retorna coordenada Z

		void clampX(float min, float max);		// Define o lower e upper bounds de X 
		void clampY(float min, float max);		// Define o lower e upper bounds de Y
		void clampZ(float min, float max);		// Define o lower e upper bounds de Z
		
		float getRotationY();	// Retorna rotacao em X
		float getRotationXZ();	// Retorna rotacao em X e Z
};

#endif
