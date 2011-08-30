#ifndef BOOLVECTOR
#define BOOLVECTOR

#include <vector>
#include <iostream>

//#define INTSIZE CHAR_BIT * sizeof(int)
#define INTSIZE 32

//TODO: Describe memory layout and usage

class BoolVector {
public:
  BoolVector( const int size )
    : vector_((size-1)/INTSIZE + 1, 0)
    , sizeInBits_(size)
  {};

  ~BoolVector() {};

  const int& size() {return sizeInBits_;};

  void myXOR( const BoolVector& vb, const int& begin = 0 ) {
    int n = vector_.size();
    for ( int i = begin/INTSIZE; i < n; i++ )
      vector_[i] ^= vb.vector_[i];
  };

  bool operator[] ( const int& i ) {
    // -two's complement check of first bit
    return (( vector_[(unsigned int)i/INTSIZE] <<
              ((unsigned int)i%INTSIZE) 
            ) < 0);
  };

  bool back() {
    return (*this)[sizeInBits_- 1];
  };

  void swap( BoolVector& vb) {
    vector_.swap(vb.getVector());
  };

  void flipBit( const int& i ) {
    vector_[i/INTSIZE] ^= ((unsigned int)INT_MIN >> (i%INTSIZE));
  };

  void flipON( const int& i ) {
    vector_[i/INTSIZE] |= ((unsigned int)INT_MIN >> (i%INTSIZE));
  };

  void flipOFF( const int& i )
  {
    vector_[i/INTSIZE] &= ~((unsigned int)INT_MIN >> (i%INTSIZE));
  };

  std::vector<int>& getVector() {
    return vector_;
  };

  void print() {
    for (int i = 0; i < sizeInBits_; ++i) {
      std::cout << (int)(*this)[i];
    }
  };

private:
  BoolVector(); //Do not call

  int sizeInBits_;
  std::vector<int> vector_;
};

#endif // BOOLVECTOR
