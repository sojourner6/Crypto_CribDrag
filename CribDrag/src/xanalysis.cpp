#include <iostream>
#include<stdlib.h>
#include<iomanip>
#include<fstream>
#include<string>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<string>
#include"basicutilities.h"
#include"wordsearch.h"
//#include"testheader.h"
//#include<crepository.h>

using namespace std;

char freqWordsList[MAX_SIZE][MAX_SIZE];
int binCribLen = 0;
char crib[40];
const char* xorCipherText;// = (char*)calloc(MAX_SIZE, sizeof(char));

//char FILE_DATA_1[MAX_SIZE][MAX_SIZE];

//char* fHomePath;
//char* fPath;
//char* fData;
//char* fileName;

/*int main()
{
    return 0;
}*/


int displayCanalysisMenu()
{
    int choice;
    do
    {
    cout<<endl<<endl;
    cout<<"\t\t\t\t"<<"MENU"<<endl;
    cout<<"\t----------------------------------------------------------------"<<endl;
    cout<<"\t"<<"1. Enter the name of the ciphertext file (name) to be read"<<endl;
    cout<<"\t"<<"2. Search frequently occuring words in English 10 at a time"<<endl;
    cout<<"\t"<<"3. Continue with step 2?"<<endl;
    cout<<"\t"<<"4. Choose a crib"<<endl;
    //cout<<"\t"<<"5. Search frequently occuring words in English starting with an alphabet (enter the alphabet)"<<endl;
    cout<<"\t"<<"5. Search for a word in English Dictionary"<<endl;
    //cout<<"\t"<<"7. Search for a word in English Dictionary starting with an alphabet (enter the alphabet)"<<endl;
    cout<<"\t"<<"6. Exit"<<endl;
    cout<<endl<<"Enter you choice (1-6)"<<endl;
    cin>>choice;
    if(choice<1 || choice>6)
    {
        cout<<endl<<"Invalid Choice: "<<choice<<" ... Please input in the range (1-8)";
    }
    }while(choice>6 || choice<1);
    return choice;
}

//----------------------------------------------------------

char* getFreqEnglishWord(char* rcvdMem, int noWords)
{
    int i=0, j=0, startIx, endIx, small;
    FILE* inFile;
    char fChar;
    char* fPath=(char*)calloc(MAX_STRING, sizeof(char));
    char* freqData=(char*)calloc(MAX_SIZE,sizeof(char));
    buildAbsoluteFilePath(fPath);
    strcat(fPath,"freqWords.txt");
    //cout<<endl<<fPath<<endl;       //---------- remove --------
    if(inFile=fopen(fPath,"r"))
    {
        do
        {
            fChar=fgetc(inFile);
            //cout<<fChar<<",";
            freqWordsList[i][j]=fChar;
            j++;
            if(fChar=='\n' || fChar=='\0')
            {
                //freqWordsList[i][j-1]=", ";
                i++;
                j=0;
            }
        }while(!feof(inFile));
    }
    else
    {
        cout<<"Failed to open file for reading: "<<fPath<<endl;
    }
    fclose(inFile);
    //cout<<endl<<"no. of words: "<<i;
    startIx=10*noWords;
    endIx=10*(noWords+1);
    small=(endIx < i)?endIx:i;
    int count=0;
    for(i=startIx;i<small;i++)
    {
        /*for(j=0;freqWordsList[i][j]!='\n';j++)
        {
            freqData[count++]=freqWordsList[i][j];
        }*/
        strcat(freqData, freqWordsList[i]);
    }
    strcpy(rcvdMem,freqData);
}

//-------------------------------------------------------------

