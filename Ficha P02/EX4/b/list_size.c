#include "list.h"

int list_size(list *l) {
	
	if (l->first == NULL) {
		return 0;
		}
		
	node* p = l->first;
	int counter = 0;
	
	
	while (p->next != NULL) {
		p = p->next;
		counter++;
	}
	
	return counter;
}
