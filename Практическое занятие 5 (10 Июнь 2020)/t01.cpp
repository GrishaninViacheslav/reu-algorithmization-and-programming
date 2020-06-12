// 1. Необходимо завершить  задание на программирование базовых операций
// с бинарным деревом (создание упорядоченного бинарного дерева, обходы, включение/исключение, удаление).

#include <iostream>
#include <stdarg.h>
struct BinTreeNode
{
	int key;
	BinTreeNode* left, *right, *parent;
	//---------------------------------


	int keyCount;
};
enum TraversalType
{
	// В глубину:
	LNR_REQ = 123, // Центрированный(In-order) обход. Рекурсивная реализация
	RNL_REQ = 321, // Обратный центрированный(Reverse in-order) обход. Рекурсивная реализация
	NLR_REQ = 213, // Прямой(Pre-order) обход. Рекурсивная реализация
	LRN_REQ = 132, // Обратный(Post-order) обход. Рекурсивная реализация
};
struct BinTree
{
	BinTreeNode* mainRoot;
	bool (*sorter)(int a, int b);
	bool isMultiKey;
	//---------------------------


	BinTreeNode* find(int val)
	{
		BinTreeNode* currNode = mainRoot;
		while (currNode and currNode->key != val)
			currNode = (sorter(val, currNode->key)) ? currNode->right : currNode->left;
		return currNode;
	}
	void insert(int val)
	{
		BinTreeNode* keyIsValNode = find(val);
		if (keyIsValNode)
		{
			if (isMultiKey)
				keyIsValNode->keyCount++;
		}
		else
		{
			if (mainRoot)
			{
				BinTreeNode* currNode = mainRoot;
				for (BinTreeNode* nextNode = (sorter(val, currNode->key)) ? currNode->right : currNode->left;
					nextNode;
					nextNode = (sorter(val, currNode->key)) ? currNode->right : currNode->left)
					currNode = nextNode;
				if (sorter(val, currNode->key))
					currNode->right = new BinTreeNode{ val, NULL, NULL, currNode };
				else
					currNode->left = new BinTreeNode{ val, NULL, NULL, currNode };
			}
			else
				mainRoot = new BinTreeNode{ val, NULL, NULL, NULL };
		}
	}
	void erase(int val)
	{
		BinTreeNode* currNode = find(val);
		if (!currNode)
			return;
		if (currNode->left && currNode->right)
		{
			BinTreeNode* rightTreeMinNode = currNode->right;
			while (rightTreeMinNode->left)
				rightTreeMinNode = rightTreeMinNode->left;
			int rtmnKey = rightTreeMinNode->key, rtmnKeyCount = rightTreeMinNode->keyCount;
			erase(rightTreeMinNode->key);
			currNode->key = rtmnKey;
			currNode->keyCount = rtmnKeyCount;
		}
		else
		{
			BinTreeNode* successorNode = (currNode->left) ? currNode->left : currNode->right;
			successorNode && (successorNode->parent = currNode->parent);
			if (currNode->parent)
			{
				if (currNode == currNode->parent->left)
					currNode->parent->left = successorNode;
				else
					currNode->parent->right = successorNode;
			}
			else
				mainRoot = successorNode;
			delete currNode;
		}
	}
	void clear()
	{
		while (mainRoot) erase(mainRoot->key);
	}
	void traverseVals(void (*func)(int, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		traverseVals(mainRoot, TraversalType::LNR_REQ, func, argCount, funcArgs);
		va_end(funcArgs);
	}
	void traverseVals(BinTreeNode* currNode, TraversalType traversalType, void (*func)(int, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		traverseVals(currNode, traversalType, func, argCount, funcArgs);
		va_end(funcArgs);
	}
	void traverseVals(BinTreeNode* currNode, TraversalType traversalType, void (*func)(int, int, va_list), int argCount, va_list funcArgs)
	{
		if (!currNode)
			return;
		switch (traversalType)
		{
		case LNR_REQ:
			traverseVals(currNode->left, TraversalType::LNR_REQ, func, argCount, funcArgs);
			for(int i = 0; i <= currNode->keyCount; i++)
				func(currNode->key, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LNR_REQ, func, argCount, funcArgs);
			break;
		case RNL_REQ:
			traverseVals(currNode->right, TraversalType::RNL_REQ, func, argCount, funcArgs);
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->key, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::RNL_REQ, func, argCount, funcArgs);
			break;
		case NLR_REQ:
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->key, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::NLR_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::NLR_REQ, func, argCount, funcArgs);
			break;
		case LRN_REQ:
			traverseVals(currNode->left, TraversalType::LRN_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LRN_REQ, func, argCount, funcArgs);
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->key, argCount, funcArgs);
			break;
		default:
			break;
		}
	}
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------


bool greaterInt(int a, int b)
{
	return (a > b);
}

void coutData(int data, int argCount, va_list args)
{
	std::cout << data << " ";
}
void countNodes(int data, int argCount, va_list args)
{
	(*va_arg(args, int*))++;
}
void cpyToBuff(int data, int argCount, va_list args)
{
	*va_arg(args, int*)++ = data;
}
void test(int data, int argCount, va_list args)
{
	va_arg(args, int);
}

int main()
{
	// Создание упорядоченного дерева:
	BinTree binTree{ NULL, greaterInt, false }; // Бинарное дерево главный корень которого не имеет предков(NULL), упорядоченное по возрастанию(greaterInt) и не имеющее узлов с одинаковыми значениями(false)

	// Включение:
	binTree.insert(5);
	binTree.insert(-1);
	binTree.insert(100);
	binTree.insert(200);
	binTree.insert(-100);
	binTree.insert(150);
	binTree.insert(-50);
	binTree.insert(-55);
	binTree.insert(100);

	// Обходы:
	binTree.traverseVals(coutData);
	std::cout << std::endl;

	std::cout << "0 is" << ((binTree.find(0)) ? " " : " NOT ") << "in the binary tree" << std::endl;
	std::cout << "100 is" << ((binTree.find(100)) ? " " : " NOT ") << "in the binary tree" << std::endl;
	std::cout << "5 is" << ((binTree.find(5)) ? " " : " NOT ") << "in the binary tree" << std::endl;
	int nodesCount = 0;
	binTree.traverseVals(countNodes, 1, &nodesCount);
	std::cout << "Nodes count: " << nodesCount << std::endl;
	int* buff = new int[nodesCount];
	binTree.traverseVals(binTree.mainRoot, TraversalType::RNL_REQ, cpyToBuff, 1, buff);
	std::cout << "sorted: " << std::endl;
	for(int i = 0; i < nodesCount; i++)
		std::cout << buff[i] << " ";
	std::cout << std::endl;

	// Исключения:
	binTree.erase(0);
	binTree.erase(5);
	binTree.erase(-50);
	binTree.erase(-55);

	std::cout << "erased 0, 5, -50, -55: " << std::endl;
	binTree.traverseVals(coutData);

	// Удаления:
	binTree.clear();

	return 0;
}
