#include "FlexGraph.h"

void FlexGraph::add_Vertex(const char* vertexName, int data, const char* edgeName, int cost)
{
	Vertex* newVertex = new Vertex(vertexName, data);
	Edge newEdge(HeadVertex, newVertex, edgeName, cost);

	HeadVertex->NeighborVertices.add_ElementBack(*newVertex);
	HeadVertex->ListOfEdges.add_ElementBack(newEdge);
	newVertex->ListOfEdges.add_ElementBack(newEdge);
}
