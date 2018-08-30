//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    Result.h
// Author:  Joscha Knolle
// Date:    2018-04-22
//----------------------------------------------------------------------------//

#ifndef PoTATo_common_Result_h
#define PoTATo_common_Result_h

#include <string>

#include <TTree.h>

class Result {
public:
    Result() : Result("result") {}
    Result(std::string name) : _tree(new TTree(name.c_str(), name.c_str())) {}
    virtual ~Result() { if(_tree!=nullptr) delete _tree; }

    TTree* tree() { return _tree; }
    void fill() { _tree->Fill(); }

    #define CREATE_BRANCH(TYPE) \
    void branch(std::string, TYPE*); \
    void branch(std::string, TYPE*, int); \
    void branch(std::string, TYPE*, std::string);
    CREATE_BRANCH(int)
    CREATE_BRANCH(unsigned int)
    CREATE_BRANCH(float)
    CREATE_BRANCH(double)
    CREATE_BRANCH(bool)
    #undef CREATE_BRANCH

protected:
    void _branch(std::string, void*, std::string, int=0, std::string="");
    TTree* _tree = nullptr;

};

#endif //ifndef PoTATo_common_Result_h
