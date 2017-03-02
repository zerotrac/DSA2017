//
//  Points.cpp
//  HW2_Pairs
//
//  Created by 陈书新 on 2017/3/2.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include <random>
#include <algorithm>
#include "Points.h"

const int Points::C = 1000000000;

Points::Points(int _size)
{
    size = _size;
    elem = new Point[size];
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-C, C);
    
    for (int i = 0; i < size; ++i)
    {
        int xx = dis(gen);
        int yy = dis(gen);
        elem[i] = Point(xx, yy);
    }
}

Points::Points(const Points* that)
{
    size = that->size;
    elem = new Point[size];
    for (int i = 0; i < size; ++i)
    {
        elem[i] = that->elem[i];
    }
}

Points::~Points()
{
    delete[] elem;
}

Point Points::get(int index) const
{
    return elem[index];
}

Point Points::closestPairBruteForce() const
{
    int ansx = 0;
    int ansy = 1;
    long long mindis = elem[0].distanceTo(elem[1]);
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            long long curdis = elem[i].distanceTo(elem[j]);
            if (curdis < mindis)
            {
                mindis = curdis;
                ansx = i;
                ansy = j;
            }
        }
    }
    return Point(ansx, ansy);
}

Point Points::closestPairOptimized() const
{
    std::sort(elem, elem + size, Point::cmpX);
    
    double up = sqrt(2.0) * 2 * C;
    int down = sqrt(size - 1.0);
    long long dmax = up / down;
    
    int ansx = 0;
    int ansy = 1;
    long long mindis = dmax * dmax;
    
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            long long dx = elem[j].getX() - elem[i].getX();
            if (dx * dx > mindis) break;
            
            long long curdis = elem[i].distanceTo(elem[j]);
            if (curdis < mindis)
            {
                mindis = curdis;
                ansx = i;
                ansy = j;
            }
        }
    }
    return Point(ansx, ansy);
}

Point Points::closestPairRecurision() const
{
    return Point();
}
