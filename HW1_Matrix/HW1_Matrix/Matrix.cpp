//
//  Matrix.cpp
//  HW1_Matrix
//
//  Created by 陈书新 on 2017/2/21.
//  Copyright © 2017年 陈书新. All rights reserved.
//

#include "Matrix.h"
#include <cassert>
#include <iostream>
#include <fstream>

Matrix::Matrix(int _n)
{
    n = _n;
    initializeElem();
}

Matrix::Matrix(const Matrix& _matrix)
{
    n = _matrix.n;
    initializeElem();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            elem[i][j] = _matrix.elem[i][j];
        }
    }
}

Matrix::Matrix(const std::string URL)
{
    std::ifstream in(URL);
    in >> n;
    initializeElem();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            in >> elem[i][j];
        }
    }
    in.close();
}

Matrix::~Matrix()
{
    for (int i = 0; i < n; ++i)
    {
        delete[] elem[i];
    }
    delete[] elem;
}

void Matrix::initializeElem()
{
    elem = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        elem[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            elem[i][j] = 0;
        }
    }
}

Matrix& Matrix::operator=(const Matrix &_matrix)
{
    assert(n == _matrix.n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            elem[i][j] = _matrix.elem[i][j];
        }
    }
    return *this;
}
