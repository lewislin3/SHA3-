#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <bitset>
#include "Sponge.h"
#include "InternalFun.h"



bitset<64> RC[24] = 
{ 
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};






Binary internalFun(Binary stateVar) 
{
	
	for(int i=0; i<24; i++)
		stateVar = roundFun( stateVar, RC[i] ) ;
		
	return stateVar ;
}




/*** Round function in SHA-3 ***/
Binary roundFun(Binary stateVar, bitset<64> singleRC)
{
	
	/*** TODO: Implement your SHA3's 5 functions as follows ***/
    
    bitset<64> a[5][5];
    bitset<64> ttmp[5][5];
    for (int x=0; x!=5; x++) {
        for (int y=0; y!=5; y++) {
            for (int z=0; z!=64; z++) {
                a[x][y][63-z]=stateVar[1599-(64*(5*y+x)+z)];
                ttmp[x][y][63-z]=stateVar[1599-(64*(5*y+x)+z)];
            }
        }
    }
	/*** Theta ***/
	
    
    
    for (int x=0; x!=5; x++) {
        for (int y=0; y!=5; y++) {
            for (int z=0; z!=64; z++) {
                for(int i=0; i!=5; i++){
                    ttmp[x][y][z]=ttmp[x][y][z]^a[(x-1+5)%5][i][z];
                }
                for(int i=0; i!=5; i++){
                    ttmp[x][y][z]=ttmp[x][y][z]^a[(x+1)%5][i][(z+1)%64];
                }            }
        }
    }
    
	/*** Rho  ***/
    bitset<64> rtmp[5][5];
    int rot[5][5]={{ 0,36, 3,41,18},
                    { 1,44,10,45, 2},
                    {62, 6,43,15,61},
                    {28,55,25,21,56},
                    {27,20,39, 8,14}};
    
    for(int x=0; x!=5; x++){
        for(int y=0; y!=5; y++){
            for(int z=0; z!=64; z++){
                rtmp[x][y][z]=ttmp[x][y][(z+rot[x][y])%64];
            }
        }
    }
    
    /*** Pi ***/	
    bitset<64> ptmp[5][5];
    for (int x=0; x!=5; x++) {
        for (int y=0; y!=5; y++) {
            for (int z=0; z!=64; z++) {
                ptmp[y][(2*x+3*y)%5][z]=rtmp[x][y][z];
            }
        }
    }
    
    
	/*** Xi ***/
    bitset<64>xtmp[5][5];
    
    for (int x=0; x!=5; x++) {
        for (int y=0; y!=5; y++) {
            for (int z=0; z!=64; z++) {
                xtmp[x][y]=ptmp[x][y];
            }
            
        }
    }
    
    for(int x=0; x!=5; x++){
        for(int y=0; y!=5; y++){
            xtmp[x][y]=xtmp[x][y]^((~ptmp[(x+1)%5][y])&ptmp[(x+2)%5][y]);
        }
    }
    
	
	/*** Iota ***/
    xtmp[0][0]=xtmp[0][0]^singleRC;
    
    
    string tmpa,tmpa2;
    for(int y=0; y!=5; y++){
        for(int x=0; x!=5; x++){
            tmpa.resize(64);
            for(int z=63; z!=-1; z--){
                tmpa[63-z]=xtmp[x][y][z]+'0';
            }
            tmpa2=tmpa2+tmpa;
        }
    }
    Binary ans(tmpa2);
    return ans;
}