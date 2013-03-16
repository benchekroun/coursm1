Temp_algae <- read.table("algaeClassification.txt",header=TRUE);

NrNARow <- function(x){
sum(is.na(x))
}

manyNAs <- function(x,seuil){
	cpt <- apply(x,1,NrNARow)
	percent <- cpt/ncol(x)
	return(x[percent < seuil,])
}

algae <- manyNAs(Temp_algae,0.2)

#remplace les valeurs manquantes par le mode(facteur) ou la mediane
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
	return(x)	
}		
 

Mode <- function (z) 
{ 
    xtab <- table(z) 
    xmode <- names(which(xtab == max(xtab))) 
    if (length(xmode) > 1) 
        xmode <- ">1 mode" 
    return(xmode) 
} 

cleanAlgae <- centerImputation(algae)
algae <- cleanAlgae
attach(algae)

#prior probabilite de a1 qui continet des facteurs, necessité de repasser par table
priorProb <- prop.table(table(algae$a1))

#table construit un tableau qui contient la distribution des instances en fonction d'un (ou plusieru parametre, ici nous chercherons a avoir 
#les freq réparties en fonction des seasons soit
seasonfreq <- table(season,a1)

#on obtient des nombre d'instances, on cherche des proba , on passe dans prop.table, avec un petit 2 en parametre pour dire qu'on divise par colonne (en effet on divise la frequence par le nombre d'instance, toute saison confondue
Pseason <- prop.table(seasonfreq,2)

#
t31 <- Pseason[season="winter",a1="feqLow"]
t32 <- prop.table(table(size,a1),2)[size="medium",a1="feqHigh"]
t33 <- prop.table(table(speed,a1),2)[speed="slow",a1="feqMedium"]

#fonction dnorm prend en paramettre, les observations, mais aussi la moyenne et le sd (ecrat type)
mxPHfeqLow <- algae[algae$a1=="feqLow","mxPH"]
meanmxphfeqlow <- mean(mxPHfeqLow,na.rm=T)
sdmxphfeqlow <- sd(mxPHfeqLow,na.rm=T)
t41 <- dnorm(mxPHfeqLow,meanmxphfeqlow,sdmxphfeqlow)


