#include <iostream>

#include "FlexGraph.h"

#define PRINT(X) std::cout << (X) << std::endl

int main()
{
	FlexGraph<int> test(5);
	test.create_VertexWithEdge("Bergen", 11, "A", 2);
	test.create_VertexWithEdge("Oslo", 123, "Bergen", 20);

	PRINT(test.find_Vertex("Oslo")->ListOfEdges[0].Name);
}