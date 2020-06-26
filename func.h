#ifndef _F
#define _F
#include <map>
#include <iostream>



using std::map;
using std::ostream;


class func {
protected:
    int maxVal_; //maximum of all inputs
    int minVal_; //minimum of all inputs
    map<int,int> fmap_; //holds inputs and corresponding outputs
    void plot(ostream& os) const ; //plot fmap_
    virtual int f(const int& x) = 0;
public:
    friend ostream& operator<<(ostream&, const func&);
    func& operator<<(const int& x);
};


#endif
