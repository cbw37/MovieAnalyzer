//
//  marray.h
//  MovieAnalyzer
//
//  Created by Chad Williams on 1/6/16.
//  Copyright (c) 2016 Chad Williams. All rights reserved.
//

#ifndef __MovieAnalyzer__marray__
#define __MovieAnalyzer__marray__

#include <iostream>
#include "blob.h"
#include "Header.h"

class marray
{
public:
    int h, w,frames,limit, count,sdcut,index,numBlobs=0;
    int * blobs, * blobInd, * data;
    //blob * obs;

    marray (int,int,int,int,int,int);
    //int * fillArray(char *);
    int countBlobs(int,int);
    int countBlobs();
    float average(int);
    float stdev(int,float);
    int * fillArray(char *);
    void printArray(int *,int,int,int);
    void printArray(float *,int,int,int);
    void traceBlobs();
    //blob * getBlobArray(int);
    int * findBlobs(int);
    int getLimit() {return limit;}
    int getWidth() {return w;}
    int getHeight() {return h;}
    int getFrames() {return frames;}
    int getCutOff() {return sdcut;}

};

#endif /* defined(__MovieAnalyzer__marray__) */
