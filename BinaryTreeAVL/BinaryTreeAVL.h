#pragma once
#include <iostream>

struct Node
{
	size_t value{};
	size_t nodeBalance{};
	size_t indexNumber{};
	size_t nodeHeight{};

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
	size_t Get_NodeHeight(Node* node);
	int Get_NodeBalance(Node* node);

	//Insertion, searching and deletion
	void Add(Node* node, int nodeValue);
	void Remove(Node* node, int nodeValue);
	Node* Search(Node* node, int nodeValue);

	//Rotations
	Node* RotateRight(Node* y);
	Node* RotateLeft(Node* y);

	//Updates
	void UpdateHeight(Node* node);
	void UpdateBalance(Node* node);
	void UpdateNode(Node* node);
};

class BinaryTreeAVL
{
private:
	Node* root = nullptr;
	void deallocateMemory(Node* root);
public:
	size_t numberOfNodes = 0;

	BinaryTreeAVL() = default;

	BinaryTreeAVL(int rootValue)
	{
		root = new Node(rootValue, nullptr, nullptr, nullptr);
	}
	//Add node
	void AddNode(int nodeValue);
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
		return root->Search(root, nodeValue);
	}

	//Free memory
	~BinaryTreeAVL()
	{
		deallocateMemory(root);
	}
};

