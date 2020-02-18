#ifndef GRITVM_H
#define GRITVM_H

#include "GritVMBase.hpp"

#include <list>
#include <vector>
#include <string> 
#include <fstream>


using namespace std;

class GritVM : GritVMInterface {
    private: 
        std::vector<long>                   dataMem;
        std::list<Instruction>              instructMem;
        std::list<Instruction>::iterator    currentInstruct;
        STATUS                              machineStatus;
        long                                accumulator;
        bool printData = false; 
        bool printInstruction = false;
        long evaluate(Instruction instruction);
        STATUS advance(long distance);
    public:
        GritVM() {
            machineStatus = WAITING;
            accumulator = 0;
        }
        
        //inherited functions
        STATUS              load(const std::string filename, const std::vector<long> &initialMemory);
        STATUS              run();
        std::vector<long>   getDataMem();
        STATUS              reset(); 
        void                printVM(bool pData, bool pInstruction);
        bool                getPrintData() {return printData;}
        bool                getPrintInstruction() {return printInstruction;}
        //Memory management functions



};

#endif /*GRITVM_H*/