#ifndef Z2ROWREDUCER
#define Z2ROWREDUCER

#include "BoolVector.h"
#include <iostream>


class Z2Matrix {
public:
  Z2Matrix(const int m, const int n);

  void frontSolve();
  void backSolve();
//  int getRank();

  void flipON(int i, int j) {
    matrix_[i].flipON(j);
  }

  void print() {
    for (int i = 0; i < m_; ++i) {
      matrix_[i].print();
      std::cout << std::endl;
    }
    std::cout << std::endl;
  };


private:
  Z2Matrix();

  std::vector< BoolVector > matrix_;
  int rank_;
  int m_; //Number of rows
  int n_; //Number of columns
};

#endif //Z2ROWREDUCER
