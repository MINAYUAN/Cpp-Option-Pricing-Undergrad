//  implementation
//  DoubArray.cpp
//  Created by Mina Yuan on 2018-11-11.

/*********************************************************************************/
/* Implementation DoubArray.cpp **************************************************/
/*********************************************************************************/

#include "DoubArray.h"

// Member functions **************************************************************
// Constructor
DoubArray::DoubArray(int length)
{
    assert(length > 0);
    m_array = new double[length] {};
    m_length = length;
    //m_p = p;
    
    // false = norm is not calculated/updated yet
    // true = norm is calculated/updated
    m_normflag = false;
}

// Copy constructor
DoubArray::DoubArray(const DoubArray &org_array)
{
    m_length = org_array.m_length;
    
    m_array = new double[m_length];
    
    for (int i=0; i<m_length; i++)
        m_array[i]=org_array.m_array[i];
    
   /* // Only reset m_normflag if p is changed
    if (org_array.m_p != p)
    {
        //m_p = p;
        m_normflag = false;
    }
    
    else
    {
       // m_p = org_array.m_p;
        m_normflag = true;
    }*/
}

// Destructor
DoubArray::~DoubArray()
{
    // Dynamically delete the array we allocated earlier
    delete[] m_array ;
}

// Calculate p-norm
/*double DoubArray::PNorm(int p)
{
    if ((m_normflag == false) ||)// (p!=m_p))
    {
        //m_p = p;
        double sum = 0.0;
        for (int i=0; i<m_length; i++)
        {
            sum += pow(fabs(m_array[i]),p);
        }
        
        m_norm = pow(sum, 1.0/p);
        m_normflag = true;
        return m_norm;
    }
    
    else
    {
        return m_norm;
    }
}*/

// Setter
void DoubArray::setValue(int index, double value)
{
    m_array[index] = value;
    m_normflag = false;
    // m_norm = PNorm(m_p);
}

// Operator = overload function
DoubArray& DoubArray::operator= (const DoubArray array_new)
{
    assert(m_length == array_new.m_length);
    
    for (int i=0; i<m_length; i++)
    {
        m_array[i] = array_new[i];
    }
    
    // Reset norm flag because elements are changed
    m_normflag = false;
    return *this;
}

// Operator [] overload function, non-const
double& DoubArray::operator[] (const int index)
{
    assert((index>=0) && (index < m_length));
    return m_array[index];
}

// Operator [] overload function, const
const double& DoubArray::operator[] (const int index) const
{
    assert((index>=0) && (index < m_length));
    return m_array[index];
}

// Getter
double& DoubArray::getValue(int index) const { return m_array[index]; }

// Getter for length
int DoubArray::getLength() const { return m_length; }

// Friend functions **********************************************************
// Operator - overload
DoubArray operator-(const DoubArray& array1, const DoubArray& array2)
{
    assert (array1.m_length == array2.m_length);
    DoubArray array_result(array1.m_length);//, array1.m_p);
    
    for (int i=0; i<array1.m_length; i++)
    {
        array_result[i] = array1[i] - array2[i];
    }
    
    return array_result;
}

// Functions *******************************************************************
// Get N grip points from user
int getN()
{
    int N;
    std::cout << "Enter integer grid points N, then press 'return': ";
    std::cin >> N;
    assert( N > 1 );
    return N;
}

// Implicit Euler method
void impEuler(int N, DoubArray& y)
{
    // Step size
    double h = 1.0/((double)(N)-1.0);
    y[0] = 1.0;
    
    // Declare outstream file variable
    std::ofstream write_out ("q2q3_euler_y.dat");
    
    // Euler method: iteration of y values
    for (int i=1; i<N; i++)
    {
        // y[i] derived from a given equation, see comments
        y[i] = y[i-1]/(1+h*sin(i*h));
        
        // Write y values to outstream file immediately
        write_out << y[i] << "\n";
        write_out.flush();
    }
}

// Exact solution s
void exact(int N, DoubArray& y)
{
    // Initial value of x is 0 if y is 0, derived mannually
    double x = 0.0;
    
    // Step size
    double h = 1.0/(static_cast<double>(N)-1.0);
    
    // Declare outstream file variable
    std::ofstream write_out ("q3_exact_y.dat");
    
    // Calcualte iteration of exact y values
    for (int i=0; i<N; i++)
    {
        // Exact solution, given: y = e^[-1 + cos(x)]
        y[i] = exp(-1+cos(x));
        
        // Write y values to outstream file
        write_out << y[i] << "\n";
        write_out.flush();
        
        x = x + h;
    }
}












