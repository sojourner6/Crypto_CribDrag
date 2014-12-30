//============================================================================
// Name        : CribDrag.cpp
// Author      : Somnath Sarkar
// Version     :
// Copyright   : Public access
// Description : Cryptanalysis of reused One Time Pad
//============================================================================

#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<iomanip>
#include<fstream>
#include<string>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include"basicutilities.h"
#include"wordsearch.h"
//#include"testheader.h"
using namespace std;


char* fHomePath;
char* fPath;
char* fData;
char* fileName;


//------------------------------------------------------

void getRandomStream(char* rcvdMem)
{
    int i, randNum, maxSum=0, maxDigits;
    long flag1;/*, flag2;*/
    char* c=(char*)calloc(1, sizeof(char));
    char* prgStream=(char*)calloc(MAX_SIZE, sizeof(char));
    srand(time(0));
    for(i=0;i<FILE_COUNTER;i++)
    {
        if(maxSum<FILE_CHAR_COUNT[i])
        {
            maxSum=FILE_CHAR_COUNT[i];
        }
    }
    maxDigits=maxSum*3*4;
    //cout<<endl<<"Max Length: "<<maxSum<<" Max Digits: "<<maxDigits<<endl;//------------------------ remove later --------
    for(i=0;i<maxDigits;i++)
    {
        //cout<<i<<",";
        randNum = rand()%500+1;
        randNum = randNum%50;
        //cout<<randNum<<","; // ---------- remove later --------
        flag1 = fibonacci[randNum]%2;
        //cout<<flag1<<",";
        if(flag1==0)
        {
            prgStream[i]='0';
        }
        else
        {
            prgStream[i]='1';
        }
        //flag2 = convertNumToChar(c, flag1);
        //prgStream[i]=c[0];
    }
    prgStream[i]='\0';
    /*for(i=0;prgStream[i]!='\0';i++)
    {
        cout<<prgStream[i];
    }*/
    strcpy(rcvdMem, prgStream);
    //return "100100101000101101110000100000110";
    //return "001100001110101010100010100011111000001000101011100010010111001100000000000000100010001101011101";
}

//-------------------------------------------------------


int readFile(char* rcvdMem, char* str)
{
    cout<<"File to be read: \""<<str<<"\"";
    int count=0,noChars=0;
    FILE* fplainText;
    char streamData[MAX_FILE_CHAR];
    if(fplainText=fopen(str, "r"))
    {
        do
        {
            streamData[count]=fgetc(fplainText);
            //char* fHomePath=(char*)calloc(MAX_STRING, sizeof(char));
            FILE_DATA[FILE_COUNTER][noChars]=streamData[(count)];
            //cout<<endl<<int(streamData[count]);  // -------------- Remove --------------
            count++; noChars++;
            //noChars++;
        }while(!feof(fplainText));
        streamData[count]='\0';
        cout<<" ... File read successful! "<<endl;
    }
    else
    {
        cout<<"Failed to open file for reading: "<<str<<endl;
    }
    fclose(fplainText);
    strcpy(rcvdMem,streamData);
    FILE_CHAR_COUNT[FILE_COUNTER]=noChars-2;  //-2 for linefeed and terminator
    if(FILE_MAX_LENGTH < FILE_CHAR_COUNT[FILE_COUNTER])
    { FILE_MAX_LENGTH = FILE_CHAR_COUNT[FILE_COUNTER];}
    FILE_COUNTER++;
    return noChars;
}

//------------------------------------------------------------


int displayUserMenu()
{
    int choice;
    do
    {
    cout<<endl<<"\t\t\t\t"<<"MENU"<<endl;
    cout<<"\t-----------------------------------------------------------"<<endl;
    cout<<"\t"<<"1. Enter the name of the plaintext file (name) to be read"<<endl;
    cout<<"\t"<<"2. Exit"<<endl;
    cout<<endl<<"Enter you choice (1-2)"<<endl;
    cin>>choice;
    if(choice<1 || choice>2)
    {
        cout<<endl<<"Invalid Choice: "<<choice<<" ... Please input in the range (1-2)";
    }
    }while(choice>2 || choice<1);
    return choice;
}

//-------------------------------------------------------

