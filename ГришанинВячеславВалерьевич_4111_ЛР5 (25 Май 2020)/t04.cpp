// Сегодня на занятии обсуждаем реализацию
// базовых операций с однонаправленным линейным списком:
// 4. Вставка элемента в начало или в конец списка(оба варианта).

#include <iostream>
struct SinglyLinkedListNode
{
	SinglyLinkedListNode* next;
	int data;
};
struct SinglyLinkedList
{
	SinglyLinkedListNode* frontNode;
	SinglyLinkedListNode* backNode;
	void push_back(int val)
	{

		SinglyLinkedListNode* currNode = new SinglyLinkedListNode;
		currNode->data = val;
		currNode->next = NULL;
		if (backNode == NULL)
		{
			frontNode = currNode;
			backNode = currNode;
		}
		else
		{
			backNode->next = currNode;
			backNode = currNode;
		}
	}
	void push_front(int val)
	{
		SinglyLinkedListNode* currNode = new SinglyLinkedListNode;
		currNode->data = val;
		if (frontNode == NULL)
		{
			currNode->next = NULL;
			frontNode = currNode;
			backNode = currNode;
		}
		else
		{
			currNode->next = frontNode;
			frontNode = currNode;
		}
	}
};
int main()
{
	SinglyLinkedList slList{ NULL, NULL };

	slList.push_back(5);
	slList.push_back(6);

	slList.push_front(4);
	slList.push_front(3);

	slList.push_back(7);

	slList.push_front(2);

	slList.push_back(8);

	slList.push_front(1);

	for (SinglyLinkedListNode* currNode = slList.frontNode; currNode; currNode = currNode->next)
		std::cout << currNode->data << " ";
	return 0;
}
