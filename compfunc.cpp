#include <math.h>
#include <string>
#include "compfunc.h"

/*
 Function: compfunc C'tor
 Abstract: creates a new compfunc object.
 Parameters: outter - the outter function in the new compound function
             inner - the inner function in the new compound function
 Return: a new compfunc object.
 */
compfunc::compfunc(func& outter, func& inner) : outter_(&outter), inner_(&inner) {}

/*
 Function: f (evaluator)
 Abstract: evaluates the compfunc y value for the givven x
 Parameters: x - int, the x coordinate for the point calc
 Return: int, the y coordinate for the point.
 */
int compfunc::f(const int& x) {
	return outter_->f(inner_->f(x));
}

/*
 Function: print
 Abstract: adds specific compfunc prints to the osstream
 Parameters: os - ostream object to add the print data to
 Return: N/A
 */
void compfunc::print(ostream& os) const { os << endl; }
