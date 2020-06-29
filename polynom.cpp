#include <math.h> 
#include <string>
#include "polynom.h"

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom::polynom(int order, int* coefs) : func(), n_(order) {
    coefs_ = new int[order + 1];
    for (int i = 0; i <= order; ++i) {
        coefs_[i] = coefs[i];
    }
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom::polynom(const polynom& p) : func(p), n_(p.n_) {
    coefs_ = new int[p.n_ + 1];
    for (int i = 0; i <= p.n_; ++i) {
        coefs_[i] = p.coefs_[i];
    }
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom::~polynom() {
    delete[] coefs_;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom polynom::operator+(polynom& p) {
    // find the larger coefs array and work by it's size
    int deg = (n_ > p.n_) ? n_ : p.n_;
    int* new_coefs = new int[deg+1];
    // zero new coefs_ array
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    // fill new coefs_ array
    for (int i = 0; i <= deg; ++i) {
        if (i <= p.n_)
            new_coefs[i] += p.coefs_[i];
        if (i <= n_)
            new_coefs[i] += coefs_[i];
    }
    // resize coefs_ array
    for (int i = deg; i >= 0; --i) {
        deg = i;
        if (new_coefs[i] != 0) {
            break;
        }
    }
    int* proper_coef = new int[deg + 1];
    for (int i = deg; i >= 0; --i) {
        proper_coef[i] = new_coefs[i];
    }
    delete[] new_coefs;
    polynom r_p = polynom(deg, proper_coef);
    delete[] proper_coef;
    return r_p;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom polynom::operator-(polynom& p) {
    // find the larger coefs array and work by it's size
    int deg = (n_ > p.n_) ? n_ : p.n_;
    int* new_coefs = new int[deg + 1];
    // zero new coefs_ array
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    // fill new coefs_ array
    for (int i = 0; i <= deg; ++i) {
        if (i <= p.n_)
            new_coefs[i] -= p.coefs_[i];
        if (i <= n_)
            new_coefs[i] += coefs_[i];
    }
    // resize coefs_ array
    for (int i = deg; i >= 0; --i) {
        deg = i;
        if (new_coefs[i] != 0) {
            break;
        }
    }
    int* proper_coef = new int[deg + 1];
    for (int i = deg; i >= 0; --i) {
        proper_coef[i] = new_coefs[i];
    }
    delete[] new_coefs;
    polynom r_p = polynom(deg, proper_coef);
    delete[] proper_coef;
    return r_p;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom polynom::operator*(polynom& p) {
    // add degs when multiplying
    int deg = n_+p.n_;
    int* new_coefs = new int[deg+1];
    // zero new coefs_ array
    for (int i = 0; i <= deg; ++i) {
        new_coefs[i] = 0;
    }
    // fill new coefs_ array
    for (int i = 0 ; i <= n_ ; ++i) {
        for (int j = 0; j <= p.n_; ++j) {
            new_coefs[i + j] += coefs_[i] * p.coefs_[j];
        }
    }
    // resize coefs_
    for (int i = deg; i >= 0; --i) {
        deg = i;
        if (new_coefs[i] != 0) {
            break;
        }
    }
    int* proper_coef = new int[deg + 1];
    for (int i = deg; i >= 0; --i) {
        proper_coef[i] = new_coefs[i];
    }
    delete[] new_coefs;
    polynom r_p = polynom(deg, proper_coef);
    delete[] proper_coef;
    return r_p;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
int polynom::f(const int& x) {
    int value = 0;
    for (int i = 0; i <= n_; ++i) {
        value += (int)((*(coefs_ + i)) * pow(x, i));
    }
    return value;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom polynom::Derivative() const {
    int deg;
    int* new_coefs = nullptr;
    // if not zero deg polynom remove 1 from deg and calc new coefs_
    if (n_ > 0) {
        deg = n_ - 1;
        new_coefs = new int[deg + 1];
        for (int i = 0; i <= deg; ++i) {
            new_coefs[i] = coefs_[i + 1] * (i + 1);
        }
    }
    // if zero deg polynom turn it into the zero polynom
    else {
        deg = n_;
        new_coefs = new int[1];
        new_coefs[0] = 0;
    }
    polynom r_p = polynom(deg, new_coefs);
    delete[] new_coefs;
    return r_p;
}

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
polynom polynom::Integral() const {
    // if the zero polynom return the zero polynom and C will be written at print
    if (n_ == 0 && coefs_[0] == 0)
        return polynom(*this);
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

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
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

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
void polynom::print(ostream& os) const {
    polynom d = this->Derivative();
    polynom in = this->Integral();
    printcoefs(os);
    os << endl;
    os << "Derivative: ";
    d.printcoefs(os);
    os << endl;
    os << "Integral: ";
    // don't add + sign if the zero polynom in the integral
    if (in.n_ == 0 && in.coefs_[0] == 0) {
        os << "C" << endl;
    }
    else {
        in.printcoefs(os);
        os << "+";
        os << "C" << endl;
    }
    
}
