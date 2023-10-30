#pragma once

#include <string>
#include "vector"

template <typename T, typename = void>
class Edge;

template <typename T>
class Vertex
{
public:
	Vertex() = default;
	Vertex(int id)
	{
		ID = id;
	}
	Vertex(std::string name, int id, T& data)
	{
		Name = name;
		ID = id;
		Data = data;
	}
	Vertex(std::string name, int id, T&& data)
	{
		Name = name;
		ID = id;
		Data = data;
	}

	std::string Name;
	int ID;
	T Data;

	std::vector<Edge<T>> ListOfEdges;

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
	Edge(Vertex<T>* firstVertex, Vertex<T>* secondVertex, const std::string& name, int cost)
	{
		FirstVertex = firstVertex;
		SecondVertex = secondVertex;
		Name = name;
		Cost = cost;
	}

	std::string Name;
	int Cost;

	Vertex<T>* FirstVertex;
	Vertex<T>* SecondVertex;
};


template <typename T>
class FlexGraph
{
public:
	FlexGraph()
	{
		HeadVertex = nullptr;
	}
	FlexGraph(const std::string& name, T& data)
	{
		HeadVertex = create_Vertex(name, data);
	}
	FlexGraph(const std::string& name, T&& data)
	{
		HeadVertex = create_Vertex(name, data);
	}
	~FlexGraph()
	{
		for (size_t i = 0; i < VertexList.size(); i++)
		{
			delete VertexList[i];
		}
	}

	void set_HeadVertex(Vertex<T>* vertex)
	{
		HeadVertex = vertex;
	}

	Vertex<T>* get_HeadVertex()
	{
		return HeadVertex;
	}

