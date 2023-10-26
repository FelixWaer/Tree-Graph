#pragma once
#include "FlexVector.h"

template <typename T>
struct TreeNode
{
	TreeNode(int id) : ID(id) {}
	TreeNode(T data, int id) : Data(data), ID(id){}
	~TreeNode()
	{
		//std::cout << "Deleted :(" << std::endl;
	}

	T Data;
	int ID;

	FlexVector<TreeNode*> ChildrenList;
};

template <typename T>
class FlexTree
{
public:
	FlexTree()
	{
		Root = create_Node();
	}
	FlexTree(T data)
	{
		Root = create_Node(data);
	}
	~FlexTree()
	{
		for (size_t i = 0; i < ListOfNodes.get_NumberOfElements(); i++)
		{
			delete ListOfNodes[i];
		}
	}

	TreeNode<T>* Root;

	TreeNode<T>* add_Child(TreeNode<T>* parentNode, T data)
	{
		TreeNode<T>* tempNode = create_Node(data);
		parentNode->ChildrenList.add_ToLast(tempNode)	;

		return tempNode;
	}

	TreeNode<T>* add_ChildByID(int id, T data)
	{
		TreeNode<T>* tempNode = create_Node(data);
		find_NodeByID(id)->ChildrenList.add_ToLast(tempNode);

		return tempNode;
	}

	TreeNode<T>* find_NodeByID(int id)
	{
		for (size_t i = 0; i < ListOfNodes.get_NumberOfElements(); i++)
		{
			if (id == ListOfNodes[i]->ID)
			{
				return ListOfNodes[i];
			}
		}
		return nullptr;
	}

	size_t get_TreeSize() const
	{
		return ListOfNodes.get_NumberOfElements();
	}

private:
	int IDCounter = 0;
	FlexVector<TreeNode<T>*> ListOfNodes;

	TreeNode<T>* create_Node()
	{
		IDCounter++;
		TreeNode<T>* tempNode = new TreeNode<T>(IDCounter);
		ListOfNodes.add_ToLast(tempNode);

		return tempNode;
	}

	TreeNode<T>* create_Node(T data)
	{
		IDCounter++;
		TreeNode<T>* tempNode = new TreeNode<T>(data, IDCounter);
		ListOfNodes.add_ToLast(tempNode);

		return tempNode;
	}
};

