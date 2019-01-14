# GBM-STOCK-MC
## Geometric Brownian Motion with Monte Carlo Method on Stock Prices

### Getting Started
The programs aims to read in stock prices data file, simulates and plots stock price n-day paths based on GBM and Monte Carlo methods, and other additional applications of financial mathematics.

### Structure
The repository's codes are consisted of 
- 2 price input files of Tesla Motors and Danaos Corp
- The GBM Simulation programs that will generate simulations of stock prices
- 2 price output files of Tesla Motors and Danos Corp

The program can reading any stock prices data files by changing the simulation matrix size of the 
number of days in the data and number of simulations wanted. Using this simulations, additional
features such option pricing, MSE, MAPE, VaR based on Black-Sholes-Merton models and statistical fundamentals are included.

#### GBM Simulation Structure
The structure of the GBM Simulation program is splitted into 3 set of implementation and header files: DoubArray, DoubMatrix, Brownian, and main. 

### Deployment
To run the program on command line, please place all data files and program codes into one file. The R code is for reading simulation data and plotting the simulated stock paths.The project's research paper is included for anyone who is interested on our findings and conclusions.
 
### Authors
Mina Yuan
Natalie To

Creator contact: minayuanml@gmail.com
Last Update: 2018/12/07
