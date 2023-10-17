#include <iostream>

#include "FlexGraph.h"

#define PRINT(X) std::cout << (X) << std::endl

int main()
{
	FlexGraph test(5);
	test.add_Vertex("B", 9, "ab", 100);

	PRINT(test.HeadVertex->NeighborVertices[0]);
}