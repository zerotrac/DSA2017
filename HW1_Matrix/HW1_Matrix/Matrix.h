#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix
{
private:
    int n;
    int** elem;
    
public:
    Matrix(int _n);
    Matrix(const Matrix& _matrix);
    Matrix(const std::string URL);
    ~Matrix();
    
private:
    void initializeElem();
    
public:
    Matrix& operator= (const Matrix& _matrix);
};

#endif
