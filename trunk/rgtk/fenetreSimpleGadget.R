#fenetre simple avec quelques gadget de base
library(RGtk2)

#on créé ma fenetre
fenetre = gtkWindow()

#on change le titre
fenetre["title"] = "Fenetre avec quelques gadgets"

#on crée la frame
laFrame = gtkFrameNew("la frame principale")

#ajout dans la fenetre
fenetre$add(laFrame)



#on creer le panel pour mettre un/des bouton(s) dedans
buttonsPanel = gtkVButtonBoxNew()
buttonsPanel$setLayout("spread")
buttonsPanel$setSpacing(20)
#on l'ajoute à la frame
laFrame$add(buttonsPanel)

#on va ajouter un bouton pour afficher les gadgets
afficherGagets = gtkButton("afficher les gadgets")

buttonsPanel$packStart(afficherGagets,fill = F)
