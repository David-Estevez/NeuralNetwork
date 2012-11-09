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
    ~Matrix();

    //-- Data interface:

    //-- Output functions:
    int getNumRows() const;
    int getNumCols() const;

    double& get(const int row,const int col) const;

    std::vector<double *> getRow(const int row) const;
    std::vector<double> getRowValues(const int row) const;

    std::vector<double *> getCol(const int col) const;
    std::vector<double> getColValues(const int col) const;

    //-- Input functions
    void set(const int row,const int col,const double value);

    void setRow(const std::vector<double> row, const int index);
    void setRow(const std::vector<double *> row,const  int index);

    void setCol(const std::vector<double> col, const int index);
    void setCol(const std::vector<double *> col, const int index);

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

    Matrix& operator = (Matrix&);
    Matrix& transpose();

    friend std::ostream& operator << ( std::ostream& out, Matrix& matrix);

private:
    int cols, rows;

    double *matrix;

    Matrix();
};


#endif // MATRIX_H
