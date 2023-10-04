#include "vector.h"

vector* vector_scale(double s, vector* v1) {
	
	return vector_new(v1->x * s, v1->y*s, v1->z*s); 
}
