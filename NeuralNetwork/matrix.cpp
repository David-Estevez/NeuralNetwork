#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
	std::vector<double *> aux(cols);

	for( int j = 0; j < cols; j++)
	     {
		 aux.at(j) = new double;
		*aux.at(j) = 0;
	     }

	matrix.push_back( aux );
    }
}

//Matrix::Matrix( Matrix& otherMatrix) {}

/*Matrix::~Matrix()
{
    for (int i = 0; i < matrix.size(); i++)
	for (int j = 0; j < matrix.at(i).size(); j++)
	    delete matrix.at(i).at(j);
}*/


int Matrix::getNumRows()
{
    return matrix.size();
}

int Matrix::getNumCols()
{
    return matrix.at(0).size();
}


double Matrix::get(int row, int col)
{
    if ( (row >= 0 && row < matrix.size()) && (col >= 0 && col < matrix.at(row).size() ) )
	return *matrix.at(row).at(col);
    else
    {
	std::cerr << "Error [Matrix]: index not valid.";
	return 0;
    }
}

void Matrix::set(int row, int col, double value)
{
    if ( (row >= 0 && row < matrix.size()) && (col >= 0 && col < matrix.at(row).size() ) )
	*matrix.at(row).at(col) = value;
    else
	std::cerr << "Error [Matrix]: index not valid.";
}


std::vector<double *> Matrix::getRow( int row)
{
    //-- Returns a given row

    if (row >= 0 && row < matrix.size() )
    {
	return matrix.at(row);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist.";

}

std::vector<double> Matrix::getRowValues( int row)
{
    std::vector<double> outRow;

    //-- Returns a given column
    if (row >= 0 && row < matrix.size() )
    {
	for (int i = 0; i < matrix.at(0).size() ; i++)
	    outRow.push_back( *matrix.at(row).at(i)  );
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist.";

    return outRow;
}


std::vector<double *> Matrix::getCol( int col)
{
    std::vector<double *> outCol;

    //-- Returns a given column
    if (col >= 0 && col < matrix.at(0).size() )
    {
	for (int i = 0; i < matrix.size() ; i++)
	    outCol.push_back( matrix.at(i).at(col)  );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";

    return outCol;
}

std::vector<double> Matrix::getColValues( int col)
{
    std::vector<double> outCol;

    //-- Returns a given column
    if (col >= 0 && col < matrix.at(0).size() )
    {
	for (int i = 0; i < matrix.size() ; i++)
	    outCol.push_back( *matrix.at(i).at(col)  );
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";

    return outCol;
}

void Matrix::setRow( std::vector<double> row, int index)
{
    //-- Set the values of a row
    if (index >= 0 && index < matrix.size() )
    {
	for (int i = 0; i < matrix.at(0).size() ; i++)
	    *matrix.at(index).at(i) = row.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist.";
}

void Matrix::setRow( std::vector<double *> row, int index)
{
    //-- Set a row
    if (index >= 0 && index < matrix.size() )
    {
	for (int i = 0; i < matrix.at(0).size() ; i++)
	    matrix.at(index).at(i) = row.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified row does not exist.";
}

void Matrix::setCol( std::vector<double> col, int index)
{
    //-- Set the values of a column
    if (index >= 0 && index < matrix.at(0).size() )
    {
	for (int i = 0; i < matrix.size() ; i++)
	    *matrix.at(i).at(index) = col.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";
}

void Matrix::setCol( std::vector<double *> col, int index)
{
    //-- Set a column
    if (index >= 0 && index < matrix.at(0).size() )
    {
	for (int i = 0; i < matrix.size() ; i++)
	    matrix.at(i).at(index) = col.at(i);
    }
    else
	std::cerr << "Error [Matrix]: specified column does not exist.";
}

std::ostream& operator << ( std::ostream& out, Matrix& matrix)
{
    for (int i = 0; i < (int)matrix.matrix.size() ; i++)
    {
	out << "| ";
	for (int j = 0; j < (int)matrix.matrix.at(i).size(); j++)
    	    out << matrix.get(i,j) << " ";
	out << "|" << std::endl;
    }

    return out;
}

