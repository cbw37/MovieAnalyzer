//
//  marray.cpp
//  MovieAnalyzer
//
//  Created by Chad Williams on 1/6/16.
//  Copyright (c) 2016 Chad Williams. All rights reserved.
//

#include "Header.h"
using namespace std;


marray::marray(int l,int wd, int ht, int f, int c, int i)
{
    limit=l;
    w=wd;
    h=ht;
    frames=f;
    sdcut=c;
    index=i;
    vector<int> data(limit*frames);//Initialize one, single dimensional array for all data
    vector<int> blobs(limit*frames);
}


//printf("For frame %i there are %i blobs\n",i,numBlobs);
//printBlobArray(blobArray,i);


/*int count = 0;
 vector<int> blobInd(limit);
 
 for (int n=0;n<limit;n++)
 {
 if (blobs[limit*i+n]==1)
 {
 blobInd[count]=limit*i+n;
 count++;
 //printf("For frame %i there is a blob at index %i which is blob number %i\n",frame,limit*frame+i,count);
 }
 }
 
 numBlobs = count;
 
 for (int n=0; n<numBlobs; n++)
 {
 blobArray.resize(numBlobs);
 //printf("Inner1: The index for blob %i is %i\n",n,blobInd[n]);
 //blobArray.push_back(blob(limit,w,h,frames,blobInd[n]));
 blobArray[n]=blob(limit,w,h,frames,blobInd[n]);
 //printf("Inner2: The index for blob %i is %i\n",n,blobArray[n].getIndex(0));
 blobArray[n].convertInd();
 //printf("Inner3: The index for blob %i is %i\n\n",n,blobArray[n].getIndex(0));
 }
 //obs[0].getIndex(0);
 //printArray(blobInd,0,1,1);//*/

//blobArray[0].getIndex(0);
//int * point = blobArray[0].getPointer();
//printf("Pointer: %i\n", point[i]);
//printf("BlobArray.size() = %i\n",(int)blobArray.size());
//for (int m = 0; m<blobArray.size();m++)
//  printf("BlobArray[%i]= %i\n",m,blobArray[m].getIndex(0));


