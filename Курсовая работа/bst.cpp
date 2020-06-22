#include <Windows.h>
#include <iostream>
#include <stdarg.h>
#include <string>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <fstream>


// Реализация FIFO.
// Очередь нужна для итеративной реализации обхода бинарного дерева в ширину

// Реализация бинарного дерева поиска:
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
struct BinSearchTree
{
	struct Node
	{
		KeyType key;
		Node* left, * right, * parent;
		ValueType value;
		//---------------------------------
	};
	enum TraversalType
	{
		// В глубину:
		LNR_REQ = 123, // Центрированный(In-order) обход. Рекурсивная реализация
		RNL_REQ = 321, // Обратный центрированный(Reverse in-order) обход. Рекурсивная реализация
		NLR_REQ = 213, // Прямой(Pre-order) обход. Рекурсивная реализация
		LRN_REQ = 132, // Обратный(Post-order) обход. Рекурсивная реализация

		// В ширину
		BFS_QUE = 231 // Обход в ширину слева на право. Итеративная реализация с помощью очереди
	};
	Node* mainRoot;
	bool (*sorter)(KeyType a, KeyType b);
	//---------------------------


	Node* find(KeyType val)
	{
		// Начинаем поиск с корня дерева. Устанавливаем указатель на корень
		Node* currNode = mainRoot;
		// Пока текущий узел существует(указатель не нулевой) и значение текущего узла не равно искомому.
		while (currNode and !isKeyTypeValsEqual(currNode->key, val))
			// Переставляем указатель на правый дочерний узел если значение больше текущего и на левый если меньше
			currNode = (sorter(val, currNode->key)) ? currNode->right : currNode->left;
		// Возращается NULL, если значение небыло найденно(так как перешли на указатель дочернего узла, который равен нулю)
		// и указатель на узел со значением если он существует
		return currNode;
	}


	ValueType get(KeyType key)
	{
		// Получаем указатель на узел со значением или ноль если такого узла нет
		Node* currNode = find(key);
		// Если указатель не нулевой, то возращаем значение узла.
		// Если нулевой, то значение по умолчанию
		return (currNode) ? currNode->value : ValueType();
	}

	void insert(KeyType key, ValueType val)
	{
		// Ключу соответсятует только одно значение,
		// если данный ключ уже есть, то завершаем функцию.
		Node* keyIsValNode = find(key);
		if (keyIsValNode)
			return;
		if (mainRoot) // Если в дереве есть узлы(указатель на корень не нулевой)
		{
			// Начинаем обход с корня, для этого устанавливаем на него указатель
			Node* currNode = mainRoot;
			// Переходим в зависимости от значения ключа создаваемого узла и ключа текущего узла
			// на правое или левое поддерево
			for (Node* nextNode = (sorter(key, currNode->key)) ? currNode->right : currNode->left;
				nextNode;
				nextNode = (sorter(key, currNode->key)) ? currNode->right : currNode->left)
				currNode = nextNode;
			// Найдя родительский узел для создаваемого узла,
			// в зависимости от значений ключей,
			// создаем дочерней узел с права или слева
			if (sorter(key, currNode->key))
				currNode->right = new Node{ key, NULL, NULL, currNode, val };
			else
				currNode->left = new Node{ key, NULL, NULL, currNode, val };
		}
		// Если дерево пустое, то корнем становится создаваемый узел
		else
			mainRoot = new Node{ key, NULL, NULL, NULL, val };
	}

	void erase(KeyType val)
	{
		// Если узла с таким значением нет, то завершаем функцию
		Node* currNode = find(val);
		if (!currNode)
			return;
		// Если удаляемый узел имеет дочерние узлы с обоих сторон
		if (currNode->left && currNode->right)
		{
			// Находим минимальный по клюжчу узел правого поддерева
			Node* rightTreeMinNode = currNode->right;
			while (rightTreeMinNode->left)
				rightTreeMinNode = rightTreeMinNode->left;
			// Меняем значение удаляемого узла значением найденного узла
			KeyType rtmnKey = rightTreeMinNode->key;
			// Рекурсивно удаляем найденный узел
			erase(rightTreeMinNode->key);
			currNode->key = rtmnKey;
		}
		// Если удаляемый узел имеет один дочерний узел или не имеет потомков
		else
		{
			// Если у удаляемого узла есть левый дочерний узелб
			// то он становится узлом-преемником,
			// иначе узел-преемник - правый узел
			// или, в том случае если удаляемый узел не имеет потомков - нулевой указатель
			Node* successorNode = (currNode->left) ? currNode->left : currNode->right;
			// В том случае если указатель на узел-преемник не нулевой, то
			// то меняем значение указателя дочернего узла на родительский узел,
			// который может быть нулевым, если удаляемый узел - корень
			successorNode && (successorNode->parent = currNode->parent);
			// Если удаляемый узел не корень
			if (currNode->parent)
			{
				// Меняем указатель родительского узла на дочерний узел
				// на указатель узла-преемника
				if (currNode == currNode->parent->left)
					currNode->parent->left = successorNode;
				else
					currNode->parent->right = successorNode;
			}
			// Если удаляемый узел-корень
			else
				// то корнем становится его дочерний узел или нулевой указатель
				mainRoot = successorNode;
			// удаляем удаляемый узел
			delete currNode;
		}
	}
	void clear()
	{
		clear(mainRoot);
	}


	void clear(Node*& currNode)
	{
		// Оптимальным алгоритмом удаления дерева
		// является такой алгоритм, который в процессе
		// выполнения не требует перестраивания дерева.
		// Для этого нужно удалять только те узлы которые не имею потомков.
		// Для этого можно удалять узлы в обратном топологическом порядке
		// обходя узлы методом обратного(LRN) обхода.

		// Условие выхода из рекурсии
		if (!currNode)
			return;

		// L - рекурсивное удаление левых поддеревьев
		clear(currNode->left);
		// R - рекурсивное удаление правых поддеревьев
		clear(currNode->right);
		// N - удаление самомго узла
		delete currNode;
		currNode = NULL;
	}

