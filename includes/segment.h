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
		float rotX, rotY, rotZ;		// Rotacoes (graus)

	public:
    	Segment(Segment* target, float dist);		// Construtor

		void updatePosition();		// Atualiza a posicao do segmento
		void translate(float x, float y, float z);		// Movimenta o segmento

		float getX();	// Retorna coordenada X
		float getY();	// Retorna coordenada Y
		float getZ();	// Retorna coordenada Z

		void clampX(float min, float max);		// Define o lower e upper bounds de X 
		void clampY(float min, float max);		// Define o lower e upper bounds de Y
		void clampZ(float min, float max);		// Define o lower e upper bounds de Z
		
		void multClampedDist(float value, float minDist, float maxDist);	// Multiplica a distancia dentro dos limites permitidos
		
		float getRotationX();	// Retorna rotacao em X
		float getRotationY();	// Retorna rotacao em Y
		float getRotationZ();	// Retorna rotacao em Z
};

#endif
