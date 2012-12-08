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
    //-- Check dimensions of vector and new matrix to be consistent:
    if ( dataVector.size() == rows*cols)
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
    else
    {
	//-- Display error message:
	std::cerr << "[Matrix] Error: vector dimensions not consistent with matrix dimensions." << std::endl;
    }
}

Matrix::~Matrix()
{
    //-- Deallocate memory if allocated:
    if (matrix != 0)
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


Matrix Matrix::operator +( Matrix& m)
{
    //-- Create new matrix
    Matrix result( this->rows, this->cols);

    if ( this->cols == m.cols && this->rows == m.rows)
    {
	for (int i = 0; i < this->cols * this->rows; i++)
	    result.matrix[i] = this->matrix[i] + m.matrix[i];
    }
    else
    {
	std::cerr << "Error [Matrix]: matrices don't have the same dimensions"
		  << std::endl;
    }

    return result;
}

Matrix Matrix::operator -(const Matrix m)
{
    //-- Create new matrix
    Matrix result( this->rows, this->cols);

    if ( this->cols == m.cols && this->rows == m.rows)
    {
	for (int i = 0; i < this->cols * this->rows; i++)
	    result.matrix[i] = this->matrix[i] - m.matrix[i];
    }
    else
    {
	std::cerr << "Error [Matrix]: matrices don't have the same dimensions"
		  << std::endl;
    }

    return result;
}

Matrix Matrix::operator *( Matrix& m)
{

    if ( this->cols == m.rows )
    {
	Matrix result( this->rows, m.cols );

	for (int i = 0; i < this->rows; i++)
	    for (int j = 0; j < m.cols; j++)
	    {
		double sum = 0;

		for (int k = 0; k < this->cols; k ++)
		    sum+= matrix[i * cols + k] * m.matrix[ k * m.cols + j];

		result.matrix[ i * m.cols + j] = sum;
	    }
	return result;
    }
    else
    {
	std::cerr << "Error [Matrix]: matrices don't have compatible dimensions"
		  << std::endl;
	return *this;
    }
}

Matrix Matrix::operator *( double n)
{
    //-- Create new matrix
    Matrix result( this->rows, this->cols);

    for (int i = 0; i < this->cols * this->rows; i++)
	this->matrix[i] *= n;

    return result;
}

Matrix Matrix::operator /( double n)
{
    //-- Create new matrix
    Matrix result( this->rows, this->cols);

    for (int i = 0; i < this->cols * this->rows; i++)
	this->matrix[i] = this->matrix[i] / n;

    return result;
}

//-- Comparison operators
//--------------------------------------------------------------------

bool Matrix::operator == (Matrix& otherMat)
{
    //-- Element-wise comparison:
    int i = 0;
    while ( i < rows*cols )
    {
	if ( *(matrix+i) != *(otherMat.matrix+i))
	    return false;
	i++;
    }
    return true;
}


bool Matrix::operator != (Matrix& otherMat)
{
    //-- If it is not equal, then it is different
    return !(*this == otherMat);
}


//-- Asignation operator
//------------------------------------------------------------------------
void Matrix::operator =(const Matrix& otherMatrix)
{
    if ( this->rows == otherMatrix.rows && this->cols == otherMatrix.cols )
    {
	for(int i = 0; i < this->rows; i++)
	    for (int j = 0; j < this->cols; j++)
		this->set( i, j, otherMatrix.get(i, j) );
    }
}


//-- Operator + = operators:
//------------------------------------------------------------------------------

Matrix& Matrix::operator += (Matrix& m)
{
    if ( this->cols == m.cols && this->rows == m.rows)
    {
	for (int i = 0; i < this->cols * this->rows; i++)
	     this->matrix[i] += m.matrix[i];
    }
    else
    {
	std::cerr << "Error [Matrix]: matrices don't have the same dimensions"
		  << std::endl;
    }

    return *this;
}

Matrix& Matrix::operator -= (Matrix& m)
{
    if ( this->cols == m.cols && this->rows == m.rows)
    {
	for (int i = 0; i < this->cols * this->rows; i++)
	     this->matrix[i] -= m.matrix[i];
    }
    else
    {
	std::cerr << "Error [Matrix]: matrices don't have the same dimensions"
		  << std::endl;
    }

    return *this;
}

Matrix& Matrix::operator *= (double n)
{
    for (int i = 0; i < this->cols * this->rows; i++)
	this->matrix[i] *= n;

    return *this;
}

Matrix& Matrix::operator /= (double n)
{
    for (int i = 0; i < this->cols * this->rows; i++)
	this->matrix[i] /= n;

    return *this;
}



//-- Other matrix operations:
//-----------------------------------------------------------------------------
Matrix Matrix::transpose()
{
    //-- Create new matrix
    Matrix result( cols, rows);

    for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	    result.set(j,i, *(matrix + i * cols + j) );

    return result;
}


std::ostream& operator << ( std::ostream& out, Matrix& matrix)
{
    for (int i = 0; i < matrix.rows ; i++)
    {
	for (int j = 0; j < matrix.cols; j++)
    	    out << matrix.get(i,j) << " ";

	out << std::endl;
    }

    return out;
}


//-- Vector
//---------------------------------------------------------------------------
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

std::ostream& operator << ( std::ostream& out, std::vector<int> data)
{
    out << "[ ";
    for ( int i = 0; i < (int) data.size(); i++)
    {
	out << data.at(i) << " ";
    }
    out << "]";

    return out;
}

