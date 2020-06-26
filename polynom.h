#ifndef _POLY_F
#define _POLY_F

#include "func.h"

using namespace std;


class polynom : public func {
public:
    polynom(int order, int* coefs);
    polynom(polynom& p);
    ~polynom();
    void printcoefs(ostream&) const;
    polynom operator+(polynom& p);
    polynom operator-(polynom& p);
    polynom operator*(polynom& p);
    polynom Derivative() const;
    polynom Integral() const;
    virtual int f(const int& x);

protected:
    int n_; //order of the polynom
    int* coefs_; //coefficients
    virtual void print(ostream& os) const;
};



#endif
 
