#include "MatrixGenerator.h"
#include <ctime>
#include <cstdlib>

const int MatrixGenerator::MATRIX_ELEM_MINIMUM = 1;
const int MatrixGenerator::MATRIX_ELEM_MAXIMUM = 100;

MatrixGenerator::MatrixGenerator()
{
    srand((unsigned int)time(nullptr));
}

MatrixGenerator::~MatrixGenerator()
{
    //
}

Matrix MatrixGenerator::getMatrix(int _n)
{
    Matrix result(_n);
    for (int i = 0; i < result.sz(); ++i)
    {
        for (int j = 0; j < result.sz(); ++j)
        {
            result.setElem(i, j, rand() % (MATRIX_ELEM_MAXIMUM - MATRIX_ELEM_MINIMUM + 1) + MATRIX_ELEM_MINIMUM);
        }
    }
    return result;
}
