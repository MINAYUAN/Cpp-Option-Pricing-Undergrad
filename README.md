# GBM-STOCK-MC
## Geometric Brownian Motion with Monte Carlo Method on Stock Prices

The repository's codes are consisted of 2 historical stock price files "input" of Tesla Mortors and Danaos Corp, and the GBM Simulation programs that will generate simulations of stock prices.

The program can reading any stock prices data files by changing the simulation matrix size of the 
number of days in the data and number of simulations wanted. Using this simulations, additional
features such option pricing, MSE, MAPE, VaR based on Black-Sholes-Merton models and statistical fundamentals are included.

The structure of the program is splitted into 3 set of implementation and header files: DoubArray, DoubMatrix, Brownian, and main. 

The program outputs simulated prices of Tesla and Danaos in file names: Tesla_GBM2.dat, D.dat; the name can be modified inside the program. 

To run the program on command line, please place all data files and program codes into one file. 

The R code is for reading simulation data and plotting the simulated stock paths.

The project's research paper is included for anyone who is interested on our findings and conclusions.

Creator contact: minayuanml@gmail.com
Last Update: 2018/12/07
