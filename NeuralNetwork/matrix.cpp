#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
	//-- Create a row:
	double n[cols];

	//-- Initialize to 0:
	for (int j = 0; j < rows; j++)
	    n[j] = 0;

	matrix.push_back( n );
    }
}

double Matrix::get(int row, int col)
{
    if ( (row >= 0 && row < this->rows) && (col >= 0 && col < this->cols))
	return *(matrix[row]+col);
    else
	return 0;
}

void Matrix::set(int row, int col, double value)
{
    if ( (row >= 0 && row < this->rows) && (col >= 0 && col < this->cols))
	*(matrix[row]+col) = value;
}


std::vector<double> Matrix::getRow( int row)
{
    std::vector<double> outRow;

    //-- Returns a given row
    if (row >= 0 && row < this->rows)
    {
	for (int i = 0; i < this->cols; i++)
	    outRow.push_back( *(matrix[row]+i) );
    }

    return outRow;
}

std::vector<double> Matrix::getCol( int col)
{
    std::vector<double> outCol;

    //-- Returns a given column
    if (col >= 0 && col < this->cols)
    {
	for (int i = 0; i < this->rows; i++)
	    outCol.push_back( *( matrix[i]+col) );
    }

    return outCol;
}

void Matrix::setRow( std::vector<double> row, int index)
{
    //-- Set a row
    if (index >= 0 && index < this->rows)
    {

    }
}

void Matrix::setCol( std::vector<double> col, int index)
{
    //-- Set a column
    if (index >= 0 && index < this->cols)
    {

    }
}