/*char* getFreqEnglishWordAlpha(char* rcvdMem, char c)
{
    int i=0, j=0, startIx, endIx, small;
    FILE* inFile;
    char fChar;
    char* fPath=(char*)calloc(MAX_STRING, sizeof(char));
    char* freqData=(char*)calloc(MAX_SIZE,sizeof(char));
    buildAbsoluteFilePath(fPath);
    strcat(fPath,"freqWords.txt");
    //cout<<endl<<fPath<<endl;       //---------- remove --------
    if(inFile=fopen(fPath,"r"))
    {
        do
        {
            fChar=fgetc(inFile);
            //cout<<fChar<<",";
            freqWordsList[i][j]=fChar;
            j++;
            if(fChar=='\n' || fChar=='\0')
            {
                //freqWordsList[i][j-1]=", ";
                i++;
                j=0;
            }
        }while(!feof(inFile));
    }
    else
    {
        cout<<"Failed to open file for reading: "<<fPath<<endl;
    }
    fclose(inFile);
    //cout<<endl<<"no. of words: "<<i;
    startIx=10*noWords;
    endIx=10*(noWords+1);
    small=(endIx < i)?endIx:i;
    int count=0;
    for(i=startIx;i<small;i++)
    {
        /*for(j=0;freqWordsList[i][j]!='\n';j++)
        {
            freqData[count++]=freqWordsList[i][j];
        }
        strcat(freqData, freqWordsList[i]);
    }
    strcpy(rcvdMem,freqData);
}*/

//-------------------------------------------------------------

void getFrequentWords(int searchTimes)
{
    char* freqEngWords=(char*)calloc(MAX_SIZE,  sizeof(char));
    getFreqEnglishWord(freqEngWords,searchTimes);
    cout<<endl<<"freq words"<<endl;
    displayData(freqEngWords,0);

}

//-------------------------------------------------------------

void readCipherTextFiles()
{
    char fName[MAX_STRING];
    cout<<endl<<"ENTER CIPHERTEXT FILE NAME: ";
    cin>>fName;

    int i, charsRead=0;
    char* fData=(char*)calloc(MAX_SIZE, sizeof(char));
    char* fPath=(char*)calloc(MAX_STRING, sizeof(char));
    char* fileName=(char*)calloc(MAX_STRING, sizeof(char));

    buildAbsoluteFilePath(fPath);
    strcat(fPath,fileName);

    charsRead=readInputFile(fData, fPath);

    for(i=0;fData[i]!='\0';i++)
    {
        FILE_DATA[FILE_COUNTER][i]=fData[i];
    }

}

//-------------------------------------------------------------

