//
//  Array.h
//  HW2_Sort
//
//  Created by 陈书新 on 2017/2/28.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>

#define uint unsigned int

class Array
{
private:
    int size;
    uint* elem;

public:
    Array(int _size);
    Array(Array* that);
    ~Array();
    
private:
    void qsort(int l, int r);
    
public:
    void insertionSort();
    void shellSort();
    void quickSort();
    void mergeSort();
    void radixSort();
    
public:
    bool equals(Array* that) const;
    
public:
    void print(std::ostream& out);
};

#endif