vector<int> marray::traceBlobs()
{
    vector<blob> oldBlobArray;
    bool blobsPrevious = false, same, rads, blobsFound = false;
    int oldNumBlobs, lifeSize=100;
    vector<int> lifeTime(lifeSize);

    for (int i=0; i<frames ;i++)//For testing I was using 480-500
    {
        if (countBlobs(i*limit,(i+1)*limit-1)!=0 )
        {
            blobsFound = true;
            vector<blob> blobArray = getBlobArray(i);
            
            if (blobsPrevious)
            {
                for (int n = 0; n<oldNumBlobs; n++)
                    oldBlobArray[n].setCounted(false);
                
                for (int j = 0; j<oldNumBlobs; j++)
                {
                    for (int k = 0; k<numBlobs; k++)
                    {
                        same = oldBlobArray[j].areSame(blobArray[k]);
                        
                        if (same)
                        {printf("Same\n");
                            printf("Lifetime[%i] before: %i\n",oldBlobArray[j].getLife(),lifeTime[oldBlobArray[j].getLife()]);
                            lifeTime[oldBlobArray[j].getLife()]-=1;
                            printf("Lifetime[%i] after: %i\n",oldBlobArray[j].getLife(),lifeTime[oldBlobArray[j].getLife()]);
                            blobArray[k].setLife(oldBlobArray[j].getLife()+1);
                            printf("New Blob Lifetime: %i\n",blobArray[j].getLife());
                            lifeTime[blobArray[k].getLife()]+=1;
                            printf("New Lifetime[%i]: %i\n",blobArray[j].getLife(),lifeTime[blobArray[j].getLife()]);
                            blobArray[k].setCounted(true);
                            oldBlobArray[j].setCounted(true);
                        }
                    }
                }
                
                for (int j = 0; j<oldNumBlobs; j++)
                {
                    for (int k = 0; k<numBlobs; k++)
                    {
                        
                        if(blobArray[k].getCounted()==false)
                        {
                            rads = oldBlobArray[j].areRads(blobArray[k]);
                        
                            if (rads && oldBlobArray[j].getCounted()==false)
                            {printf("Rads\n");
                                lifeTime[oldBlobArray[j].getLife()]-=1;
                                blobArray[k].setLife(oldBlobArray[j].getLife()+1);
                                lifeTime[blobArray[k].getLife()]+=1;
                                blobArray[k].setCounted(true);
                                oldBlobArray[j].setCounted(true);
                            }
                            else
                            {
                                //if (oldBlobArray[j].getCounted()==true && blobArray[k].getCounted()==false)
                                lifeTime[0]+=1;
                            }
                        }
                    }
                }
                
            }
            else
            {
                blobsPrevious = true;
                lifeTime[0]+=numBlobs;
                //printf("numBlobs = %i, lifeTime[0] = %i\n",numBlobs,lifeTime[0]);
                for (int n = 0; n<numBlobs; n++)
                    blobArray[n].setCounted(true);
            }
            
            //oldBlobArray.reserve(numBlobs);
            oldNumBlobs = numBlobs;
            oldBlobArray.clear();
            oldBlobArray = blobArray;
            
            //for (int i=0; i<numBlobs; i++)
            //    printf("The old index for blob %i is %i\nThe new index is %i\n",i,oldBlobArray[i].getIndex(),blobArray[i].getIndex());
        }
        else
        {
            blobsPrevious = false;
            oldNumBlobs = 0;
            numBlobs=0;
        }
        //blobArray.clear();
        //printf("Frame %i has \t %i \t blobs\n",i,numBlobs);//Uncomment "numBlobs=0" right above for this printout to work!
        printf("Frame %i ends with: \n",i);
        for (int m =0; m<lifeSize;m++)
            if (lifeTime[m]!=0)
                printf("For lifetime %i there are %i blobs\n",m,lifeTime[m]);
         printf("Frame %i has %i blobs\n",i,numBlobs);
    }
    //for (int m =0; m<lifeSize;m++)
      //  printf("For lifetime %i there are %i blobs\n",m,lifeTime[m]);
    
    return lifeTime;
}

vector<blob> marray::getBlobArray(int frame) //blob * marray::getBlobArray(int frame)
{
    int count = 0;
    //bool big;
    numBlobs=0;
    vector<int> blobInd(limit);
    vector<blob> blobArray;
    
    for (int i=0;i<limit;i++)
    {
        if (blobs[limit*frame+i]==1)
        {
            //big = isBig(limit*frame+i);
            blobInd[count]=limit*frame+i;
            count++;
        //printf("For frame %i there is a blob at index %i which is blob number %i\n",frame,limit*frame+i,count);
        }
    }

    vector<blob> obs;
    //blob * p = obs.data();
    numBlobs = count;
    
    for (int i=0; i<numBlobs; i++)
    {
        obs.resize(numBlobs); 

        obs[i] = blob(limit,w,h,frames,blobInd[i]);
        //obs.push_back(blob(limit,w,h,frames,blobInd[i]));
        obs[i].convertInd();

        //printf("Inner: The index for blob %i is %i\n",i,obs[i].getIndex(0));
        //obs[i].getIndex(0);
        //*p = blob(limit,w,h,frames,blobInd[i]);
        //p->convertInd();
        //p->getIndex(0);
    }
    //printf("First Print\n");
    //printBlobArray(obs, frame);
    
    if (numBlobs>1)
        blobArray = findBlobMass(obs);
    else
        blobArray = obs;
    //printf("Second Print\n");
    
   
    printBlobArray(blobArray,frame);////////////////////////////
    printArray(blobs,frame,frame+1,1);//////////////////////////////
    return blobArray;
    //return p;
}

