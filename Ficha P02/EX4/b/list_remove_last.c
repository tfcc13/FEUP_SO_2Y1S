#include "list.h"

void list_remove_last(list *l) {
	node* q = l->first;
	node* p = l->first;
 	while(q->next != NULL) {
 		p = q;
 		q = q->next;
 	}
 	
 	p->next = NULL;
 	l->size--;
 	free(q);
 	
 	
}
}
