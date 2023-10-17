#pragma once
#include <iostream>

template <typename T>
class Node
{
public:
	T Data;
	Node* NextNode;

	Node(const T& data, Node* nextNode) : Data(data), NextNode(nextNode) {}
	Node(const T&& data, Node* nextNode) : Data(data), NextNode(nextNode) {}
	Node(const T& data) : Data(data), NextNode(nullptr) {}
	Node(const T&& data) : Data(data), NextNode(nullptr) {}
};

template <typename T>
class FlexList
{
public:
	FlexList()
	{
		HeadNode = nullptr;
		NumberOfElements = 0;
	}

	FlexList(const T& data)
	{
		HeadNode = new Node<T>(data, nullptr);
		NumberOfElements = 1;
	}

	FlexList(const T&& data)
	{
		HeadNode = new Node<T>(data, nullptr);
		NumberOfElements = 1;
	}

	~FlexList()
	{
		Node<T>* tempNode;
		while (HeadNode != nullptr)
		{
			tempNode = HeadNode;
			HeadNode = HeadNode->NextNode;
			delete tempNode;
		}
	}
	
	void add_ElementBack(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode);
	}

	void add_ElementBack(const T&& data)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode);
	}

	void add_ElementFront(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode, 1);
	}

	void add_ElementFront(const T&& data)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode, 1);
	}

	void add_Element(const T& data, size_t listPosition)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode, listPosition);
	}

	void add_Element(const T&& data, size_t listPosition)
	{
		Node<T>* newNode = new Node<T>(data);

		adding_Element(newNode, listPosition);
	}

	void remove_Element(size_t listPosition)
	{
		removing_Element(listPosition);
	}

	void remove_ElementFront()
	{
		removing_Element(1);
	}

	void remove_ElementBack()
	{
		remove_Element(NumberOfElements);
	}

	size_t get_ListSize() const
	{
		return NumberOfElements;
	}

	T& operator[](size_t listPosition)
	{
		if (listPosition >= NumberOfElements)
		{
			throw std::runtime_error("Out of range of the list");
		}

		Node<T>* tempNode;
		tempNode = HeadNode;
		for (size_t i = 0; i < listPosition; i++)
		{
			tempNode = tempNode->NextNode;
		}
		return tempNode->Data;
	}

private:
	Node<T>* HeadNode;
	size_t NumberOfElements = 0;

	void adding_Element(Node<T>* newNode, size_t listPosition = 0)
	{
		NumberOfElements++;

		if (listPosition > NumberOfElements)
		{
			throw std::runtime_error("List is out of bounds!");
		}

		if (listPosition == 0)
		{
			if (HeadNode == nullptr)
			{
				HeadNode = newNode;

				return;
			}

			Node<T>* nextNode = HeadNode;
			while (nextNode->NextNode != nullptr)
			{
				nextNode = nextNode->NextNode;
			}

			nextNode->NextNode = newNode;

			return;
		}
		if (listPosition == 1)
		{
			newNode->NextNode = HeadNode;
			HeadNode = newNode;

			return;
		}

		Node<T>* tempNode = HeadNode;
		Node<T>* previousTempNode = tempNode;
		for (size_t i = 1; i < listPosition; i++)
		{
			previousTempNode = tempNode;
			tempNode = tempNode->NextNode;
		}

		previousTempNode->NextNode = newNode;
		newNode->NextNode = tempNode;
	}

	void removing_Element(size_t listPosition)
	{
		if (HeadNode == nullptr)
		{
			return;
		}

		NumberOfElements--;

		if (listPosition == 1)
		{
			Node<T>* newHeadNode = HeadNode->NextNode;
			delete HeadNode;
			HeadNode = newHeadNode;
			return;
		}

		Node<T>* tempNode = HeadNode;
		Node<T>* previousTempNode = tempNode;

		for (size_t i = 1; i < listPosition; i++)
		{
			previousTempNode = tempNode;
			tempNode = tempNode->NextNode;
		}
		previousTempNode->NextNode = tempNode->NextNode;
		delete tempNode;
	}
};