void inputMenu()
{
    int choice, i, j, x, charsRead=0, fileCount=0;//, xorStreamLen;
    char userChar;

    choice=displayUserMenu();

    switch(choice)
    {
    case 1:
    {
        do
        {
        // -------------- variable declaration -----------
        fPath=(char*)calloc(MAX_STRING, sizeof(char));
        fileName=(char*)calloc(MAX_STRING, sizeof(char));
        char* fData=(char*)calloc(MAX_FILE_CHAR, sizeof(char));
        // -------------- variable declaration -----------

        cout<<endl<<"Please provide the input file name: ";
        cin>>fileName;
        buildAbsoluteFilePath(fPath);
        strcat(fPath, fileName);
        charsRead=readFile(fData, fPath);
        //---------------- Re-interaction -----------------
        choice=displayUserMenu();
        //---------------- Re-interaction ends ------------

        }while(choice!=2);

        //---------------- input data right-padding with spaces ----------

        for(i=0;i<FILE_COUNTER;i++)
        {
            if(FILE_CHAR_COUNT[i] < FILE_MAX_LENGTH)
            {
                for(j=FILE_CHAR_COUNT[i];j<FILE_MAX_LENGTH;j++)
                {
                    FILE_DATA[i][j]=' ';
                }
            }
        }

        //---------------- input data right-padding ends -----------------

        for(x=0;x<FILE_COUNTER;x++) // -------- Loop around all files (FILE_DATA) --------------
        {
        char* fileSeq=(char*)malloc(4);
        char* fOPath=(char*)calloc(MAX_STRING, sizeof(char));
        char* fileOName=(char*)calloc(MAX_STRING, sizeof(char));
        char* charToBin=(char*)calloc(MAX_STRING, sizeof(char));
        char* binaryStream=(char*)calloc(MAX_SIZE, sizeof(char));
        char* oneTimePad=(char*)calloc(MAX_SIZE, sizeof(char));
        char* xorStream=(char*)calloc(MAX_SIZE, sizeof(char));
        //char* fData=(char*)calloc(MAX_FILE_CHAR, sizeof(char));
        char* fHomePath=(char*)calloc(MAX_STRING, sizeof(char));
        int binStreamLen=0;
        //int sum=0;
        //for(i=0;i<charsRead;i++)
        for(i=0;i<FILE_MAX_LENGTH;i++)
        {
            //userChar=fData[i];
            userChar=FILE_DATA[x][i];
            //cout<<endl;
            //cout<<userChar;
            binStreamLen+=convertToBinary(charToBin,userChar);
            strcat(binaryStream, charToBin);
            //cout<<endl<<binaryStream;
        }
        //cout<<endl<<"Ciphertext Length: "<<binStreamLen<<" stream: "<<binaryStream<<endl;
        //binaryStream[FILE_MAX_LENGTH]='\n';
        //---------- get OTP and XOR ------------
        getRandomStream(oneTimePad);
        //cout<<"One Time Pad: "<<oneTimePad;
        //xorStreamLen=strlen(oneTimePad);
        //cout<<"OTP: ";
        //displayData(oneTimePad, 0);
        xorBinary(xorStream,binaryStream,oneTimePad,binStreamLen);

        strcat(fileOName,OUT_CIPHER);
        if(fileCount<10)
        {
            strcat(fileOName,"000");
        }
        if(fileCount>9 and fileCount<100)
        {
            strcat(fileOName,"00");
        }
        if(fileCount>99)
        {
            strcat(fileOName,"0");
        }
        decimaltoCharSame(fileSeq,fileCount);
        strcat(fileOName,fileSeq);

        //----------------------------
        char* home=getenv("HOME");
        //cout<<endl<<"Home: "<<home<<" path: "<<fHomePath;
        strcat(fHomePath,home);
        strcat(fHomePath,"/");
        //----------------------------

        strcat(fOPath,fHomePath);
        strcat(fOPath, fileOName);

        writeFile(xorStream, fOPath);
        //fcipher=fopen(fPath,"wb");
        //fputs(xorStream, fcipher);
        //fputs('\0',fcipher);
        //fclose(fcipher);

        fileCount++;
        } // -------------------------------- Loop around all files (FILE_DATA) --------------
        break;}
    case 2: break;

    default: cout<<endl<<"Invalid input";
    }
    //}while(choice!=2);

}

//-------------------------------------------------------




int main()
{
    generateDefaultFibonacci();
    inputMenu();
    int n=mainProg();
    return 0;
}


