#pragma once

template <class T>
class List
{
public:
	class Node
	{
	public:
		T data;
		Node *next;
		Node(T data, Node *next) : data(data), next(next) {}
		Node(Node *next) : data(), next(next) {}
		Node(T data) : data(data), next(nullptr) {}
		Node() : data(), next(nullptr) {}
	};
	Node *head;
	Node *tail;
	int size;
	List();
	~List();
	template <class... Args>
	List(const T &data, Args &&...args);
	template <class... Args>
	void Add(const T &data, Args &&...args);
	void Insert(T data, int index);
	void RemoveAt(int index);
	void Remove(T data);
	void Sort();
	static List<T> *Create();

	class Iterator
	{
	private:
		Node *current;

	public:
		Iterator(Node *node) : current(node) {}
		// 重载解引用运算符
		T &operator*() { return current->data; }
		// 重载前进运算符
		Iterator &operator++()
		{
			if (current)
			{
				current = current->next;
			}
			return *this;
		}
		// 重载比较运算符
		bool operator!=(const Iterator &other) const
		{
			return current != other.current;
		}
	};
	// 返回链表的起始迭代器
	Iterator begin() { return Iterator(head->next); }
	// 返回链表的结束迭代器
	Iterator end() { return Iterator(nullptr); }

private:
	void Add();
};

#include "List.tpp"