void XORCipherCrib(char binCrib[], int cribLen)
{
    int i, j, k, l, x, y, remXORs, cell;
    char* xorOp2=(char*)calloc(MAX_STRING,sizeof(char));
    strcpy(xorOp2, binCrib);
    char subCipherText[MAX_STRING];
    remXORs=CIPHERTEXT_LEN;
    //displayData(xorCipherText, 0);
    //cout<<endl<<"FILE COUNTER: "<<FILE_COUNTER<<endl;
    //for(i=0;i<FILE_COUNTER;i++)
    //{
    cout<<endl<<"Possible plaintext message with crib = "<<crib;
    cout<<endl<<"--------------------------------------------------------"<<endl;
        //cout<<endl<<"FILE 1: ";
        for(j=0;j<CIPHERTEXT_LEN/*binCrib[j]!='\0' && binCrib[j]!='\n'*/;j++)
        {
            //remXORs=CIPHERTEXT_LEN-j;
            //cout<<endl<<"Rem XORs: "<<remXORs;
            char* fullXORData=(char*)calloc(MAX_SIZE, sizeof(char));
            int fullXorCell=0;
            for(k=/*0*/j;(CIPHERTEXT_LEN-k)>=cribLen/*k<CIPHERTEXT_LEN*/;k+=cribLen)
            {
                cell=0;
                char* xorData=(char*)calloc(MAX_SIZE,sizeof(char));
                char* xorOp1=(char*)calloc(MAX_SIZE,sizeof(char));
                //char* decryptWord=(char*)calloc(MAX_SIZE,sizeof(char));
                for(l=k;l<(k+cribLen);l++)
                {
                    subCipherText[cell++]=xorCipherText[l];//  FILE_DATA[i][l];
                    //cout<<FILE_DATA[i][k];
                }
                //subCipherText[cell]='\0';
                strcpy(xorOp1,subCipherText);
                //cout<<endl<<"XOR files, k = "<<k<<" ciphertext length = "<<CIPHERTEXT_LEN<<" l = "<<l<<endl;
                //cout<<endl<<"OP 1: "<<xorOp1<<" OP 2: "<<xorOp2<<endl;
                //displayData(xorOp1, cribLen); //----------- remove -----------
                //displayData(xorOp2,cribLen); //----------- remove -----------

                xorBinary(xorData, xorOp1, xorOp2, cribLen);
                //strcpy(fullXORData,xorData);
                //strcat(fullXORData,xorData);
                for(int m=0; m<cribLen; m++)
                {
                    fullXORData[fullXorCell++]=xorData[m];
                }



                // ---------- convert to char here! -----------------

                //remXORs-=cribLen;
            }
            //------------ last remaining chars in cipher txt ---------
            cell=0;
            char* xorData=(char*)calloc(MAX_SIZE,sizeof(char));
            char* xorOp1=(char*)calloc(MAX_SIZE,sizeof(char));
            if((CIPHERTEXT_LEN-k)>0)
            {
                //cout<<endl<<"XOR files (rem)";
                char* xorOp3=(char*)calloc(MAX_SIZE,sizeof(char));
                char truncatedCrib[MAX_SIZE];
                for(x=k/*l*/;x<CIPHERTEXT_LEN/*xorCipherText[x]!='\0'*/;x++)
                {
                    subCipherText[cell++]=xorCipherText[x];
                }
                strcpy(xorOp1,subCipherText);
                //cout<<endl<<"cell: "<<cell<<endl;
                //displayData(xorOp1, cell);
                for(x=0;x<cell;x++)
                {
                    truncatedCrib[x]=binCrib[x];
                }
                strcpy(xorOp3, truncatedCrib);
                //cout<<endl<<"cell: "<<cell<<endl;
                //displayData(xorOp3, x);
                xorBinary(xorData, xorOp1, xorOp3, cell/*CIPHERTEXT_LEN-k*/);

                // ------------ right padding remaining bits with 0 ------------------

                for(int m=cell;m<cribLen;m++)
                {
                    xorData[m]='0';
                }

                // ------------ right padding ends -----------------------------------

//                char* decryptWord=(char*)calloc(MAX_SIZE, sizeof(char));
                //strcat(fullXORData, xorData);

                for(int m=0; m<cribLen; m++)
                {
                    fullXORData[fullXorCell++]=xorData[m];
                }

//                convertBinaryToChar(decryptWord, fullXORData, CIPHERTEXT_LEN);
//                //cout<<","<<decryptWord;
//                displayData(decryptWord,0);
            }

            char* decryptWord=(char*)calloc(MAX_SIZE, sizeof(char));
            //strcat(fullXORData, xorData);
            //cout<<"j = "<<j<<" fullXorCell = "<<fullXorCell;
            convertBinaryToChar(decryptWord, fullXORData, fullXorCell /*CIPHERTEXT_LEN*/);
            //cout<<","<<decryptWord;
            //displayData(decryptWord,0);
            //cout<<endl<<"Possible plaintext message ...";
            //cout<<endl<<"-------------------------------"<<endl;
            cout<<endl;
            for(int m=0;decryptWord[m]!='\0';m++)
            {
                cout<<decryptWord[m];
            }

        }
        //cout<<endl;
            //---------------- end ----------------------------------
     //}
}

//-------------------------------------------------------------

