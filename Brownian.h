//
//  Brownian.h
//  Created by Mina Yuan on 2018-11-20.

/***********************************************************************************/
/* Header Brownian.h ***************************************************************/
/***********************************************************************************/
/* This program create class Brownian that contains functions to estimate drift and*/
/* volatility, and use these member variables to simulate stock prices using GBM.  */
/* The simulation function will generate a doubMatrix instance that store all paths*/
/***********************************************************************************/

#ifndef Brownian_h
#define Brownian_h

#include "DoubArray.h"
#include "DoubMatrix.h"

#include <iostream>
#include <fstream>
#include <random>

class Brownian
{
private:
    double m_mean;
    double m_sd;

public:
    Brownian(double mean=0, double sd=1);
    void mu_sd_estimator(DoubArray &log_rate);
    double getMean();
    double getSD();
    // Find the next price given previous price
    double NextPrice(double prev);
    // A matrix to store all stimualted prices for all paths
    DoubMatrix simulate(int nday,int npath, double S0);
};

#endif /* Brownian_h */

