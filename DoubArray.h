//  header
//  DoubArray.h
//  Created by Mina Yuan on 2018-11-11.


/************************************************************************************/
/* Header DoubArray.h ***************************************************************/
/************************************************************************************/
/* This program create class DoubArray that creates a dynamic array and calculates  */
/* its p-norm of the array. The program is used to perform Euler method to solve DE.*/
/* In addition to previous functions, this program has a new impEuler function to n-*/
/* umerically derive estimated y(s), and an exact function for y(s) of real solution*/
/* In(e) main, it asks users for grid point N wanted for Euler in another function. */
/* In(f) main, it iterates N for 10,20,...,100, and test other N to find ones that  */
/* gives error (norm) less than 0.0001. Finally, (e) writes Euler y values to file, */
/* (f) writes exact y values, differences, step h, and norms to files and on screen.*/
/* (e) and (f) share same header and function implementation file; different mains. */
/************************************************************************************/

#ifndef DoubArray_h
#define DoubArray_h

#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>

class DoubArray
{
private:
    

    double m_norm;
    bool m_normflag;
    int m_p; // For p-norm

protected:
    double *m_array;
    int m_length;
    
public:
    DoubArray(int length); // constructor
    DoubArray(const DoubArray &org_array);
    ~DoubArray();
    
    double PNorm(int p); // Calcualte p-norm
    void setValue(int index, double value);
    DoubArray& operator= (const DoubArray array_new);
    double& operator[] (const int index);
    const double& operator[] (const int index) const;
    double& getValue(int index) const;
    int getLength() const;
    
    friend DoubArray operator-(const DoubArray& array1, const DoubArray& array2);
};

int getN();
void impEuler(int N, DoubArray& y);
void exact(int N, DoubArray& y);


#endif /* DoubArray_h */
