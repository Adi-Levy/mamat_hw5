#pragma once

#include "polynom.h"

using namespace std;

class compfunc : public func {
public:
    compfunc(polynom& outter, polynom& inner);
    virtual int f(const int& x);

protected:
    polynom outter_;
    polynom inner_;
    virtual void print(ostream& os) const;
};
