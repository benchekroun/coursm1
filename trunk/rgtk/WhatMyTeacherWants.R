# Required: e1071 and ineq
WhatMyTeacherWants <- function(x){
	res <- c(
		round(mean(x, na.rm=TRUE), digits=2),
		round(median(x, na.rm=TRUE), digits=2),
		round(min(x, na.rm=TRUE), digits=2),
		max(x, na.rm=TRUE),
		max(x, na.rm=TRUE)-min(x, na.rm=TRUE),
		round(sd(x, na.rm=TRUE)),
		round(kurtosis(x, type=1,na.rm=TRUE), digits=2),
		round(skewness(x, type=1, na.rm=TRUE), digits=2),
		round(mean(x)/sd(x), digits=2),
		round(quantile(x,probs=c(0.25,0.75), na.rm=TRUE), digits=2),
		round(ineq(x),2))
	names(res) <- c("mean","median","min","max","range","sd","kurtosis","skewness","variation","1st quantile","3rd quantile","gini")
	res
}