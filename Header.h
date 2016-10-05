//
//  Header.h
//  MovieAnalyzer
//
//  Created by Chad Williams on 1/6/16.
//  Copyright (c) 2016 Chad Williams. All rights reserved.
//

#ifndef MovieAnalyzer_Header_h
#define MovieAnalyzer_Header_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <vector>
#define  dir  "/Users/cbw/Documents/Code/MovieAnalyzer/"

using namespace std;

class blob
{
public:
    int limit,w,h,frames,life;
    vector<int> loc;
    bool counted;
    int *  p;
    
    blob(int ,int , int , int, int);
    blob(int ,int , int , int, vector<int>, int);
    blob();
    void copyArray(vector<blob>,int);
    void convertInd();
    bool areRads(blob);
    bool isNeibs(blob);
    bool areSame(blob);
    vector<int> findRadPts(int);
    vector<int> findNeibs(int);
    void combine(blob);
    void setIndex(int, int);
    void setLife(int);
    void setCounted(bool);
    vector<int> getIndex();// {return loc;}
    int * getPointer();
    int getIndex(int);
    int getLimit() {return limit;}
    int getWidth() {return w;}
    int getHeight() {return h;}
    int getFrames() {return frames;}
    int getLife() {return life;}
    bool getCounted() {return counted;}
    //delete [];
};


class marray
{
public:
    int h, w,frames,limit, sdcut,index,numBlobs=0,start,end;
    vector<int> blobs, blobInd, data;
    vector<blob> obs;
    
    marray (int,int,int,int,int,int);
    //int * fillArray(char *);
    int countBlobs(int,int);
    int countBlobs();
    float average(int);
    float stdev(int,float);
    vector<int> fillArray(char *);
    void printArray(vector<int>,int,int,int);
    void printArray(vector<float>,int,int,int);
    vector<int> traceBlobs();
    vector<blob> getBlobArray(int);
    bool isBig(int);
    vector<int> findNeibs(int);
    vector<blob> findBlobMass(vector<blob>);
    bool areNeibs(int, int);
    void printBlobArray(vector<blob>,int);
    

    //blob * getBlobArray(int);
    vector<int> findBlobs(int);
    int getLimit() {return limit;}
    int getWidth() {return w;}
    int getHeight() {return h;}
    int getFrames() {return frames;}
    int getCutOff() {return sdcut;}
    
};


#endif
