#include "Z2RowReducer.h"
#include <iostream>


int main() {
  std::cout << "TEST 1:\n";
  // 0 1 0 1
  // 1 1 0 0
  // 1 1 1 1
  Z2Matrix mat(3, 4);
  mat.flipON(0, 1);
  mat.flipON(0, 3);
  mat.flipON(1, 0);
  mat.flipON(1, 1);
  mat.flipON(2, 1);
  mat.flipON(2, 2);
  mat.flipON(2, 3);
  mat.flipON(2, 4);

  mat.print();

  mat.frontSolve();
  mat.print();
  mat.backSolve();
  mat.print();
}


