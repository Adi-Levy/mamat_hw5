#include <math.h> 
#include "polynom.h"

polynom::polynom(int order, int* coefs) : func(), n_(order) {
    coefs_ = new int[order + 1];
    for (int i = 0; i <= order; ++i) {
        coefs_[i] = coefs[i];
    }
}

polynom::polynom(polynom& p) : func(p), n_(p.n_) {
    coefs_ = new int[p.n_ + 1];
    for (int i = 0; i <= p.n_; ++i) {
        coefs_[i] = p.coefs_[i];
    }
}

polynom::~polynom() {
    delete[] coefs_;
}

polynom polynom::operator+(polynom& p) {
    int deg = (n_ > p.n_) ? n_ : p.n_;
    int* new_coefs = new int[deg+1];
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    for (int i = 0; i <= deg; ++i) {
        if (i <= p.n_)
            new_coefs[i] += p.coefs_[i];
        if (i <= n_)
            new_coefs[i] += coefs_[i];
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

polynom polynom::operator-(polynom& p) {
    int deg = (n_ > p.n_) ? n_ : p.n_;
    int* new_coefs = new int[deg+1];
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    for (int i = 0; i <= deg; ++i) {
        if (i <= p.n_)
            new_coefs[i] -= p.coefs_[i];
        if (i <= n_)
            new_coefs[i] += coefs_[i];
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

polynom polynom::operator*(polynom& p) {
    int deg = n_+p.n_;
    int* new_coefs = new int[deg+1];
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    for (int i = 0 ; i <= n_ ; ++i) {
        for (int j = 0; j <= p.n_; ++j) {
            new_coefs[i + j] += coefs_[i] * p.coefs_[j];
        }
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

int polynom::f(const int& x) {
    int value = 0;
    for (int i = 0; i <= n_; ++i) {
        value += (int)((*(coefs_ + i)) * pow(x, i));
    }
    return value;
}

polynom& polynom::Derivative() const {
    int deg = n_ - 1;
    int* new_coefs = new int[deg + 1];
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = coefs_[i + 1] * (i + 1);
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

polynom& polynom::Integral() const {
    int deg = n_ + 1;
    int* new_coefs = new int[deg + 1];
    new_coefs[0] = 0;
    for (int i = 1; i <= deg; ++i) {
        new_coefs[i] = coefs_[i - 1] / i;
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

void polynom::printcoefs(ostream& os)  const {
    int allZero = 1;
    for (auto i = n_ ; i>=0; i--) {
        if (coefs_[i]>0) {
            allZero = 0;
            if(i!=n_){
	            os << "+";
            }
            if (coefs_[i]!=1 || i==0){
	            os << coefs_[i];
            }
            if(i>0) {
	            os << "x";
	            if (i>1) 
	                os << "^" << i ;
            }
        }
        else if(coefs_[i]<0) {
            allZero = 0;
            if (coefs_[i]!=-1 || i==0){
	            os << coefs_[i];
            }
            else 
	            os << "-";
            if(i>0) {
	            os << "x";
	            if (i>1) 
	                os << "^" << i ;
            }
        }
        else if(i==0 && allZero == 1){ //coefs_[i]==0
            os << "0";
	        continue;
        }
    }
}

void polynom::print(ostream& os) const {
    polynom d = this->Derivative();
    polynom in = this->Integral();
    printcoefs(os);
    os << endl;
    os << "Derivative: ";
    d.printcoefs(os);
    os << endl;
    os << "Integral: ";
    in.printcoefs(os);
    os << "+C" << endl;
}
