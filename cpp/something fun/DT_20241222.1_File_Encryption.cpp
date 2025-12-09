//DT_20241222.1_File_Encryption.cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{


    string key="f e ath e r";
    string plaintxt="abcbcdef ghijklm nopqr stuvwxyz";


    //Cipher Table
    char table[26]={};
    short i1=0;
    for(short i2=0; i2<key.length(); i2++)
    {
        //Duplicate Check
        bool duplicate=false;
        for(short i3=0; table[i3]!='\0'; i3++)
            if(key[i2]==table[i3])
            {
                duplicate=true;
                break;
            }

        if(!duplicate)
            table[i1++]=key[i2];
    }
    
    for(char ch='z'; ch>='a' && i1<26; ch--, i1++)
    {
        //Duplicate Check
        for(char chK: key)
            if(ch==chK)
            {
                ch--;
                break;
            }
        if(ch>='a')
            table[i1]=ch;
    }

 
    for(char chcp: plaintxt)
    {
        if(chcp>='a' && chcp<='z')
            cout<<table[chcp-'a'];
        else
            cout<<chcp;
    }

    
    return 0;
}