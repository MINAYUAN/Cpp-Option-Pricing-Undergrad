//  DoubMatrix.h
//  Created by Mina Yuan on 2018-11-01.

/***********************************************************************************/
/* Header DoubMatrix.h *************************************************************/
/***********************************************************************************/
/* This program create class DoubMatrix that creates a dynamic matrix (array) and  */
/* calculates multiplication between matrices, vectors, and scalars. It overloads  */
/* <<, *(5 types) and = operators to multiply and prints multiplication results to */
/* the screen. A power function is also created to make multiplication easier. When*/
/* compiling, the main file includes DoubArray to ensure successful executions. If */
/* the program runs as expected, DoubMatrix type(incl.row/col vectors) new objects */
/* after multiplication and power operation are returned and printed to the screen.*/
/***********************************************************************************/

#ifndef DoubMatrix_h
#define DoubMatrix_h

#include "DoubArray.h"

#include <iostream>
#include <cassert>
#include <cmath>

class DoubMatrix
{
protected:
    double **m_A;
    int m_row;
    int m_col;
    
public:
    // Member Functions
    DoubMatrix(int row, int col);
    DoubMatrix(const DoubMatrix &org_matrix);
    ~DoubMatrix();
    
    void setValue(int row, int col, double value);
    double& getValue(int row, int col) const ;
    int getRow() const ;
    int getCol() const ;
    // = overload
    void operator= (const DoubMatrix &matrix_new);
    // Power: (Matrix)^exponent
    DoubMatrix Pow(int exponent);
    
    // Friend Functions
    // << overload
    friend std::ostream& operator<<(std::ostream& output, const DoubMatrix &matrix);
    
    // matrix, matrix
    friend DoubMatrix operator*(const DoubMatrix &matrix1, const DoubMatrix &matrix2);
    // matrix, vector = col vector = matrix(row, col=1)
    friend DoubMatrix operator*(const DoubMatrix &matrix, const DoubArray &array);
    // vector, matrix = row vector = matrix(row=1, col)
    friend DoubMatrix operator*(const DoubArray &array, const DoubMatrix &matrix);
    // scalar, matrix = matrix, scalar; hence 1 function is sufficient
    friend DoubMatrix operator*(int integer, const DoubMatrix &matrix);
};

#endif /* DoubMatrix_h */