vector<blob> marray::findBlobMass(vector<blob> obs)//Given a starting index, find all blobs touching this point, then all blobs touching them, etc
{
    vector<int> neibs;
    bool keepGoing;
    int combCount;
    
    for (int i = 0; i<obs.size(); i++)
    {
        //vector<int> index = obs[i].getIndex();
        keepGoing = true;
        while (keepGoing)
        {
            combCount = 0;
            //printf("Here 1, i=%i, size = %i, j will be %i\n",i,(int)obs.size(),i+1);
            for (int j = i+1; j<obs.size(); j++)
            {
                if (obs[i].isNeibs(obs[j]))
                {
                    obs[i].combine(obs[j]);
                    obs.erase(obs.begin()+j);
                    //obs.shrink_to_fit();
                    combCount++;
                    numBlobs--;
                }
            }
            if (combCount==0)
                keepGoing = false;
        }
    
    }
    
    return obs;
}

bool marray::isBig(int ind)
{
    bool big=false;
    
    vector<int> neibs = findNeibs(ind);
    for (int i = 0; i<neibs.size(); i++)
    {//printf("neibs[%i]=%i, blobs[%i]=%i\n",i,neibs[i],i,blobs[i]);
        if (neibs[i]==1 && blobs[i]==1)
            big = true;
    }
    //printf("Ind = %i, Bool Big = %i\n",ind,big);
    return big;
}

vector<int> marray::findNeibs(int ind)
{
    vector<int> neibs(limit);
    printf("\nFinding Neibs, index = %i\n",ind);
    
    printArray(neibs,0,1,1);
    
    //Find the neighbors of each point in the grid, including diagonals
    if (ind<0 ||  ind >=limit)// make sure index is valid
    {
        printf("Invalid Index, zero array returned\n");
        return neibs;
    }
    else
    {
        //neibs[index]=1;
        if ((ind+1)%w !=0)//Right side of grid
            neibs[ind+1]=1;
        if (ind%w !=0)//left
            neibs[ind-1]=1;
        if (ind/w < (h-1))//top
            neibs[ind+w]=1;
        if (ind/w > 0)//bottom
            neibs[ind-w]=1;
        if ((ind+1)%w !=0 && ind/w < (h-1))//top right
            neibs[ind+w+1]=1;
        if ((ind+1)%w !=0 && ind/w > 0)//bottom right
            neibs[ind-w+1]=1;
        if (ind%w !=0 && ind/w < (h-1))//top left
            neibs[ind+w-1]=1;
        if (ind%w !=0 && ind/w > 0)//bottom left
            neibs[ind-w-1]=1;
    }
    
    printArray(neibs,0,1,1);
    
    return neibs;
}

bool marray::areNeibs(int ind1, int ind2)
{
    bool areNeibs;
    
    vector<int> neibs = findNeibs(ind1);
    if (neibs[ind2]==1)
        areNeibs = true;
    else
        areNeibs = false;
    
    return areNeibs;
}

int marray::countBlobs(int start, int end)
{
    int count = 0;
    for (int i=start;i<=end;i++)
    {
        count+= blobs[i];
    }
    //if (count>0)
      //  printf("There are %i blobs\n",count);
    return count;
}

int marray::countBlobs()
{
    int count = 0;
    for (int i=0;i<limit*frames;i++)
    {
        count+= blobs[i];
    }
    return count;
}

