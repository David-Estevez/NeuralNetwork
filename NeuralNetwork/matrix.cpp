#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;

    this->matrix = new double[rows*cols];

}

//Matrix::Matrix( Matrix& otherMatrix) {}

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


double& Matrix::get(const int row, const int col) const
{
    if ( (row >= 0 && row < rows) && (col >= 0 && col < cols ) )
    {
	 return (matrix + row*cols + col);
    }
    else
    {
	std::cerr << "Error [Matrix]: index not valid.";
	return 0;
    }
}

void Matrix::set(int row, int col, const double value)
{
    if ((row >= 0 && row < rows) && (col >= 0 && col < cols ) )
	*(matrix + row*cols + col) = value;
    else
	std::cerr << "Error [Matrix]: index not valid.";
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
	std::cerr << "Error [Matrix]: specified row does not exist.";

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
	std::cerr << "Error [Matrix]: specified row does not exist.";

    return aux;
}


std::vector<double *> Matrix::getCol(const int col) const
{
    //-- Create auxiliar vector
    std::vector<double *> aux;

    //-- Returns a given column
    if (col >= 0 && col < cols )
    {
	for (int i = 0; i < matrix.size() ; i++)
	   aux.push_back( matrix + i * cols + col );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";

    return aux;
}

    std::vector<double> Matrix::getColValues(const int col) const
{
    //-- Create auxiliar vector
    std::vector<double> aux;

    //-- Returns a given column
    if (col >= 0 && col < cols )
    {
	for (int i = 0; i < matrix.size() ; i++)
	   aux.push_back( *(matrix + i * cols + col) );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";

    return aux;
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
	std::cerr << "Error [Matrix]: specified row does not exist.";
}

void Matrix::setRow(const std::vector<double *> row, const int index)
{
    //-- Set a row
    if (index >= 0 && index < rows )
    {
	for (int i = 0; i < cols ; i++)
	    (matrix + index * cols + i)  = row.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist.";
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
	std::cerr << "Error [Matrix]: specified column does not exist.";
}

void Matrix::setCol(const std::vector<double *> col,const int index)
{
    //-- Set a column
    if (index >= 0 && index < cols )
    {
	for (int i = 0; i < rows ; i++)
	    (matrix + i * cols + index) = col.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";
}

std::ostream& operator << ( std::ostream& out, Matrix& matrix)
{
    for (int i = 0; i < rows ; i++)
    {
	out << "| ";
	for (int j = 0; j < cols; j++)
    	    out << matrix.get(i,j) << " ";
	out << "|" << std::endl;
    }

    return out;
}

