//
//  main.cpp
//  Created by Mina Yuan on 2018-11-20.

/*********************************************************************************/
/* Implementation: Functions + Main main.cpp *************************************/
/*********************************************************************************/

#include "DoubMatrix.h"
#include "DoubArray.h"
#include "Brownian.h"

#include <vector>
#include <algorithm>

// Functions ********************************************************************

// Read_data
// Read stock price data from a file
DoubArray getData(std::string const &file)
{
    std::ifstream read_file(file);
    if (!read_file.is_open())
        return 1;
    
    int number_of_rows = 0;
    while(!read_file.eof()){
        double dummy;
        read_file >> dummy;
        
        // If ".fail()" are "false" = the next row is not empty, continue
        if (!read_file.fail())
            number_of_rows++;
    }
    
    read_file.clear();
    read_file.seekg(std::ios::beg);
    
    DoubArray price_data(number_of_rows);
    for (int i = 0; i < number_of_rows; i++){
        double dummy;
        read_file >> dummy;
        price_data.setValue(i,dummy);
    }
    return price_data;
}

// Daily natrual log return array
DoubArray log_return_rate(DoubArray& price_data)
{
    DoubArray log_rate(price_data.getLength()-1);
    
    for (int i=0; i<log_rate.getLength(); i++){
        log_rate[i] = log(price_data[i+1]/price_data[i]);
    }
    
    return log_rate;
}

// Get the average of St(s) that will be used in option pricing
double AvgSt(DoubMatrix& mtx)
{
    double sum = 0.0;
    for(int p = 0; p<mtx.getCol(); p++){
        sum += mtx.getValue(mtx.getRow()-1,p);
    }
    double St = sum/mtx.getCol();
    return St;
}


// Calculate call and put option's price
double Option_Pricing(double risk_free, double strike, int maturity, bool option, double estimate_ST){
    double val_at_maturity = 0.0;
    
    //If option == 1 then this is a call option
    if (option){
        val_at_maturity = fmax(estimate_ST - strike,0);
    }
    
    //If option == 0 then this is a put option
    else{
        val_at_maturity = fmax(strike - estimate_ST,0);
    }
    //Calculate the option price using present value
    double option_price = option_price = val_at_maturity*exp(-risk_free*maturity);
    return option_price;
}


// Get MSE
// Array is the estimate array
double Mean_Squared_Error(DoubMatrix &matrix, double real_price){
    double MSE = 0.0;
    double sum = 0.0;
    
    //Loop through the columns of simulations
    for(int i = 0; i < matrix.getCol(); i++){
        sum += pow(matrix.getValue(matrix.getRow()-1,i) - real_price, 2);
    }
    
    MSE = sqrt(sum / matrix.getCol());
    return MSE;
}

// Value at Risk
double VaR (DoubMatrix &matrix){
    double plevel = 0.01;
    std::vector <double> ST(matrix.getCol());
    for (int i=0; i<matrix.getCol(); i++){
        ST.at(i) = matrix.getValue(matrix.getRow()-1,i);
    }
    std::sort(ST.begin(), ST.end());
    for (int i=0; i<ST.size(); i++){
        //  std::cout << ST.at(i) << std::endl;
    }
    int nlevel = plevel*ST.size();
    return ST[0] - ST[nlevel];
}

double MAPE (DoubMatrix &matrix, double real_price){
    double MAPE = 0.0;
    double sum = 0.0;
    
    //Loop through the columns of simulations
    for(int i = 0; i < matrix.getCol(); i++){
        sum += fabs(real_price - matrix.getValue(matrix.getRow()-1,i)) / real_price;
    }
    
    MAPE = 100 * (sum / matrix.getCol());
    return MAPE;
}

// Main ***********************************************************************

