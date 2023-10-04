#include "complex.h"
complex* complex_div(complex* z, complex* w){
	double divisor = (w->x * w->x) + (w->y*w->y);
	return complex_new((z->x * w->x + z->y * w->y) / divisor, (z->y * w->x - z->x * w->y) / divisor);

}
