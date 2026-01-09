#include <iostream>
#include "BinaryTreeAVL.h"

int main()
{
	BinaryTreeAVL BT(5); // value is root

	int numberArr[] = { 10, 20, 3, 2, 4, 1, 30 };

	BT.AddNode(10);
	BT.AddNode(20);
	BT.AddNode(3);
	BT.AddNode(2);
	BT.AddNode(4);
	BT.AddNode(1);
	BT.AddNode(30);

	//BT.DeleteNode(1);

	std::cout << "\n";
	std::cout << "Min node: " << BT.Get_MinTreeNode()->value << "\n";
	std::cout << "Number of nodes: " << BT.numberOfNodes << "\n";
	std::cout << "Tree height: " << BT.Get_TreeHeight() << "\n\n";

	int size = sizeof(numberArr) / sizeof(int);

	for (size_t i = 0; i < size; i++)
	{

		std::cout << "Node " << numberArr[i] << "\n" << "Height: " << BT[numberArr[i]]->Get_NodeHeight(BT[numberArr[i]]) << "\n";
		std::cout << "Balance: " << (int)BT[numberArr[i]]->Get_NodeBalance(BT[numberArr[i]]) << "\n";
		if(BT[numberArr[i]]->left != nullptr)
			std::cout << "Left child: " << BT[numberArr[i]]->left->value << "\n";
		else
			std::cout << "Left child: nullptr" << "\n";
		if (BT[numberArr[i]]->right != nullptr)
			std::cout << "Right child: " << BT[numberArr[i]]->right->value << "\n\n";
		else
			std::cout << "Right child: nullptr" << "\n\n";
	}

	return 0;
}