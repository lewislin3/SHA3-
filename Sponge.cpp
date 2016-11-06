#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <bitset>
#include "Sponge.h"
#include "InternalFun.h"

using namespace std;

#define bitRate   576 
#define capacity  1024



void SpongeConstruction(string inputString, int outputLen) 
{
	// Transform the input string into binary bits
	BinaryTransfer( inputString ) ;
						
	// Padding using Multirate
    
	vector< Binary > Message = Padding( inputString ) ; 	
	
	//Initialize the state variable
		
		
	// Absorbing phase
	/*** TODO: Implement your SHA3's absorbing phase here ***/
    Binary stateVar;
    
    Binary tmp;
    
  
    for (int i=0; i!=Message.size(); i++) {
        tmp=Message[i]^stateVar;
        stateVar=internalFun(tmp);
    }
    
	
	// Squeezing phase
	string hashVal ; // The final output value 
	/*** TODO: Implement your SHA3's squeezing phase here ***/
    
    if(outputLen<576){

        for (int i=1599; i!=-1; i--) {
            if (stateVar[i]==0) {
                hashVal=hashVal+'0';
            }
            if (stateVar[i]==1) {
                hashVal=hashVal+'1';
            }
        }
    }
    else{
        while(hashVal.length()<outputLen){
            
            string tmp;
            
            for (int i=1599; i!=-1; i--) {
                if (stateVar[i]==0) {
                    tmp=tmp+'0';
                }
                if (stateVar[i]==1) {
                    tmp=tmp+'1';
                }
            }
            stateVar=internalFun(stateVar);
            hashVal=hashVal+tmp.substr(0,576);
        }
    }
    
    // Print the hash value to the stdout
	PrintHex( hashVal.substr(0, outputLen) ) ;
}


void BinaryTransfer(string& inputString)
{
	string binary = "" ;
	
	for(int i=0; i<inputString.length(); i++)
	{
		for(int k=7; k!=-1; k--)
			if( ((inputString[i] >> k) & 0x01) )
				binary += "1" ;
			else
				binary += "0" ;
	}	
	
	inputString = binary ;
}



vector< Binary > Padding(string inputString) 
{
	/*** TODO: Implement with Multirate padding ***/
    string stringtmp;
    vector<Binary> out;
    
    int k=(int(inputString.length())/576)+1;
    stringtmp.resize((k*576)-inputString.length());
    
    for(int i=0; i!=stringtmp.length(); i++){
        if(i==0 || i==stringtmp.length()-1){
            stringtmp[i]='1';
        }
        else{
            stringtmp[i]='0';
        }
    }

    inputString=inputString+stringtmp;
    
    string tmp2;
    tmp2.resize(1024);
    
    for(int i=0; i!=1024; i++){
        tmp2[i]='0';
    }
    for(int i=0; i!=k; i++){
        string tmp;
        tmp.assign(inputString,576*i,576);
        tmp=tmp+tmp2;
        out.push_back(Binary(tmp));
    }
    return out;
    
}


/*** Print the hash value in hex ***/
void PrintHex(string hashVal) 
{
	
	for(int i=0; i<hashVal.length(); i+=4)
	{
		string Ahex = hashVal.substr(i, 4) ; 
		int Val = 0 ;
		
		for(int k=0; k<4; k++)
			if( Ahex[k]-'0' )	
				Val += (1 << (3-k)) ;
		
		if( Val < 10 )	cout << Val ;
		else	cout << (char)(Val+55) ;			
	}		
}
