#pragma once
using namespace std;

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
	static List<T> *Create();

private:
	void Add();
};
#include "List.tpp"
