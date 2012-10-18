//-- Matrix.h
//------------------------------------------
//-- Adds simple support for matrices
//------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
private:
    int rows;
    int cols;

    std::vector<double *> matrix;

public:
    Matrix(int rows, int cols);

    //-- Data interface:
    int getRows() {return rows;}
    int getCols() {return cols;}
    void setRows(int rows) { this->rows = rows; }
    void setCols(int cols) { this->cols = cols; }

    double get(int row, int col);
    void set(int row, int col, double value);

    std::vector<double> getRow( int row);
    std::vector<double> getCol( int col);

    void setRow( std::vector<double> row, int index);
    void setCol( std::vector<double> col, int index);

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

};

#endif // MATRIX_H
