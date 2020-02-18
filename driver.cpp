#include "GritVM.hpp"
//#include "GritVMBase.cpp"
#include <iostream>
#include <cmath>

int main () {
    GritVM vm;
    std::vector<long> initialMemory;
    std::vector<long> outputMemory;
    std::vector<long> checkMemory;
    
    
//test for run without load
    //string stringStatus = GVMHelper::statusToString(vm.run());
    
//test for throw if wrong file or empty file
    //string stringStatus = GVMHelper::statusToString(vm.load("", initialMemory));
    
//test for load
    //string stringStatus = GVMHelper::statusToString(vm.load("test.gvm", initialMemory));
    
//test for load + run 
    /*
    std::vector<long> initialMemory = { 10 };
    vm.load("test.gvm", initialMemory);
    string stringStatus = GVMHelper::statusToString(vm.run());
    */
    //cout << stringStatus;

//below are the test cases for test.gvm
    /*
    long n1 = (rand() + 1) % 50, n2 = (rand() + 1) % 50;

    initialMemory = { n1 };
    checkMemory = {624, n1, 0};
    vm.load("test.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }

    vm.reset();
    initialMemory = { n2 };
    checkMemory = {624, n2, 0};
    vm.load("test.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }
    */

//test for surfarea.gvm
    /*
    long l = (rand() + 1) % 50, w = (rand() + 1) % 50, h = (rand() + 1) % 50;

    auto func = [](long l, long w, long h) -> long {
      return 2*((l*w) + (h*w) + (l*h)); 
    };

    initialMemory = { l, w, h };
    checkMemory = { func(l,w,h) };
    vm.load("surfarea.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }

    vm.reset();
    l = (rand() + 1) % 50, w = (rand() + 1) % 50, h = (rand() + 1) % 50;

    initialMemory = { l, w, h };
    checkMemory = { func(l,w,h) };
    vm.load("surfarea.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }
    */

//test for the altseq.gvm
    /*
    long n = (rand() + 1) % 10, n1 = (rand() + 1) % 10;

    auto func = [](long n) -> long {
      return std::pow(-2, n) * 3 + 4; 
    };

    initialMemory = { n };
    checkMemory = { n, func(n), n+1 };
    vm.load("altseq.gvm", initialMemory);
    vm.run();
    
    if (vm.getDataMem() == checkMemory) {
        cout << "Good job1" << endl;
    } else {
        cout << ":(" << endl;
    }

    vm.reset();

    initialMemory = { n1 };
    checkMemory = { n1, func(n1), n1+1 };
    vm.load("altseq.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job2" << endl;
    } else {
        cout << ":(" << endl;
    }
    */

//test for towers of HANOI
    long n = (rand() + 1) % 10, n1 = (rand() + 1) % 10, n2 = (rand() + 1) % 10;

    auto func = [](long n) -> long {
      return std::pow(2, n) - 1; 
    };

    initialMemory = { n };
    checkMemory = { n, func(n) };
    vm.load("toh.gvm", initialMemory);
    vm.printVM(true,true);
    vm.run();
    vm.printVM(true,true);
    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }

    vm.reset();

    initialMemory = { n1 };
    checkMemory = { n1, func(n1) };
    vm.load("toh.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }

    vm.reset();

    initialMemory = { n2 };
    checkMemory = { n2, func(n2) };
    vm.load("toh.gvm", initialMemory);
    vm.run();

    if (vm.getDataMem() == checkMemory) {
        cout << "Good job" << endl;
    } else {
        cout << ":(" << endl;
    }
    
    return 0;
}