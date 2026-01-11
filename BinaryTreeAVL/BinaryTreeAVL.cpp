#include "BinaryTreeAVL.h"
#include <algorithm>


//Node

Node* Node::Get_MinNode(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->left == nullptr)
	{
		return node;
	}

	return Get_MinNode(node->left);
}

void Node::Remove(Node* node, int nodeValue)
{
	if (node == nullptr)
		return;

	if (node->value < nodeValue)
	{
		//Right side
		if (node->right == nullptr)
			return;

		Remove(node->right, nodeValue);
		return;
	}
	else if (node->value > nodeValue)
	{
		//Left side
		if (node->left == nullptr)
			return;

		Remove(node->left, nodeValue);
		return;
	}

	std::cout << "Found node: " << node->value << "\n";
	Node* parent = node->parent;

	if (parent == nullptr)
	{
		std::cout << "error could not find parent of node: " << node->value << "\n";
		return;
	}


	if (node->left != nullptr && node->right != nullptr) //Two children
	{
		std::cout << "Two child\n";
		Node* nodeToDelete = Get_MinNode(node->right);

		if (nodeToDelete->right != nullptr) //NodeToDelete can only have right child cause its the furthest left
		{
			Node* nodeToDeleteParent = nodeToDelete->parent;
			Node* nodeChild = nodeToDelete->right;

			nodeToDeleteParent->left = nodeChild;

			delete nodeToDelete;
			return;
		}

		if (nodeToDelete->parent->value < nodeToDelete->value)
		{
			nodeToDelete->parent->right = nullptr;
			delete nodeToDelete;
			return;
		}
		else
		{
			nodeToDelete->parent->left = nullptr;
			delete nodeToDelete;
			return;
		}
	}
	else if (node->left != nullptr || node->right != nullptr) //One child
	{
		std::cout << "One child\n";
		if (node->left)
		{
			if (node->value < parent->value)
			{
				//right side
				parent->right = node->left;
				node->left->parent = parent;
				delete node;
				return;
			}
			else
			{
				//left side
				parent->left = node->left;
				node->left->parent = parent;
				delete node;
				return;
			}
		}
		else
		{
			if (node->value > parent->value)
			{
				//right side
				parent->right = node->right;
				node->right->parent = parent;
				delete node;
				return;
			}
			else
			{
				//left side
				parent->left = node->right;
				node->right->parent = parent;
				delete node;
				return;
			}
		}
	}
	else if (node->left == nullptr && node->right == nullptr)
	{
		std::cout << "Zero child\n";
		//No children
		if (parent->value < node->value)
		{
			parent->right = nullptr;
			delete node;
		}
		else
		{
			parent->left = nullptr;
			delete node;
		}
	}
}

Node* Node::Search(Node* node, int nodeValue)
{
	if (node == nullptr)
		return nullptr;

	if (node->value < nodeValue)
		return Search(node->right, nodeValue);
	if (node->value > nodeValue)
		return Search(node->left, nodeValue);
	
	return node;
}

int Node::Get_NodeHeight(Node* node)
{
	if (node == nullptr)
		return -1;

	int leftHeight = Get_NodeHeight(node->left);
	int rightHeight = Get_NodeHeight(node->right);

	node->nodeHeight = (leftHeight > rightHeight) ? (leftHeight) : (rightHeight) + 1;

	return node->nodeHeight;
}

int Node::Get_NodeBalance(Node* node)
{
	if (node == nullptr)
		return 0;

	if (node->left && node->right)
	{
		node->nodeBalance = (node->left->nodeHeight - node->right->nodeHeight);
	}
	else if (!node->left && node->right)
	{
		node->nodeBalance = (-1 - node->right->nodeHeight);
	}
	else if (node->left && !node->right)
	{
		node->nodeBalance = (node->left->nodeHeight - -1);
	}
	else
	{
		node->nodeBalance = -1 - -1;
	}

	return node->nodeBalance;
}

//Node rotation

