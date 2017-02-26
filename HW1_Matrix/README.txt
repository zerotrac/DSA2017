bin目录存放可执行文件，后续会说明使用方式，
HW1_Matrix目录存放源代码。

可执行文件使用方式：
使用带参数的命令行运行，
./executable_file <algorithm_type> <matrix_size> <repeat_times>
其中<algorithm_type>表示算法类型，可以选择bruteforce或strassen，
<matrix_size>表示矩阵大小，建议不要大于12，
<repeat_times>表示重复次数，每次重复时矩阵都会随机生成。
一种可行的方式为：
./mt bruteforce 8 100
或
./mt strassen 10 5

在实验报告中，我们提到了四种算法，bruteforce/strassen/strassen32/strassen128，
二在bin目录中有三个可执行文件，mt/mt-5/mt-7
在命令行运行中选择bruteforce时，这三个可执行文件调用的都是普通的暴力算法，
而选择strassen时，分别调用strassen/strassen32/strassen128算法。

源代码编译后和mt-7相同，可以在Matrix.cpp的106行把7改成2/5，编译之后即为mt/mt-5。
