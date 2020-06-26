#include <math.h>
#include <vector>
#include "func.h"



func::func() : maxVal_(), minVal_() {
    map<int, int> fmap_;
}

void func::plot(ostream& os) const {
 
    std::vector<int> sortImage;
    
    sortImage.clear();
    for ( auto it : fmap_){
        //complete code here: insert the image of the function into sortImage
        sortImage.push_back(it.second);
    }
    //complete code here: sort sortImage
    //complete code here: flip sortImage (reverse)
  
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
        for (auto it_dom : fmap_/*complete code here: loop over map*/) {
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
    if (fmap_.at(x) == p.second) {
        if(minVal_
    }
    return *this;
}

ostream& operator<<(ostream& os, const func& f) {
    
}
