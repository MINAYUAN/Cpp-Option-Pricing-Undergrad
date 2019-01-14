//
//  Brownian.cpp
//  Created by Mina Yuan on 2018-11-20.

/*********************************************************************************/
/* Implementation: Member Functons Brownian.cpp **********************************/
/*********************************************************************************/

#include "Brownian.h"
#include "DoubMatrix.h"
#include "DoubArray.h"

// Constructor
Brownian::Brownian(double mean, double sd){
    //µ
    m_mean = mean;
    //ø
    m_sd = sd;
}

// Sample mean µ, sample variance ø MLE and setter
void Brownian::mu_sd_estimator(DoubArray &log_rate)
{
    // Estimate µ
    double sum = 0;
    for (int i=1; i<log_rate.getLength(); i++){
        sum += log_rate[i];
    }
    m_mean = sum / (log_rate.getLength());
    
    // Estimate ø
    double sum_var = 0;
    for (int i=1; i<log_rate.getLength(); i++){
        sum_var += (log_rate[i] - m_mean)*(log_rate[i] - m_mean);
    }
    
    m_sd = sqrt(sum_var / (log_rate.getLength() - 1));
}

// Get m_mean
double Brownian::getMean(){return m_mean;}

// Get m_sd
double Brownian::getSD(){return m_sd;}

// Find the next price given previous price
double Brownian::NextPrice(double prev)
{
    std::random_device generator;
    std::normal_distribution<double> stdnormal (0,1);
    double stdNormal = stdnormal(generator);
    
    double next_price =0;
    // for ∆t = 1 day = 1
    next_price = prev * exp((m_mean - m_sd*m_sd/2) + m_sd*stdNormal);
    
    return next_price;
}

// A matrix to store all stimualted prices for all paths
DoubMatrix Brownian::simulate(int nday,int npath, double S0)
{
    DoubMatrix mtx(nday,npath);
    
    // first day of every path is the given S0 price
    for (int p=0; p<npath;p++){
        mtx.setValue(0,p,S0);
    }
    
    for (int p=0; p<npath; p++){
        for (int d=1; d<nday; d++){
            mtx.setValue(d, p, NextPrice(mtx.getValue(d-1,p)));
        }
    }
    return mtx;
}




