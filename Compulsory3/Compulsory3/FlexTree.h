#pragma once
#include "Code Files/FlexList.h"

template <typename T>
struct TreeNode
{
	TreeNode(T data)
	{
		Data = data;
	}

	T Data;
	FlexList<TreeNode*> ChildrenList;
};

template <typename T>
class FlexTree
{
public:
	FlexTree(T data)
	{
		Root = new TreeNode<T>(data);
	}

	

private: 	
	TreeNode<T>* Root;
};
