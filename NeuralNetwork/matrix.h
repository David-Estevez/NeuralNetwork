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
    Matrix(int rows, int cols);
    // Matrix( Matrix& otherMatrix);

    //-- Destructor:
   // ~Matrix();

    //-- Data interface:

    //-- Output functions:
    int getNumRows();
    int getNumCols();

    double get(int row, int col);

    std::vector<double *> getRow( int row);
    std::vector<double> getRowValues( int row);

    std::vector<double *> getCol( int col);
    std::vector<double> getColValues( int col);

    //-- Input functions
    void set(int row, int col, double value);

    void setRow( std::vector<double> row, int index);
    void setRow( std::vector<double *> row, int index);

    void setCol( std::vector<double> col, int index);
    void setCol( std::vector<double *> col, int index);

    //-- Basic matrix operations: (to be implemented when/if needed)
    Matrix& operator + (Matrix& );
    Matrix& operator - (Matrix& );
    Matrix& operator * (Matrix& );

    Matrix& operator * (double );
    Matrix& operator / (double );

    Matrix& operator += (Matrix& );
    Matrix& operator -= (Matrix& );
    Matrix& operator *= (Matrix& );

    Matrix& operator == (Matrix& );
    Matrix& operator != (Matrix& );

    Matrix& transpose();

private:
    std::vector< std::vector<double *> > matrix;

    Matrix();
};


#endif // MATRIX_H
