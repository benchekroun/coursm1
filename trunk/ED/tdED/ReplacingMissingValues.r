 
 ######## Missing Values **********
 NrNAObs <- function(x){
	NotCompleteIndex <- !complete.cases(x)
	NotCompleteVector <- x[NotCompleteIndex,]
	TotalMissingObs <- nrow(NotCompleteVector)
	TotalMissingObs
 }
 
 # which(!complete.cases(algae)) Which cases (row numbers) are incomplete?
 
 NrNARow <- function(x){
 sum(is.na(x))
 }
 
 ManyNAs <- function(x,t){
   aux <- apply(x, 1, NrNARow)/ncol(x)
   x[aux <= t,]	
 }
 

centerImputation <- function(x){ 
 
 	for (i in 1:ncol(x)) { 
	#savoir si c'ets numeric
	    if ((class(x[,i]) == "numeric")) { 
		# une case spéciale dnas la colonne qui est NA
                x[is.na(x[,i]),i] <- median(x[,i], na.rm = TRUE) 
				
	#savoir si la colonne ets un facteur
        } else if ((class(x[,i]) == "factor")) { 
                x[is.na(x[,i]),i] <- Mode(x[,i]) 
        }
		}
	x	
}		
 

Mode <- function (z) 
{ 
    xtab <- table(z) 
    xmode <- names(which(xtab == max(xtab))) 
    if (length(xmode) > 1) 
        xmode <- ">1 mode" 
    return(xmode) 
} 


# which(!complete.cases(algae))
# NrNAObs(algae)
# Temp <- ManyNAs(algae,0.20)
# cleanAlgae <- centerImputation(Temp)
