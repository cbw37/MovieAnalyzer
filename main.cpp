//
//  main.cpp
//  MovieAnalyzer
//
//  Created by Chad Williams on 12/29/15.
//  Copyright (c) 2015 Chad Williams. All rights reserved.
//

#include "Header.h"
using namespace std;
char shot[9];

vector< vector<int> > readFile();
void writeFile(int shotn,vector<int> array, bool grid);
void intToChar(int num);

int main(int argc, const char * argv[])
{ 
    //int numShots;
    vector<int> data1, blobs1, inst,shots;
    
    vector< vector<int> > fileData = readFile();// Read Instruction File

    shots = fileData[0];
    inst = fileData[1];
    

    //for (int i = 0; i<shots.size(); i++)//Loop over shots
    {
        int i = 0;
        intToChar(shots[i]);

        char file[100], name[100];
        strcpy(name,"MovieData-");
        strcat(name,shot);
        strcat(name,".txt");
        sprintf(file,"%s%s",dir,name);
       
    
        marray test (inst[0],inst[1],inst[2],inst[3],inst[4],inst[5]);

        printf("Analyzing shot number %i\n",shots[i]);
        data1=test.fillArray(file);
        //test.printArray(data1,0,1,1);
            
         /*data1[16]*=10;
         data1[65]*=10;
         data1[123]*=10;
         data1[181]*=10;
         data1[238]*=10;
         data1[345]*=10;
         data1[394]*=10;
         data1[406]*=10; //377,425*/
        
        //test.printArray(data1,0,1,1);
        blobs1=test.findBlobs(inst[4]);
        //writeFile(shots[i],blobs1,true);
        //printf("There are %i blobs\n",test.countBlobs());
        
        vector<int> results = test.traceBlobs();
        for (int j = 0; j<results.size(); j++)
            printf("Lifetime: %i, Number: %i\n",j,results[j]);
        writeFile(shots[i],results,false); //Write results of each shot to separate file. Returned result is a histogram of blob lifetimes.
    }
    
    return 0;
}

void writeFile(int shotn,vector<int> array, bool grid)
{
    FILE * dataFile;
    char fName[100];
    sprintf(fName, "%sBlobData-%d.xls",dir,shotn);
    dataFile = fopen(fName,"a");
    fprintf(dataFile,"%i\n",shotn);
    if(grid)
    {
        for(int i = 0; i<2000; i++)
        {
            fprintf(dataFile,"Frame number %i\n",i);
            for (int j=0;j<6;j++)               //Loop through columns
            {
                for (int k=0;k<8;k++)           //Loop through rows
                {
                    fprintf(dataFile,"%i\t",array[i*48+j*8+k]);
                }
                fprintf(dataFile,"\n");
            }
        }
        fprintf(dataFile,"\n");
    }
    else
    {
    for (int i=0; i<(int) array.size(); i++)
        fprintf(dataFile, "%i\n",array[i]);
    }
    fclose(dataFile);
}

vector< vector<int> > readFile()
{
    int tempc,tempi=0,ShotBase;
    vector<int> shots, file;
    vector< vector<int> > fileData;

    char fileName[100];
    sprintf(fileName,"%s%s",dir,"Instructions.txt");
    
    ifstream fin(fileName);
    
    if(fin.is_open())
    {
        fin>>tempc;
        shots.push_back(tempc);
        ShotBase = 1000*(shots[0]/1000);
        fin>>tempi;
        while (tempi!= -1)
        {
            shots.push_back(ShotBase + tempi);
            fin>>tempi;
        }
        
        fin>>tempi;
        while (tempi!= -1)
        {
            file.push_back(tempi);
            fin>>tempi;
        }
        fileData.push_back(shots);
        fileData.push_back(file);
        return fileData;
    }
    else
	{
		cout << "Instructions could not be opened. Zero array returned.\n" << endl;
        vector< vector<int> > blank(1);
        return blank;
	}
}

void intToChar(int num)
{
    //Only useful for shot numbers which are set at 9 characters
    int j=1;
    for (int i=8;i>=0;i--)
    {
        shot[i]=(char)((num-(int)pow(10.0,j)*(num/(int)pow(10.0,j)))/(int)pow(10.0,j-1)+48);
        j++;
    }
}
