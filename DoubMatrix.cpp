//  DoubMatrix.cpp
//  Created by Mina Yuan on 2018-11-01.

/*********************************************************************************/
/* Implementation: Functions DoubMatrix.cpp **************************************/
/*********************************************************************************/

#include "DoubMatrix.h"

// Member functions ****************************************************
// constructor
DoubMatrix::DoubMatrix(int row, int col)
{
    assert((row > 0) && (col>0));
    
    m_row = row;
    m_col = col;
    
    // Declare new matrix (2-d array)
    m_A = new double* [m_row];
    m_A[0] = new double[m_row*m_col];
    for (int i=1; i<m_row; i++)
    {
        m_A[i] = m_A[i-1] + m_col;
    }
}

// copy constructor
DoubMatrix::DoubMatrix(const DoubMatrix &org_matrix)
{
    m_row = org_matrix.m_row;
    m_col = org_matrix.m_col;
    
    // Declare a new matrix
    m_A = new double* [m_row];
    m_A[0] = new double[m_row*m_col];
    
    for (int i=1; i<m_row; i++)
    {
        m_A[i] = m_A[i-1] + m_col;
    }
    
    // Copy values to the new matrix
    for (int i=0; i<m_row; i++)
    {
        for (int j=0; j<m_col; j++)
        {
            m_A[i][j] = org_matrix.m_A[i][j];
        }
    }
}

// Destructor
DoubMatrix::~DoubMatrix()
{
    // Dynamically delete the array we allocated earlier
    delete[] m_A[0];
    delete[] m_A;
}

// Set element value
void DoubMatrix::setValue(int row, int col, double value) { m_A[row][col] = value; }

// Get element value
double& DoubMatrix::getValue(int row, int col) const { return m_A[row][col]; }

// Get total row num
int DoubMatrix::getRow() const { return m_row; }

// Get total col num
int DoubMatrix::getCol() const { return m_col; }

// Operator = overload function
void DoubMatrix::operator= (const DoubMatrix &matrix_new)
{
    for (int i=0; i<matrix_new.getRow(); i++)
    {
        for (int j=0; j<matrix_new.getCol(); j++)
        {
            m_A[i][j] = matrix_new.getValue(i,j);
        }
    }
}

// Power calculation (matrix)^ exponent
DoubMatrix DoubMatrix::Pow(int exponent)
{
    DoubMatrix matrix(*this);
    assert(matrix.m_row == matrix.m_col);
    
    DoubMatrix matrix_temp(matrix.m_row,matrix.m_col);
    matrix_temp = matrix;
    
    for (int i=0; i<exponent-1; i++)
    {
        matrix = matrix_temp * matrix;
    }
    return matrix;
}

// Friend functions ****************************************************

// Friend operator << overload function
std::ostream& operator<<(std::ostream& output, const DoubMatrix &matrix)
{
    // Print out matrix in (row x col) format
    for (int i=0; i<matrix.m_row; i++)
    {
        for (int j=0; j<matrix.m_col; j++)
        {
            output << matrix.m_A[i][j] << "\t";
        }
        output << "\n";
    }
    return output;
}

// * Overload: matrix, matrix
DoubMatrix operator*(const DoubMatrix &matrix1, const DoubMatrix &matrix2)
{
    assert(matrix1.getCol() == matrix2.getRow());
    
    DoubMatrix matrix_result(matrix1.m_row, matrix2.m_col);
    
    for (int i=0; i<matrix1.getRow(); i++)
    {
        for (int j=0; j<matrix2.getCol(); j++)
        {
            double sum = 0.0;
            
            for (int k=0; k<matrix1.getCol(); k++)
            {
                sum += matrix1.getValue(i,k) * matrix2.getValue(k,j);
            }
            matrix_result.setValue(i,j,sum);
        }
    }
    return matrix_result;
}

// * Overload: matrix, col vector => col vector
DoubMatrix operator*(const DoubMatrix &matrix, const DoubArray &array)
{
    assert(matrix.m_col == array.getLength());
    
    DoubMatrix matrix_result(matrix.m_row, 1);
    
    for (int i=0; i<matrix.m_row; i++)
    {
        double sum = 0.0;
        for (int j=0; j<array.getLength(); j++)
        {
            sum += matrix.getValue(i,j) * array.getValue(j);
        }
        matrix_result.setValue(i,0,sum);
        
    }
    return matrix_result;
}

// * Overload: row vector, matrix => row vector
DoubMatrix operator*(const DoubArray &array, const DoubMatrix &matrix)
{
    assert(matrix.m_row == array.getLength());
    
    DoubMatrix matrix_result(1, matrix.m_col);
    
    for (int i=0; i<matrix.m_col; i++)
    {
        double sum = 0.0;
        for (int j=0; j<array.getLength(); j++)
        {
            sum += array.getValue(j) * matrix.getValue(j,i);
        }
        matrix_result.setValue(0,i,sum);
    }
    return matrix_result;
}

// * Overload: scalar, matrix = matrix, scalar
DoubMatrix operator*(int scalar, const DoubMatrix &matrix)
{
    DoubMatrix matrix_result(matrix.m_row, matrix.m_col);
    
    for (int i=0; i<matrix.m_row; i++)
    {
        for (int j=0; j<matrix.m_col; j++)
        {
            matrix_result.setValue( i, j, scalar * matrix.getValue(i,j) );
        }
    }
    return matrix_result;
}


































