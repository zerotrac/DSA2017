//
//  main.cpp
//  HW2_Pairs
//
//  Created by 陈书新 on 2017/3/2.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include "Point.h"
#include "Points.h"
#include <iostream>

const int N = 100000000;

int main(int argc, const char** argv)
{
    Points* points0 = new Points(N);
    //Points* points1 = new Points(points0);
    //Points* points2 = new Points(points0);
    clock_t s = clock();
    Point ans1 = points0->closestPairSystem();
    //Point ans2 = points1->closestPairOptimized();
    //Point ans3 = points2->closestPairBruteForce();
    clock_t t = clock();
    double p = (double)(t - s) / CLOCKS_PER_SEC;
    std::cout << "time = " << p << "s" << std::endl;
    
    Point p00 = points0->get(ans1.getX());
    Point p01 = points0->get(ans1.getY());
    //Point p10 = points1->get(ans2.getX());
    //Point p11 = points1->get(ans2.getY());
    //Point p20 = points2->get(ans3.getX());
    //Point p21 = points2->get(ans3.getY());
    
    std::cout << p00 << " " << p01 << std::endl;
    //std::cout << p10 << " " << p11 << std::endl;
    //std::cout << p20 << " " << p21 << std::endl;
    std::cout << p00.distanceTo(p01) << std::endl;
    //std::cout << p00.distanceTo(p01) << " " << p10.distanceTo(p11) << " " << p20.distanceTo(p21) << std::endl;
    
    delete points0;
    //delete points1;
    //delete points2;
    
    return 0;
}