int processCrib()
{
    int i, binStreamLen=0, flagFound, wordLen;
    char c, /*crib[40],*/ binaryCrib[MAX_SIZE], searchWord[40], subWord[40], searchWordCell=0;
    //string crib;
    cout<<endl<<"Enter a crib: ";
    //cin.ignore( numeric_limits <streamsize> ::max(), '\n' );
    //gets(crib);
    cin.ignore();
    cin.getline(crib, 40);
    //cout<<strlen(crib);

    // -------------------- search crib in dictionary ------------------------

    wordLen=0;
    for(i=0;i<strlen(crib);i++)
    {
        if(crib[i]==' ' || crib[i]==',' || crib[i]=='.' ||
                crib[i]=='!' || crib[i]=='?')
        {
            searchWord[searchWordCell++]='\n';
            int j;
            for(j=0;j<searchWordCell;j++)
            {
                subWord[j]=searchWord[j];
                wordLen++;
            }
            subWord[j]='\0';
            //cout<<"word lookup: "<<searchWord<<" len: "<<subWord;

            if(wordLen>1)
            {
                flagFound=wordLookupDictionary(subWord);


                if(flagFound!=0)
                {
                    cout<<" VALID word. "<<flagFound+1<<"th word in the Dictionary";
                }
                else
                {
                    cout<<" is a NOT a valid Dictionary word";
                    return -1;
                }
            }

            //searchWord[i]=crib[i];
            searchWordCell=0;
            wordLen=0;
        }
        else
        {
            searchWord[searchWordCell++]=crib[i];
            wordLen++;
            /*if(crib[i]!='\n' && crib[i]!=' ' && crib[i]!=',' && crib[i]!='!'
                    && crib[i]!='?')
            {
                wordLen++;
            }*/
        }
    }
    if(wordLen>1)
    {
        searchWord[searchWordCell++]='\n';
        searchWord[searchWordCell]='\0';
        flagFound=wordLookupDictionary(searchWord);
        if(flagFound!=0)
        {
            cout<<" VALID word. "<<flagFound+1<<"th word in the Dictionary";
        }
        else
        {
            cout<<" is a NOT a valid Dictionary word";
            return -1;
        }
    }

    // -------------- crib search in dictionary ends -------------------------------

    //------------ ciphertext1 XOR ciphertext2 XOR ciphertext3 XOR .... ------------

    char* xorResult=(char*)calloc(MAX_SIZE, sizeof(char));
    for(i=0;i<CIPHERTEXT_LEN;i++)
    {
        xorResult[i]=FILE_DATA[0][i];
    }
    //cout<<endl<<"FILEDATA[0] record length: "<<i;
    //strcpy(xorResult, FILE_DATA[0]);
    for(i=1; i<FILE_COUNTER; i++)
    {
        char* xorOp2=(char*)calloc(MAX_SIZE, sizeof(char));
        char* xorTempRes=(char*)calloc(MAX_SIZE, sizeof(char));

        strcpy(xorOp2, FILE_DATA[i]);
        //displayData(xorResult, 0); //------------ remove -----------
        //displayData(xorOp2, 0); //--------------- remove -----------
        //cout<<endl<<"Ciphertext length: "<<CIPHERTEXT_LEN;
        xorBinary(xorTempRes, xorResult, xorOp2, CIPHERTEXT_LEN);
        strcpy(xorResult,xorTempRes);
    }
    //strcpy(xorCipherText, xorResult);
    xorCipherText=xorResult;
    /*cout<<endl<<"xored ciphertext: ";
    for(int i=0;i<CIPHERTEXT_LEN;i++)
    {
        cout<<xorCipherText[i];
    }*/
    cout<<endl;

    //------------------ ciphertext XOR ends ---------------------------------

        //readCipherTextFiles();
    //------------------------------------------
    //------  check crib with dictionary--------
    //------            here            --------
    //------------------------------------------

    // --------- converts crib to binary --------

    char* binaryStream=(char*)calloc(MAX_SIZE, sizeof(char));
    for(i=0;crib[i]!='\0';i++)
    {
        c=crib[i];
        //cout<<endl<<"Crib: "<<c;
        char* charToBin=(char*)calloc(MAX_STRING, sizeof(char));
        binStreamLen+=convertToBinary(charToBin,c);
        strcat(binaryStream, charToBin);

    }
    //cout<<endl<<"BINARY CRIB LENGTH: "<<binStreamLen<<endl;
    //cout<<endl<<"BINARY CRIB: "<<binaryStream<<endl;
    for(i=0;i<binStreamLen;i++)
    {
        binaryCrib[i]=binaryStream[i];
    }
    binaryCrib[i]='\0';
    binCribLen=binStreamLen; cout<<endl;
    //cout<<endl<<"BINARY CRIB: "<<binaryCrib<<endl;
    //------------ crib to binary ends -----------

    //--------- Start XOR in the crib ------------
    XORCipherCrib(binaryCrib, binCribLen);
    //----------- End XOR in the crib ------------
    return 0;

}

//----------------------------------------------------------------

