#include <iostream>
#include "List.h"

int main()
{
	List<int> list;
	list.Add(1, 2);
	std::cout << list.size << std::endl;
	return 0;
}