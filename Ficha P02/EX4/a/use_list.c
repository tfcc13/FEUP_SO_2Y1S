#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main (int argc, char** argv) {
	
	list* my_list = list_new();

    list_add_first(3, my_list);
    list_add_last(5, my_list);
    list_add_last(7, my_list);
    list_add_first(2, my_list);

    list_print(my_list);

    printf("Size of the list: %d\n", list_size(my_list));
    printf("First element: %d\n", list_get_first(my_list));
    printf("Last element: %d\n", list_get_last(my_list));

    list_remove_first(my_list);
    list_remove_last(my_list);

    list_print(my_list);
	
	return 0;

}
