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
  // rows_ 行， cols_ 列
  Matrix(int rows, int cols) : rows_(rows), cols_(cols) { linear_ = new T[rows_ * cols_]; }

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
  virtual ~Matrix() { delete[] linear_; };
};

/**
 * The RowMatrix type is a concrete matrix implementation.
 * It implements the interface defined by the Matrix type.
 */
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
    // data_是指向T*的指针
    data_ = reinterpret_cast<T **>(malloc(sizeof(T *) * rows));
    for (int i = 0; i < rows; ++i) {
      // 记录每一行首指针
      data_[i] = Matrix<T>::linear_ + i * cols;
    }
  }

  /**
   * TODO(P0): Add implementation
   * @return The number of rows in the matrix
   */
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
    // 边界检查再返回元素
    // throw NotImplementedException{"RowMatrix::GetElement() not implemented."};
    if (i < 0 || j < 0 || i >= Matrix<T>::rows_ || j >= Matrix<T>::cols_) {
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
    // 边界检查再设置元素
    if (i < 0 || j < 0 || i >= Matrix<T>::rows_ || j >= Matrix<T>::cols_) {
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
    auto r = Matrix<T>::rows_;
    auto c = Matrix<T>::cols_;
    if (source.size() != size_t(r * c)) {
      throw Exception(ExceptionType::OUT_OF_RANGE, "OUT_OF_RANGE");
    }
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        data_[i][j] = source[i * c + j];
      }
    }
  }

  /**
   * TODO(P0): Add implementation
   *
   * Destroy a RowMatrix instance.
   */
  ~RowMatrix() override {
    delete[] data_;
  };

  void print() {
    for (int i = 0; i < Matrix<T>::rows_; ++i) {
      for (int j = 0; j < Matrix<T>::cols_; ++j) {
        printf("%d  ", data_[i][j]);
      }
      printf("\n");
    }
  }

 private:
  /**
   * A 2D array containing the elements of the matrix in row-major format.
   *
   * TODO(P0):
   * - Allocate the array of row pointers in the constructor.
   * - Use these pointers to point to corresponding elements of the `linear` array.
   * - Don't forget to deallocate the array in the destructor.
   */
  T **data_;
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
    // 检查类型是否为空再检查参数
    // 矩阵计算
    if (matrixA == nullptr || matrixB == nullptr) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    auto ra = matrixA->GetRowCount();
    auto ca = matrixA->GetColumnCount();
    auto rb = matrixB->GetRowCount();
    auto cb = matrixB->GetColumnCount();
    if (ra != rb || ca != cb) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    std::vector<T> source;
    for (int i = 0; i < ra; ++i) {
      for (int j = 0; j < ca; ++j) {
        auto val = matrixA->GetElement(i, j) + matrixB->GetElement(i, j);
        source.emplace_back(val);
      }
    }
    auto matrixC = std::unique_ptr<RowMatrix<T>>(new RowMatrix<T>(ra, ca));
    matrixC->FillFrom(source);
    return matrixC;
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
    // 检查类型是否为空再检查参数
    // 矩阵计算
    if (matrixA == nullptr || matrixB == nullptr) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    auto ra = matrixA->GetRowCount();
    auto ca = matrixA->GetColumnCount();
    auto rb = matrixB->GetRowCount();
    auto cb = matrixB->GetColumnCount();
    if (ca != rb) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    // std::vector<T> source;
    auto matrixC = std::make_unique<RowMatrix<T>>(ra, cb);
    for (int i = 0; i < ra; ++i) {
      for (int j = 0; j < cb; ++j) {
        T temp = T();
        for (int k = 0; k < rb; ++k) {
          temp += matrixA->GetElement(i, k) * matrixB->GetElement(k, j);
        }
        matrixC->SetElement(i, j, temp);
      }
    }
    // matrixC->FillFrom(source);
    return matrixC;
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
    auto matrixTmp = Multiply(matrixA, matrixB);
    if (matrixTmp == nullptr) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    auto res = Add(matrixTmp, matrixC);
    if (res == nullptr) {
      return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    return res;
  }
};
}  // namespace bustub
