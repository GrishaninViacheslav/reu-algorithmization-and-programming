// 2. Оператор мобильной связи организовал базу данных абонентов,
// содержащую сведения о телефонах, их владельцах и используемых тарифах,
// в виде бинарного дерева. Составьте программу, которая:
// • обеспечивает начальное формирование базы данных в виде бинарного дерева;
// • производит вывод всей базы данных;
// • производит поиск владельца по номеру телефона;
// • выводит наиболее востребованный тариф (по наибольшему числу абонентов).

#include <iostream>
#include <stdarg.h>
#include <iomanip>

struct TeleSubscriber
{
	unsigned long long number;
	std::string owner;
	std::string tariff;
};

typedef unsigned long long KeyType;
typedef TeleSubscriber ValueType;

bool isKeyTypeValsEqual(KeyType a, KeyType b)
{
	return (a == b);
}
struct BinTreeNode
{
	KeyType key;
	BinTreeNode* left, * right, * parent;
	ValueType value;
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
	bool (*sorter)(KeyType a, KeyType b);
	bool isMultiKey;
	//---------------------------


	BinTreeNode* find(KeyType val)
	{
		BinTreeNode* currNode = mainRoot;
		while (currNode and !isKeyTypeValsEqual(currNode->key, val))
			currNode = (sorter(val, currNode->key)) ? currNode->right : currNode->left;
		return currNode;
	}
	ValueType get(KeyType key)
	{
		BinTreeNode* currNode = find(key);
		return (currNode) ? currNode->value : ValueType();
	}
	void insert(KeyType key, ValueType val)
	{
		BinTreeNode* keyIsValNode = find(key);
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
				for (BinTreeNode* nextNode = (sorter(key, currNode->key)) ? currNode->right : currNode->left;
					nextNode;
					nextNode = (sorter(key, currNode->key)) ? currNode->right : currNode->left)
					currNode = nextNode;
				if (sorter(key, currNode->key))
					currNode->right = new BinTreeNode{ key, NULL, NULL, currNode, val };
				else
					currNode->left = new BinTreeNode{ key, NULL, NULL, currNode, val };
			}
			else
				mainRoot = new BinTreeNode{ key, NULL, NULL, NULL, val };
		}
	}
	void erase(KeyType val)
	{
		BinTreeNode* currNode = find(val);
		if (!currNode)
			return;
		if (currNode->left && currNode->right)
		{
			BinTreeNode* rightTreeMinNode = currNode->right;
			while (rightTreeMinNode->left)
				rightTreeMinNode = rightTreeMinNode->left;
			KeyType rtmnKey = rightTreeMinNode->key;
			int rtmnKeyCount = rightTreeMinNode->keyCount;
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
	void traverseVals(void (*func)(const ValueType&, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		traverseVals(mainRoot, TraversalType::LNR_REQ, func, argCount, funcArgs);
		va_end(funcArgs);
	}
	void traverseVals(BinTreeNode* currNode, TraversalType traversalType, void (*func)(const ValueType&, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		traverseVals(currNode, traversalType, func, argCount, funcArgs);
		va_end(funcArgs);
	}
	void traverseVals(BinTreeNode* currNode, TraversalType traversalType, void (*func)(const ValueType&, int, va_list), int argCount, va_list funcArgs)
	{
		if (!currNode)
			return;
		switch (traversalType)
		{
		case LNR_REQ:
			traverseVals(currNode->left, TraversalType::LNR_REQ, func, argCount, funcArgs);
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LNR_REQ, func, argCount, funcArgs);
			break;
		case RNL_REQ:
			traverseVals(currNode->right, TraversalType::RNL_REQ, func, argCount, funcArgs);
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::RNL_REQ, func, argCount, funcArgs);
			break;
		case NLR_REQ:
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::NLR_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::NLR_REQ, func, argCount, funcArgs);
			break;
		case LRN_REQ:
			traverseVals(currNode->left, TraversalType::LRN_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LRN_REQ, func, argCount, funcArgs);
			for (int i = 0; i <= currNode->keyCount; i++)
				func(currNode->value, argCount, funcArgs);
			break;
		default:
			break;
		}
	}

};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------


