#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class Matrix {
    private:
        int __rows;
        int __cols;
        T** data;
    public:
        Matrix(int __rows, int __cols) : __rows(__rows), __cols(__cols) {
            data = new T*[__rows];
            for (int i = 0; i < __rows; i++) {
                data[i] = new T[__cols];
            }
        }
        Matrix(const Matrix<T>& other) : __rows(other.__rows), __cols(other.__cols) {
            data = new T*[__rows];
            for (int i = 0; i < __rows; i++) {
                data[i] = new T[__cols];
                std::copy(other.data[i], other.data[i] + __cols, data[i]);
            }
        }
        ~Matrix() {
            for (int i = 0; i < __rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
        int rows() const {
            return __rows;
        }
        int cols() const {
            return __cols;
        }

        void fill(T value) {
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    data[i][j] = value;
                }
            }
        }
        void randomize() {
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    data[i][j] = rand() % 100;
                }
            }
        }
        void zero() {
            fill(0);
        }
        void diagonal(T* values) {
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    if (i == j) {
                        data[i][j] = values[i];
                    } else {
                        data[i][j] = 0;
                    }
                }
            }
        }
        Matrix split(int row_start, int row_end, int col_start, int col_end) const {
            Matrix<T> result(row_end - row_start, col_end - col_start);
            for (int i = row_start; i < row_end; i++) {
                for (int j = col_start; j < col_end; j++) {
                    result[i - row_start][j - col_start] = data[i][j];
                }
            }
            return result;
        }
        void concatenate(const Matrix<T>& other, int position, bool row) {
            if (row) {
                int new_rows = __rows + other.rows();
                T** new_data = new T*[new_rows];
                for (int i = 0; i < new_rows; i++) {
                    new_data[i] = new T[__cols];
                }
                for (int i = 0; i < position; i++) {
                    std::copy(data[i], data[i] + __cols, new_data[i]);
                }
                for (int i = 0; i < other.rows(); i++) {
                    std::copy(other.data[i], other.data[i] + other.cols(), new_data[position + i]);
                }
                for (int i = position + other.rows(); i < new_rows; i++) {
                    std::copy(data[i - other.rows()], data[i - other.rows()] + __cols, new_data[i]);
                }
                for (int i = 0; i < __rows; i++) {
                    delete[] data[i];
                }
                delete[] data;
                data = new_data;
            } else {
                int new_cols = __cols + other.cols();
                T** new_data = new T*[__rows];
                for (int i = 0; i < __rows; i++) {
                    new_data[i] = new T[new_cols];
                    std::copy(data[i], data[i] + __cols, new_data[i]);
                    std::copy(other.data[i], other.data[i] + other.cols(), new_data[i] + __cols);
                }
                for (int i = 0; i < __rows; i++) {
                    delete[] data[i];
                }
                delete[] data;
                data = new_data;
            }
        }

        void operator=(const Matrix<T>& other) {
            for (int i = 0; i < __rows; i++) {
                std::copy(other.data[i], other.data[i] + __cols, data[i]);
            }
        }

        Matrix operator+(const Matrix<T>& other) const {
            Matrix<T> result(__rows, __cols);
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    result[i][j] = data[i][j] + other.data[i][j];
                }
            }
            return result;
        }

        Matrix operator-(const Matrix<T>& other) const {
            Matrix<T> result(__rows, __cols);
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    result[i][j] = data[i][j] - other.data[i][j];
                }
            }
            return result;
        }

        bool operator==(const Matrix<T>& other) const {
            for (int i = 0; i < __rows; i++) {
                for (int j = 0; j < __cols; j++) {
                    if (data[i][j] != other.data[i][j]) {
                        std::cout <<"*** ERROR ***\n"<<std::endl;
                        std::cout << "Mismatch at " << i << " " << j << std::endl;
                        std::cout << data[i][j] << " " << other.data[i][j] << std::endl;
                        return false;
                    }
                }
            }
            return true;
        }

        T* operator[](int i) {
            return data[i];
        }
        const T* operator[](int i) const {
            return data[i];
        }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.cols(); j++) {
            os << matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}