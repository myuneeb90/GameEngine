#ifndef LINESHAPES_H
#define LINESHAPES_H

class LineShapes
{
	public:
			static Mesh* CreateLine(Vector3f point1, Vector3f point2);
			static Mesh* CreateQuad(float size);
			static Mesh* CreateCircle(float radius, int sides);
			static Mesh* CreateCube(float size);
			static Mesh* CreateCylinder(float bottomRadius, float topRadius, float height, int sides);
			
};

#endif