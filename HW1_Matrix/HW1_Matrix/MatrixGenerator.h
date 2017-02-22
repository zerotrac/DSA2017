#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "Matrix.h"

class MatrixGenerator
{
public:
    static const int MATRIX_ELEM_MINIMUM;
    static const int MATRIX_ELEM_MAXIMUM;
    
public:
    MatrixGenerator();
    ~MatrixGenerator();
    static Matrix getMatrix(int _n);
};

#endif
