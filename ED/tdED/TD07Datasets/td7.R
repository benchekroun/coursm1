#on lit les données
ozoneTrain <- read.table("ozoneTrain.txt", header=TRUE)
#un fait un summary mais avec juste les données qui nou sintéressent
summary(ozoneTrain[,c("maxO3","T12")])

#mettre face a face les deux valuer,s et si 'lon veux considérer toutes les valeurs, on met un . au lieu de T12
plot(maxO3~T12,data=ozoneTrain,pch=15,cex=0.5,col="blue")
#dans ce plot, on constate que plus il fait chaud, plus la concentration d'Ozone est haute, 
#la fonction lm implémente la régréssion simple , avec la méthodes des moindres carrés
reg.simple <- lm(maxO3 ~ T12, data = ozoneTrain)
#on en affiche le summary
resSum <- summary(reg.simple)
#dnas ce summary , il y a une proba a la fin, si cette proba est haute, alors , il existe des varaibles utilisée dnas la régression qui ne sont pas pertinente, on peux donc les retirer, il faut tout de fois découvrir nous meme les quelles sont pas pertinentes.

#on ajoute au plot une ligne rouge qui correspond a notre régression
abline(reg.simple,col="red")

#on étudie(rstudent) les résidus de la régression
#on essaye de ramener les residus à la meme échelle , car les erreurs ne se comportent pas pareil en extrémité de courbe qu'au centre,
#ici on regarde la tendnace des erreurs, dnas notre cas c'es taléatoire, ce qui est une bonne choses
#on regarde aussi si la plupart des velurs sont dnas notre intervalle de confiance, 
#c'est a dire si nous prédictions peuvent être utilisées car elle ne se trompent pas trop.
#si jamais la répartitions des résidus ne semble pas random, alors , il est possible que le modèle ne soit pas linéaire, pareil si les valeurs sont toutes en dehors de l'intervalle.
res.stu <- rstudent(reg.simple)
plot(res.stu,pch=15,cex=0.5,ylab="Residuals",ylim=c(-3,3),col="blue")
abline(h=c(-2,0,2),lty=c(2,1,2),col="red")

#on affiche la comparaison entre les valeurs prédites et les valeurs observées, la répartition nous donne les ecarts, et peut montrer les extremes
plot(reg.simple$fitted.values,ozoneTrain[,"maxO3"])
abline(0,1)

#on charge notre jeu de données, ou on va vouloir préduire
ozoneTest <- read.table("ozoneTest.txt", header=TRUE)
#on tente la prédiction 
reg.pred <- predict(reg.simple, ozoneTest)
#on va afficher les vraies valeurs a coté de celles prédites pour voir le resulats si notre modèle marche bien sur un autre jeu de données
plot(reg.pred,ozoneTest[,"maxO3"],main="linear Model", xlab="Predictions",ylab="True values")
abline(0,1)

#on regarde la différnece en tre notre prédiction et un pprédicteur NMSE 
nmse.reg <- mean((reg.pred - ozoneTest[,"maxO3"])^2)/ mean((mean(ozoneTest[,"maxO3"])-ozoneTest[,"maxO3"])^2)

#on passe a la task 3
load('algae.RData')
load('testAlgae.RData')


NrNARow <- function(x){
sum(is.na(x))
}

manyNAs <- function(x,seuil){
	cpt <- apply(x,1,NrNARow)
	percent <- cpt/ncol(x)
	return(x[percent < seuil,])
}


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

algae <- manyNAs(algae,0.2)
cleanAlgae <- centerImputation(algae)
algae <- cleanAlgae

test.algae <- manyNAs(test.algae,0.2)
cleanTest <- centerImputation(test.algae)
test.algae <- cleanTest
plot(a1~.,data=algae,pch=15,cex=0.5,col="blue")
lm.a1 <- lm(a1 ~ ., data = algae)
abline(lm.a1,col="red")

#--------------------------------------
#on va tenter la régression multiple
reg.mult <- lm(max03 ~ ., data = ozoneTrain)
