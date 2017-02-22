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
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
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
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            in >> elem[i][j];
        }
    }
    in.close();
}

Matrix::~Matrix()
{
    for (int i = 0; i < size; ++i)
    {
        delete[] elem[i];
    }
    delete[] elem;
}

void Matrix::initializeElem()
{
    size = 1 << n;
    elem = new int*[size];
    for (int i = 0; i < size; ++i)
    {
        elem[i] = new int[size];
        for (int j = 0; j < size; ++j)
        {
            elem[i][j] = 0;
        }
    }
}

Matrix& Matrix::operator= (const Matrix& _matrix)
{
    assert(n == _matrix.n);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            elem[i][j] = _matrix.elem[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+ (const Matrix& _matrix)
{
    assert(n == _matrix.n);
    Matrix result(n);
    result.initializeElem();
    for (int i = 0; i < result.size; ++i)
    {
        for (int j = 0; j < result.size; ++j)
        {
            result.elem[i][j] = elem[i][j] + _matrix.elem[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator- (const Matrix& _matrix)
{
    assert(n == _matrix.n);
    Matrix result(n);
    result.initializeElem();
    for (int i = 0; i < result.size; ++i)
    {
        for (int j = 0; j < result.size; ++j)
        {
            result.elem[i][j] = elem[i][j] - _matrix.elem[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator* (const Matrix& _matrix)
{
    assert(n == _matrix.n);
    Matrix result(n);
    result.initializeElem();
    for (int i = 0; i < result.size; ++i)
    {
        for (int j = 0; j < result.size; ++j)
        {
            for (int k = 0; k < result.size; ++k)
            {
                result.elem[i][j] += elem[i][k] * _matrix.elem[k][j];
            }
        }
    }
    return result;
}
