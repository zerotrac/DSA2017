//
//  Points.h
//  HW2_Pairs
//
//  Created by 陈书新 on 2017/3/2.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#ifndef POINTS_H
#define POINTS_H

#include "Point.h"

class Points
{
private:
    int size;
    Point* elem;
    static const int C;
    
public:
    Points(int _size);
    Points(const Points* that);
    ~Points();
    
public:
    Point get(int index) const;
    
public:
    Point closestPairBruteForce() const;
    Point closestPairOptimized() const;
    Point closestPairRecurision() const;
};

#endif
