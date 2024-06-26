#pragma once
#include <iostream>
#include <thread>
#include <cassert>
#include "Matrix.hpp"

/// @brief 朴素的矩阵乘法，复杂度为O(n^3)
/// 一共需要x*y*z次乘法和x*y*(z-1)次加法
void serial_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C) {
    int Aheight = A.rows();
    int Awidth = A.cols();
    int Bheight = B.rows();
    assert(Awidth == Bheight);
    int Bweight = B.cols();
    for (int i = 0; i < Aheight; i++) {
        for (int j = 0; j < Bweight; j++) {
            C[i][j] = 0;
            for (int k = 0; k < Awidth; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/// @brief 利用访存局部性原理优化矩阵乘法
/// 更改了循环顺序，使得内存访问更加连续
/// 本来是按行访问，取A的第i行和B的第j列，然后相乘
/// 现在是取A的第i行，然后和B的第k行的每一个元素相乘，放到对应的C[i][j]中
/// 这样可以使B是按行读取的，读取到cache中的数据能够被重复利用
void matrix_multiply_better(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C){
    int Aheight = A.rows();
    int Awidth = A.cols();
    int Bheight = B.rows();
    assert(Awidth == Bheight);
    int Bweight = B.cols();
    for (int i = 0; i < Aheight; i++) {
        for (int k = 0; k < Awidth; k++) { 
            for (int j = 0; j < Bweight; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


/// @brief strassen矩阵乘法,复杂度为O(n^2.81),引入了递归和分治的思想，需要注意的是n必须是2的幂次方
/// 具体而言方法就是：将两个矩阵分成四个子矩阵，然后计算出这四个子矩阵的乘积，然后再合并成一个矩阵
/// 引入了7个中间矩阵，分别是M1,M2,...,M7，然后根据这些中间矩阵计算出最终的矩阵乘积
/// 一共需要7次乘法和18次加法，相较于朴素的矩阵乘法，strassen算法减少了一半的乘法次数
/// Strassen算法的优势在于当矩阵较大时才会显现出来，在小规模问题上，由于递归和额外的加法运算，其效率可能不如标准的矩阵乘法算法。
/// 但是在大规模问题上，Strassen算法的优势就会显现出来，因为它的时间复杂度是O(n^2.81)而不是O(n^3)
/// 实际上很少有矩阵满足2的幂次方，所以Strassen算法并不是很实用，但是可以通过填充0的方法来解决这个问题
/// 也可以将矩阵划分为2的幂次乘以x的形式，直到递归到最小矩阵x*x，然后再使用朴素的矩阵乘法
void strassen_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C) {
    C.zero();
    int Aheight = A.rows();
    int Awidth = A.cols();
    int Bheight = B.rows();
    assert(Awidth == Bheight);
    int Bweight = B.cols();
    if (Aheight < 64) {
        matrix_multiply_better(A, B, C);
        return;
    }
    if(Aheight % 2 != 0 || Awidth % 2 != 0 || Bweight % 2 != 0){
        Matrix<int> __A = A;
        Matrix<int> __B = B;
        Matrix<int> __C = C;
        if(Aheight % 2 != 0){
            __A.padding(true,0);
            __C.padding(true,0);
        }
        if(Awidth % 2 != 0){
            __A.padding(false,0);
            __B.padding(true,0);
        }
        if(Bweight % 2 != 0){
            __B.padding(false,0);
            __C.padding(false,0);
        }
        strassen_matrix_multiply(__A,__B,__C);
        C = __C.split(0,Aheight,0,Bweight);
        return;
    }
    Matrix<int> A11 = A.split(0, Aheight / 2, 0, Awidth / 2);
    Matrix<int> A12 = A.split(0, Aheight / 2, Awidth / 2, Awidth);
    Matrix<int> A21 = A.split(Aheight / 2, Aheight, 0, Awidth / 2);
    Matrix<int> A22 = A.split(Aheight / 2, Aheight, Awidth / 2, Awidth);
    Matrix<int> B11 = B.split(0, Awidth / 2, 0, Bweight / 2);
    Matrix<int> B12 = B.split(0, Awidth / 2, Bweight / 2, Bweight);
    Matrix<int> B21 = B.split(Awidth / 2, Awidth, 0, Bweight / 2);
    Matrix<int> B22 = B.split(Awidth / 2, Awidth, Bweight / 2, Bweight);

    Matrix<int> M1(Aheight / 2, Bweight / 2);
    Matrix<int> M2(Aheight / 2, Bweight / 2);
    Matrix<int> M3(Aheight / 2, Bweight / 2);
    Matrix<int> M4(Aheight / 2, Bweight / 2);
    Matrix<int> M5(Aheight / 2, Bweight / 2);
    Matrix<int> M6(Aheight / 2, Bweight / 2);
    Matrix<int> M7(Aheight / 2, Bweight / 2);

    strassen_matrix_multiply(A11 + A22, B11 + B22, M1);
    strassen_matrix_multiply(A21 + A22, B11, M2);
    strassen_matrix_multiply(A11, B12 - B22, M3);
    strassen_matrix_multiply(A22, B21 - B11, M4);
    strassen_matrix_multiply(A11 + A12, B22, M5);
    strassen_matrix_multiply(A21 - A11, B11 + B12, M6);
    strassen_matrix_multiply(A12 - A22, B21 + B22, M7);

    Matrix<int> C11 = M1 + M4 - M5 + M7;
    Matrix<int> C12 = M3 + M5;
    Matrix<int> C21 = M2 + M4;
    Matrix<int> C22 = M1 - M2 + M3 + M6;

    C11.concatenate(C12, C11.cols(), false);
    C21.concatenate(C22, C21.cols(), false);
    C11.concatenate(C21, C11.rows(), true);
    C = C11;
}

/// @brief Coppersmith–Winograd算法，复杂度为O(n^2.376)
void Coppersmith_Winograd_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C) {
    //TODO
}


void column_parallel_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C, int tid) {
    int Aheight = A.rows();
    int Awidth = A.cols();
    int Bheight = B.rows();
    assert(Awidth == Bheight);
    int Bweight = B.cols();
    if (tid == 0) {
        for(int j = 0;j<Bweight/2;j++){
            for(int i = 0;i<Aheight;i++){
                C[i][j] = 0;
                for(int k = 0;k<Awidth;k++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    } else {
        for(int j = Bweight/2;j<Bweight;j++){
            for(int i = 0;i<Aheight;i++){
                C[i][j] = 0;
                for(int k = 0;k<Awidth;k++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
}
enum MODE{
    ColumnParallel,
    RowParallel,
    BlockSplitParallel
};

void column_parallel_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C, int tid);

void parallel_matrix_multiply(const Matrix<int>& A, const Matrix<int>& B, Matrix<int>& C,MODE mode) {

    if(mode == ColumnParallel){
        std::thread threads[2];
        threads[0] = std::thread(column_parallel_matrix_multiply, std::ref(A), std::ref(B), std::ref(C), 0);
        threads[1] = std::thread(column_parallel_matrix_multiply, std::ref(A), std::ref(B), std::ref(C), 1);
        threads[0].join();
        threads[1].join();
    }else if(mode == RowParallel){
        std::thread threads[2];
        const Matrix<int> A1 = A.split(0,A.rows(),0,A.cols()/2);
        const Matrix<int> A2 = A.split(0,A.rows(),A.cols()/2,A.cols());
        const Matrix<int> B1 = B.split(0,B.rows()/2,0,B.cols());
        const Matrix<int> B2 = B.split(B.rows()/2,B.rows(),0,B.cols());

        Matrix<int> C1(A.rows(),B.cols());
        Matrix<int> C2(A.rows(),B.cols());
        C1.zero();
        C2.zero();

        threads[0] = std::thread(matrix_multiply_better, std::ref(A1), std::ref(B1), std::ref(C1));
        threads[1] = std::thread(matrix_multiply_better, std::ref(A2), std::ref(B2), std::ref(C2));
        threads[0].join();
        threads[1].join();

        C = C1 + C2;
    }else if(mode == BlockSplitParallel){
        //TODO
    }
}
