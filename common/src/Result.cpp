//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Result.cpp
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#include "Result.h"

void Result::_branch(std::string name, void* pointer, std::string type, int n, std::string ref) {
    std::string leaflist = name;
    if(n>0) leaflist += "["+std::to_string(n)+"]";
    else if(ref.length()>0) leaflist += "["+ref+"]";
    leaflist += "/"+type;
    _tree->Branch(name.c_str(), pointer, leaflist.c_str());
}

#define CREATE_BRANCH(TYPEA, TYPEB) \
void Result::branch(std::string name, TYPEA* pointer) { _branch(name, pointer, TYPEB); } \
void Result::branch(std::string name, TYPEA* pointer, int n) { _branch(name, pointer, TYPEB, n); } \
void Result::branch(std::string name, TYPEA* pointer, std::string ref) { _branch(name, pointer, TYPEB, 0, ref); }
CREATE_BRANCH(int, "I")
CREATE_BRANCH(unsigned int, "i")
CREATE_BRANCH(float, "F")
CREATE_BRANCH(double, "D")
CREATE_BRANCH(bool, "O")
#undef CREATE_BRANCH
