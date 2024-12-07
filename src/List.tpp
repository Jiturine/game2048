#pragma once
#include "List.h"

template <class T>
List<T>::List()
{
	head = new Node();
	tail = head;
	size = 0;
}

template <class T>
List<T>::~List()
{
	Node *p;
	while (head->next != nullptr)
	{
		p = head->next;
		head->next = p->next;
		delete p;
	}
	delete head;
}

template <class T>
template <class... Args>
List<T>::List(const T &data, Args &&...args)
{
	head = new Node();
	tail = head;
	size = 0;
	Add(data, args...);
}

template <class T>
template <class... Args>
void List<T>::Add(const T &data, Args &&...args)
{
	Node *p = new Node(data);
	tail->next = p;
	tail = p;
	size++;
	Add(args...);
}

template <class T>
void List<T>::Insert(T data, int index)
{
	if (index > size)
		return;
	Node *p = head;
	for (int i = 1; i <= index; i++)
	{
		p = p->next;
	}
	Node *q = new Node(data, p->next);
	p->next = q;
	if (p == tail)
	{
		tail = q;
	}
	size++;
}

template <class T>
void List<T>::RemoveAt(int index)
{
	if (index > size)
	{
		return;
	}
	Node *p = head;
	for (int i = 1; i < index; i++)
	{
		p = p->next;
	}
	Node *q = p->next;
	p->next = q->next;
	delete q;
	size--;
}

template <class T>
void List<T>::Remove(T data)
{
	Node *p = head;
	bool find = false;
	while (p->next != nullptr)
	{
		if (p->next->data == data)
		{
			find = true;
			break;
		}
		p = p->next;
	}
	if (!find)
	{
		return;
	}
	Node *q = p->next;
	p->next = q->next;
	delete q;
	size--;
	return;
}

template <class T>
List<T> *List<T>::Create()
{
	List<T> *p = new List<T>();
	return p;
}

template <class T>
void List<T>::Add()
{
	return;
}
