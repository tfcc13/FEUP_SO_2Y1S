#include "list.h"

void list_print(list* l) {
		if (l->first == NULL) {
			printf("theres no list biiiiii");
		}
		
	else {
	int v;
	node* p = l->first;
	
	
	while (p->next != NULL) {
		v = p->val;
		p = p->next;
		printf(" %c", v);
		printf("\n");
	}	
	
}
}
