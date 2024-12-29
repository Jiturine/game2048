#pragma once
#include <concepts>
#include "Log.h"

template <class T>
class List
{
  private:
	class Node;

  public:
	Node *head;
	Node *tail;
	int size;
	List();
	~List();
	template <class U, class... Args>
		requires std::same_as<std::remove_cvref_t<U>, T>
	void Add(U &&data, Args &&...args);
	template <class U>
		requires std::same_as<std::remove_cvref_t<U>, T>
	void Add(U &&data);
	void Insert(T data, int index);
	void RemoveAt(int index);
	void Remove(const T &data);
	void RemoveToTen();
	void Sort();

	class Iterator;
	Iterator begin();
	Iterator end();
};

#include "List.tpp"
