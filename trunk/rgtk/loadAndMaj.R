#fonction pour charger les donnees et mettre a jour
#l'affichage apres le chargement
loadAndMaj <- function(button, user.data){
	
	# On recupere les infos presentes dans les widget
		the.file <- filename$getText()
		the.sep <- sepEntry$getText()
		the.headers <- headersEntry$active
		the.dec <- decEntry$getText()
		#on charge le fichier
		the.data <- read.table(the.file,sep=the.sep,header=the.headers,dec=the.dec)
		plot(the.data)
}



