//
//  main.cpp
//  HW2_Sort
//
//  Created by 陈书新 on 2017/2/28.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include <iomanip>
#include "Array.h"

const int N = 1000000000;
//const int N = 1000000000;

int main(int argc, const char** argv)
{
    Array* array0 = new Array(N);
    //Array* array1 = new Array(array0);
    clock_t s = clock();
    array0->systemSort();
    //array1->systemSort();
    //std::cout << "check = " << array0->equals(array1) << std::endl;
    //array1->insertionSort();
    clock_t t = clock();
    double p = (double)(t - s) / CLOCKS_PER_SEC;
    //std::cout << std::setprecision(2) << p << "s" << std::endl;
    std::cout << p << "s" << std::endl;
    
    //array0->print(std::cout);
    
    //array1->print(std::cout);
    //array2->print(std::cout);
    //array3->print(std::cout);
    
    //std::cout << array0->equals(array1) << " " << std::endl;
    
    delete array0;
    
    return 0;
}
