//
//  Point.cpp
//  HW2_Pairs
//
//  Created by 陈书新 on 2017/3/2.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include "Point.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(int _x, int _y)
{
    x = _x;
    y = _y;
}

Point::~Point()
{
    
}

int Point::getX() const
{
    return x;
}

int Point::getY() const
{
    return y;
}

long long Point::distanceTo(Point that) const
{
    long long a = x - that.x;
    long long b = y - that.y;
    return a * a + b * b;
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "<" << point.x << ", " << point.y << ">";
    return out;
}

bool Point::cmpX(const Point &a, const Point &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool Point::cmpY(const Point &a, const Point &b)
{
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
