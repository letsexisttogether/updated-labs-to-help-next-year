#include <iostream>
#include <malloc.h>
#include <stdint.h>

#include "./MenuItem.h"
#include "List.h"
#include "Date.h"
#include "Worker.h"
#include "Int32Holder.h"

int main()
{	
	List<int> list;
	list.Add(3);
	list.Add(5);
	list.Add(6);
	list.Add(7);

	return EXIT_SUCCESS;
}