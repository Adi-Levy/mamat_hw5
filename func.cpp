#include <math.h>
#include <vector>
#include <algorithm>
#include "func.h"

/*
 Function: func C'tor
 Abstract: creates a new function with an empty map and sets the default
            min and max values of x currently in the function.
 Parameters: N/A
 Return: new function object
 */
func::func() : maxVal_(0), minVal_(0) {}

/*
 Function: func copyC'tor
 Abstract: creates a new function based on the one givven to it
 Parameters: f - a function to copy into the new function
 Return: new function object
 */
func::func(const func& f) : maxVal_(f.maxVal_), minVal_(f.minVal_) {
    fmap_ = f.fmap_;
}

/*
 Function: func D'tor
 Abstract: frees func resources and removes from memory
 Parameters: N/A
 Return: N/A
 */
func::~func() {}

/*
 Function: plot
 Abstract: plots the points in the function map into the given 
            ostream object
 Parameters: os - an ostream object to write the plot to
 Return: N/A
 */
void func::plot(ostream& os) const {
 
    std::vector<int> sortImage;
    
    sortImage.clear();
    for ( auto it : fmap_){
        sortImage.push_back(it.second);
    }
    // plot only if there are points in the map
    if (sortImage.size() > 0) {
        // sort sortImage
        std::sort(sortImage.begin(), sortImage.end());
        // flip sortImage (reverse)
        std::reverse(sortImage.begin(), sortImage.end());


        for (auto it_im = sortImage.begin();
            it_im != sortImage.end(); ++it_im) {
            if (it_im != sortImage.begin() && *it_im == *(it_im - 1)) { //remove repeated
                it_im = sortImage.erase(it_im) - 1;

            }
        }

        for (auto it_im = sortImage.begin();
            it_im != sortImage.end(); ++it_im) {
            // print y axis values
            int x_anchor = minVal_;
            if (*it_im < -9)
                os << *it_im;
            else
                if ((*it_im < 0) || (*it_im > 9))
                    os << " " << *it_im;
                else
                    os << "  " << *it_im;

            // print function point
            for (auto it_dom : fmap_) {
                if (it_dom.second == *it_im) {
                    int x = it_dom.first;
                    int spaces = x - x_anchor;
                    int i = 0;
                    while (i < spaces) {
                        os << "   ";
                        i++;
                    }
                    os << "*  ";
                    x_anchor = x + 1;
                }

            }

            os << std::endl;
            if ((it_im + 1) != sortImage.end()) { //print empty lines
                int lines = *it_im - *(it_im + 1) - 1;
                int i = 1;

                while (i < lines + 1) {
                    if (*it_im - i < -9)
                        os << *it_im - i;
                    else
                        if ((*it_im - i < 0) || (*it_im - i > 9))
                            os << " " << *it_im - i;
                        else
                            os << "  " << *it_im - i;
                    os << std::endl;
                    i++;

                }
            }

        }//for sortImage

        //print x axis
        os << " ";
        for (auto i = minVal_; i < maxVal_ + 1; i++) {
            if (i < 0) os << " " << i;
            else os << "  " << i;
        }
        os << std::endl;
    }
}

/*
 Function: operator<<
 Abstract: overloaded operator that acts as a method to input data point
            pairs (x,f(x)) into the function.
 Parameters: x - an int location on x axis to add to the function.
                    method calcs the y part of the point on it's own.
 Return: func object (self by refrence)
 */
func& func::operator<<(const int& x) {
    std::pair<int, int> p;
    p.first = x;
    p.second = f(x);
    fmap_.insert(p);
    // if this is the first point added
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

/*
 Function: operator<<
 Abstract: overloaded ostream operator. adds the option of inserting 
            a func object into the ostream.
 Parameters: os - the os by reference to be added to.
             f - the function to push to the ostream.
 Return: ostream object by refrence with the added func print data.
 */
ostream& operator<<(ostream& os, const func& f) {
    f.print(os);
    f.plot(os);
    return os;
}
