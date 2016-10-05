//
//  blob.h
//  MovieAnalyzer
//
//  Created by Chad Williams on 1/6/16.
//  Copyright (c) 2016 Chad Williams. All rights reserved.
//

#ifndef __MovieAnalyzer__blob__
#define __MovieAnalyzer__blob__

#include <iostream>
#include "Header.h"
#include "marray.h"

class blob
{
public:
    int *loc,limit,w,h,frames;

    blob(int ,int , int , int, int);
    blob();
    void copyArray(blob *,int);
    void convertInd();
    bool areRads(blob);
    bool areNeibs(blob);
    int * findRadPts(int);
    int * findNeibs(int);
    void setIndex(int);
    //int getIndex() {return loc;}
    int getLimit() {return limit;}
    int getWidth() {return w;}
    int getHeight() {return h;}
    int getFrames() {return frames;}
    //delete [];
};

#endif /* defined(__MovieAnalyzer__blob__) */
