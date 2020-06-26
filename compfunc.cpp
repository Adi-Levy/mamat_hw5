#include <math.h>
#include <string>
#include "compfunc.h"

compfunc::compfunc(func& outter, func& inner) : outter_(&outter), inner_(&inner) {}

int compfunc::f(const int& x) {
	return outter_->f(inner_->f(x));
}

void compfunc::print(ostream& os) const { os << endl; }
