//-- Matrix.h
//------------------------------------------
//-- Adds simple support for matrices
//------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{

public:
    //-- Constructors
    Matrix(const int rows, const int cols);
    Matrix(const std::vector<double> dataVector,const int rows, const int cols);
    Matrix(const Matrix& otherMatrix);

    //-- Destructor:
    ~Matrix();

    //-- Data interface:

    //-- Output functions:
    int getNumRows() const;
    int getNumCols() const;

    double get(const int row,const int col) const;

    std::vector<double *> getRow(const int row) const;
    std::vector<double> getRowValues(const int row) const;

    std::vector<double *> getCol(const int col) const;
    std::vector<double> getColValues(const int col) const;

    std::vector<double> unroll();

    //-- Input functions
    void set(const int row,const int col,const double value);

    void setRow(const std::vector<double> row, const int index);
    void setCol(const std::vector<double> col, const int index);

    //-- Basic matrix operations: (to be implemented when/if needed)
    Matrix& operator + (Matrix& );
    Matrix& operator - (Matrix& );
    Matrix& operator * (Matrix& );

    Matrix& operator * (double );
    Matrix& operator / (double );

    Matrix& operator += (Matrix& );
    Matrix& operator -= (Matrix& );
    Matrix& operator *= (Matrix& );

    bool operator == (Matrix& otherMat)
    {
	int i = 0;
	while ( i < rows*cols )
	    if ( *(matrix+i) != *(otherMat.matrix+i))
		return false;
	return true;
    }

    Matrix& operator != (Matrix& );

    void operator = (const Matrix&);

    Matrix& transpose();

    friend std::ostream& operator << ( std::ostream& out, Matrix& matrix);

private:
    int cols, rows;

    double *matrix;

    Matrix();
};

std::ostream& operator << (std::ostream&, std::vector<double>);

#endif // MATRIX_H