Node* Node::RotateLeft(Node* unbalancedNode)
{
	Node* pivotNode = unbalancedNode->right;

	if (pivotNode == nullptr)
		return unbalancedNode;

	Node* pivotNodeChild = pivotNode->left;

	//Make rotation
	pivotNode->left = unbalancedNode;

	if (pivotNodeChild != nullptr)
	{
		unbalancedNode->right = pivotNodeChild;
		pivotNodeChild->parent = unbalancedNode;
	}
	else
	{
		unbalancedNode->right = nullptr;
	}

	if (unbalancedNode->parent != nullptr)
	{
		Node* parent = unbalancedNode->parent;
		pivotNode->parent = parent;

		if (parent->left == unbalancedNode)
		{
			parent->left = pivotNode;
		}
		else
		{
			parent->right = pivotNode;
		}
	}
	else if (unbalancedNode->parent == nullptr)
	{
		pivotNode->parent = nullptr;
	}

	unbalancedNode->parent = pivotNode;

	return pivotNode;
}

Node* Node::RotateRight(Node* unbalancedNode)
{
	Node* pivotNode = unbalancedNode->left;

	if (pivotNode == nullptr)
		return unbalancedNode;

	Node* pivotNodeChild = pivotNode->right;

	if (pivotNode == nullptr)
		return unbalancedNode;


	//Make rotation
	pivotNode->right = unbalancedNode;

	if (pivotNodeChild != nullptr)
	{
		unbalancedNode->left = pivotNodeChild;
		pivotNodeChild->parent = unbalancedNode;
	}
	else
	{
		unbalancedNode->left = nullptr;
	}

	if (unbalancedNode->parent != nullptr)
	{
		Node* parent = unbalancedNode->parent;
		pivotNode->parent = parent;

		if (parent->left == unbalancedNode)
		{
			parent->left = pivotNode;
		}
		else
		{
			parent->right = pivotNode;
		}
	}
	else if (unbalancedNode->parent == nullptr)
	{
		pivotNode->parent = nullptr;
	}

	unbalancedNode->parent = pivotNode;

	return pivotNode;
}


//Update node balance and height,

Node* Node::UpdateNode(Node* node)
{
	if (node == nullptr)
		return nullptr;

	node->nodeHeight = Get_NodeHeight(node);
	node->nodeBalance = Get_NodeBalance(node);


	if (node->nodeBalance > 1)
	{
		if (node->left != nullptr && node->left->nodeBalance < 0)
		{
			node->left = RotateLeft(node->left);
		}

		node = RotateRight(node);
	}

	if (node->nodeBalance < -1)
	{
		if (node->right != nullptr && node->right->nodeBalance > 0)
		{
			node->right = RotateRight(node->right);
		}

		node = RotateLeft(node);
	}

	node->nodeHeight = Get_NodeHeight(node);
	node->nodeBalance = Get_NodeBalance(node);

	return node;
}


//Binary tree

void BinaryTreeAVL::deallocateMemory(Node* root)
{
	if (root == nullptr) return;

	deallocateMemory(root->left);
	deallocateMemory(root->right);

	delete root;
}

void BinaryTreeAVL::Insert(int nodeValue)
{
	if (!root)
	{
		root = new Node(nodeValue, nullptr, nullptr, nullptr);
		return;
	}

	Node* node = root;

	while (true)
	{
		if (nodeValue == node->value)
		{
			return;
		}

		if (node->value > nodeValue)
		{
			//Left side
			if (!node->left)
			{
				node->left = new Node(nodeValue, node, nullptr, nullptr);
				node = node->left;
				break;
			}
			node = node->left;
		}
		else if (node->value < nodeValue)
		{
			//Right side
			if (!node->right)
			{
				node->right = new Node(nodeValue, node, nullptr, nullptr);
				node = node->right;
				break;
			}
			node = node->right;
		}
	}

	while (node != nullptr)
	{
		// Update or rebalance this node and its subtree.
		Node* updated = node->UpdateNode(node);

		// If this subtree root has no parent, it's the overall root.
		if (updated->parent == nullptr)
			root = updated;

		// Move upward: parent may have changed due to rotation,
		// so always use updated->parent, not the old saved parent.
		node = updated->parent;
	}

	numberOfNodes++;

}

void BinaryTreeAVL::DeleteNode(int nodeValue)
{
	root->Remove(root, nodeValue);
}