#include <iostream>

#include "FlexGraph.h"
#include "FlexTree.h"

#define PRINT(X) std::cout << (X) << std::endl

int main()
{
	FlexGraph<int> Graph("Oslo", 5);
	Graph.create_VertexWithEdge("Hamar", 10, "Oslo", 10);
	Graph.create_VertexWithEdge("Bergen", 13, "Oslo", 16);
	Graph.create_VertexWithEdge("Trondheim", 26, "Oslo", 100);
	Graph.create_VertexWithEdge(Graph.get_VertexByName("Oslo"), 32);
	Graph.create_RandomVertex(Graph.get_HeadVertex(), 43);

	std::vector<Vertex<int>*> adjVertices = Graph.get_AdjacentVertices(Graph.get_HeadVertex());
	PRINT(Graph.get_GraphSize(Graph.get_HeadVertex()));
	PRINT(adjVertices.size());

	int b;
	std::cin >> b;
}