#include "CuboidShape.h"



CuboidShape::CuboidShape()
{
}


CuboidShape::~CuboidShape()
{
}

void CuboidShape::generateCuboid(int l, int b, int h)
{
	//front
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	vertex.push_back(0 - b);
	vertex.push_back(0 + h);
	vertex.push_back(0 + l);

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	vertex.push_back(0 - b);
	vertex.push_back(0 - h);
	vertex.push_back(0 + l);

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 + l  );

	//right
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );
	//back
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	vertex.push_back(0 - b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	vertex.push_back(0 - b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );
	//left
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(-1);
	normals.push_back(0);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 + l  );
	//top
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(1);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 + h  );
	vertex.push_back(0 - l  );
	//bottom
	texCoords.push_back(1);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 + l  );

	texCoords.push_back(1);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	vertex.push_back(0 - b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(0);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 - l  );

	texCoords.push_back(0);
	texCoords.push_back(1);
	normals.push_back(0);
	normals.push_back(-1);
	normals.push_back(0);
	vertex.push_back(0 + b  );
	vertex.push_back(0 - h  );
	vertex.push_back(0 + l  );
}
