//
//  blob.cpp
//  MovieAnalyzer
//
//  Created by Chad Williams on 1/6/16.
//  Copyright (c) 2016 Chad Williams. All rights reserved.
//

#include "Header.h"
using namespace std;

blob::blob(int l,int wd, int ht, int f, int ind)
{
    loc.push_back(ind);
    p = loc.data();
    limit=l;
    w=wd;
    h=ht;
    frames=f;
    life=0;
}

blob::blob(int l,int wd, int ht, int f, vector<int> ind,int size)
{
    loc = ind;
    limit=l;
    w=wd;
    h=ht;
    frames=f;
    life=0;
}

blob::blob(){}

void blob::convertInd()
{
    for (int i =0; i<loc.size(); i++)
    {
        while (loc[i]>=limit)//while (loc[i]>=limit)
            this->setIndex(i,loc[i]-limit);//this->setIndex(loc[i]-limit);
    }
}

void blob::combine(blob blob2)//Combine blob2 to this blob
{
    int len = (int)blob2.loc.size();
    for (int i = 0; i<len; i++)
        this->loc.push_back(blob2.getIndex(i));
}

bool blob::areSame(blob b)
{
    bool same=false;
    
    int len1 = (int)this->loc.size();
    int len2 = (int) b.loc.size();
    
    for (int i = 0; i<len1; i++)
    {
        for (int j = 0; j<len2; j++)
        {
            if (this->loc[i]==b.loc[j])
                same = true;
        }
    }
    
    return same;
}

bool blob::areRads(blob blobComp)// Determines if blobComp is radially outward of the calling blob
{
    bool rads=false;
    int sizeThis = (int)loc.size();
    int sizeComp = (int)blobComp.loc.size();
    int thisInd, compInd;
    vector<int> thisVec = this->getIndex();
    vector<int> compVec = blobComp.getIndex();
    
    if (this->areSame(blobComp))
        rads=false;
    else
    {
        for (int i=0; i<sizeThis; i++)
        {
            thisInd = thisVec[i];
            for (int j=0; j<sizeComp; j++)
            {
                compInd = compVec[j];
                vector<int> radPts = findRadPts(thisInd);
            
                if (radPts[compInd]==1)
                    rads = true;
            
            }
        }
    }
    
    return rads;
}

vector<int> blob::findRadPts(int index)//Return all points in a 45 deg cone radially outward from a given point
{
    vector<int> rads(limit);
    int ind=index,row,col,rowstart,colstart;
    
    if (index<0 ||  index >=limit)// make sure index is valid
    {
        printf("Invalid Index, zero array returned\n");
        return rads;
    }
    
    rowstart = index/w;
    row=rowstart;
    colstart=ind%w;
    
    while (row>=0)//Fill upper half
    {
        col=colstart;
        while(col/w == 0)
        {
            rads[row*w+col]=1;
            col++;
        }
        row--;
        colstart++;
    }
    
    row=rowstart+1;
    colstart =ind%w+1;
    
    while (row<h)//Fill lower half
    {
        col=colstart;
        while(col/w == 0)
        {
            rads[row*w+col]=1;
            col++;
        }
        row++;
        colstart++;
    }
    
    //printArray(rads,1,1,1);
    return rads;
}



bool blob::isNeibs(blob blobComp)//Determines if blobComp is neighbors to the calling blob (does not actually matter which is which)
{
    bool neibs,found;
    int sizeThis = (int)loc.size();
    int sizeComp = (int)blobComp.loc.size();
    int thisInd, compInd;
    vector<int> thisVec = this->getIndex();
    vector<int> compVec = blobComp.getIndex();
    
    for (int i=0; i<sizeThis; i++)
    {
        thisInd = thisVec[i];
        for (int j=0; j<sizeComp; j++)
        {
            
            compInd = compVec[j];
            vector<int> neibPts = findNeibs(thisInd);
            
            if (neibPts[compInd]==1)
                found = true;
        }
    }
    
    if (found)
        neibs = true;
    else
        neibs = false;
    
    
    return neibs;
}

vector<int> blob:: findNeibs(int index) // Assumes a grid of at least 2x2
{
    vector<int> neibs(limit);
    
    //Find the neighbors of each point in the grid, including diagonals
    if (index<0 ||  index >=limit)// make sure index is valid
    {
        printf("Invalid Index, zero array returned\n");
        return neibs;
    }
    else
    {
        //neibs[index]=1;
        if ((index+1)%w !=0)//Right side of grid
            neibs[index+1]=1;
        if (index%w !=0)//left
            neibs[index-1]=1;
        if (index/w < (h-1))//top
            neibs[index+w]=1;
        if (index/w > 0)//bottom
            neibs[index-w]=1;        
        if ((index+1)%w !=0 && index/w < (h-1))//top right
            neibs[index+w+1]=1;
        if ((index+1)%w !=0 && index/w > 0)//bottom right
            neibs[index-w+1]=1;
        if (index%w !=0 && index/w < (h-1))//top left
            neibs[index+w-1]=1;
        if (index%w !=0 && index/w > 0)//bottom left
            neibs[index-w-1]=1;
    }
    
    //printArray(neibs,1,1,1);
    return neibs;
}

void blob:: setIndex(int i,int index)
{
    loc[i] = index;
}

vector<int> blob::getIndex()
{
    return loc;
}

int blob::getIndex(int i)
{//printf("loc = %i\n",loc[i]);
    //for (int m = 0; m < 5; m++)
      //  printf("loc 2 = %i\n",p[m]);
    return loc[i];
}

int * blob::getPointer()
{
    return p;
}

void blob:: setLife(int age)
{
    life = age;
}

void blob:: setCounted(bool flag)
{
    counted = flag;
}


void blob:: copyArray(vector<blob> copyTo,int size)
{
    for (int i =0; i<size; i++)
        copyTo[i]=this[i];
}
