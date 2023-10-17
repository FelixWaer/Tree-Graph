#pragma once

#include <string>
#include "FlexList.h"

class Vertex;

class Edge
{
public:
	Edge() = default;
	Edge(Vertex* firstVertex_ptr, Vertex* secondVertex_ptr, const char* name, int cost)
	{
		VertexArray[0] = firstVertex_ptr;
		VertexArray[1] = secondVertex_ptr;
		Name = name;
		Cost = cost;
	}

	std::string Name;
	int Cost;

	Vertex* VertexArray[2];
};

class Vertex
{
public:
	Vertex() = default;
	Vertex(const char* name, int data)
	{
		Name = name;
		Data = data;
	}

	std::string Name;
	int Data;

	FlexList<Vertex> NeighborVertices;
	FlexList<Edge> ListOfEdges;

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
	{
		std::cout << "Name: " << vertex.Name << " Data: " << vertex.Data;
		return os;
	}
};

class FlexGraph
{
public:
	FlexGraph(int data)
	{
		HeadVertex = new Vertex("A", data);
	}
	~FlexGraph()
	{
		delete HeadVertex;
	}

	Vertex* HeadVertex;

	void add_Vertex(const char* vertexName, int data, const char* edgeName, int cost);
	void add_Edge(Vertex* firstVertex_ptr, Vertex* secondVertex_ptr);

private:	
};
