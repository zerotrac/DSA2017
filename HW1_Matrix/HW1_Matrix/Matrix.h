#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix
{
private:
    int n;
    int size;
    int** elem;
    
public:
    Matrix(int _n); // matrix size = 2^n
    Matrix(const Matrix& _matrix);
    Matrix(const Matrix& _matrix, int posx, int posy);
    Matrix(const std::string& URL);
    ~Matrix();
    
private:
    void initializeElem();
    
public:
    int sz() const;
    void setElem(int x, int y, int z);
    void print(const std::string& URL) const;
    Matrix strassen(const Matrix& _matrix) const;

    
public:
    Matrix& operator= (const Matrix& _matrix);
    Matrix operator+ (const Matrix& _matrix) const;
    Matrix operator- (const Matrix& _matrix) const;
    Matrix operator* (const Matrix& _matrix) const;
};

#endif