bool greaterInt(KeyType a, KeyType b)
{
	return (a > b);
}

void coutData(const ValueType& data, int argCount, va_list args)
{
	std::cout << data.number << " | " << std::setw(20) << std::left << data.owner << " | " << data.tariff << std::endl;
}
void countNodes(const ValueType& data, int argCount, va_list args)
{
	(*va_arg(args, int*))++;
}
void cpyToBuff(const ValueType& data, int argCount, va_list args)
{
	*va_arg(args, const std::string**)++ = &data.tariff;
}

void coutSubOwnerByNumber(BinTree& binTree, KeyType number)
{
	TeleSubscriber sub = binTree.get(number);
	std::cout << number << " sub is: " << ((sub.owner.size()) ? sub.owner : "UNDEFINED") << std::endl;
}

int main()
{
	// Обеспечивает начальное формирование базы данных в виде бинарного дерева:
	BinTree subsBase{ NULL, greaterInt, false };

	subsBase.insert(78005553535, TeleSubscriber{ 78005553535, "Oleg Rudovsky", "NOLIMITS"});
	subsBase.insert(72141201211, TeleSubscriber{ 72141201211, "Stanislav Rubin", "SHITHAPPENDS" });
	subsBase.insert(78001495515, TeleSubscriber{ 78001495515, "Vasilii Kartashev", "5IN1" });
	subsBase.insert(78001495511, TeleSubscriber{ 78001495511, "Vasilii Kartashev", "5IN1" });
	subsBase.insert(78001495512, TeleSubscriber{ 78001495512, "Vasilii Kartashev", "5IN1" });
	subsBase.insert(78005553535, TeleSubscriber{ 78005553535, "Old Ekav", "THIEF" });
	subsBase.insert(72141202129, TeleSubscriber{ 72141202129, "Simon Kain", "SLEEPYHEAD" });
	subsBase.insert(78001495513, TeleSubscriber{ 78001495513, "Vasilii Kartashev", "5IN1" });
	subsBase.insert(78001495514, TeleSubscriber{ 78001495514, "Vasilii Kartashev", "5IN1" });
	subsBase.insert(79851446345, TeleSubscriber{ 79851446345, "Engosh Lorpav", "NOLIMITS" });

	// Производит вывод всей базы данных:
	subsBase.traverseVals(coutData);

	// Производит поиск владельца по номеру телефона:
	std::cout << std::endl;
	coutSubOwnerByNumber(subsBase, 78005553535);
	coutSubOwnerByNumber(subsBase, 79851402928);
	std::cout << std::endl;

	// Выводит наиболее востребованный тариф (по наибольшему числу абонентов):
	int subsCount = 0;
	subsBase.traverseVals(countNodes, 1, &subsCount);
	const std::string** subsTariffsBuff = new const std::string*[subsCount];
	subsBase.traverseVals(cpyToBuff, 1, subsTariffsBuff);
	const std::string* mostFreqTariff = NULL;
	unsigned maxFreq = 0;
	for (int i = 0, currFreq = 0; i < subsCount; i++, currFreq = 1)
	{
		for (int j = i-1; j > 0; j--)
			if (subsTariffsBuff[i] == subsTariffsBuff[j])
				goto CONTINUE_OUTER_FOR;
		for (int j = i+1; j < subsCount; j++)
			if (*subsTariffsBuff[i] == *subsTariffsBuff[j])
				currFreq++;
		if (currFreq > maxFreq)
		{
			maxFreq = currFreq;
			mostFreqTariff = subsTariffsBuff[i];
		}
		CONTINUE_OUTER_FOR:;
	}
	std::cout << "One of the most popular tariffs is " << *mostFreqTariff << " has " << maxFreq << " sub(s)" << std::endl;

	subsBase.clear();

	return 0;
}
