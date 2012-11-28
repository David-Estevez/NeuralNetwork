/*! \file matrix.h
 *  \brief Matrix basic support.
 *
 * Provides basic matrix functionality, such as element, row and column values placement/return.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 15th, 2012
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

/*! \class Matrix
 *  \brief Bidimensional matrix of doubles.
 *
 * It has functions for single value, row or column modification and return.
 *
 * \todo Add basic matrix arithmetics if needed.
 */

class Matrix
{

public:

    //-- Constructors
    //-----------------------------------------------------------------------------

    /*!
     * \brief Creates a rows x cols matrix of doubles.
     *
     *	\param rows Number of rows.
     *	\param cols Number of columns.
     *
     */
    Matrix(const int rows, const int cols);

    /*!
     * \brief Creates a rows x cols matrix from a vector with the data.
     *
     * \param dataVector Vector containing the numbers of the matrix.
     * \param rows Number of rows.
     * \param cols Number of columns.
     *
     */
    Matrix(const std::vector<double> dataVector,const int rows, const int cols);

    /*!
     * \brief Creates a matrix from other matrix.
     *
     * \param otherMatrix The matrix we are copying.
     *
     */
    Matrix(const Matrix& otherMatrix);

    /*!
     * \brief Default destructor
     */
    ~Matrix();

    //-- Data interface:
    //------------------------------------------------------------------------------

    //-- Output functions:

    /*!
     * \brief Returns the number of rows of the matrix.
     *
     * \return Number of rows of the matrix
     */
    int getNumRows() const;

    /*!
     * \brief Returns the number of columns of the matrix.
     *
     * \return Number of columns of the matrix
     */
    int getNumCols() const;

    /*!
     * \brief Returns a concrete value from the matrix.
     *
     * \param row Row selection.
     * \param col Column selection.
     *
     * \return Value of the element at position (row , col)
     */
    double get(const int row,const int col) const;

     /*!
      * \brief Returns a vector of pointers to each element of a row of the matrix.
      *
      * \param row Row selection.
      * \return Vector containing pointers to each element of the selected row.
      */
    std::vector<double *> getRow(const int row) const;

     /*!
      * \brief Returns the values from a row of the matrix.
      *
      * \param row Row selection.
      * \return Vector containing the values from a row of the matrix.
      */
    std::vector<double> getRowValues(const int row) const;

     /*!
      * \brief Returns a vector of pointers to each element of a column of the matrix.
      *
      * \param col Column selection.
      * \return Vector containing pointers to each element of the selected column.
      */
    std::vector<double *> getCol(const int col) const;

     /*!
      * \brief Returns the values from a column of the matrix.
      *
      * \param col Column selection.
      * \return Vector containing the values from a column of the matrix.
      */
    std::vector<double> getColValues(const int col) const;

     /*!
      * \brief Returns a one-dimensional vector containing all the values from the matrix.
      *
      * Concatenates columns one after the other to form a one-dimensional vector.
      *
      * \return Vector containing all the values of matrix.
      */
    std::vector<double> unroll();


    //-- Input functions
    //----------------------------------------------------------------------------------------

     /*!
      * \brief Set manually one value of the matrix.
      *
      * \param row Row selector.
      * \param col Column selector.
      * \param value Value to store.
      */
    void set(const int row, const int col, const double value);


     /*!
      * \brief Change all the values of a row with the values of a vector.
      *
      * \warning Dimensions must be compatible.
      *
      * \param row Values for the new row.
      * \param index Index of the row to change values.
      */
    void setRow(const std::vector<double> row, const int index);

     /*!
      * \brief Change all the values of a column with the values of a vector.
      *
      * \warning Dimensions must be compatible.
      *
      * \param col Values for the new column.
      * \param index Index of the column to change values.
      */
    void setCol(const std::vector<double> col, const int index);


    //-- Basic matrix operations: (to be implemented when/if needed)
    //---------------------------------------------------------------------------------------
    Matrix& operator + (Matrix& );
    Matrix& operator - (Matrix& );
    Matrix& operator * (Matrix& );

    Matrix& operator * (double );
    Matrix& operator / (double );

    Matrix& operator += (Matrix& );
    Matrix& operator -= (Matrix& );
    Matrix& operator *= (Matrix& );


    /*!
     * \brief Checks if two matrices are equal, element-wise.
     *
     *	Two matrices are equal if all their corresponding elements are equal.
     *
     * \param otherMat Matrix we are comparing with this matrix.
     * \return True if both are equal, false otherwise.
     *
     */
    bool operator == (Matrix& otherMat);

    /*!
     * \brief Checks if two matrices are different, element-wise.
     *
     *	Two matrices are different if any of their corresponing elements are different.
     *
     * \param otherMat Matrix we are comparing with this matrix.
     * \return True if both are different, false otherwise.
     *
     */
    bool operator != (Matrix& otherMat);

    /*!
     * \brief Asign to this matrix the value of other matrix.
     *
     * \param otherMatrix Matrix from which values are assigned to this matrix.
     */
    void operator = (const Matrix& otherMatrix);


    Matrix& transpose();

    /*!
     * \brief Shows a matrix in an output stream.
     *
     * \param out Output stream to which we are passing the data that we want to
     * represent.
     * \param matrix Matrix which contains the data passed to the output stream.
     */
    friend std::ostream& operator << ( std::ostream& out, Matrix& matrix);

private:
    /*! \var int cols
     * \brief Stores the number of columns in matrix
     */

    /*! \var int rows
      * \brief Stores the number of rows in matrix
      */

    int cols, rows;

    /*! \var double *matrix
     *	\brief points to an array of doubles storing the values of the matrix elements.
     */
    double *matrix;

    /*! \brief Default constructor
     */
    Matrix();
};

/*!
 * \brief Shows a vector in an output stream.
 *
 * \param out Output stream to which we are passing the data we want to represent.
 * \param data Vector containing the data passed to the output stream.
 */
std::ostream& operator << (std::ostream& out, std::vector<double> data);

#endif // MATRIX_H
