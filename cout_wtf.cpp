#include <iostream>
struct SinglyLinkedList_queue
{
	struct Node
	{
		Node* next;
		int data;
	};
	Node* head;
	Node* tail;
	void insert(int val)
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
	int shift()
	{
		if (!head)
			return NULL;
		Node* nextHead = head->next;
		int popedValue = head->data;
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
int main()
{

	SinglyLinkedList_queue slList{ NULL, NULL };
	//for(unsigned long i = 0; i < 4000000000; i++) // Цикл для проверки на утечки памяти
	//{
	slList.insert(1);
	slList.insert(2);
	slList.insert(3);
	slList.insert(4);

	/*
	std::cout << slList.shift() << std::endl;
	std::cout << slList.shift() << std::endl;
	std::cout << slList.shift() << std::endl;
	std::cout << slList.shift() << std::endl;
	*/

	//std::cout << slList.shift() << std::endl << slList.shift() << std::endl << slList.shift() << std::endl << slList.shift() << std::endl << std::endl; //wtf

	for (SinglyLinkedList_queue::Node* currNode = slList.head; currNode; currNode = currNode->next)
		std::cout << currNode->data << " ";

	slList.destroy();
	//}

	std::cout << "\nok.\n";

	return 0;
}