	void traverseVals(Node* currNode, TraversalType traversalType, void (*func)(const ValueType&, int, va_list), int argCount, va_list funcArgs)
	{
		if (!currNode)
			return;
		switch (traversalType)
		{
		case LNR_REQ:
			traverseVals(currNode->left, TraversalType::LNR_REQ, func, argCount, funcArgs);
			func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LNR_REQ, func, argCount, funcArgs);
			break;
		case RNL_REQ:
			traverseVals(currNode->right, TraversalType::RNL_REQ, func, argCount, funcArgs);
			func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::RNL_REQ, func, argCount, funcArgs);
			break;
		case NLR_REQ:
			func(currNode->value, argCount, funcArgs);
			traverseVals(currNode->left, TraversalType::NLR_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::NLR_REQ, func, argCount, funcArgs);
			break;
		case LRN_REQ:
			traverseVals(currNode->left, TraversalType::LRN_REQ, func, argCount, funcArgs);
			traverseVals(currNode->right, TraversalType::LRN_REQ, func, argCount, funcArgs);
			func(currNode->value, argCount, funcArgs);
			break;
		default:
			break;
		}
	}
	void traverseVals_BFS(Node* currNode, TraversalType traversalType, void (*func)(const ValueType&, int, va_list), int argCount, va_list funcArgs)
	{

	}
	void traverseVals(void (*func)(const ValueType&, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		traverseVals(mainRoot, TraversalType::LNR_REQ, func, argCount, funcArgs);
		va_end(funcArgs);
	}
	void traverseVals(Node* currNode, TraversalType traversalType, void (*func)(const ValueType&, int, va_list), int argCount = 0, ...)
	{
		va_list funcArgs;
		va_start(funcArgs, argCount);
		if(traversalType == TraversalType::BFS_QUE)
			traverseVals_BFS(currNode, traversalType, func, argCount, funcArgs);
		else
			traverseVals(currNode, traversalType, func, argCount, funcArgs);
		va_end(funcArgs);
	}


};

