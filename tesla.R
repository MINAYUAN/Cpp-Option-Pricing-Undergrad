Tesla_GBM <- read.delim("~/Desktop/3611/Project/Tesla_GBM2.dat", header=FALSE)
Tesla_GBM[501] <- NULL

plot.ts(Tesla_GBM,plot.type = "s",col=rainbow(500),
        main = "Tesla Motors Stock Price: Geometric Brownian Motion Simulation", 
        ylab = "Stock Price",
        xlab = "Days (1 Year from 11-13-2017)")


year<-c(seq(0,252,by = 20),252)
legend("topright",lty =1, cex = 0.5, legend=year,col=rainbow(500),horiz = TRUE)

