#fenetre simple avec quelques gadget de base
library(RGtk2)

go  <- function(){
	
	afficherWidget <- function(button, user.data){
		panelafficher = gtkVBoxNew(FALSE,8)
		superPanel$add(panelafficher)
		#un bouton
		leBouton = gtkButton("un bouton")
		panelafficher$packStart(leBouton,FALSE,FALSE,0)
		#un label
		leLabel = gtkLabelNewWithMnemonic("un label")
		panelafficher$packStart(leLabel,FALSE,FALSE,0)
		#un champ de texte
		leTextfield = gtkEntryNew() #champ d'entrée de texte
		leTextfield$setText("un champ de texte")
		panelafficher$packStart(leTextfield,FALSE,FALSE,0)
		
		
		
		
		
	}


#on créé ma fenetre
fenetre = gtkWindow()

#on change le titre
fenetre["title"] = "Fenetre avec quelques gadgets"

#on crée la frame
laFrame = gtkFrameNew("la frame principale")

#ajout dans la fenetre
fenetre$add(laFrame)

#ici , on n'avais pas rajoute de panel intermédiaire dnas la frame
#mais , la frame ne peut contenir qu'on seul objet dnas elle
#l'astuce est alors d'utiliser une VBox intermédiare, dans laquelle
#on pourra ajouter dynamiquement autant d'objets que l'on souhaite
superPanel = gtkVBoxNew(FALSE,8)
laFrame$add(superPanel)

#on creer le panel pour mettre un/des bouton(s) dedans
buttonsPanel = gtkVButtonBoxNew()
buttonsPanel$setLayout("spread")
buttonsPanel$setSpacing(20)
#on l'ajoute à la frame
superPanel$add(buttonsPanel)

#on va ajouter un bouton pour afficher les gadgets
afficherGagets = gtkButton("afficher les widgets")


gSignalConnect(afficherGagets, "clicked", afficherWidget)
#on ajoute le bouton pour afficher des widget au panel
buttonsPanel$packStart(afficherGagets,FALSE,FALSE,0)


}
