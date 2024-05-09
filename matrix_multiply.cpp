#include <iostream>

#include "Matrix.hpp"
#include "FunctionDecorator.hpp"
#include "multiply_algorithm.hpp"

using namespace std;

int main() {
    int n = 1000;
    int m = 1000;
    int k = 1000;
    Matrix<int> A(n, k);
    Matrix<int> B(k, m);
    Matrix<int> C(n, m);
    Matrix<int> D(n, m);
    Matrix<int> E(n, m);
    A.fill(1);
    B.fill(1);

    // auto serial_func = measureTime(serial_matrix_multiply, "Serial matrix multiplication");
    // serial_func(A, B, C);
    auto strassen_matrix_multiply_func = measureTime(strassen_matrix_multiply, "Strassen matrix multiplication");
    strassen_matrix_multiply_func(A, B, C);
    auto better_serial = measureTime(matrix_multiply_better, "Better serial matrix multiplication");
    better_serial(A, B, D);
    // auto parallel_func = measureTime(parallel_matrix_multiply, "Column parallel matrix multiplication");
    // parallel_func(A, B, D, ColumnParallel);
    auto row_parallel_func = measureTime(parallel_matrix_multiply, "Row parallel matrix multiplication");
    row_parallel_func(A, B, E, RowParallel);
    cout << "C == D: " << (C == D) << endl;
    cout << "C == E: " << (C == E) << endl;

    return 0;
}