	Vertex<T>* create_Vertex()
	{
		Vertex<T>* tempVertex = new Vertex<T>(IDCounter);
		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_Vertex(const std::string& vertexName, T& data)
	{
		Vertex<T>* tempVertex = new Vertex<T>(vertexName, IDCounter, data);
		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_Vertex(const std::string& vertexName, T&& data)
	{
		Vertex<T>* tempVertex = new Vertex<T>(vertexName, IDCounter, data);
		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_VertexWithEdge(Vertex<T>* otherVertex,  int edgeCost)
	{
		Vertex<T>* tempVertex = new Vertex<T>(IDCounter);
		std::string tempEdgeName = " ";

		tempVertex->ListOfEdges.emplace_back(Edge<T>(tempVertex, otherVertex, tempEdgeName, edgeCost));
		otherVertex->ListOfEdges.emplace_back(Edge<T>(otherVertex, tempVertex, tempEdgeName, edgeCost));

		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_VertexWithEdge(const std::string& vertexName, T& data, const std::string& otherVertexName, int edgeCost)
	{
		Vertex<T>* otherVertex = get_VertexByName(otherVertexName);

		Vertex<T>* tempVertex = new Vertex<T>(vertexName, IDCounter, data);
		std::string tempEdgeName = vertexName + "-" + otherVertex->Name;

		tempVertex->ListOfEdges.emplace_back(Edge<T>(tempVertex, otherVertex, tempEdgeName, edgeCost));
		otherVertex->ListOfEdges.emplace_back(Edge<T>(otherVertex, tempVertex, tempEdgeName, edgeCost));

		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_VertexWithEdge(const std::string& vertexName, T&& data, const std::string& otherVertexName, int edgeCost)
	{
		Vertex<T>* otherVertex = get_VertexByName(otherVertexName);
		Vertex<T>* tempVertex = new Vertex<T>(vertexName, IDCounter, data);

		std::string tempEdgeName = vertexName + "-" + otherVertex->Name;

		tempVertex->ListOfEdges.emplace_back(Edge<T>(tempVertex, otherVertex, tempEdgeName, edgeCost));
		otherVertex->ListOfEdges.emplace_back(Edge<T>(otherVertex, tempVertex, tempEdgeName, edgeCost));

		VertexList.emplace_back(tempVertex);
		IDCounter++;

		return tempVertex;
	}

	Vertex<T>* create_RandomVertex(Vertex<T>* vertex, int numberOfRandom)
	{
		srand(time(NULL));
		if (vertex == nullptr)
		{
			 vertex = create_Vertex();
			 numberOfRandom--;
		}

		for (int i = 0; i < numberOfRandom; i++)
		{
			create_VertexWithEdge(VertexList[rand() % VertexList.size()], rand());
		}

		return vertex;
	}

	void create_Edge(const std::string& firstVertexName, const std::string& secondVertexName, int edgeCost)
	{
		Vertex<T>* firstVertex = get_VertexByName(firstVertexName);
		Vertex<T>* secondVertex = get_VertexByName(secondVertexName);

		std::string tempEdgeName = firstVertex->Name + "-" + secondVertex->Name;

		firstVertex->ListOfEdges.emplace_back(Edge<T>(firstVertex, secondVertex, tempEdgeName, edgeCost));
		secondVertex->ListOfEdges.emplace_back(Edge<T>(secondVertex, firstVertex, tempEdgeName, edgeCost));
	}

	void delete_Vertex(Vertex<T>* vertex)
	{
		for (Edge<T>& edge : vertex->ListOfEdges)
		{
			delete_Edge(edge);
		}
		for (size_t i = 0; i < VertexList.size(); i++)
		{
			if (VertexList[i] == vertex)
			{
				VertexList.erase(VertexList.begin() + i);
			}
		}

		delete vertex;
	}

	void delete_Edge(Edge<T> edge)
	{
		Vertex<T>* firstVertex = edge.FirstVertex;
		Vertex<T>* secondVertex = edge.SecondVertex;
		for (size_t i = 0; i < secondVertex->ListOfEdges.size(); i++)
		{
			if (secondVertex->ListOfEdges[i].Name == edge.Name)
			{
				secondVertex->ListOfEdges.erase(secondVertex->ListOfEdges.begin() + i);
				break;
			}
		}
		for (size_t i = 0; i < firstVertex->ListOfEdges.size(); i++)
		{
			if (firstVertex->ListOfEdges[i].Name == edge.Name)
			{
				firstVertex->ListOfEdges.erase(firstVertex->ListOfEdges.begin() + i);
				break;
			}
		}
	}

	Vertex<T>* get_VertexByName(const std::string& nameOfVertex)
	{
		for (size_t i = 0; i < VertexList.size(); i++)
		{
			if (VertexList[i]->Name == nameOfVertex)
			{
				return VertexList[i];
			}
		}
		return nullptr;
	}

	std::vector<Vertex<T>*> get_AdjacentVertices(Vertex<T>* vertex)
	{
		std::vector<Vertex<T>*> tempVector;

		for (Edge<T>& edge : vertex->ListOfEdges)
		{
			tempVector.emplace_back(edge.SecondVertex);
		}

		return tempVector;
	}

	std::vector<Vertex<T>*> get_Vertices() const
	{
		return VertexList;
	}

	size_t get_GraphSize(Vertex<T>* vertex)
	{
		std::vector<Vertex<T>*> tempVector;
		calculate_GraphSize(vertex, tempVector);

		return tempVector.size();
	}

	bool is_Empty()
	{
		return VertexList.size() == 0;
	}

private:
	Vertex<T>* HeadVertex;
	std::vector<Vertex<T>*> VertexList;
	int IDCounter = 1;

	//This is my Depth first search traversal implementation in my graph.
	//I use it to calculate in the graph how many vertices are connected together in the graph.
	void calculate_GraphSize(Vertex<T>* vertex, std::vector<Vertex<T>*>& vector)
	{
		vector.emplace_back(vertex);
		for (Edge<T>& edge : vertex->ListOfEdges)
		{
			bool visited = false;
			for (Vertex<T>* vertex : vector)
			{
				if (edge.SecondVertex ==  vertex)
				{
					visited = true;
				}
			}
			if (visited == false)
			{
				calculate_GraphSize(edge.SecondVertex, vector);
			}
		}
	}
};