int main()
{
    // Using DoubArray copy constructor to:
    // Declare and assign a DoubArray object of all Tesla price data
    DoubArray price_data(getData("Tesla_5yr_NODATE.prn"));
    
    std::ofstream write_tesla("Tesla_GBM2.dat");
    
    // Declare and assign a DoubArray object of all daily log rates
    DoubArray log_rate(log_return_rate(price_data));
    
    // Declare Brownian object
    Brownian tesla;
    tesla.mu_sd_estimator(log_rate);
    
    // Declare DoubMatrix object to store all simulations (day = 252, simlations = 500)
    DoubMatrix mtx_tesla_simulate(252,500);
    
    // Simulate 252 days, 10 path, starting price, S0 = $315.4 (price 1 years ago)
    // Assign the result to the matrix
    mtx_tesla_simulate = tesla.simulate(252,500,315.4);
    
    // Print out the simulation matrix
    write_tesla << mtx_tesla_simulate;
    
    // Average of 500 paths' end prices at day 252nd
    double avg = AvgSt(mtx_tesla_simulate);
    std::cout << "The average simulated ST: "<< avg << std::endl;
    
    // Estimate Call Price: interest rate, strike, maturity, bool:1-call 0-put, avg)
    double estimate_option_price = Option_Pricing(0.0144, 300, 252, 1, avg);
    std::cout << "Call Price: " << estimate_option_price << std::endl;
    
    // Reset to store put's price
    estimate_option_price = 0.0;
    
    // Estimate Put Price
    // interest rate = 1.44% for 1-3 year Canada Gov Bond on 2017 Nov 13
    estimate_option_price = Option_Pricing(0.0144, 350, 252, 0, avg);
    std::cout << "Put Price: " << estimate_option_price << std::endl;
    
    // MSE of GBM
    double MSE = Mean_Squared_Error(mtx_tesla_simulate, price_data[1259]);
    std::cout << "Mean Squared Error: " << MSE << std::endl;
    
    // VaR base on Monte Carlo Simualtion of Stock
    std::cout << "VaR at 1% probability: $" << VaR(mtx_tesla_simulate) << std::endl;
    
    // MAPE
    double Mean_Absolute_Percentage_Error = MAPE(mtx_tesla_simulate, price_data[1259]);
    std::cout << "Mean Absolute Percentage Error: " << Mean_Absolute_Percentage_Error << std::endl;
   
    //--Danos Stock, a small market capitalization stock -----------
    std::cout << std::endl;
    // Using DoubArray copy constructor to:
    // Declare and assign a DoubArray object of all Tesla price data
    DoubArray Danaos_data(getData("Danaos.prn"));

    std::ofstream write_danaos("D.dat");
    
    // Declare and assign a DoubArray object of all daily log rates
    DoubArray log_rate2(log_return_rate(Danaos_data));
    
    // Declare Brownian object
    Brownian Danaos;
    Danaos.mu_sd_estimator(log_rate2);
    
    // Declare DoubMatrix object to store all simulations (day = 252, simlations = 500)
    DoubMatrix mtx_Danaos_simulate(252,500);
    
    // Simulate 252 days, 10 path, starting price, S0 = $315.4 (price 1 years ago)
    // Assign the result to the matrix
    mtx_Danaos_simulate = Danaos.simulate(252,500,1.55);
    
    // Print out the simulation matrix
    write_danaos << mtx_Danaos_simulate;
    
    // Average of 500 paths' end prices at day 252nd
    avg = AvgSt(mtx_Danaos_simulate);
    std::cout << "The average simulated ST: "<< avg << std::endl;
    
    // MSE of GBM
    double MSE2 = Mean_Squared_Error(mtx_Danaos_simulate, price_data[1257]);
    std::cout << "Mean Squared Error of Danaos: " << MSE2 << std::endl;

    // MAPE
    double Mean_Absolute_Percentage_Error2 = MAPE(mtx_Danaos_simulate, price_data[1257]);
    std::cout << "Mean Absolute Percentage Error of Danaos: " << Mean_Absolute_Percentage_Error2 << std::endl;
    
    return 0;
}

