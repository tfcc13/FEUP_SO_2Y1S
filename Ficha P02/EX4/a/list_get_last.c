#include "list.h"

int list_get_last(list *l) {
	node* q = l->first;
 	while(q->next != NULL) {
 		q = q->next;
 	}
 	return q->val;
}
