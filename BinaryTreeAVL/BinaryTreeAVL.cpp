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

void Node::Add(Node* node, int nodeValue)
{
	if (node == nullptr)
		return;

	if (node->value < nodeValue)
	{
		//Right side
		if (node->right == nullptr)
		{
			node->right = new Node(nodeValue, node, nullptr, nullptr);
			UpdateNode(node->right);
			std::cout << "Right node: " << node->right->value << " of node: " << node->right->parent->value << "\n";
			return;
		}
		else
		{
			Add(node->right, nodeValue);
			return;
		}
	}
	else if (node->value == nodeValue)
	{
		std::cout << "Value already in binary tree!\n";
		return;
	}
	else
	{
		//Left side
		if (node->left == nullptr)
		{
			Node* parent = node;
			node->left = new Node(nodeValue, parent, nullptr, nullptr);
			UpdateNode(node->left);
			std::cout << "Left node: " << node->left->value << " of node: " << node->left->parent->value << "\n";
			return;
		}
		else
		{
			Add(node->left, nodeValue);
			return;
		}
	}
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
	else if(node->left == nullptr && node->right == nullptr)
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
	if (node == nullptr) return nullptr;

	if (node->value < nodeValue)
	{
		return Search(node->right, nodeValue);
	}
	else if(node->value > nodeValue)
	{
		return Search(node->left, nodeValue);
	}
	else
	{
		return node;
	}
}

size_t Node::Get_NodeHeight(Node* node)
{
	if (node == nullptr)
		return 0;
	else
		return 1 + std::max(Get_NodeHeight(node->left), Get_NodeHeight(node->right));
}

int Node::Get_NodeBalance(Node* node)
{
	if (node == nullptr)
		return 0;

	if (node->left && node->right)
	{
		node->nodeBalance = Get_NodeHeight(node->left) - Get_NodeHeight(node->right);
	}
	else if (node->left || node->right)
	{
		node->nodeBalance = 1;
		return node->nodeBalance;
	}
	else
	{
		node->nodeBalance = 0;
		return node->nodeBalance;
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
	unbalancedNode->parent = pivotNode;

	return pivotNode;
}


//Update node balance and height,

void Node::UpdateNode(Node* node)
{
	if (node == nullptr) return;

	UpdateHeight(node);
	UpdateBalance(node);

	if (node->nodeBalance > 1)
	{
		if (node->left != nullptr && node->left->nodeBalance < 0)
		{
			node = RotateLeft(node->left);
		}
		node = RotateRight(node);
	}
	else if (node->nodeBalance < -1)
	{
		if (node->right != nullptr && node->right->nodeBalance > 0)
		{
			node = RotateRight(node->right);
		}
		node = RotateLeft(node);
	}
}

void Node::UpdateBalance(Node* node)
{
	if (node == nullptr) return;

	UpdateBalance(node->left);
	UpdateBalance(node->right);

	node->nodeBalance = Get_NodeBalance(node);
}

void Node::UpdateHeight(Node* node)
{
	if (node == nullptr) return;

	UpdateHeight(node->left);
	UpdateHeight(node->right);

	node->nodeHeight = Get_NodeHeight(node);
}


//Binary tree

void BinaryTreeAVL::deallocateMemory(Node* root)
{
	if (root == nullptr) return;

	deallocateMemory(root->left);
	deallocateMemory(root->right);

	delete root;
}

void BinaryTreeAVL::AddNode(int nodeValue)
{
	root->Add(root, nodeValue);
	root->UpdateNode(root);
}

void BinaryTreeAVL::DeleteNode(int nodeValue)
{
	root->Remove(root, nodeValue);
}

