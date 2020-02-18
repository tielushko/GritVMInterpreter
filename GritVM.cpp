#include "GritVM.hpp"
//#include "GritVMBase.cpp"
#include "iostream"

long GritVM::evaluate(Instruction instruction) {
    int steps = 1;

    switch (instruction.operation) {
        //Accumulator function
        case CLEAR:
            accumulator = 0;
            break;
        //Data Memory Management Functions
        case AT:
            accumulator = dataMem.at(instruction.argument);
            break;
        case SET:
            dataMem.at(instruction.argument) = accumulator;
            break;
        case INSERT:
            dataMem.insert(dataMem.begin() + instruction.argument, accumulator);
            break;
        case ERASE:
            dataMem.erase(dataMem.begin() + instruction.argument);
            break;

        // Accumulator Maths with a constant
        case ADDCONST:
            accumulator = accumulator + instruction.argument;
            break;
        case SUBCONST:
            accumulator = accumulator - instruction.argument;
            break;
        case MULCONST:
            accumulator = accumulator * instruction.argument;
            break;
        case DIVCONST:
            accumulator = accumulator / instruction.argument;
            break;
        
        //accumulator maths with a memory location
        case ADDMEM:
            accumulator = accumulator + dataMem.at(instruction.argument);
            break;
        case SUBMEM: 
            accumulator = accumulator - dataMem.at(instruction.argument);
            break;
        case MULMEM: 
            accumulator = accumulator * dataMem.at(instruction.argument); 
            break;
        case DIVMEM:
            accumulator = accumulator / dataMem.at(instruction.argument); 
            break;
        
        //Instructor Jump functions
        case JUMPREL:
            steps = instruction.argument;
            break;
        case JUMPZERO:
            if (accumulator == 0) {
                steps = instruction.argument;
            } else {
                steps = 1;
            }
            break;
        case JUMPNZERO:
            if (accumulator != 0) {
                steps = instruction.argument; 
            } else {
                steps = 1;
            }
            break;
        
        //misc functions
        case NOOP: 
            steps = 1; 
            break;
        case HALT:
            machineStatus = HALTED;
            break;
        case OUTPUT:
            std::cout << accumulator;
            break;
        case CHECKMEM:
            if (dataMem.size() >= instruction.argument) {
                steps = 1;
                break;
            } else {
                machineStatus = ERRORED;
                steps = 0;
            }
            break;
        default: 
            machineStatus = ERRORED; 
            steps = 0;
    }
    return steps; 
}

STATUS GritVM::advance(long distance) {
  
    //test cases in case the instructions fail
    if (distance == 0) {
        machineStatus = ERRORED;
        return run();
    } else if (machineStatus == HALTED) {
        return HALTED;
    }

    //if the distance is positive exceeds the end of the instructions stops at last one
    while ((distance > 0) && (currentInstruct != instructMem.end())) {
        currentInstruct++;
        distance--;
    }

    //in case distance is negative
    while (distance < 0) {
        currentInstruct--;
        distance++;
        if (currentInstruct == instructMem.begin())
            break;
    }
    return machineStatus; 
}

STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory) {
    
    //in order to load, the machine needs to be initialized to "WAITING"
    if (machineStatus != WAITING) {
        return machineStatus;
    }
    
    //file operations and checking is_open
    std::ifstream in(filename);
    std::string line;
    if (!in.is_open()) {
        throw std::runtime_error("Error opening the file");
    }

    //reading the file line by line
    while (std::getline(in, line)) {
        if((line[0] == '#') || (line.empty())) { //if comment or empty line - ignore
            continue;
        } else {
            Instruction toPush = GVMHelper::parseInstruction(line); //parse the command using helper function
            
            if(toPush.operation == UNKNOWN_INSTRUCTION) { //in case of incorrect instruction
                return ERRORED;
            } 
            instructMem.push_back(toPush); //push the instruction to list of instructions.
        }
    }

    dataMem = initialMemory; //copy vector
    printData = true; //set the printData bool to true so that we can call the print function on the GritVM program
    
    //testing to make sure the function updates the machine status.
    if (instructMem.size() == 0) {
        machineStatus = WAITING;
        return machineStatus;
    } else {
        machineStatus = READY;
        return machineStatus;
    }
}

STATUS GritVM::run() {
    //machine can only run commands if it is READY
    if (machineStatus != READY) {
        return machineStatus;
    }

    //while the machine is running set status and initialize the current instruction.
    machineStatus = RUNNING;
    currentInstruct = instructMem.begin(); 

    //going through each instruction one by one.
    while ((machineStatus == RUNNING) && (currentInstruct != instructMem.end())) {
        long jumpDistance = evaluate(*currentInstruct);      
        advance(jumpDistance);
    }

    //changing the print instruction private data member to true.
    printInstruction = true;
    return machineStatus;
}

std::vector<long> GritVM::getDataMem() {
    std::vector<long>copy; 
    vector<long>::iterator it;
    
    //copy the array to return.
    for (it = dataMem.begin(); it != dataMem.end(); it++) {
        copy.push_back(*it);
    }

    return copy;  
}
STATUS GritVM::reset() {
    //acc to 0
    accumulator = 0;
    
    //erase and shrink the dataMem vector
    dataMem.erase(dataMem.begin(), dataMem.end());
    dataMem.shrink_to_fit();

    //delete the list of instructions.
    instructMem.clear();

    //reset status
    machineStatus = WAITING;

    return machineStatus;
}

void GritVM::printVM(bool pData, bool pInstruction) {
    cout << "***Output Dump***" << endl;
    cout << "Status: " << GVMHelper::statusToString(machineStatus) << endl;
    cout << "Accumulator: " << accumulator << endl;
    
    if (printData) {
        cout << "*** Data Memory ***" << endl; 
        int index = 0;
        vector<long>::iterator it = dataMem.begin(); 
        
        while(it != dataMem.end()) {
            long item = (*it);
            cout << "Location " << index++ << ": " << item << endl; 
            it++;
        }
    }

    if (printInstruction) {
        cout << "*** Instruction Memory ***" << endl; 
        int index = 0;
        list<Instruction>::iterator it = instructMem.begin(); 
        
        while(it != instructMem.end()) {
            Instruction item = (*it);
        
            cout << "Instruction " << index++ << ": " << GVMHelper::instructionToString(item.operation) << " " << item.argument << endl;
            it++;
        }
    }
}