vector<int> marray::findBlobs(int cut)
{
    float avg,temp;//,std;
    
    for (int i=0;i<frames;i++)//Loop over all frames  ////////////Change 10 back to frames, 0
    {
        avg=average(i);
        //std=stdev(i,avg);
        for (int j=0;j<h;j++)               //Loop through columns
        {
            for (int k=0;k<w;k++)           //Loop through rows
            {
                //blobs[i*limit+j*w+k]=abs((float) data[i*limit+j*w+k]-avg)/std;
                //temp=abs((float) data[i*limit+j*w+k]-avg)/std; //Check with standard deviation
                temp = ((float) data[i*limit+j*w+k])/avg;//Check with average
                if (temp>(float)cut)
                {
                    blobs.push_back(1);
                }
                else
                {
                    //printf("size() = %i, index mess = %i\n",blobs.size(),i*limit+j*w+k);
                    blobs.push_back(0);
                }
            }
        }
        //printArray(blobs, i, i+1, 1);
    }
    
    return blobs;
}


float marray::average(int frm)
{
    int sum=0;
    for (int j=0; j<limit; j++)
    {
        sum+= data[frm*limit+j];
    }
    return (float) sum/limit;
}

float marray::stdev(int frm, float avg)
{
    float E=0.0;
    float inv = (float) 1/limit;
    for (int j=0; j<limit; j++)
    {
        E+= pow(((float)data[frm*limit+j]-avg),2);
    }
    return sqrt(inv*E);
}

vector<int> marray::fillArray(char * file)
{
    int i=0, temp;
    ifstream fin(file);
    
    if(fin.is_open())
    {
        while(i<limit*frames)
        {
            //fin>>data[i];
            fin >> temp;
            data.push_back(temp); 
            i++;
        }
        /*data[16]*=10;//This is some fake data to test using only the first ten frames. This should guarantee that some blobs are present
        data[17]*=10;
        data[15]*=100;
        data[14]*=50;
        data[25]*=10;
        data[33]*=10;
        data[42]*=10;
        data[45]*=50;
        data[65]*=10; //Equivalent to 17
        data[123]*=10;//27
        data[181]*=10;//37
        data[238]*=10;//46
        data[345]*=10;//9
        data[346]*=10;
        data[394]*=10;//10
        data[406]*=10;//22 //377,425*/
        return data;
    }
    else
	{
		cout << "File could not be opened. Zero vector returned.\n" << endl;
        return vector<int>(limit*frames);
	}
}

void marray::printBlobArray(vector<blob> array, int frame)
{
    printf("Frame: %i\nThere are %i blobs\n",frame,(int)array.size());
    int size = (int)array.size();
    for (int i = 0; i<size; i++)
    {
        printf("Blob %i\n",i);
        int ind = (int)array[i].loc.size();
        for (int j = 0 ; j<ind; j++)
        {
            printf("Indices: %i\n",array[i].loc[j]);
        }
    }
    printf("\n");
}

void marray::printArray(vector<int> arr,int start,int end,int step)
{
    if (start<0 || end>frames || end<start)  //Check to make sure indices are within the allowed range (1-20000), break if not
    {
        printf("Invalid Frame Indices\n");
        return;
    }
    
    for(int i = start; i<end; i+=step)    //Loop through frames, print every step-th frame (can skip frames if desired)
    {
        printf("Frame number %i\n",i);
        for (int j=0;j<h;j++)               //Loop through columns
        {
            for (int k=0;k<w;k++)           //Loop through rows
            {
                //cout << *(array+i)<<"\n";
                printf("%i\t",arr[i*limit+j*w+k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void marray::printArray(vector<float> arr,int start,int end,int step)
{
    if (start<0 || end>frames || end<start)  //Check to make sure indices are within the allowed range (1-20000), break if not
    {
        printf("Invalid Frame Indices\n");
        return;
    }
    
    for(int i = start; i<end; i+=step)    //Loop through frames, print every step-th frame (can skip frames if desired)
    {
        printf("\nFrame number %i\n",i+1);
        for (int j=0;j<h;j++)               //Loop through columns
        {
            for (int k=0;k<w;k++)           //Loop through rows
            {
                //cout << *(array+i)<<"\n";
                printf("%f\t",arr[i*limit+j*w+k]);
            }
            printf("\n");
        }
    }
}
