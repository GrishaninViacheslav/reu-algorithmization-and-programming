// Сегодня на занятии обсуждаем реализацию
// базовых операций с однонаправленным линейным списком:
// 1. Создание пустого списка.

#include <iostream>
struct SinglyLinkedListNode
{
	SinglyLinkedListNode* next;
	int data;
};
struct SinglyLinkedList
{
	SinglyLinkedListNode* prevNode;
	void push_front(int val)
	{
		SinglyLinkedListNode* node = new SinglyLinkedListNode;
		node->data = val;
		node->next = prevNode;
		prevNode = node;
	}
};
int main()
{
	SinglyLinkedList slList{ NULL };
	return 0;
}
