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

Matrix::Matrix(const Matrix& _matrix, int posx, int posy)
{
    n = _matrix.n - 1;
    initializeElem();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            elem[i][j] = _matrix.elem[i + posx * size][j + posy * size];
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

Matrix Matrix::strassen(const Matrix &_matrix) const
{
    Matrix result(n);
    
    if (n <= 7)
    {
        result = *this * _matrix;
        return result;
    }
    
    /*
    [r s] = [a b] * [e f]
    [t u]   [c d] * [g h]
    */
    
    Matrix a(*this, 0, 0), b(*this, 0, 1), c(*this, 1, 0), d(*this, 1, 1);
    Matrix e(_matrix, 0, 0), f(_matrix, 0, 1), g(_matrix, 1, 0), h(_matrix, 1, 1);
    
    Matrix p1 = a.strassen(f - h),
           p2 = (a + b).strassen(h),
           p3 = (c + d).strassen(e),
           p4 = d.strassen(g - e),
           p5 = (a + d).strassen(e + h),
           p6 = (b - d).strassen(g + h),
           p7 = (a - c).strassen(e + f);
    
    Matrix r = p5 + p4 - p2 + p6,
           s = p1 + p2,
           t = p3 + p4,
           u = p5 + p1 - p3 - p7;
    
    int s0 = size >> 1;
    for (int i = 0; i < s0; ++i) for (int j = 0; j < s0; ++j)
        result.elem[i][j] = r.elem[i][j];
    for (int i = 0; i < s0; ++i) for (int j = 0; j < s0; ++j)
        result.elem[i][j + s0] = s.elem[i][j];
    for (int i = 0; i < s0; ++i) for (int j = 0; j < s0; ++j)
        result.elem[i + s0][j] = t.elem[i][j];
    for (int i = 0; i < s0; ++i) for (int j = 0; j < s0; ++j)
        result.elem[i + s0][j + s0] = u.elem[i][j];
    
    return result;
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

Matrix Matrix::operator+ (const Matrix& _matrix) const
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

Matrix Matrix::operator- (const Matrix& _matrix) const
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

Matrix Matrix::operator* (const Matrix& _matrix) const
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
