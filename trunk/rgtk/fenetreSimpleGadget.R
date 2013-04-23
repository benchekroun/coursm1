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
		
		#une checkbox deja cochée
		checkCochee = gtkCheckButton()
		checkCochee$active = TRUE;
		
		
		#une checkbox pas cochée	
		checkPasCochee = gtkCheckButton()
		checkPasCochee$active = FALSE;
		
		#on a créé les checkbox , mais on voudrait mettre un label a coté
		#on cherche donc un alignement horizontal
		boxCochee = gtkHBoxNew(TRUE,8)
		panelafficher$add(boxCochee)
		boxPasCochee = gtkHBoxNew(TRUE,8)
		panelafficher$add(boxPasCochee)
		labelCochee = gtkLabelNewWithMnemonic("une checkBox cochée")
		labelPasCochee = gtkLabelNewWithMnemonic("une checkBox pas cochée")
		
		#on ajoute dans les box
		boxCochee$packStart(labelCochee,FALSE,FALSE,0)
		boxCochee$packStart(checkCochee,FALSE,FALSE,0)
		
		boxPasCochee$packStart(labelPasCochee,FALSE,FALSE,0)
		boxPasCochee$packStart(checkPasCochee,FALSE,FALSE,0)
		
		
		#on va faire la suite des item dans la liste item
		
		#fleche
		panelArrow = gtkHBoxNew(TRUE,8)
		panelafficher$add(panelArrow)
		Arrow =gtkArrowNew()
		labelArrow= gtkLabelNew("une fleche")
		panelArrow$packStart(labelArrow,FALSE,FALSE,0)
		panelArrow$packStart(Arrow,FALSE,FALSE,0)
		
		#image 
		#http://rss.acs.unt.edu/Rdoc/library/RGtk2/html/GtkImage.html
		#cette doc est tres utile pour l'image
		panelImg = gtkHBoxNew(TRUE,8)
		panelafficher$add(panelImg)
		img = gtkImageNewFromFile("Cortus.gif")
		labelImg= gtkLabelNew("Une image (ici un .gif)")
		panelImg$packStart(labelImg,FALSE,FALSE,0)
		panelImg$packStart(img,FALSE,FALSE,0)		
		
		#un bouton radio
		panelRadio = gtkHBoxNew(TRUE,8)
		panelafficher$add(panelRadio)
		labelRadio = gtkLabel("un bouton radio")
		radioBtn = gtkRadioButtonNew()
		radioBtn$active=FALSE
		panelRadio$packStart(labelRadio,FALSE,FALSE,0)
		panelRadio$packStart(radioBtn,FALSE,FALSE,0)
		
		#selection d'une couleur
		colored = gtkColorSelection()
		panelafficher$add(colored)
		
		#un comboBox pour faire un choix parmis un liste
		#je ne sais pas encore comment le remplir
		combo = gtkComboBoxEntryNew()
		panelafficher$add(combo)
		
	    #on va mettre la suite dans un autre panel
	    #car sinn on ne verra rien
	    panelSuivant = gtkVBoxNew(FALSE,8)
	    superPanel$add(panelSuivant)
		
		notbk = gtkNotebookNew()
		panelSuivant$packStart(notbk,FALSE,FALSE,0)
		
		
		
		#on essaie de faire un filechosser
		# fileChooser = gtkFileChooserWidgetNew("Open File")
		# fileChooser$title = "un fileSelection"
		#mais pour le moment on ne sais pas comment binder des événements
		#sur les boutons du fileChooser
		
	}


#on créé ma fenetre
fenetre = gtkWindow()

#on change le titre
fenetre$title = "Fenetre avec quelques gadgets"

#on crée la frame
laFrame = gtkFrameNew("la frame principale")

#ajout dans la fenetre
fenetre$add(laFrame)

#ici , on n'avais pas rajoute de panel intermédiaire dnas la frame
#mais , la frame ne peut contenir qu'on seul objet dnas elle
#l'astuce est alors d'utiliser une VBox intermédiare, dans laquelle
#on pourra ajouter dynamiquement autant d'objets que l'on souhaite
superPanel = gtkHBoxNew(FALSE,8)
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
