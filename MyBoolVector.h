#include <vector>

#define INTSIZE 32


class MyBoolVector
{
public:
    MyBoolVector( const int& size )
        : _vector((size-1)/INTSIZE+1, 0)
        , _sizeInBits(size)
    {};

    ~MyBoolVector() {};

    const int& size() {return _sizeInBits;};

    void myXOR( const MyBoolVector& vb, const int& begin = 0 ) {
        int n = _vector.size();
        for ( int i = begin/INTSIZE; i < n; i++ )
            _vector[i] ^= vb._vector[i];
    };

    bool operator[] (const int& i) {
        // -unsigned int division is faster than int division aparently
        // -two's complement check of first bit
        return (( _vector[(unsigned int)i/INTSIZE] <<
                  ((unsigned int)i%INTSIZE) 
                ) < 0);
    };

    bool back() {
        return (*this)[_sizeInBits - 1];
    };

    void mySwap( MyBoolVector& vb) {
        _vector.swap(vb.getVector());
    };

    void flipBit( const int& i ) {
        _vector[i/INTSIZE] ^= (INT_MIN >> (i%INTSIZE));
    };

    void flipON( const int& i ) {
        _vector[i/INTSIZE] |= (INT_MIN >> (i%INTSIZE));
    };

    void flipOFF( const int& i )
    {
        _vector[i/INTSIZE] &= ~(INT_MIN >> (i%INTSIZE));
    };

    std::vector<int>& getVector() {
        return _vector;
    }

private:
    MyBoolVector(); //Do not call

    int _sizeInBits;
    std::vector<int> _vector;
};
