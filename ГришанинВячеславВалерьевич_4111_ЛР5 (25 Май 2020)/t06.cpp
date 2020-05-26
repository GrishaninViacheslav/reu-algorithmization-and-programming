// ������� �� ������� ��������� ����������
// ������� �������� � ���������������� �������� �������:
// 6. ����������� ������ � ������������� ������.

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
	void destroy()
	{
		for (SinglyLinkedListNode* currNode = head, *nodeToDestroy = NULL; currNode; nodeToDestroy = currNode, currNode = currNode->next)
			if (nodeToDestroy)
				delete nodeToDestroy;
		head = NULL;
		tail = NULL;
	}
};
int main()
{

	SinglyLinkedListStruct slList{ NULL, NULL };
	//for (unsigned long i = 0; i < 4000000000; i++)  // Не уверен, что правильно освобождается память
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
	std::cout << std::endl;

	slList.destroy();
	//}

	for (SinglyLinkedListNode* currNode = slList.head; currNode; currNode = currNode->next)
		std::cout << currNode->data << " ";

	return 0;
}
