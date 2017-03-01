//
//  Array.cpp
//  HW2_Sort
//
//  Created by 陈书新 on 2017/2/28.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <queue>
#include "Array.h"

#define mp std::make_pair
#define PII std::pair<int, int>

Array::Array(int _size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    //std::uniform_int_distribution<uint> dis(0LL, 100000LL);
    
    std::uniform_int_distribution<uint> dis(0LL, (1LL << 32) - 1);
    
    size = _size;
    elem = new uint[size];
    uint* cur = elem;
    for (int i = 0; i < size; ++i)
    {
        *(cur++) = dis(gen);
    }
}

Array::Array(Array* that)
{
    size = that->size;
    elem = new uint[size];
    memcpy(elem, that->elem, sizeof(uint) * size);
}

Array::~Array()
{
    delete[] elem;
}

void Array::insertionSort()
{
    for (int i = 1; i < size; ++i)
    {
        int l = 0, r = i - 1, w = i, p = elem[i];
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (elem[mid] <= p)
            {
                l = mid + 1;
            }
            else
            {
                w = mid;
                r = mid - 1;
            }
        }
        for (int j = i - 1; j >= w; --j)
        {
            elem[j + 1] = elem[j];
        }
        elem[w] = p;
    }
}

void Array::shellSort()
{
    std::vector<int> v;
    long long p = 1;
    for (; p < size; p *= 2)
    {
        long long q = 1;
        for (; p * q < size; q *= 3)
        {
            v.push_back((int)(p * q));
        }
    }
    std::sort(v.begin(), v.end());
    for (int i = (int)v.size() - 1; i >= 0; --i)
    {
        int gap = v[i];
        for (int j = gap; j < size; ++j)
        {
            uint tmp = elem[j];
            uint* cur = elem + j;
            for (; cur - gap >= elem && *(cur - gap) > tmp; cur -= gap)
            {
                *cur = *(cur - gap);
            }
            *cur = tmp;
        }
    }
}


void Array::qsort(int l, int r)
{
    if (l >= r) return;
    uint pivot = elem[r], tmp;
    uint* w = elem + l - 1;
    uint* cur = elem + l;
    uint* dest = elem + r;
    for (; cur < dest; ++cur)
    {
        if (*cur < pivot)
        {
            tmp = *(++w);
            *w = *cur;
            *cur = tmp;
        }
    }
    tmp = *(++w);
    *w = *cur;
    *cur = tmp;
    
    int diff = (int)(w - elem);
    qsort(l, diff - 1);
    qsort(diff + 1, r);
}

void Array::quickSort()
{
    qsort(0, size - 1);
}

void Array::mergeSort()
{
    uint* tmp = new uint[size];
    for (int block = 1; block < size; block <<= 1)
    {
        for (int start = 0; start + block < size; start += block << 1)
        {
            uint* sa = elem + start;
            uint* ea = sa + block - 1;
            uint* sb = ea + 1;
            uint* eb = sb + block - 1;
            if (eb > elem + size - 1) eb = elem + size - 1;
            int len = (int)(eb - sa + 1);
            
            uint* cur = tmp + start;
            while (sa <= ea && sb <= eb) (*cur++) = *sa <= *sb ? *(sa++) : *(sb++);
            while (sa <= ea) (*cur++) = *(sa++);
            while (sb <= eb) (*cur++) = *(sb++);
            memcpy(elem + start, tmp + start, sizeof(uint) * len);
        }
    }
    delete[] tmp;
}

void Array::radixSort()
{
    int bucketSize = 8;
    int sz = 1 << bucketSize;
    int op = sz - 1;
    int* bucket = new int[sz];
    uint* copy = new uint[size];
    
    for (int i = 0; i < 32; i += bucketSize)
    {
        for (int j = 0; j < sz; ++j) bucket[j] = 0;
        uint* cur = elem;
        uint* dest = elem + size;
        for (; cur < dest;) ++bucket[(*(cur++) >> i) & op];
        for (int j = 1; j < sz; ++j) bucket[j] += bucket[j - 1];
        
        cur = elem + size - 1;
        for (; cur >= elem;)
        {
            copy[--bucket[(*cur >> i) & op]] = *cur;
            --cur;
        }
        
        i += bucketSize;
        for (int j = 0; j < sz; ++j) bucket[j] = 0;
        cur = copy;
        dest = copy + size;
        for (; cur < dest;) ++bucket[(*(cur++) >> i) & op];
        for (int j = 1; j < sz; ++j) bucket[j] += bucket[j - 1];
        
        cur = copy + size - 1;
        for (; cur >= copy;)
        {
            elem[--bucket[(*cur >> i) & op]] = *cur;
            --cur;
        }
    }
}

bool Array::equals(Array *that) const
{
    if (size != that->size) return false;
    for (int i = 0; i < size; ++i)
    {
        if (elem[i] != that->elem[i]) return false;
    }
    return true;
}

void Array::print(std::ostream& out)
{
    out << "[" << elem[0];
    for (int i = 1; i < size; ++i)
    {
        out << ", " << elem[i];
    }
    out << "]\n";
}
