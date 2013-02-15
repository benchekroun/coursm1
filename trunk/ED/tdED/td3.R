da <-read.table("td3-source.txt", header=TRUE)
#plot est générique, et essaye de s'adapter , soit valeurs numériques, et plot, soit qualitative et il fait un barplot
plot(da$sexe)
poidsHom <- da$poids[da$sexe == "masculin"]
poidsFem <- da$poids[da$sexe == "feminin"] 
#divise la fentre en deux
par(mfrow=c(1,2))
hHom <- hist(poidsHom)
hFem <- hist(poidsFem)
#boxPlotHom <- boxplot(poidsHom)
#boxPlotFem <- boxplot(poidsFem)
ex2 <- c(61,62,67,68,69,76,77,78,79)

