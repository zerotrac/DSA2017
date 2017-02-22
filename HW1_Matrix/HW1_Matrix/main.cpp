#include "Matrix.h"
#include "MatrixGenerator.h"

int main(int argc, const char** argv)
{
    MatrixGenerator* matrixGenerator = new MatrixGenerator();
    Matrix a = matrixGenerator->getMatrix(6);
    Matrix b = matrixGenerator->getMatrix(6);
    Matrix c = a * b;
    a.print("a.txt");
    b.print("b.txt");
    c.print("c.txt");
    return 0;
}
