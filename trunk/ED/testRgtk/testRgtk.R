library(RGtk2)
# Create window
window = gtkWindow()
# Add title
window["title"] = "test rgtk"
# Add a frame
frame = gtkFrameNew("Fenetre principal (panel principal)")
#comme dans d'autyre biblio de GUI, on ajoute la frame dnas la window
window$add(frame)

# Create vertical container for file name entry
vbox = gtkVBoxNew(FALSE, 8)
#option de creation de bordure
vbox$setBorderWidth(24)
#on ajoute dans la frame
frame$add(vbox)
# Add horizontal container for every widget line
hbox = gtkHBoxNew(FALSE, 8)
vbox$packStart(hbox, FALSE, FALSE, 0)

#creer n valeur réutilisable
label = gtkLabelNewWithMnemonic("_File name")
hbox$packStart(label,FALSE,FALSE,0)
# Add entry in the second column; named "filename"
filename = gtkEntryNew() #champ d'entrée de texte
filename$setWidthChars(50)
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
sepEntry$setText(",")
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
exportFileName$setWidthChars(50)
exportFileName$setText("outputs") 
hbox$packStart(exportFileName,FALSE,FALSE,0)
label$setMnemonicWidget(exportFileName)
label = gtkLabel(".csv")
hbox$packStart(label,FALSE,FALSE,0)

# Add button
the.buttons = gtkHButtonBoxNew()
the.buttons$setBorderWidth(5)
vbox$add(the.buttons)
the.buttons$setLayout("spread")
the.buttons$setSpacing(40)
buttonOK = gtkButtonNewFromStock("gtk-ok")#btn ok
#connecter un bouton a une fonction
gSignalConnect(buttonOK, "clicked", window$destroy)
the.buttons$packStart(buttonOK,fill=F)
buttonCancel = gtkButtonNewFromStock("gtk-close")#btn close
gSignalConnect(buttonCancel, "clicked", window$destroy)
the.buttons$packStart(buttonCancel,fill=F)


