#pragma once

#include "polynom.h"

using namespace std;

class compfunc : public func {
public:
    compfunc(func& outter, func& inner);
    virtual int f(const int& x);

protected:
    func* outter_;
    func* inner_;
    virtual void print(ostream& os) const;
};
