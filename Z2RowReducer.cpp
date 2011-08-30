#include "Z2RowReducer.h"


Z2Matrix::Z2Matrix(const int m, const int n)
: rank_(-1)
, m_(m)
, n_(n)
{
  matrix_.reserve(m);
  for (int i = 0; i < m; ++i) {
    BoolVector row(n);
    matrix_.push_back(row);
  }
}


void Z2Matrix::frontSolve() {
  int nPivotRow = 0;

  //n-1 because we assume the last column is the "objective" vector
  for ( int j = 0; j < n_-1; j++ ) {
    //Find pivot
    int nPivot = nPivotRow;
    while (nPivot < m_) {
      if ( matrix_[nPivot][j] )
        break;
      nPivot++;
    }

    if (nPivot < m_) { //If we found a pivot row
      if (nPivot != nPivotRow) { // And it's not the main row
        //Swap with main row if not main row
        matrix_[nPivotRow].swap(matrix_[nPivot]);
      }
    } else continue; //this column is clear, go to next column

    //Kill all non zero in the column except for pivot.
    for ( int i = nPivot+1; i < m_; i++ ) {
      if ( matrix_[i][j] ) {
        matrix_[i].myXOR(matrix_[nPivotRow], j);
      }
    }
        
    nPivotRow++;
  }
}


void Z2Matrix::backSolve() {
  for ( int j = n_-2; j > 0; j-- ) {
    //Find first non-zero entry from the bottom
    int nPivot = j;
    while ( nPivot >= 0 && !matrix_[nPivot][j] ) {
      nPivot--;
    }

    //The whole column is 0, try again with next column
    if (nPivot == -1) {
      continue;
    }

    //TODO: There may be some optimization here by not XOR-ing when
    //we're not actually at a pivot, depending on if XOR-ing is faster than 
    //checking if it's a pivot, and how often we're right about it not
    //being a pivot.

    //Kill all non-zero above
    for ( int i = nPivot-1; i > -1; i-- )
      if ( matrix_[i][j] )
        matrix_[i].myXOR(matrix_[nPivot]);
  }
}
