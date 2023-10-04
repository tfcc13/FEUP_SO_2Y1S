#include "vector.h"
#include <math.h>

double vector_mod(vector* v1) {
	return sqrt(v1->x*v1->x + v1->y*v1->y + v1->z*v1->z);
}