typedef BinSearchTree::Node* SinglyLinkedList_queue_ValueType;
struct SinglyLinkedList_queue
{
	struct Node
	{
		Node* next;
		SinglyLinkedList_queue_ValueType data;
	};
	Node* head;
	Node* tail;
	void insert(SinglyLinkedList_queue_ValueType val)
	{

		Node* currNode = new Node;
		currNode->data = val;
		currNode->next = NULL;
		if (tail == NULL)
		{
			head = currNode;
			tail = currNode;
		}
		else
		{
			tail->next = currNode;
			tail = currNode;
		}
	}
	SinglyLinkedList_queue_ValueType shift()
	{
		if (!head)
			return NULL;
		Node* nextHead = head->next;
		SinglyLinkedList_queue_ValueType popedValue = head->data;
		delete head;
		head = nextHead;
		return popedValue;
	}
	void destroy()
	{
		for (Node* currNode = head, *nex; currNode; currNode = nex)
		{
			nex = currNode->next;
			delete currNode;
		}
		head = NULL;
		tail = NULL;
	}
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// Функции для форматирования текста в консоли
void coutCenterStr(const std::string&);  // https://ru.stackoverflow.com/questions/802079/%D0%92%D1%8B%D1%80%D0%B0%D0%B2%D0%BD%D0%B8%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BF%D0%BE-%D1%86%D0%B5%D0%BD%D1%82%D1%80%D1%83-%D0%B2%D1%8B%D0%B2%D0%BE%D0%B4-%D0%B2-%D1%81
void gotoxy(short, short); // https://forum.vingrad.ru/topic-279072.html
std::string formatNumber(std::string);

int countNodesBetweenByKeys(BinSearchTree*, KeyType, KeyType);

// Функции экранов меню:
void intro(int argc, char* argv[]);
void mainMenu(int argc, char* argv[]);
void valueInputMenu(bool&, HANDLE&, BinSearchTree*);
void valueEraseManu(bool&, HANDLE&, BinSearchTree*);
void countNodesBetweenByKeysMenu(HANDLE&, BinSearchTree*);
void saveInFileMenu(int argc, char* argv[], bool&, HANDLE&, BinSearchTree*);
void openFromFileMenu(int argc, char* argv[], bool&, HANDLE&, BinSearchTree*&);

// Функции для работы с BinTree
// Функция определяющая операцию сравнения для ключей
bool greaterInt(KeyType a, KeyType b)
{
	return (a > b);
}

void coutData(const ValueType& data, int argCount, va_list args)
{
	std::cout << "  " << std::setw(14) << std::left << data.number << " | " << std::setw(27) << std::left << data.owner << " | " << std::setw(24) << std::left << data.tariff << std::endl;
}
void countNodes(const ValueType& data, int argCount, va_list args)
{
	(*va_arg(args, int*))++;
}
void cpyValsToBuff(const ValueType& data, int argCount, va_list args)
{
	*va_arg(args, ValueType*)++ = data;
}
void cpyKeysToBuff(const ValueType& data, int argCount, va_list args)
{
	*va_arg(args, KeyType*)++ = data.number;
}

void coutSubOwnerByNumber(BinSearchTree& binTree, KeyType number)
{
	TeleSubscriber sub = binTree.get(number);
	std::cout << number << " sub is: " << ((sub.owner.size()) ? sub.owner : "UNDEFINED") << std::endl;
}

int scoutPath(BinSearchTree::Node* currNode, KeyType key, int pathLength, SinglyLinkedList_queue& addOfVisitedNodes)
{
	// Если текущий узел не существует(указатель на него нулевой),
	// то вернуть отрицательный результат, так как
	// данная ветвь рекурсии не смогла обнаружить узел к которому ищется путь
	if (!currNode)
		return -1;
	// Если текущий узел уже был посещен,
	// (его адрес есть в контейнере уже посещенных узлов)
	// то вернуть отрицательный результат, так как
	// данная ветвь рекурсии или уже была обработана или обработается другой ветвью
	for (SinglyLinkedList_queue::Node* iter = addOfVisitedNodes.head; iter != NULL; iter = iter->next)
	{
		//std::cout << "<<< " << iter->data->key << " >>>" << std::endl;
		if (iter->data == currNode)
			return -1;
	}
	// Добавить адресс текущего узла в контейнер,
	/// который сожержит адреса уже посещенных узлов
	addOfVisitedNodes.insert(currNode);
	// Если текущий узел - узел назначения,
	// то вернуть колличество узлов лежищих между ним
	// и начальным узлом
	if (currNode->key == key)
		return pathLength;
	// Возращаемое значение
	int returnVal;
	// Рекурсивно искать в родительском узле
	returnVal = scoutPath(currNode->parent, key, pathLength + 1, addOfVisitedNodes);
	// Если искомый узел не был найден(результат отрицателен), то искать в левом дочернем узле
	if(returnVal == -1)
		returnVal = scoutPath(currNode->left, key, pathLength + 1, addOfVisitedNodes);
	// Если искомый узел не был найден(результат отрицателен), то искать в правом дочернем узле
	if (returnVal == -1)
		returnVal = scoutPath(currNode->right, key, pathLength + 1, addOfVisitedNodes);
	// Вернуть найденный результат
	return returnVal;
}
int scoutPath(BinSearchTree* bst, KeyType keyA, KeyType keyB)
{
	// Если один из узлов отсутствует в дереве, то возращаем отрицательный результат
	BinSearchTree::Node* nodeA = bst->find(keyA);
	if (!nodeA || !bst->find(keyB))
		return -1;
	// В качесте контейнера для хранения адрессов уже посещенных узлов,
	// лучше было бы использовать все тот-же BinSearchTree,
	// но чтобы реализовать хранения ключей и значений произвольного типа нужны шаблоны
	int nodeCount = 0;
	bst->traverseVals(countNodes, 1, &nodeCount);
	SinglyLinkedList_queue addOfVisitedNodes{NULL, NULL};
	// Устанавливает изначальные значения переменных
	return scoutPath(nodeA, keyB, -1, addOfVisitedNodes);
}

struct Preinseq
{
	int length;
	KeyType* nlrArr;
	KeyType* lnrArr;
	ValueType* valsArr;
};
void recon_BST_from_NLR_LNR_seq(BinSearchTree::Node*& rootNodeAdd, KeyType* nlr, int nlrLength, int nlrRootIndex, KeyType* lnr, int lnrLength, int lnrBeginIndex, ValueType* vals)
{
	if (lnrLength < 1)
	{
		rootNodeAdd = NULL;
		return;
	}
	rootNodeAdd->key = nlr[nlrRootIndex];
	rootNodeAdd->value = vals[nlrRootIndex];
	rootNodeAdd->left = new BinSearchTree::Node;
	rootNodeAdd->left->parent = rootNodeAdd;
	rootNodeAdd->right = new BinSearchTree::Node;
	rootNodeAdd->right->parent = rootNodeAdd;

	int lnrRootIndex;
	for (lnrRootIndex = 0; lnr[lnrRootIndex] != nlr[nlrRootIndex]; lnrRootIndex++);

	// https://cs.stackexchange.com/questions/439/which-combinations-of-pre-post-and-in-order-sequentialisation-are-unique
	recon_BST_from_NLR_LNR_seq(rootNodeAdd->left, nlr, (lnrRootIndex + (nlrRootIndex - lnrBeginIndex)) - nlrRootIndex, nlrRootIndex + 1, lnr, (lnrRootIndex + (nlrRootIndex - lnrBeginIndex)) - nlrRootIndex, lnrBeginIndex, vals);
	recon_BST_from_NLR_LNR_seq(rootNodeAdd->right, nlr, nlrLength - (( lnrRootIndex+(nlrRootIndex-lnrBeginIndex) ) - nlrRootIndex) - 1, (lnrRootIndex + (nlrRootIndex - lnrBeginIndex)) + 1, lnr, nlrLength - ((lnrRootIndex + (nlrRootIndex - lnrBeginIndex)) - nlrRootIndex) - 1, lnrRootIndex + 1, vals);
}
void recon_BST_from_NLR_LNR_seq(BinSearchTree::Node*& rootNodeAdd, Preinseq& preinseq)
{
	recon_BST_from_NLR_LNR_seq(rootNodeAdd, preinseq.nlrArr, preinseq.length, 0, preinseq.lnrArr, preinseq.length, 0, preinseq.valsArr);
}
Preinseq con_NLR_LNR_seq_of_BST(BinSearchTree*& bst)
{
	Preinseq preinseq;

	preinseq.length = 0;
	bst->traverseVals(countNodes, 1, &preinseq.length);

	preinseq.nlrArr = new KeyType[preinseq.length];
	preinseq.lnrArr = new KeyType[preinseq.length];
	preinseq.valsArr = new ValueType[preinseq.length];

	bst->traverseVals(bst->mainRoot, BinSearchTree::TraversalType::NLR_REQ, cpyKeysToBuff, 1, preinseq.nlrArr);
	bst->traverseVals(bst->mainRoot, BinSearchTree::TraversalType::LNR_REQ, cpyKeysToBuff, 1, preinseq.lnrArr);
	bst->traverseVals(bst->mainRoot, BinSearchTree::TraversalType::NLR_REQ, cpyValsToBuff, 1, preinseq.valsArr);

	return preinseq;
}
bool make_preinseq_file(std::string path, Preinseq& preinseq)
{
	std::ofstream outFile(path + ".preinseq", std::ios::binary);
	if (!outFile)
		return false;
	outFile.write(reinterpret_cast<char*>(&preinseq.length), sizeof(preinseq.length));
	for (int i = 0; i < preinseq.length; i++)
		outFile.write(reinterpret_cast<char*>(preinseq.nlrArr + i), sizeof(preinseq.nlrArr[i]));
	for (int i = 0; i < preinseq.length; i++)
		outFile.write(reinterpret_cast<char*>(preinseq.lnrArr + i), sizeof(preinseq.lnrArr[i]));
	for (int i = 0; i < preinseq.length; i++)
		outFile.write(reinterpret_cast<char*>(preinseq.valsArr + i), sizeof(preinseq.valsArr[i]));
	if (!outFile)
		return false;
	outFile.close();
	return true;
}
Preinseq read_preinseq_file(std::string path)
{
	Preinseq preinseq;
	std::ifstream inFile(path + ".preinseq", std::ios::binary);
	inFile.seekg(inFile.beg);
	if (!inFile)
	{
		preinseq.length = -1;
		return preinseq;
	}
	inFile.read(reinterpret_cast<char*>(&preinseq.length), sizeof(preinseq.length));
	preinseq.nlrArr = new KeyType[preinseq.length];
	preinseq.lnrArr = new KeyType[preinseq.length];
	preinseq.valsArr = new ValueType[preinseq.length];
	for (int i = 0; i < preinseq.length; i++)
		inFile.read(reinterpret_cast<char*>(preinseq.nlrArr + i), sizeof(preinseq.nlrArr[i]));
	for (int i = 0; i < preinseq.length; i++)
		inFile.read(reinterpret_cast<char*>(preinseq.lnrArr + i), sizeof(preinseq.lnrArr[i]));
	for (int i = 0; i < preinseq.length; i++)
		inFile.read(reinterpret_cast<char*>(preinseq.valsArr + i), sizeof(preinseq.valsArr[i]));

	if (!inFile)
	{
		preinseq.length = -1;
		return preinseq;
	}
	inFile.close();
	return preinseq;
}

int main(int argc, char* argv[])
{
	intro(argc, argv);
	return 0;
}
void coutCenterStr(const std::string& s)
{
	int width_field = 68;
	std::string v(width_field, ' ');
	std::string v1;

	int l_word = s.size();
	int l_field = v.size();
	int step = (l_field - l_word) / 2;

	for (int i = 0; i < l_word; i++) {
		v1.push_back(s[i]);
	}
	copy(v1.begin(), v1.end(), v.begin() + step);
	for (auto x : v) {
		std::cout << x;
	}
	std::cout << std::endl;
}
void gotoxy(short x, short y)
{
	HANDLE    StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD    coord = { x, y };
	SetConsoleCursorPosition(StdOut, coord);
}
int wherex()
{
	HANDLE                        StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    csbi;
	GetConsoleScreenBufferInfo(StdOut, &csbi);
	return int(csbi.dwCursorPosition.X);
}
int wherey()
{
	HANDLE                        StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO    csbi;
	GetConsoleScreenBufferInfo(StdOut, &csbi);
	return int(csbi.dwCursorPosition.Y);
}

void pressAnyKeyToContinue()
{
	for (int state = 1, lastClockVal = clock(); !_kbhit(); state = (state > 1000) ? (state % 2) ? 0 : 1 : state + (clock() - lastClockVal) * 2, lastClockVal = clock())
	{
		if (state % 2)
		{
			gotoxy(0, wherey() - 1);
			coutCenterStr("  НАЖМИТЕ ЛЮБУЮ КЛАВИШУ ВВОДА ДЛЯ ПРОДОЛЖЕНИЯ");
		}
		else
		{
			gotoxy(0, wherey() - 1);
			printf("                                                                                      \n");
		}
	}
	_getche();
	gotoxy(0, wherey());
	std::cout << " ";
	gotoxy(0, wherey());
}
void intro(int argc, char* argv[])
{
	// https://www.cyberforum.ru/cpp/thread2454842.html
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = FALSE;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));

	setlocale(LC_ALL, "Russian");

	std::cout << "\n\n";
	coutCenterStr("  КУРСОВАЯ РАБОТА");
	coutCenterStr("  по дисциплине");
	coutCenterStr("  \"Алгоритмизация и программирование\"");
	coutCenterStr("  на тему");
	coutCenterStr("  \"Определения количества узлов, лежащих на пути между двумя узлами,");
	coutCenterStr("  заданными своими ключевыми признаками в бинарном дереве\"");

	std::cout << std::endl <<
		"  Выполнил" << std::endl <<
		"  обучающийся группы 15.11Д-МО11/19б" << std::endl <<
		"  очной формы обучения" << std::endl <<
		"  института цифровой экономики" << std::endl <<
		"  и информационных технологий" << std::endl <<
		"  Гришанин Вячеслав Валерьевич" << std::endl;
	std::cout << "\n\n";
	pressAnyKeyToContinue();
	mainMenu(argc, argv);
}
void mainMenu(int argc, char* argv[])
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	BinSearchTree* subsBase = NULL;
	bool isSaved = false;
	while (true)
	{

		system("cls");
		std::cout << "  БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ): ";
		if (subsBase)
		{
			if (isSaved)
				std::cout << "СОХРАНЕННО В ФАЙЛЕ";
			else
				std::cout << "НЕ ЗАПИСАННО В ФАЙЛ";
		}
		else
			std::cout << "НЕОПРЕДЕЛЕННО";
		std::cout << "\n\n";

		coutCenterStr("  ВЫБЕРИТЕ ДЕЙСТВИЕ:");
		std::cout << "  КЛАВИША 1 - создать новое бинарное дерево(базу абонентов);" << std::endl
				  << "  КЛАВИША 2 - обход бинарного дерева с выдачей на экран содержимого информационных полей(вывод всех абонентов базы);" << std::endl
				  << "  КЛАВИША 3 - включить элемент в бинарное дерево(добавить абонента);" << std::endl
				  << "  КЛАВИША 4 - удаление заданного узла из дерева (удаление абонента);" << std::endl
				  << "  КЛАВИША 5 - удаление дерева(базы абонентов) с освобождением памяти;" << std::endl
				  << "  КЛАВИША 6 - определить количество узлов, лежащих на пути между двумя узлами, заданными своими ключевыми признаками;" << std::endl
				  << "  КЛАВИША 7 - открыть бинарное дерево(базу абонентов) из файла;" << std::endl
				  << "  КЛАВИША 8 - сохранить текущее состояние бинарного дерева(базы абонентов) в файл;" << std::endl
				  << "  КЛАВИША 0 - заваершить программу;" << std::endl;

		GET_ACTION:
		char action = _getche();
		gotoxy(0, wherey());
		std::cout << " ";
		gotoxy(0, wherey());
		switch (action - 48)
		{
		case 1:
			system("cls");
			std::cout << "\n\n";
			if (subsBase)
			{
				coutCenterStr("  В ДАННЫЙ МОМЕНТ ОБРАБАТЫВАЕТСЯ СОЗДАННОЕ РАНЕЕ ДЕРЕВО");
			}
			else
			{
				subsBase = new BinSearchTree{ NULL, greaterInt};
				coutCenterStr("  НОВОЕ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) СОЗДАННО");
			}
			std::cout << "\n\n";
			pressAnyKeyToContinue();
			break;
		case 2:


			system("cls");
			std::cout << "\n\n";
			if (subsBase)
			{
				if (subsBase->mainRoot)
				{
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
					std::cout << "  " << std::setw(14) << std::left << "ТЕЛЕФОН (КЛЮЧ)"<< " | " << std::setw(27) << std::left << "ВЛАДЕЛЕЦ" << " | " << std::setw(24) << std::left << "ТАРИФ" << std::endl;
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
					//subsBase->traverseVals(coutData);
					subsBase->traverseVals(subsBase->mainRoot, BinSearchTree::TraversalType::LNR_REQ, coutData);

				}
				else
					coutCenterStr("  БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ИМЕЕТ ЗНАЧЕНИЙ");
			}
			else
				coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");

			std::cout << "\n\n";
			pressAnyKeyToContinue();
			break;
		case 3:
			valueInputMenu(isSaved, hConsoleHandle, subsBase);
			break;
		case 4:
			valueEraseManu(isSaved, hConsoleHandle, subsBase);
			break;
		case 5:
			system("cls");
			std::cout << "\n\n";
			if (subsBase)
			{
				subsBase->clear();
				delete subsBase;
				subsBase = NULL;
				coutCenterStr("  БИНАРНОЕ ДЕРЕВО(БАЗА АБОНЕНТОВ) УДАЛЕННО");
			}
			else
				coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");

			std::cout << "\n\n";
			pressAnyKeyToContinue();
			break;
		case 6:
			countNodesBetweenByKeysMenu(hConsoleHandle, subsBase);
			break;
		case 7:
			openFromFileMenu(argc, argv, isSaved, hConsoleHandle, subsBase);
			break;
		case 8:
			saveInFileMenu(argc, argv, isSaved, hConsoleHandle, subsBase);
			break;
		case 0:
			system("cls");
			return;
			break;
		default:
			goto GET_ACTION;
			break;
		}
	}
}
void valueInputMenu(bool& isSaved, HANDLE& hConsoleHandle, BinSearchTree* subsBase)
{
	int selectedMenuItem = 1;
	system("cls");
	std::cout << "\n\n";

	if (!subsBase)
	{
		coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");
		std::cout << "\n\n";
		pressAnyKeyToContinue();
		return;
	}
	coutCenterStr("  ВВЕДИТЕ ДАННЫЕ ДОБАВЛЯЕМОГО УЗЛА (АБОНЕНТА)");
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
	std::cout << std::setw(68) << std::left << "  НОМЕР: +_ (___) ___-__-__" << std::endl;
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
	std::cout << "    ИМЯ: __________________" << std::endl;
	std::cout << "  ТАРИФ: __________________" << std::endl;
	coutCenterStr("  ДОБАВИТЬ УЗЕЛ (АБОНЕНТА)");
	std::cout << "\n\n"
		<< "  КЛАВИША UP - переключение на поле выше;" << std::endl
		<< "  КЛАВИША DOWN - переключение на поле ниже;" << std::endl
		<< "  КЛАВИША ENTER - подтвердить ввод;" << std::endl
		<< "  КЛАВИША ESC - отменить ввод и вернуться в меню выбора действия;" << std::endl;

	std::string number = "", name = "", tariff = "";
	int ch;
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		std::string formatedNumber = formatNumber(number),
				    formatName = (name.length())?name:"__________________",
					formatTariff = (tariff.length()) ? tariff : "__________________";

		if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
			gotoxy(0, wherey() - 1);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
			if (selectedMenuItem == 1)
				std::cout << std::setw(68) << std::left << ("  НОМЕР: " + formatedNumber) << std::endl;
			if (selectedMenuItem == 2)
				std::cout << std::setw(68) << std::left << "    ИМЯ: " + formatName;
			if (selectedMenuItem == 3)
				std::cout << std::setw(68) << std::left << "  ТАРИФ: " + formatTariff << std::endl;
			if (selectedMenuItem == 4)
				coutCenterStr("  ДОБАВИТЬ УЗЕЛ (АБОНЕНТА)");
			if (GetKeyState(VK_UP) < 0 && selectedMenuItem > 1)
				selectedMenuItem--;

			if (GetKeyState(VK_RETURN) < 0 && selectedMenuItem == 4)
			{
				gotoxy(27, 3);
				SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 4));
				if (number.length())
				{
					if(subsBase->find(stoull(number)))
						std::cout << "(ДАННЫЙ НОМЕР УЖЕ ЕСТЬ В БАЗЕ)" << std::endl;
					else
					{
						subsBase->insert(stoull(number), TeleSubscriber{ stoull(number), name, tariff });
						SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
						isSaved = false;
						return;
					}
				}
				else
					std::cout << "(ПОЛЕ С НОМЕРОМ НЕ ДОЛЖНО БЫТЬ ПУСТЫМ)" << std::endl;
			}

			if ((GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0) && selectedMenuItem < 4)
				selectedMenuItem++;

			if(GetKeyState(VK_BACK) < 0)
				switch (selectedMenuItem)
				{
				case 1:
					if(number.length())
						number.pop_back();
					break;
				case 2:
					if (name.length())
						name.pop_back();
					break;
				case 3:
					if (tariff.length())
						tariff.pop_back();
					break;
				default:
					break;
				}
		}
		while (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{ }

		SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
		gotoxy(0, selectedMenuItem + 2);
		if (selectedMenuItem == 1)
			std::cout << std::setw(68) << std::left << ("  НОМЕР: " + formatedNumber) << std::endl;
		if (selectedMenuItem == 2)
			std::cout << std::setw(68) << std::left << "    ИМЯ: " + formatName << std::endl;
		if (selectedMenuItem == 3)
			std::cout << std::setw(68) << std::left << "  ТАРИФ: " + formatTariff << std::endl;
		if (selectedMenuItem == 4)
			coutCenterStr("  ДОБАВИТЬ УЗЕЛ (АБОНЕНТА)");
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));

		if (_kbhit())
		{
			ch = _getche();
			gotoxy(0, wherey());
			std::cout << " ";
			gotoxy(0, wherey());
			if (ch == 0xE0 || ch == 0x00) // https://ru.stackoverflow.com/questions/1141080/%d0%9f%d1%80%d0%be%d0%b1%d0%bb%d0%b5%d0%bc%d0%b0-%d1%81-%d0%bf%d0%be%d0%bb%d1%83%d1%87%d0%b5%d0%bd%d0%b8%d0%b5%d0%bc-%d1%81%d0%b8%d0%bc%d0%b2%d0%be%d0%bb%d0%b0-%d1%81-%d0%bf%d0%be%d0%bc%d0%be%d1%89%d1%8c%d1%8e-getche
			{
				ch = _getch();
				if (ch == 0x48 || ch == 0x50 || ch == 0x4B || ch == 0x4D)
					continue;
			}
			switch (selectedMenuItem)
			{
			case 1:
				if (number.length() < 11 && ch > 47 && ch < 58)
					number += ch;
				break;
			case 2:
				if ((ch > 96 && ch < 123) || (ch > 64 && ch < 91) || ch == ' ')
					name += ch;
				break;
			case 3:
				if ((ch > 32 && ch < 127) || ch == ' ')
					tariff += ch;
				break;
			}
		}

	}

}
void valueEraseManu(bool& isSaved, HANDLE& hConsoleHandle, BinSearchTree* subsBase)
{
	int selectedMenuItem = 1;
	system("cls");
	std::cout << "\n\n";
	if (subsBase)
	{
		if (!subsBase->mainRoot)
		{
			coutCenterStr("  БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ИМЕЕТ ЗНАЧЕНИЙ");
			std::cout << "\n\n";
			pressAnyKeyToContinue();
			return;
		}
	}
	else
	{
		coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");
		std::cout << "\n\n";
		pressAnyKeyToContinue();
		return;
	}
	coutCenterStr("  ВВЕДИТЕ КЛЮЧ (НОМЕР) УДАЛЯЕМОГО УЗЛА (АБОНЕНТА)");
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
	std::cout << std::setw(68) << std::left << "  НОМЕР: +_ (___) ___-__-__" << std::endl;
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
	coutCenterStr("  УДАЛИТЬ УЗЕЛ (АБОНЕНТА)");
	std::cout << "\n\n"
		<< "  КЛАВИША UP - переключение на поле выше;" << std::endl
		<< "  КЛАВИША DOWN - переключение на поле ниже;" << std::endl
		<< "  КЛАВИША ENTER - подтвердить ввод;" << std::endl
		<< "  КЛАВИША ESC - отменить ввод и вернуться в меню выбора действия;" << std::endl;

	std::string number = "";
	int ch;
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		std::string formatedNumber = formatNumber(number);

		if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
			gotoxy(0, wherey() - 1);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
			if (selectedMenuItem == 1)
				std::cout << std::setw(68) << std::left << ("  НОМЕР: " + formatedNumber) << std::endl;
			if (selectedMenuItem == 2)
				coutCenterStr("  УДАЛИТЬ УЗЕЛ (АБОНЕНТА)");
			if (GetKeyState(VK_UP) < 0 && selectedMenuItem > 1)
				selectedMenuItem--;

			if (GetKeyState(VK_RETURN) < 0 && selectedMenuItem == 2)
			{
				gotoxy(27, 3);
				SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 4));
				if (number.length())
				{
					if (!subsBase->find(stoull(number)))
						std::cout << "(ДАННЫЙ НОМЕР ОТСУТСТВУЕТ В БАЗЕ)" << std::endl;
					else
					{
						subsBase->erase(stoull(number));
						SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
						isSaved = false;
						return;
					}
				}
				else
					std::cout << "(ПОЛЕ С НОМЕРОМ НЕ ДОЛЖНО БЫТЬ ПУСТЫМ)" << std::endl;
			}

			if ((GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0) && selectedMenuItem < 2)
				selectedMenuItem++;

			if (GetKeyState(VK_BACK) < 0)
				switch (selectedMenuItem)
				{
				case 1:
					if (number.length())
						number.pop_back();
					break;
				default:
					break;
				}
		}
		while (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{ }

		SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
		gotoxy(0, selectedMenuItem + 2);
		if (selectedMenuItem == 1)
			std::cout << std::setw(68) << std::left << ("  НОМЕР: " + formatedNumber) << std::endl;
		if (selectedMenuItem == 2)
			coutCenterStr("  УДАЛИТЬ УЗЕЛ (АБОНЕНТА)");
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));

		if (_kbhit())
		{
			ch = _getche();
			gotoxy(0, wherey());
			std::cout << " ";
			gotoxy(0, wherey());
			if (ch == 0xE0 || ch == 0x00)
			{
				ch = _getch();
				if (ch == 0x48 || ch == 0x50 || ch == 0x4B || ch == 0x4D)
					continue;
			}
			switch (selectedMenuItem)
			{
			case 1:
				if (number.length() < 11 && ch > 47 && ch < 58)
					number += ch;
				break;
			}
		}

	}
}
void countNodesBetweenByKeysMenu(HANDLE& hConsoleHandle, BinSearchTree* subsBase)
{
	int selectedMenuItem = 1;
	system("cls");
	std::cout << "\n\n";
	if (subsBase)
	{
		int nodesCount = 0;
		subsBase->traverseVals(countNodes, 1, &nodesCount);
		if (nodesCount < 2)
		{
			coutCenterStr("  В БИНАРНОМ ДЕРЕВЕ (БАЗЕ АБОНЕНТОВ) МЕНЕЕ ДВУХ ЗНАЧЕНИЙ");
			std::cout << "\n\n";
			pressAnyKeyToContinue();
			return;
		}
	}
	else
	{
		coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");
		std::cout << "\n\n";
		pressAnyKeyToContinue();
		return;
	}
	coutCenterStr("  ВВЕДИТЕ КЛЮЧИ УЗЛОВ ДЛЯ ОПРЕДЕЛЕНИЯ КОЛЛИЧЕСТВА УЗЛОВ МЕЖДУ НИМИ");
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
	std::cout << std::setw(68) << std::left << "  КЛЮЧ A: +_ (___) ___-__-__" << std::endl;
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
	std::cout << std::setw(68) << std::left << "  КЛЮЧ B: +_ (___) ___-__-__" << std::endl;
	coutCenterStr("  РАССЧИТАТЬ");
	std::cout << std::endl << std::setw(68) << std::left << "  УЗЛОВ В БИНАРНОМ ДЕРЕВЕ МЕЖДУ 'А' И 'B': НЕОПРЕДЕЛЕННО" << std::endl;
	std::cout << "\n\n"
		<< "  КЛАВИША UP - переключение на поле выше;" << std::endl
		<< "  КЛАВИША DOWN - переключение на поле ниже;" << std::endl
		<< "  КЛАВИША ENTER - подтвердить ввод;" << std::endl
		<< "  КЛАВИША ESC - отменить ввод и вернуться в меню выбора действия;" << std::endl;

	std::string numberA = "", numberB = "";
	int ch;
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		std::string formatNumberA = formatNumber(numberA),
				    formatNumberB = formatNumber(numberB);

		if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
			gotoxy(0, wherey() - 1);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
			if (selectedMenuItem == 1)
				std::cout << std::setw(68) << std::left << ("  КЛЮЧ A: " + formatNumberA) << std::endl;
			if (selectedMenuItem == 2)
				std::cout << std::setw(68) << std::left << ("  КЛЮЧ B: " + formatNumberB) << std::endl;
			if (selectedMenuItem == 3)
				coutCenterStr("  РАССЧИТАТЬ");
			if (GetKeyState(VK_UP) < 0 && selectedMenuItem > 1)
				selectedMenuItem--;

			if (GetKeyState(VK_RETURN) < 0 && selectedMenuItem == 3)
			{
				bool isKeysRelevant = true;
				SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 4));
				gotoxy(29, 3);
				if (numberA.length())
				{
					if (!subsBase->find(stoull(numberA)))
					{
						std::cout << "(ДАННЫЙ НОМЕР ОТСУТСТВУЕТ В БАЗЕ)" << std::endl;
						isKeysRelevant = false;
					}

				}
				else
				{
					std::cout << "(ПОЛЕ С НОМЕРОМ НЕ ДОЛЖНО БЫТЬ ПУСТЫМ)" << std::endl;
					isKeysRelevant = false;
				}

				gotoxy(29, 4);
				if (numberB.length())
				{
					if (!subsBase->find(stoull(numberB)))
					{
						std::cout << "(ДАННЫЙ НОМЕР ОТСУТСТВУЕТ В БАЗЕ)" << std::endl;
						isKeysRelevant = false;
					}
				}
				else
				{
					std::cout << "(ПОЛЕ С НОМЕРОМ НЕ ДОЛЖНО БЫТЬ ПУСТЫМ)" << std::endl;
					isKeysRelevant = false;
				}

				if (isKeysRelevant)
				{
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
					int count = scoutPath(subsBase, stoull(numberA), stoull(numberB));
					if (count != -1)
					{
						gotoxy(43, 7);
						std::cout << std::setw(25) << std::left << count << std::endl;
						gotoxy(0, 6);
					}
				}
			}

			if ((GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0) && selectedMenuItem < 3)
				selectedMenuItem++;

			if (GetKeyState(VK_BACK) < 0)
				switch (selectedMenuItem)
				{
				case 1:
					if (numberA.length())
						numberA.pop_back();
					gotoxy(43, 7);
					std::cout << std::setw(25) << std::left << "НЕОПРЕДЕЛЕННО" << std::endl;
					gotoxy(0, 4);
					break;
				case 2:
					if (numberB.length())
						numberB.pop_back();
					gotoxy(43, 7);
					std::cout << std::setw(25) << std::left << "НЕОПРЕДЕЛЕННО" << std::endl;
					gotoxy(0, 5);
					break;
				}
		}
		while (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{ }
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
		gotoxy(0, selectedMenuItem + 2);
		if (selectedMenuItem == 1)
			std::cout << std::setw(68) << std::left << ("  КЛЮЧ A: " + formatNumberA) << std::endl;
		if (selectedMenuItem == 2)
			std::cout << std::setw(68) << std::left << ("  КЛЮЧ B: " + formatNumberB) << std::endl;
		if (selectedMenuItem == 3)
			coutCenterStr("  РАССЧИТАТЬ");
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));

		if (_kbhit())
		{
			ch = _getche();
			gotoxy(0, wherey());
			std::cout << " ";
			gotoxy(0, wherey());
			if (ch == 0xE0 || ch == 0x00)
			{
				ch = _getch();
				if (ch == 0x48 || ch == 0x50 || ch == 0x4B || ch == 0x4D)
					continue;
			}
			switch (selectedMenuItem)
			{
			case 1:
				if (numberA.length() < 11 && ch > 47 && ch < 58)
					numberA += ch;
				gotoxy(43, 7);
				std::cout << std::setw(25) << std::left << "НЕОПРЕДЕЛЕННО" << std::endl;
				gotoxy(0, 4);
				break;
			case 2:
				if (numberB.length() < 11 && ch > 47 && ch < 58)
					numberB += ch;
				gotoxy(43, 7);
				std::cout << std::setw(25) << std::left << "НЕОПРЕДЕЛЕННО" << std::endl;
				gotoxy(0, 5);
				break;
			}
		}

	}
}
void saveInFileMenu(int argc, char* argv[], bool& isSaved, HANDLE& hConsoleHandle, BinSearchTree* subsBase)
{
	int selectedMenuItem = 1;
	system("cls");
	std::cout << "\n\n";
	if (subsBase)
	{
		if (!subsBase->mainRoot)
		{
			coutCenterStr("  БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ИМЕЕТ ЗНАЧЕНИЙ");
			std::cout << "\n\n";
			pressAnyKeyToContinue();
			return;
		}
	}
	else
	{
		coutCenterStr("  В ДАННЫЙ МОМЕНТ БИНАРНОЕ ДЕРЕВО (БАЗА АБОНЕНТОВ) НЕ ОБРАБАТЫВАЕТСЯ");
		std::cout << "\n\n";
		pressAnyKeyToContinue();
		return;
	}
	coutCenterStr("  ВВЕДИТЕ ПОЛНЫЙ ПУТЬ СОХРАНЯЕМОГО ФАЙЛА (БЕЗ ФОРМАТА)");
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
	std::cout << std::setw(68) << std::left << "  ПУТЬ:" << std::endl;
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
	coutCenterStr("  ЗАПИСАТЬ");
	std::cout << std::endl << std::setw(68) << std::left << "  СТАТУС: БИНАРНОЕ ДЕРЕВО НЕ ЗАПИСАННО В ФАЙЛ" << std::endl;
	std::cout << "\n\n"
		<< "  КЛАВИША UP - переключение на поле выше;" << std::endl
		<< "  КЛАВИША DOWN - переключение на поле ниже;" << std::endl
		<< "  КЛАВИША ENTER - подтвердить ввод;" << std::endl
		<< "  КЛАВИША ESC - отменить ввод и вернуться в меню выбора действия;" << std::endl;

	std::string fullPath = argv[0];
	fullPath = fullPath.substr(0, fullPath.length() - 11);
	int ch;
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
			gotoxy(0, wherey() - 1);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
			if (selectedMenuItem == 1)
				std::cout << std::setw(68) << std::left << ("  ПУТЬ: " + fullPath) << std::endl;
			if (selectedMenuItem == 2)
				coutCenterStr("  ЗАПИСАТЬ");
			if (GetKeyState(VK_UP) < 0 && selectedMenuItem > 1)
				selectedMenuItem--;

			if (GetKeyState(VK_RETURN) < 0 && selectedMenuItem == 2)
			{
				Preinseq preinseq = con_NLR_LNR_seq_of_BST(subsBase);

				bool fileStatus = make_preinseq_file(fullPath, preinseq);
				if (!fileStatus)
				{
					gotoxy(0, 5);
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 4));
					std::cout << std::endl << std::setw(68) << std::left << "  СТАТУС: ПРОИЗОШЛО ЧТО-ТО УЖАСНОЕ" << std::endl;
					gotoxy(0, 5);
					continue;
				}
				else
				{
					gotoxy(0, 5);
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 2));
					std::cout << std::endl << std::setw(68) << std::left << "  СТАТУС: ФАЙЛ " + fullPath.substr(strlen(argv[0]) - 11, fullPath.length()) + " ЗАПИСАН" << std::endl;
					gotoxy(0, 5);
					isSaved = true;
					continue;
				}
			}

			if ((GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0) && selectedMenuItem < 3)
				selectedMenuItem++;

			if (GetKeyState(VK_BACK) < 0)
				switch (selectedMenuItem)
				{
				case 1:
					if (fullPath.length())
						fullPath.pop_back();
					break;
				}
		}
		while (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{ }
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
		gotoxy(0, selectedMenuItem + 2);
		if (selectedMenuItem == 1)
			std::cout << std::setw(68) << std::left << ("  ПУТЬ: " + fullPath) << std::endl;
		if (selectedMenuItem == 2)
			coutCenterStr("  ЗАПИСАТЬ");
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));

		if (_kbhit())
		{
			ch = _getche();
			gotoxy(0, wherey());
			std::cout << " ";
			gotoxy(0, wherey());
			if (ch == 0xE0 || ch == 0x00)
			{
				ch = _getch();
				if (ch == 0x48 || ch == 0x50 || ch == 0x4B || ch == 0x4D)
					continue;
			}
			switch (selectedMenuItem)
			{
			case 1:
				if ((ch > 32 && ch < 127) || ch == ' ')
					fullPath += ch;
				break;
			}
		}

	}
}
void openFromFileMenu(int argc, char* argv[], bool& isSaved, HANDLE& hConsoleHandle, BinSearchTree*& subsBase)
{
	int selectedMenuItem = 1;
	system("cls");
	std::cout << "\n\n";
	if (subsBase)
	{
		coutCenterStr("  В ДАННЫЙ МОМЕНТ УЖЕ ОБРАБАТЫВАЕТСЯ БИНАРНОЕ ДЕРЕВО");
		std::cout << "\n\n";
		pressAnyKeyToContinue();
		return;
	}
	coutCenterStr("  ВВЕДИТЕ ПОЛНЫЙ ПУТЬ ОТКРЫВАЕМОГО ФАЙЛА (БЕЗ ФОРМАТА)");
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
	std::cout << std::setw(68) << std::left << "  ПУТЬ:" << std::endl;
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
	coutCenterStr("  ОТКРЫТЬ");
	std::cout << "\n\n";
	std::cout << "\n\n"
		<< "  КЛАВИША UP - переключение на поле выше;" << std::endl
		<< "  КЛАВИША DOWN - переключение на поле ниже;" << std::endl
		<< "  КЛАВИША ENTER - подтвердить ввод;" << std::endl
		<< "  КЛАВИША ESC - отменить ввод и вернуться в меню выбора действия;" << std::endl;

	std::string fullPath = argv[0];
	fullPath = fullPath.substr(0, fullPath.length() - 11);
	int ch;
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
			gotoxy(0, wherey() - 1);
			SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));
			if (selectedMenuItem == 1)
				std::cout << std::setw(68) << std::left << ("  ПУТЬ: " + fullPath) << std::endl;
			if (selectedMenuItem == 2)
				coutCenterStr("  ОТКРЫТЬ");
			if (GetKeyState(VK_UP) < 0 && selectedMenuItem > 1)
				selectedMenuItem--;

			if (GetKeyState(VK_RETURN) < 0 && selectedMenuItem == 2)
			{
				Preinseq preinseq = read_preinseq_file(fullPath);
				if (preinseq.length == -1)
				{
					gotoxy(0, 5);
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 4));
					std::cout << std::endl << std::setw(68) << std::left << "  СТАТУС: ПРОИЗОШЛО ЧТО-ТО УЖАСНОЕ" << std::endl;
					gotoxy(0, 5);
					continue;
				}
				else
				{
					if (subsBase && subsBase->mainRoot)
						subsBase->clear();
					if (!subsBase)
						subsBase = new BinSearchTree{ NULL, greaterInt };
					if (preinseq.length > 0)
						subsBase->insert(0, TeleSubscriber{ 0, "PLACEHOLDER", "PLACEHOLDER" });
					recon_BST_from_NLR_LNR_seq(subsBase->mainRoot, preinseq);

					gotoxy(0, 5);
					SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 2));
					std::cout << std::endl << std::setw(68) << std::left << "  СТАТУС: ФАЙЛ " + fullPath.substr(strlen(argv[0]) - 11, fullPath.length()) + " ПРОЧИТАН" << std::endl;
					gotoxy(0, 5);
					isSaved = false;
					continue;
				}
			}

			if ((GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0) && selectedMenuItem < 3)
				selectedMenuItem++;

			if (GetKeyState(VK_BACK) < 0)
				switch (selectedMenuItem)
				{
				case 1:
					if (fullPath.length())
						fullPath.pop_back();
					break;
				}
		}
		while (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_RETURN) < 0 || GetKeyState(VK_BACK) < 0)
		{
		}
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((7 << 4) | 0));
		gotoxy(0, selectedMenuItem + 2);
		if (selectedMenuItem == 1)
			std::cout << std::setw(68) << std::left << ("  ПУТЬ: " + fullPath) << std::endl;
		if (selectedMenuItem == 2)
			coutCenterStr("  ОТКРЫТЬ");
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((0 << 4) | 15));

		if (_kbhit())
		{
			ch = _getche();
			gotoxy(0, wherey());
			std::cout << " ";
			gotoxy(0, wherey());
			if (ch == 0xE0 || ch == 0x00)
			{
				ch = _getch();
				if (ch == 0x48 || ch == 0x50 || ch == 0x4B || ch == 0x4D)
					continue;
			}
			switch (selectedMenuItem)
			{
			case 1:
				if ((ch > 32 && ch < 127) || ch == ' ')
					fullPath += ch;
				break;
			}
		}

	}
}
int countNodesBetweenByKeys(BinSearchTree* subsBase, KeyType keyA, KeyType keyB)
{
	BinSearchTree::Node *nodeA, *nodeB;
	int count;
	for(count = -1, nodeA = subsBase->find(keyA), nodeB = subsBase->find(keyB); nodeA && nodeA != nodeB; nodeA=nodeA->parent, count++);
	if (nodeA)
		return count;
	for (count = -1, nodeB = subsBase->find(keyB), nodeA = subsBase->find(keyA); nodeB && nodeB != nodeA; nodeB = nodeB->parent, count++);
	if (nodeB)
		return count;
	return -1;
}
std::string formatNumber(std::string number)
{
	std::string formatNumber = "+_ (___) ___-__-__";
	if (number.length() > 0)
		formatNumber[1] = number[0];
	if (number.length() > 1)
		formatNumber[4] = number[1];
	if (number.length() > 2)
		formatNumber[5] = number[2];
	if (number.length() > 3)
		formatNumber[6] = number[3];
	if (number.length() > 4)
		formatNumber[9] = number[4];
	if (number.length() > 5)
		formatNumber[10] = number[5];
	if (number.length() > 6)
		formatNumber[11] = number[6];
	if (number.length() > 7)
		formatNumber[13] = number[7];
	if (number.length() > 8)
		formatNumber[14] = number[8];
	if (number.length() > 9)
		formatNumber[16] = number[9];
	if (number.length() > 10)
		formatNumber[17] = number[10];

	return formatNumber;
}
