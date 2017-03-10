//
//  main.cpp
//  HW3_LIS
//
//  Created by 陈书新 on 2017/3/7.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <fstream>

const int minRandomNumber = 1;
const int maxRandomNumber = 1000000000;

void work(int n, int dataGen)
{
    int* a = new int[n];
    
    if (dataGen == 2)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(minRandomNumber, maxRandomNumber);
        std::ofstream out("input.txt");
        out << n << std::endl;
        
        for (int i = 0; i < n; ++i)
        {
            a[i] = dis(gen);
            //a[i] = i + 1;
            out << a[i];
            if (i != n - 1) out << " "; else out << std::endl;
        }
        out.close();
        std::cout << "随机生成的输入数据已经放在input.txt文件中。\n";
    }
    else
    {
        std::cout << "请输入" << n << "个" << "范围为[" << minRandomNumber << "," << maxRandomNumber << "]的正整数，以空格或回车分开。输入以回车结尾。\n";
        for (int i = 0; i < n; ++i)
        {
            std::cin >> a[i];
        }
    }
    
    int* bin = new int[n];
    int* parent = new int[n];
    int curL = 0, curR = 0;
    bin[0] = 0;
    parent[0] = -1;
    int maxPosition = 0;
    
    clock_t s = clock();
    
    for (int i = 1; i < n; ++i)
    {
        int l = curL, r = curR, w = curR + 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (a[bin[mid]] >= a[i])
            {
                w = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (w == curR + 1)
        {
            ++curR;
            maxPosition = i;
        }
        bin[w] = i;
        if (w == 0) parent[i] = -1; else parent[i] = bin[w - 1];
    }
    
    clock_t t = clock();
    double p = (double)(t - s) / CLOCKS_PER_SEC;
    std::cout << "time = " << p << "s\n";
    
    std::ofstream ans("output.txt");
    ans << curR + 1 << std::endl;
    int calc = curR;
    int curPosition = maxPosition;
    while (curPosition != -1)
    {
        bin[calc--] = a[curPosition];
        curPosition = parent[curPosition];
    }
    for (int i = 0; i <= curR; ++i)
    {
        ans << bin[i];
        if (i != curR) ans << " "; else ans << std::endl;
    }
    
    std::cout << "输出结果已经放在output.txt文件中。\n";
    
    delete[] a;
    delete[] bin;
    delete[] parent;
}

int main()
{
    int dataGen = 0;
    while (1)
    {
        std::cout << "手动输入数据 or 随机生成数据？(A/R): ";
        std::string st;
        getline(std::cin, st);
        
        int len = (int)st.size();
        if (len != 1) continue;
        if (st[0] == 'a' || st[0] == 'A')
        {
            dataGen = 1;
            break;
        }
        else if (st[0] == 'r' || st[0] == 'R')
        {
            dataGen = 2;
            break;
        }
        else
        {
            continue;
        }
    }
    
    int n = 0;
    while (1)
    {
        std::cout << "请输入一个正整数，表示数据规模：";
        std::cin >> n;
        if (n <= 0) continue; else break;
    }
    
    work(n, dataGen);
    
    return 0;
}
