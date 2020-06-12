// Сегодня на занятии обсуждаем реализацию
// базовых операций с однонаправленным линейным списком:
// 6. Уничтожение списка с освобождением памяти.

#include <iostream>
struct SinglyLinkedListNode
{
	SinglyLinkedListNode* next;
	int data;
};
struct SinglyLinkedListStruct
{
	SinglyLinkedListNode* head;
	SinglyLinkedListNode* tail;
	void push_back(int val)
	{

		SinglyLinkedListNode* currNode = new SinglyLinkedListNode;
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
	void push_front(int val)
	{
		SinglyLinkedListNode* currNode = new SinglyLinkedListNode;
		currNode->data = val;
		if (head == NULL)
		{
			currNode->next = NULL;
			head = currNode;
			tail = currNode;
		}
		else
		{
			currNode->next = head;
			head = currNode;
		}
	}
	int pop_back()
	{
		if (!tail)
			return NULL;
		SinglyLinkedListNode* prevTail = NULL;
		for (SinglyLinkedListNode* currNode = head; currNode != tail; currNode = currNode->next)
			prevTail = currNode;
		int popedValue = tail->data;
		delete tail;
		prevTail->next = NULL;
		tail = prevTail;
		return popedValue;
	}
	int pop_front()
	{
		if (!head)
			return NULL;
		SinglyLinkedListNode* nextHead = head->next;
		int popedValue = head->data;
		delete head;
		head = nextHead;
		return popedValue;
	}
	void destroy() // https://ru.stackoverflow.com/questions/1138757/%D0%A3%D1%82%D0%B5%D1%87%D0%BA%D0%B0-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8-%D0%B2-%D0%BE%D0%B4%D0%BD%D0%BE%D1%81%D0%B2%D1%8F%D0%B7%D0%BD%D0%BE%D0%BC-%D0%BB%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D0%BE%D0%BC-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%B5/1138802#1138802
	{
		for (SinglyLinkedListNode *currNode = head, *nex; currNode; currNode = nex)
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

	SinglyLinkedListStruct slList{ NULL, NULL };
	//for(unsigned long i = 0; i < 4000000000; i++) // Цикл для проверки на утечки памяти
	//{
	slList.push_back(5);
	slList.push_back(6);
	slList.push_front(4);
	slList.push_front(3);
	slList.push_back(7);
	slList.push_front(2);
	slList.push_back(8);
	slList.push_front(1);

	for (SinglyLinkedListNode* currNode = slList.head; currNode; currNode = currNode->next)
		std::cout << currNode->data << " ";

	slList.destroy();
	//}

	std::cout << "\nok.\n";

	return 0;
}
