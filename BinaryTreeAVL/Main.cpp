#include <iostream>
#include "BinaryTreeAVL.h"
#include <vector>

int main()
{
	BinaryTreeAVL BT(5); // value is root

	std::vector<int> numbers = {5};

	srand(time(0));

	for (size_t i = 0; i < 100; i++)
	{
		int number = rand() % UINT16_MAX;
		numbers.push_back(number);
	}

	for (int &num : numbers)
	{
		if (num == numbers[0])
			continue;

		BT.Insert(num);
	}

	bool balancedTree = true;

	for (int& num : numbers)
	{

		if (BT[num] == nullptr)
		{
			std::cout << "Missing: " << num << "\n"; 
			continue;
		}

		int balance = BT[num]->Get_NodeBalance(BT[num]);
		int height = BT[num]->Get_NodeHeight(BT[num]);

		std::cout << "Node: " << BT[num]->value << "\n";
		std::cout << "Height: " << height << "\n";
		std::cout << "Balance: " << balance << "\n";

		if (balance < -1 || balance > 1)
		{
			balancedTree = false;
		}
	}

	balancedTree ? std::cout << "Tree is balanced\n" : std::cout << "Tree is not balanced\n";

	std::cout << "\n";
	std::cout << "Min node: " << BT.Get_MinTreeNode()->value << "\n";
	std::cout << "Number of nodes: " << BT.numberOfNodes << "\n";
	std::cout << "Tree height: " << BT.Get_TreeHeight() << "\n\n";

	return 0;
}