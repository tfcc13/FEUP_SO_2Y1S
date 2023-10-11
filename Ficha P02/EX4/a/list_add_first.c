#include "list.h"

void list_add_first(int val, list *l) {
	node* p = node_new(val, NULL);
		
	if (l->size != 0) {
		node* temp = l->first;
		p->next = temp;
		l->first = p;
	}
	
	else {
		l->first = p;
	}

}
