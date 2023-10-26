#include <iostream>

#include "FlexGraph.h"
#include "FlexTree.h"

#define PRINT(X) std::cout << (X) << std::endl

int main()
{
	FlexTree<int> Tree(5);
	Tree.add_Child(Tree.Root, 5);
	Tree.add_ChildByID(2, 45);
	Tree.add_ChildByID(2, 11);
	Tree.add_ChildByID(4, 23);

	PRINT(Tree.find_NodeByID(5)->Data);
	PRINT(Tree.find_NodeByID(4)->Data);
}