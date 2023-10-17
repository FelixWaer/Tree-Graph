#pragma once

#include <string>
#include "FlexList.h"

template <typename T, typename = void>
class Edge;

template <typename T>
class Vertex
{
public:
	Vertex() = default;
	Vertex(std::string name, T& data)
	{
		Name = name;
		Data = data;
	}
	Vertex(std::string name, T&& data)
	{
		Name = name;
		Data = data;
	}

	std::string Name;
	T Data;

	FlexList<Edge<T>> ListOfEdges;

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
	{
		std::cout << "Name: " << vertex.Name << " Data: " << vertex.Data;
		return os;
	}
};

template <typename T, typename>
class Edge
{
public:
	Edge() = default;
	Edge(Vertex<T>* firstVertex_ptr, Vertex<T>* secondVertex_ptr, std::string name, int cost)
	{
		VertexArray[0] = firstVertex_ptr;
		VertexArray[1] = secondVertex_ptr;
		Name = name;
		Cost = cost;
	}

	std::string Name;
	int Cost;

	Vertex<T>* VertexArray[2];
};


template <typename T>
class FlexGraph
{
public:
	FlexGraph(T& data)
	{
		HeadVertex = create_Vertex("A", data);
	}
	FlexGraph(T&& data)
	{
		HeadVertex = create_Vertex("A", data);
	}
	~FlexGraph()
	{
		for (size_t i = 0; i < VertexList.get_ListSize(); i++)
		{
			delete VertexList[i];
		}
	}

	Vertex<T>* create_Vertex(std::string vertexName, T& data)
	{
		Vertex<T>* tempVertex = new Vertex<T>(vertexName, data);
		VertexList.add_ElementBack(tempVertex);

		return tempVertex;
	}

	Vertex<T>* create_Vertex(std::string vertexName, T&& data)
	{
		Vertex<T>* tempVertex = new Vertex<T>(vertexName, data);
		VertexList.add_ElementBack(tempVertex);

		return tempVertex;
	}

	void create_VertexWithEdge(std::string vertexName, T& data, std::string otherVertexName, int edgeCost)
	{
		Vertex<T>* otherVertex = find_Vertex(otherVertexName);

		Vertex<T>* tempVertex = new Vertex<T>(vertexName, data);
		std::string tempEdgeName = otherVertex->Name + "-" + vertexName;
		Edge<T> newEdge(otherVertex, tempVertex, tempEdgeName, edgeCost);

		otherVertex->ListOfEdges.add_ElementBack(newEdge);
		tempVertex->ListOfEdges.add_ElementBack(newEdge);

		VertexList.add_ElementBack(tempVertex);
	}

	void create_VertexWithEdge(std::string vertexName, T&& data, std::string otherVertexName, int edgeCost)
	{
		Vertex<T>* otherVertex = find_Vertex(otherVertexName);

		Vertex<T>* tempVertex = new Vertex<T>(vertexName, data);
		std::string tempEdgeName = otherVertex->Name + "-" + vertexName;
		Edge<T> newEdge(otherVertex, tempVertex, tempEdgeName, edgeCost);

		otherVertex->ListOfEdges.add_ElementBack(newEdge);
		tempVertex->ListOfEdges.add_ElementBack(newEdge);

		VertexList.add_ElementBack(tempVertex);
	}

	Vertex<T>* find_Vertex(std::string nameOfVertex)
	{
		for (size_t i = 0; i < VertexList.get_ListSize(); i++)
		{
			if (VertexList[i]->Name == nameOfVertex)
			{
				return VertexList[i];
			}
		}
		throw std::runtime_error("Could not find Vertex");
	}
private:
	Vertex<T>* HeadVertex;
	FlexList<Vertex<T>*> VertexList;
};
