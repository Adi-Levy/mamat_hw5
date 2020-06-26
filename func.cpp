#include <math.h>
#include <vector>
#include <algorithm>
#include "func.h"



func::func() : maxVal_(0), minVal_(0) {}

func::func(func& f) : maxVal_(f.maxVal_), minVal_(f.minVal_) {
    fmap_ = f.fmap_;
}

void func::plot(ostream& os) const {
 
    std::vector<int> sortImage;
    
    sortImage.clear();
    for ( auto it : fmap_){
        sortImage.push_back(it.second);
    }
    // sort sortImage
    std::sort(sortImage.begin(), sortImage.end());
    // flip sortImage (reverse)
    std::reverse(sortImage.begin(), sortImage.end());
  
    for ( auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
        if(it_im!=sortImage.begin() && *it_im==*(it_im-1)){ //remove repeated
            it_im = sortImage.erase(it_im)-1;
      
        }
    }
 
    for (auto it_im = sortImage.begin();
       it_im != sortImage.end(); ++it_im) {
        // print y axis values
        int x_anchor=minVal_;
        if(*it_im<-9) 
            os <<*it_im;
        else
            if((*it_im<0) || (*it_im>9)) 
	            os<<" "<<*it_im;
            else 
	            os<<"  "<<*it_im;
        
        // print function point
        for (auto it_dom : fmap_) {
            if(it_dom.second == *it_im){
	            int x=it_dom.first;
	            int spaces= x-x_anchor;
	            int i=0;
	            while(i<spaces){
	                os<<"   ";
	                i++;
	            }
	            os<<"*  ";
	            x_anchor=x+1;
            }

        }

        os<<std::endl;
        if((it_im+1)!=sortImage.end()){ //print empty lines
            int lines=*it_im-*(it_im+1)-1;
            int i=1;
      
            while(i<lines+1){
	            if(*it_im-i<-9) 
	                os <<*it_im-i;
	            else 
	                if( (*it_im-i<0) || (*it_im-i>9) )
	                    os<<" "<<*it_im-i;
	                else 
	                    os<<"  "<<*it_im-i;
	            os<<std::endl;
	            i++;

            }
        }

    }//for sortImage

    //print x axis
    os<< " ";
    for (auto i=minVal_; i<maxVal_+1;i++){
        if(i<0) os<<" "<<i;
        else os<<"  "<<i;
    }
    os<<std::endl;
}

func& func::operator<<(const int& x) {
    std::pair<int, int> p;
    p.first = x;
    p.second = f(x);
    fmap_.insert(p);
    if (fmap_.size() == 1) {
        maxVal_ = minVal_ = x;
    }
    else {
        // if we entered a new value to fmap_ update nim and max val
        if (fmap_.at(x) == p.second) {
            if (x < minVal_)
                minVal_ = x;
            else if (x > maxVal_)
                maxVal_ = x;
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const func& f) {
    f.print(os);
    f.plot(os);
    return os;
}
