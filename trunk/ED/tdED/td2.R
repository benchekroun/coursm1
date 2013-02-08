individus<-read.table("t3var.txt", header=TRUE)
ex1_1 <- mean(individus[[3]])
ex1_2 <- median(individus$poi)
v <- 1:5
ex1_3 <- individus[1:5,]
ex1_4 <- ex1_3[,-2]
index1_5 <- c(1,5,55);
ex1_5 <- individus[index1_5,]
ex1_6 <- individus[1:10,-1]
index1_7 <- seq(1,nrow(individus),by=4)
ex1_7 <- individus[index1_7,]
index1_8 <- individus[[1]]=="f" 
ex1_8 <- individus[index1_8,]
index1_9 <- individus[[3]] > 175
ex1_9 <- individus[index1_9,]
index1_10 <- index1_8 & index1_9
ex1_10 <- individus[index1_10,]
ex1_11 <- ex1_10[,-1]

ex2_1 <- aggregate(individus[,c("poi","tai")],list(sexe=individus$sexe),sum)

ex2_2 <- aggregate(individus[,c("poi","tai")],list(sexe=individus$sexe),var)

ex2_3 <- aggregate(individus[,c("poi","tai")],list(sexe=individus$sexe),median)


