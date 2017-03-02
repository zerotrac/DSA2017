//
//  Point.h
//  HW2_Pairs
//
//  Created by 陈书新 on 2017/3/2.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <fstream>

// Integer Point

class Point
{
private:
    int x;
    int y;
    
public:
    Point();
    Point(int _x, int _y);
    ~Point();
    
public:
    int getX() const;
    int getY() const;
    long long distanceTo(Point that) const; // distance^2
    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    bool operator== (const Point& that) const;
    
public:
    static bool cmpX(const Point& a, const Point& b);
    static bool cmpY(const Point& a, const Point& b);
};

#endif
