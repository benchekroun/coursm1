#testAppli.r 
#idee: faire une petite appli qui contient deux trois bases
#de RGtk2
#peut etre incorporer des onglets plus tard
library(RGtk2)

#fonction pour charger les donnees et mettre a jour
#l'affichage apres le chargement





go <- function(){

MAJ <- function(button, user.data){
loader <- function(){
	
	# On recupere les infos presentes dans les widget
		the.file <- filename$getText()
		the.sep <- sepEntry$getText()
		the.headers <- headersEntry$active
		the.dec <- decEntry$getText()
		#on charge le fichier
		datas <<- read.table(filename$getText(),header=TRUE)				
	
}	

	loader()

	print(ncol(datas))
	print("bien ouej")
	filename$setText("bien-ouej.txt")
	
		
}


#on creer la fenetre
window = gtkWindow()
#on lui donne un titre, i.e on renseigne son champ titre
#car oui , on reste en R, ce n'est donc que plein de vecteur
window["title"] = "test d'une appli qui utilise (bien) RGtk"

#on cree la "frame" , le conteneur général de tout ce qu'il y a dans
# notre fenetre , le superPanel de Swing
frame = gtkFrameNew() 
#ici on ne met pas de titre dnas les paranthese, car dans notre cas
#avoir un "onglet" seul et avec un titre, ne serai pas pertinent ,
#ni utile

#on l'ajoute dnas la window
window$add(frame)

#on voudrais un fenetre divisée en deux, un coté pour charger le fichier
#et un autre pour afficher un sommaire du fichier
#on creer donc un conteneur horizontal qui va contenir deux autres 
#conteneur, ce qui divisera la frame en deux comme souhaité

#param : homogeneous (ici false), et spacing (espace inter-composants)
superHbox= gtkHBoxNew(FALSE, 8)
#on l'ajoute dnas la "frame"
frame$add(superHbox)

# on cree un container vertical (alignement vertical)
# pour mettre les textfields du choix de fichier
vbox = gtkVBoxNew(FALSE, 8)
#option de creation de bordure
vbox$setBorderWidth(24)
#on ajoute dans le super
superHbox$add(vbox)


hbox = gtkHBoxNew(FALSE, 8)
vbox$packStart(hbox, FALSE, FALSE, 0)

#creer n valeur réutilisable
label = gtkLabelNewWithMnemonic("_File name")
hbox$packStart(label,FALSE,FALSE,0)
# Add entry in the second column; named "filename"
filename = gtkEntryNew() #champ d'entrée de texte
filename$setWidthChars(30)
label$setMnemonicWidget(filename)
hbox$packStart(filename,FALSE,FALSE,0)


# Add an horizontal container to specify input file options
# are headers included in the file?
hbox = gtkHBoxNew(FALSE,8)
vbox$packStart(hbox, FALSE, FALSE, 0)
label = gtkLabelNewWithMnemonic("_Headers?")
hbox$packStart(label,FALSE,FALSE,0)
headersEntry = gtkCheckButton()
headersEntry$active = TRUE
hbox$packStart(headersEntry,FALSE,FALSE,0)
label$setMnemonicWidget(headersEntry)
 
# are headers included in the file?
label = gtkLabelNewWithMnemonic("Col. _Separator?")
hbox$packStart(label,FALSE,FALSE,0)
sepEntry = gtkEntryNew()
sepEntry$setWidthChars(1)
sepEntry$setText(" ")
hbox$packStart(sepEntry,FALSE,FALSE,0)
label$setMnemonicWidget(sepEntry)
 
# what's the character used for decimal points?
label = gtkLabelNewWithMnemonic("_Dec. character?")
hbox$packStart(label,FALSE,FALSE,0)
decEntry = gtkEntryNew()
decEntry$setWidthChars(1)
decEntry$setText(".")
hbox$packStart(decEntry,FALSE,FALSE,0)
label$setMnemonicWidget(decEntry)
 
# Add separator
vbox$packStart(gtkHSeparatorNew(), FALSE, FALSE, 0)
 
# Add two horizontal containers to check if the results have to be exported in a file and if so, to specify the file's name
hbox = gtkHBoxNew(FALSE,8)
vbox$packStart(hbox, FALSE, FALSE, 0)
label = gtkLabelNewWithMnemonic("Save _Results?")
hbox$packStart(label,FALSE,FALSE,0)
#creer une case à cocher
toSave = gtkCheckButton()
hbox$packStart(toSave,FALSE,FALSE,0)
label$setMnemonicWidget(toSave)
label = gtkLabelNewWithMnemonic("_Export file name?")
hbox$packStart(label,FALSE,FALSE,0)
exportFileName = gtkEntryNew()
exportFileName$setWidthChars(30)
exportFileName$setText("outputs") 
hbox$packStart(exportFileName,FALSE,FALSE,0)
label$setMnemonicWidget(exportFileName)
label = gtkLabel(".csv")
hbox$packStart(label,FALSE,FALSE,0)

# Add button
#les boutons sont ajoutées dnas une buttonBox, 
#une sorte de panel spécial pour les buttons
the.buttons = gtkVButtonBoxNew()
the.buttons$setBorderWidth(5)
vbox$add(the.buttons)
the.buttons$setLayout("spread")
the.buttons$setSpacing(20)
buttonOK = gtkButton("testbtn")#btn ok
#connecter un bouton a une fonction
gSignalConnect(buttonOK, "clicked", MAJ)
the.buttons$packStart(buttonOK,fill=F)
buttonCancel = gtkButtonNewFromStock("gtk-close")#btn close
gSignalConnect(buttonCancel, "clicked", window$destroy)
the.buttons$packStart(buttonCancel,fill=F)


}
