#include "Matrix.h"

int main(int argc, const char** argv)
{
    Matrix a(2);
    Matrix b(2);
    Matrix c(3);
    a = b;
    b = c;
    return 0;
}
