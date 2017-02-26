#include "Matrix.h"
#include "MatrixGenerator.h"
#include <cstring>

int myatoi(const char* st)
{
    int len = (int)strlen(st);
    int result = 0;
    for (int i = 0; i < len; ++i)
    {
        result = result * 10 + st[i] - 48;
    }
    return result;
}

int main(int argc, const char** argv)
{
    /*
     argv[1] is the algorithm we use to calculate matrix multiplication.
     "bruteforce" or "strassen"
     
     argv[2] is the size of matrix.
     It is recommended that this number be under 11 since the hardware is limited.
     
     argv[3] is the number of times we repeat the algorithm.
    */
    
    int matrixSize = myatoi(argv[2]);
    int repetition = myatoi(argv[3]);
    
    MatrixGenerator* matrixGenerator = new MatrixGenerator();
    while (repetition--)
    {
        Matrix a = matrixGenerator->getMatrix(matrixSize);
        Matrix b = matrixGenerator->getMatrix(matrixSize);
        if (strcmp(argv[1], "bruteforce") == 0)
        {
            Matrix c = a * b;
            c.print("ans.txt");
        }
        if (strcmp(argv[1], "strassen") == 0)
        {
            Matrix c = a.strassen(b);
            c.print("ans.txt");
        }
    }
    return 0;
}
