/*
 * wordsearch.h
 *
 *  Created on: Dec 30, 2014
 *      Author: sojourner
 */

#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#endif // WORDSEARCH_H
//#include<fstream>
using namespace std;
int mainProg();

//int mainProg();

//char* filePath;
//char* fileName;

static char dictWords[100000][60];
static int indexAlpha[100];
static int indexASCII[100];
static int indexAlphaMax;
static long wordCount;
//const int alphaFound;

//static char freqWordsList[MAX_SIZE][MAX_SIZE];


//long getDictWord(chr* rcvdMem,char subString[],int substringType)
/*static long getDictWordCount()
{
    //int i, limit;
    char dictWord[60];
    long wordCount=0;
    FILE* fDict;
    fDict=fopen("/usr/share/dict/words","r");
    //for(i=0;!feof(fDict);i++)
    while(!feof(fDict))
    {
        fgets(dictWord,60,fDict);
        wordCount++;
    }
    fclose(fDict);

    return --wordCount;
}*/

//------------------------------------------------------------

static int exactWordIndex(int a, int b, char refWord[])
{
    int i, diff, midPoint, result;
    if(a>b)
    {
        return -1;
    }
    midPoint=(a+b)/2;
    diff=strcmp(dictWords[midPoint], refWord);

    cout<<endl<<"String: "<<refWord<<" len: "<<strlen(refWord)<<" a: "<<a<<" b: "<<b<<" mid point: "<<midPoint<<" diffrnc: "<<diff;

    if(diff>0)
    {
        result=exactWordIndex((midPoint+1), b, refWord);
    }
    if(diff<0)
    {
        result=exactWordIndex(a, (midPoint+1), refWord);
    }
    if(diff==0)
    {
        return midPoint;
    }

}

//------------------------------------------------------------

static int wordLookupDictionary(char refWord[])
{
//    //--------------- working code -------------

    int flagFound=0; /*diffASCII=0;*/
    long i;
    cout<<endl<<"(Dictionary) Searching for the word: "<<refWord;
    for(i=0; i</*10*/wordCount; i++)
    {
        //cout<<endl;
        //cout<<"Dictionary: "<<dictWords[i]<<" difference: "<<strcmp(refWord,dictWords[i]);
        if(strcmp(refWord,dictWords[i])==0)
        {
            flagFound=i;
            break;
        }
    }
    //cout<<"Exit i: "<<i;
    return flagFound;
    // -------------- working code ends ----------


    //--------- at testing phase --------

//    int startIx, endIx;
//    for(int i=0;i<indexAlphaMax;i++)
//    {
//        if(indexASCII[i] == int(refWord[0]))
//        {
//            startIx=indexAlpha[i];
//            endIx=indexAlpha[i+1];
//            break;
//        }
//    }
//    int result=exactWordIndex(startIx, endIx,refWord);
//    return result;
    //---------- testing phase ends ------------------
}

//-----------------------------------------------------------

static int formDictArray()
{
    //int i;
    //char dummyWord[]="Aaron\n";
    char baseAlpha=' ';
    char firstAlpha;
    //char word[60];
    FILE* fDict;
    long /*wordCount=0,*/ alphaFound=0;
    wordCount=0;
    fDict=fopen("/usr/share/dict/words", "r");
    while(!feof(fDict))
    {
        fgets(dictWords[wordCount]/*word*/,60,fDict);
        /*for(i=0;word[i]!='\0';i++)
        {
            dictWords[wordCount][i]=word[i];
        }*/
        //dictWords[wordCount][i]='\0';
        firstAlpha=dictWords[wordCount][0];
        if((firstAlpha-baseAlpha)!=0)
        {
            indexAlpha[alphaFound]=wordCount;
            indexASCII[alphaFound]=firstAlpha;
            baseAlpha=firstAlpha;
            alphaFound++;
        }
        wordCount++;
    }
    //indexAlpha[alphaFound]='\0';
    //cout<<"Alphas: "<<alphaFound<<endl;
    indexAlphaMax=alphaFound;
    fclose(fDict);

    /*  ----------------------- important for testing --------------------------
    cout<<"Base for B at "<<indexAlpha[1]<<" "<<dictWords[indexAlpha[22/*]];
    cout<<endl<<"difference: "<<strcmp(dummyWord,dictWords[22]); --------------- important

    cout<<endl<<"length "<<int(dictWords[22][5])<<" : "<<int(dummyWord[5]);

    for(i=0;i<indexAlphaMax;i++)
    {
        cout<<endl<<indexAlpha[i]<<" ASCII: "<<indexSCII[i];
    }
    //puts(dictWords[indexAlpha[1]]);

    ----------------------------- testing ends ---------------------------------*/

    return --wordCount;
}

