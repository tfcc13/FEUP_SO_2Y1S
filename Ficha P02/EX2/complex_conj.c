#include "complex.h"
complex* complex_conj(complex* z){
	z->y = -(z->y);
	return z;
}
