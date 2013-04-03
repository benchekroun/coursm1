vec <- c(2.4,2.5,3.1,1.9,3.5)
meanvec <- mean(vec)
#on pose une hypothese que la population suit une loi normale
#trouve l'intervalle de confiance d'un vecteur, 
#on lui passe la prob de l'intervalle
intervTest <- t.test(vec,conf.level=0.95)
#trouver l'intervale haut(d'ou le +)
intervHaut <- mean(vec)+qt(0.975,df=4)*sd(vec) /sqrt(5) #ici n=5
#trouver l'intervalle bas( d'ou le - )
intervBas <- mean(vec)-qt(0.975,df=4)*sd(vec) /sqrt(5) #ici n=5
