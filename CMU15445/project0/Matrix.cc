//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
// Copyright (c) 2015-2020, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "common/exception.h"

namespace bustub {

/**
 * The Matrix type defines a common
 * interface for matrix operations.
 */
template <typename T>
class Matrix {
 protected:
  /**
   * TODO(P0): Add implementation
   *
   * Construct a new Matrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   *
   */
  // 构造初始化
  Matrix(int rows, int cols) : rows_(rows), cols_(cols) {  }

  /** The number of rows in the matrix */
  int rows_;
  /** The number of columns in the matrix */
  int cols_;

  /**
   * TODO(P0): Allocate the array in the constructor.
   * TODO(P0): Deallocate the array in the destructor.
   * A flattened array containing the elements of the matrix.
   */
  T *linear_;

 public:
  /** @return The number of rows in the matrix */
  virtual int GetRowCount() const = 0;

  /** @return The number of columns in the matrix */
  virtual int GetColumnCount() const = 0;

  /**
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual T GetElement(int i, int j) const = 0;

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual void SetElement(int i, int j, T val) = 0;

  /**
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  virtual void FillFrom(const std::vector<T> &source) = 0;

  /**
   * Destroy a matrix instance.
   * TODO(P0): Add implementation
   */
  virtual ~Matrix() { };
};

/**
 * The RowMatrix type is a concrete matrix implementation.
 * It implements the interface defined by the Matrix type.
 */
 using std::vector;
template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  /**
   * TODO(P0): Add implementation
   *
   * Construct a new RowMatrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   */
  RowMatrix(int rows, int cols) : Matrix<T>(rows, cols) {
    // 使用行列初始化
    data_.resize(rows);
    for(int i = 0; i < rows; ++i){
      data_[i].resize(cols);
    }
  }

  /**
   * TODO(P0): Add implementation
   * @return The number of rows in the matrix
   */
  // 调用从父类继承的rows
  int GetRowCount() const override { return Matrix<T>::rows_; }

  /**
   * TODO(P0): Add implementation
   * @return The number of columns in the matrix
   */
  int GetColumnCount() const override { return Matrix<T>::cols_; }

  /**
   * TODO(P0): Add implementation
   *
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  T GetElement(int i, int j) const override {
    // 先进行边界检查，再获取元素
    if (i < 0 || i >= GetRowCount() || j < 0 || j >= GetColumnCount()) {
      throw Exception(ExceptionType::OUT_OF_RANGE, "OUT_OF_RANGE");
    }
    return data_[i][j];
  }

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  void SetElement(int i, int j, T val) override {
    if (i < 0 || i >= Matrix<T>::rows_ || j < 0 || j >= Matrix<T>::cols_) {
      throw Exception(ExceptionType::OUT_OF_RANGE, "OUT_OF_RANGE");
    }
    data_[i][j] = val;
  }

  /**
   * TODO(P0): Add implementation
   *
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  void FillFrom(const std::vector<T> &source) override {
    // throw NotImplementedException{"RowMatrix::FillFrom() not implemented."};
    int cols = Matrix<T>::cols_;
    int rows = Matrix<T>::rows_;
    if (static_cast<int>(source.size()) != cols * rows) {
      throw Exception(ExceptionType::OUT_OF_RANGE, "OUT_OF_RANGE");
    }
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        data_[i][j] = source[i * cols + j];
        // std::cout << "i: " << i << " j: " << j << " data: " << data_[i][j] << std::endl;
      }
    }
  }

  /**
   * TODO(P0): Add implementation
   *
   * Destroy a RowMatrix instance.
   */
  ~RowMatrix() override {
    // 销毁数组元素data_
    // delete[] data_;
  };

 private:
  /**
   * A 2D array containing the elements of the matrix in row-major format.
   *
   * TODO(P0):
   * - Allocate the array of row pointers in the constructor.
   * - Use these pointers to point to corresponding elements of the `linear` array.
   * - Don't forget to deallocate the array in the destructor.
   */
  vector<vector<T>> data_;
};

/**
 * The RowMatrixOperations class defines operations
 * that may be performed on instances of `RowMatrix`.
 */
template <typename T>
class RowMatrixOperations {
 public:
  /**
   * Compute (`matrixA` + `matrixB`) and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix addition
   */
  static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
    int aCols = matrixA->GetColumnCount(), aRows = matrixA->GetRowCount();
    int bCols = matrixB->GetColumnCount(), bRows = matrixB->GetRowCount();
    // 判断是否越界
    if (aCols != bCols || aRows != bRows) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    int cols = aCols;
    int rows = aRows;
    T sum;
    // 使用独占指针
    auto matrix_c = std::unique_ptr<RowMatrix<T>>(new RowMatrix<T>(rows, cols));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        sum = matrixA->GetElement(i, j) + matrixB->GetElement(i, j);
        matrix_c->SetElement(i, j, sum);
      }
    }
    return matrix_c;
  }

  /**
   * Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix multiplication
   */
  static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
    // 检查维度，然后计算矩阵乘法
    int cols_a = matrixA->GetColumnCount(), rows_a = matrixA->GetRowCount();
    int cols_b = matrixB->GetColumnCount(), rows_b = matrixB->GetRowCount();
    if (cols_a != rows_b) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    int cols = cols_b, rows = rows_a, mid = rows_b;
    auto matrix_c = std::unique_ptr<RowMatrix<T>>(new RowMatrix<T>(rows, cols));
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        T sum = 0;
        for (int k = 0; k < mid; ++k) {
          sum += matrixA->GetElement(i, k) * matrixB->GetElement(k, j);
        }
        matrix_c->SetElement(i, j, sum);
      }
    }
    return matrix_c;
  }

  /**
   * Simplified General Matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @param matrixC Input matrix
   * @return The result of general matrix multiply
   */
  static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB,
                                            const RowMatrix<T> *matrixC) {
    // TODO(P0): Add implementation
    auto matrix_multiply = Multiply(matrixA, matrixB);
    if (matrix_multiply == nullptr) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    auto matrix_add = Add(matrix_multiply, matrixC);
    return matrix_add;
  }
};
}  // namespace bustub
