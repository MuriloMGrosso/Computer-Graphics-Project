#ifndef FISH_SEGMENT_H
#define FISH_SEGMENT_H

class Segment
{
	private:
		Segment* target;
		float dist;

		float x, y, z;
		float rotX, rotY, rotZ;

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

		void updateDist(float dist, float minDist);
};

#endif
