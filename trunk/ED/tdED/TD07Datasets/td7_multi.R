#on lit les données
ozoneTrain <- read.table("ozoneTrain.txt", header=TRUE)

#n produit une régression multiple 
#sur toutes les variables
reg.mult <- lm(maxO3 ~ . , data=ozoneTrain)

#le coeffcient multiple R-square ets supérieur
#a celui trouvé dnas le model dee regression
#simple. Le modele semble donc plus précis.

#la prediction pour la regression se fait avec predict#on charge notre 
#jeu de données, ou on va vouloir préduire
ozoneTest <- read.table("ozoneTest.txt", header=TRUE)
#on tente la prédiction 
reg.pred <- predict(reg.mult, ozoneTest)

#on va afficher les vraies valeurs a coté de celles prédites pour voir
# le resulats si notre modèle marche bien sur un autre jeu de données
plot(reg.pred,ozoneTest[,"maxO3"],main="linear Model", 
xlab="Predictions",ylab="True values")
abline(0,1)

#on compare nos valeur avec celle du prédicteur qui quelquesoit l'entrée
#renvoie le mean de la colonne
#si cette valeur est proche de zéro , alors notre model ets bon
nmse.reg.m <- (nmse.reg <- mean((reg.pred - ozoneTest[,"maxO3"])^2)/
mean((mean(ozoneTest[,"maxO3"])-ozoneTest[,"maxO3"])^2))
#il faut aussi prendre en compte la taille du modele, 
#un coeff nmse plus faible est mieux, mais un modele qui contient 
#moins de variable est plus efficace, car sa taille est meilleure.

#si on a des variables dont les probabilité (4° col du summary de la
# regression) inférieure a 5 %, alors on peux les exclure , mais si les 
#var on presuqe toutes au deussus alors  on ne peut rejeter le fait qu'
#elles peuvent être 0 dnas la cas général.

#il ets aussi possible d echoisir dna sl alm , les parametre à prendre
# en compte, par exmple , on êut spécifier la formule avec 
# lm( formula =  Y ~ A+B+C+D+...+J, data = DATAS)

#la fonction step permet de lancer une heuristique qui va peut etre 
#trouver le variables pertinentes pour la régression. 

#ne pas oublie que dans le summary de la regression
#si le F-statistic ets inférieur au p-value
#alors il n'existe pas d eregression linearie entre les valeurs
#utilisées pour générer le modèle et la variable que l'on essaie
#de prédire

#la valuer du multiple R-suquared doit etre le plus proche possible de &
#pour montrer que le modèele est pertinent.
#de plus si il 'ets inférieur a 30% , la relatino entre variable
#que nous testons est souvent peu pertinente

