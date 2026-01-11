#pragma once
#include <iostream>

struct Node
{
	int value{};
	int nodeBalance{};
	int indexNumber{};
	int nodeHeight{};

	Node* left{};
	Node* right{};
	Node* parent{};

	Node(int x, Node* parentNode, Node* leftNode, Node* rightNode)
	{
		value = x;
		parent = parentNode;
		left = leftNode;
		right = rightNode;
	}

	//Getters
	Node* Get_MinNode(Node* node);
	int Get_NodeHeight(Node* node);
	int Get_NodeBalance(Node* node);

	//Insertion, searching and deletion
	void Remove(Node* node, int nodeValue);
	Node* Search(Node* node, int nodeValue);

	//Rotations
	Node* RotateRight(Node* y);
	Node* RotateLeft(Node* y);

	//Updates
	Node* UpdateNode(Node* node);
};

class BinaryTreeAVL
{
private:
	void deallocateMemory(Node* root);
protected:
	Node* root = nullptr;
public:
	size_t numberOfNodes = 0;

	BinaryTreeAVL(int rootValue)
	{
		root = new Node(rootValue, nullptr, nullptr, nullptr);
	}


	//Add node
	void Insert(int nodeValue);

	//Delete node
	void DeleteNode(int nodeValue);

	Node* Get_MinTreeNode()
	{
		return root->Get_MinNode(root);
	}

	int Get_TreeHeight()
	{
		return root->Get_NodeHeight(root);
	}



	Node* operator [](int nodeValue)
	{
		Node* result = root->Search(root, nodeValue);

		return result;
	}

	//Free memory
	~BinaryTreeAVL()
	{
		deallocateMemory(root);
	}
};