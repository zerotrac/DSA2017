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

Matrix::Matrix(const std::string& URL)
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

int Matrix::sz() const
{
    return size;
}

void Matrix::setElem(int x, int y, int z)
{
    if (x < 0 || x >= size || y < 0 || y >= size) return;
    elem[x][y] = z;
}

void Matrix::print(const std::string &URL) const
{
    std::ofstream out(URL);
    out << n << std::endl;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            out << elem[i][j];
            if (j == size - 1) out << std::endl; else out << " ";
        }
    }
    out.close();
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
