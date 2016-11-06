#ifndef SPONGE_H
#define SPONGE_H

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <bitset>
#include "Sponge.h"
#include "InternalFun.h"

#define stateSize 1600

using std::string ;
using std::vector ;
using std::bitset ;

typedef bitset<stateSize> Binary ;

void SpongeConstruction( string inputString, int outputLen ) ;
void BinaryTransfer(string& inputString) ;
vector<Binary> Padding(string inputString) ;
void PrintHex(string hashVal) ;


#endif  //* SPONGE_H *// 

