#pragma once
#include "vector"

template <typename T>
struct TreeNode
{
	TreeNode(int id) : ID(id) {}
	TreeNode(T data, int id) : Data(data), ID(id){}
	~TreeNode()
	{
		std::cout << "Deleted :(" << std::endl;
	}

	T Data;
	int ID;

	TreeNode<T>* Parent = nullptr;
	std::vector<TreeNode*> ChildrenList;
};

template <typename T>
class FlexTree
{
public:
	FlexTree()
	{
		Root = nullptr;
	}
	FlexTree(T data)
	{
		Root = create_Node(data);
	}
	~FlexTree()
	{
		for (size_t i = 0; i < ListOfNodes.size(); i++)
		{
			delete ListOfNodes[i];
		}
	}

	void set_Root(TreeNode<T>* node)
	{
		Root = node;
	}

	TreeNode<T>* get_Root()
	{
		return Root;
	}

	static bool is_Root(TreeNode<T>* node)
	{
		return node->Parent == nullptr;
	}

	static TreeNode<T>* get_RootOfTree(TreeNode<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		while (node->Parent != nullptr)
		{
			node = node->Parent;
		}
		return node;
	}

	static TreeNode<T>* get_NodeParent(TreeNode<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		return node->Parent;
	}

	TreeNode<T>* get_NodeByID(int id)
	{
		for (size_t i = 0; i < ListOfNodes.size(); i++)
		{
			if (id == ListOfNodes[i]->ID)
			{
				return ListOfNodes[i];
			}
		}
		return nullptr;
	}

	static std::vector<TreeNode<T>*>& get_NodeChildren(TreeNode<T>* node)
	{
		return node->ChildrenList;
	}

	std::vector<TreeNode<T>*> get_Tree(TreeNode<T>* node)
	{
		std::vector<TreeNode<T>*> tempVector;

		if (node != nullptr)
		{
			get_AllNodes(tempVector, node);

			return tempVector;
		}

		tempVector.emplace_back(node);

		return tempVector;
	}

	TreeNode<T>* create_Child(TreeNode<T>* parentNode, T data)
	{
		TreeNode<T>* tempNode = create_Node(data);
		tempNode->Parent = parentNode;

		if (parentNode != nullptr)
		{
			parentNode->ChildrenList.emplace_back(tempNode);
		}

		return tempNode;
	}

	TreeNode<T>* create_Child(TreeNode<T>* parentNode)
	{
		TreeNode<T>* tempNode = create_Node();
		tempNode->Parent = parentNode;

		if (parentNode != nullptr)
		{
			parentNode->ChildrenList.emplace_back(tempNode);
		}

		return tempNode;
	}

	TreeNode<T>* create_ChildByID(int id, T data)
	{
		TreeNode<T>* tempNode = create_Node(data);
		TreeNode<T>* parentNode = get_NodeByID(id);

		tempNode->Parent = parentNode;
		parentNode->ChildrenList.emplace_back(tempNode);

		return tempNode;
	}

	TreeNode<T>* create_RandomChild(TreeNode<T>* root, int numberOfRandom)
	{
		srand(time(NULL));

		if (root == nullptr)
		{
			root = create_Child(nullptr);
			numberOfRandom--;
		}

		std::vector<TreeNode<T>*> tempVector = get_Tree(root);
		TreeNode<T>* tempNode;
		TreeNode<T>* newNode;
		for (int i = 0; i < numberOfRandom; i++)
		{
			tempNode = tempVector[rand() % tempVector.size()];
			newNode = create_Child(tempNode);
			tempVector.emplace_back(newNode);
		}

		return root;
	}

	void delete_Node(TreeNode<T>* node)
	{
		if (node->Parent != nullptr)
		{
			remove_FromParentVector(node);

			for (TreeNode<T>* child : node->ChildrenList)
			{
				node->Parent->ChildrenList.emplace_back(child);
				child->Parent = node->Parent;
			}
		}

		delete node;
	}

	void delete_NodeAndChildren(TreeNode<T>* node)
	{
		if (node->Parent != nullptr)
		{
			remove_FromParentVector(node);
		}
		deleting_NodeAndChildren(node);
	}

	int get_TreeSize(TreeNode<T>* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int treeSize = 0;

		calculate_TreeSize(node, treeSize);

		return treeSize;
	}

	int get_TreeDepth(TreeNode<T>* node)
	{
		return calculate_DepthOfTree(node);
	}

	bool is_Empty() const
	{
		return Root == nullptr;
	}

	static bool is_Empty(TreeNode<T>* node)
	{
		return node == nullptr;
	}

	static bool is_Leaf(TreeNode<T>* node)
	{
		return node->ChildrenList.empty() == true;
	}

private:
	TreeNode<T>* Root;
	int IDCounter = 0;

	std::vector<TreeNode<T>*> ListOfNodes;

	TreeNode<T>* create_Node()
	{
		IDCounter++;
		TreeNode<T>* tempNode = new TreeNode<T>(IDCounter);
		ListOfNodes.emplace_back(tempNode);

		return tempNode;
	}

	TreeNode<T>* create_Node(T data)
	{
		IDCounter++;
		TreeNode<T>* tempNode = new TreeNode<T>(data, IDCounter);
		ListOfNodes.emplace_back(tempNode);

		return tempNode;
	}

	void calculate_TreeSize(TreeNode<T>* node, int& treeSize)
	{
		treeSize++;
		for (TreeNode<T>* child : node->ChildrenList)
		{
			calculate_TreeSize(child, treeSize);
		}
	}

	int calculate_DepthOfTree(TreeNode<T>* node)
	{
		int depth = 0;

		for (TreeNode<T>* node : node->ChildrenList)
		{
			int tempDepth = calculate_DepthOfTree(node);
			if (depth < tempDepth)
			{
				depth = tempDepth;
			}
		}
		return depth + 1;
	}

	//This is my Depth traversal implementation in trees.
	//I use it here to get all the Nodes that is in the subtree where node is the root.
	//It puts all the nodes in a vector and the vector then gets returned in the get_Tree function
	static void get_AllNodes(std::vector<TreeNode<T>*>& vector, TreeNode<T>* node)
	{
		for (TreeNode<T>* child : node->ChildrenList)
		{
			get_AllNodes(vector, child);
		}

		vector.emplace_back(node);
	}

	void deleting_NodeAndChildren(TreeNode<T>* node)
	{
		for (TreeNode<T>* child : node->ChildrenList)
		{
			deleting_NodeAndChildren(child);
		}
		delete node;
	}

	void remove_FromParentVector(TreeNode<T>* node)
	{
		TreeNode<T>* parent = node->Parent;

		for (size_t i = 0; i < parent->ChildrenList.size(); i++)
		{
			if (parent->ChildrenList[i] == node)
			{
				parent->ChildrenList.erase(parent->ChildrenList.begin() + i);
				break;
			}
		}
	}
};