void loadDictionary()
{
    int noDictWords;/*, diff*/;

    noDictWords=formDictArray();

    /*for(int i=0;i<indexAlphaMax;i++)
    {
        cout<<endl<<"AlphaASCII: "<<indexASCII[i]<<" at index: "<<indexAlpha[i];
    }*/
    //cout<<" test diff: "<<strcmp("c","b");

    //cout<<"Enter word to search: ";
    //char c[15];
    //cin.ignore();
    //cin.getline(c, 10);
    //cin>>c;
    //cout<<endl<<"Word to search: "<<c<<" Length: "<<strlen(c);
    //diff=wordLookupDictionary(c);
//    cout<<endl<<"First+1 dictionary word: "<<dictWords[1][4];
}

//----------------------------------------------------------------

int mainProg()
{
    int choice, searchTimes=0;
    FILE_COUNTER=0;
    loadDictionary();
    //cout<<endl<<"First+1 dictionary word: "<<dictWords[1];
    choice=displayCanalysisMenu();
    do
    {
    switch(choice)
    {
    case 1:
    {
        do
        {
            int i, charsRead=0; /*, cipherLen=0;*/
            char* fData=(char*)calloc(MAX_SIZE, sizeof(char));
            char* fPath=(char*)calloc(MAX_STRING, sizeof(char));
            char* fileName=(char*)calloc(MAX_STRING, sizeof(char));
            cout<<endl<<"Please provide the input file name: ";
            cin>>fileName;

            buildAbsoluteFilePath(fPath);
            strcat(fPath,fileName);

            charsRead=readInputFile(fData, fPath);
//            cout<<endl<<charsRead<<endl;

//            for(i=0;i<charsRead;i++)                       // ----- remove
//            {                                              // ----- remove
//                cout<<"("<<i<<","<<int(fData[i])<<"),";     // ----- remove
//            }                                              // ----- remove

            for(i=0;i<charsRead/*fData[i]!='\0'*/;i++)
            {
                FILE_DATA[FILE_COUNTER][i]=fData[i];
                //cipherLen++;
            }
//            cout<<"cipher0000 file: ";
//            displayData(FILE_DATA[FILE_COUNTER],charsRead); // ---- remove ------
            FILE_DATA[FILE_COUNTER++][i]='\0';
//            FILE_COUNTER++;
            CIPHERTEXT_LEN=charsRead; // ------- important -------
            choice=displayCanalysisMenu();

        }while(choice==1);
        break;
    }
    case 2:
    {
        /*char* freqEngWords=(char*)calloc(MAX_SIZE,  sizeof(char));
        getFreqEnglishWord(freqEngWords,searchTimes);
        cout<<endl<<"freq words"<<endl;*/
        getFrequentWords(searchTimes);
        choice=displayCanalysisMenu();
        //puts(freqEngWords);
        //searchTimes++;
        break;
    }
    case 3:
    {
        searchTimes++;
        getFrequentWords(searchTimes);
        choice=displayCanalysisMenu();
        break;
    }
    case 4:
    {
        int validCrib=processCrib();
        choice=displayCanalysisMenu();
        break;
    }    // ---------- case exit -----------

    case 5:
    {
        char searchWord[40], refWord[40];
        int i;
        long wordIndex;
        cout<<endl<<"Please enter the word you want to search in the dictionary: ";
        cin.ignore();
        cin.getline(searchWord, 20);
        /*for(i=0;searchWord[i]!='\n';i++)
        {
            refWord[i]=searchWord[i];
        }
        refWord[i]='\n';*/
        //refWord[i]='\0';*/
        strcat(searchWord,"\n");
        //cout<<"Difference: "<<strcmp(searchWord, dictWords[90514]);
        wordIndex=wordLookupDictionary(searchWord);
        if(wordIndex!=0)
        {
            cout<<" VALID word. "<<wordIndex+1<<"th word in the Dictionary";
        }
        else
        {
            cout<<" is a NOT a valid Dictionary word";
            //return -1;
        }
        //choice=displayCanalysisMenu();
        choice=displayCanalysisMenu();
        break;
    }    // ---------- case exit -----------

    //}

    }    // ---------- switch exit ---------
    }while(choice!=6);


    return 0;
}
