// Сегодня на занятии обсуждаем реализацию
// базовых операций с однонаправленным линейным списком:
// 3. Вывод на экран содержимого списка.

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
	slList.push_front(1);
	slList.push_front(2);
	slList.push_front(3);
	slList.push_front(4);
	SinglyLinkedListNode* currNode = slList.prevNode;
	while (currNode)
	{
		std::cout << currNode->data << " ";
		currNode = currNode->next;
	}
	return 0;
}
