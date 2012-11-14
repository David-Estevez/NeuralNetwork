#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    //-- Store dimensions
    this->rows = rows;
    this->cols = cols;

    //-- Create storage for the matrix
    this->matrix = new double[rows*cols];

    //-- Initialize the matrix to 0:
    for(int i = 0; i < rows*cols; i++)
	*(matrix+i) = 0;
}

Matrix::Matrix(const Matrix& otherMatrix)
{
    //-- Copy dimensions
    this->rows = otherMatrix.rows;
    this->cols = otherMatrix.cols;

    //-- Create storage for the matrix
    this->matrix = new double[rows * cols];

    //-- Copy the values of the matrix
    for(int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	    this->set( i, j, otherMatrix.get(i, j) );
}

Matrix::Matrix(const std::vector<double> dataVector, const int rows, const int cols)
{
    //--Store dimensions:
    this->rows = rows;
    this->cols = cols;

    //-- Create storage for matrix
    this->matrix = new double[ dataVector.size()];

    //-- Copy elements:
    for (int i = 0; i < (int) dataVector.size(); i++)
	*(matrix+i) = dataVector.at(i);
}

Matrix::~Matrix()
{
    delete [] matrix;
}


int Matrix::getNumRows() const
{
    return rows;
}

int Matrix::getNumCols() const
{
    return cols;
}


double Matrix::get(const int row, const int col) const
{
    if ( (row >= 0 && row < rows) && (col >= 0 && col < cols ) )
    {
	 return *(matrix + row*cols + col);
    }
    else
    {
	std::cerr << "Error [Matrix]: index not valid." << std::endl;
	return 0;
    }
}

void Matrix::set(int row, int col, const double value)
{
    if ((row >= 0 && row < rows) && (col >= 0 && col < cols ) )
	*(matrix + row*cols + col) = value;
    else
	std::cerr << "Error [Matrix]: index not valid." << std::endl;
}


std::vector<double *> Matrix::getRow( const int row) const
{
    //-- Returns a given row

    //-- Create an auxiliar vector:
    std::vector<double *> aux;

    if (row >= 0 && row < rows )
    {
	//-- Add elements from this row:
	for (int i = 0; i < cols; i++)
	    aux.push_back( matrix + row * cols + i);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist." << std::endl;

    return aux;
}

std::vector<double> Matrix::getRowValues( const int row) const
{
    //-- Returns a given column

    //-- Create an auxiliar vector
    std::vector<double> aux;

    if (row >= 0 && row < rows )
    {
	//-- Add elements from this row:
	for (int i = 0; i < cols; i++)
	    aux.push_back( *(matrix + row * cols + i) );
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist." << std::endl;

    return aux;
}


std::vector<double *> Matrix::getCol(const int col) const
{
    //-- Create auxiliar vector
    std::vector<double *> aux;

    //-- Returns a given column
    if (col >= 0 && col < cols )
    {
	for (int i = 0; i < rows ; i++)
	   aux.push_back( matrix + i * cols + col );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist." << std::endl;

    return aux;
}

std::vector<double> Matrix::getColValues(const int col) const
{
    //-- Create auxiliar vector
    std::vector<double> aux;

    //-- Returns a given column
    if (col >= 0 && col < cols )
    {
	for (int i = 0; i < rows ; i++)
	   aux.push_back( *(matrix + i * cols + col) );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist." << std::endl;

    return aux;
}

std::vector<double> Matrix::unroll()
{
    //-- Create a vector
    std::vector<double> unrolledVector;

    for (int i = 0; i < rows * cols; i++)
        unrolledVector.push_back( *(matrix+i) );

    return unrolledVector;
}

void Matrix::setRow(const std::vector<double> row, const int index)
{
    //-- Set the values of a row
    if (index >= 0 && index < rows )
    {
	for (int i = 0; i < cols ; i++)
	    *(matrix + index * cols + i)  = row.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist." << std::endl;
}

void Matrix::setCol(const std::vector<double> col, const int index)
{
    //-- Set the values of a column
    if (index >= 0 && index < cols )
    {
	for (int i = 0; i < rows ; i++)
	    *(matrix + i * cols + index) = col.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist." << std::endl;
}

void Matrix::operator =(const Matrix& otherMatrix)
{
    if ( this->rows == otherMatrix.rows && this->cols == otherMatrix.cols )
    {
	for(int i = 0; i < this->rows; i++)
	    for (int j = 0; j < this->cols; j++)
		this->set( i, j, otherMatrix.get(i, j) );
    }
}

std::ostream& operator << ( std::ostream& out, Matrix& matrix)
{
    for (int i = 0; i < matrix.rows ; i++)
    {
	out << "| ";
	for (int j = 0; j < matrix.cols; j++)
    	    out << matrix.get(i,j) << " ";
	out << "|" << std::endl;
    }

    return out;
}

std::ostream& operator << ( std::ostream& out, std::vector<double> data)
{
    out << "[ ";
    for ( int i = 0; i < (int) data.size(); i++)
    {
	out << data.at(i) << " ";
    }
    out << "]";

    return out;
}
