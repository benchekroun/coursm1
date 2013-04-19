# required: RGtk2
calculateGUI <- function() {
	## Run on "OK"
	performStatistics <- function(button, user.data) {
		res <- NULL
		d <- NULL
		error <- NULL
		warning <- NULL
		# Get the information about data and the file
		the.file <- filename$getText()
		the.sep <- sepEntry$getText()
		the.headers <- headersEntry$active
		the.dec <- decEntry$getText()
		d <- read.table(the.file,sep=the.sep,header=the.headers,dec=the.dec)
		# Select numerical variables
		numVar <- sapply(1:ncol(d),function(x){is.numeric(d[,x])})
		if (sum(numVar)==0) {
			error <- "No numerical variables in the data: nothing to do...!"
		} else {
			# Run 'WhatMyTeacherWants' on numerical variables
			res <- apply(d[,numVar],2,WhatMyTeacherWants)
			# Get saving options and save if needed
			isToSave <- toSave$active
			exportName <- exportFileName$getText()
			if ((isToSave)&(exportName=="")) {
				warning <- "Invalid user data: a file name must be specified if you want to save results!"
			} else {
				where.sep <- gregexpr("/",the.file)[[1]]
				where.sep <- max(where.sep)
				save.dir <- substr(the.file,1,where.sep)
				write.table(res,file=paste(save.dir,exportName,".csv",sep=""))
			}
		}
		if (!is.null(res)) {
			########## Start dialog...
			# Open a dialog box to print results
			dialog <- gtkDialogNewWithButtons("Might be helpful for lazy students",window, "modal","gtk-ok", GtkResponseType["ok"],"gtk-quit", GtkResponseType["cancel"])
		
			# Create vertical container for file name entry
			vbox <- gtkVBoxNew(FALSE, 8)
			vbox$setBorderWidth(24)
			dialog$getContentArea()$packStart(vbox, FALSE, FALSE, 0)
		
 			# Print results (table)
			tableRes <- gtkTableNew(nrow(res)+1,ncol(res)+1)
			tableRes$setColSpacings(10)
			vbox$packStart(tableRes,FALSE,FALSE,0)
			# Print column names
			for (indC in 1:ncol(res)) {
				label <- gtkLabel(colnames(res)[indC])
				tableRes$attachDefaults(label, indC, indC+1, 0, 1)
			}
			for (indR in 1:nrow(res)) {
				label <- gtkLabel(rownames(res)[indR])
				tableRes$attachDefaults(label,0,1,indR,indR+1)
				for (indC in 1:ncol(res)) {
					label <- gtkLabel(res[indR,indC])
					tableRes$attachDefaults(label, indC, indC+1, indR, indR+1)
				}
			}
			
			# Add warning...
			if (!is.null(warning)) {
				hbox <- gtkHBoxNew()
				vbox$packStart(hbox,FALSE,FALSE,0)
				label <- gtkLabel(warning)
				hbox$packStart(label,FALSE,FALSE,0)
			}

			# If results are saved, print information about it
			if ((isToSave)&(exportName!="")) {
				hbox <- gtkHBoxNew(FALSE,20)
				vbox$packStart(hbox, FALSE, FALSE, 0)
				label <- gtkLabelNew(paste("Results are saved in file: ",save.dir,exportName,".csv",sep=""))
				hbox$packStart(label,FALSE,FALSE,0)
			}
			
			response <- dialog$run()
			# Return to previous window
			if (response == GtkResponseType["ok"]) {
				dialog$destroy()
			}
			# Quit all windows
			if (response == GtkResponseType["cancel"]) {
				dialog$destroy()
				window$destroy()
			}
		} else {
			dialog <- gtkMessageDialogNew(window, c("modal", "destroy-with-parent"), "info", "ok",error)
			dialog$run()
			dialog$destroy()
		}
	}
		
	# Create window
	window <- gtkWindow()
	# Add title
	window["title"] <- "Standard statistics for numerical variables"

	# Add a frame
	frame <- gtkFrameNew("Specify data location...")
	window$add(frame)

	# Create vertical container for file name entry
	vbox <- gtkVBoxNew(FALSE, 8)
	vbox$setBorderWidth(24)
	frame$add(vbox)
	# Add horizontal container for every widget line
	hbox <- gtkHBoxNew(FALSE, 8)
	vbox$packStart(hbox, FALSE, FALSE, 0)

	# Add label in first column
	label <- gtkLabelNewWithMnemonic("_File name")
	hbox$packStart(label,FALSE,FALSE,0)
	# Add entry in the second column; named "filename"
	filename <- gtkEntryNew()
	filename$setWidthChars(50)
	label$setMnemonicWidget(filename)
	hbox$packStart(filename,FALSE,FALSE,0)

	# Add an horizontal container to specify input file options
	# are headers included in the file?
	hbox <- gtkHBoxNew(FALSE,8)
	vbox$packStart(hbox, FALSE, FALSE, 0)
	label <- gtkLabelNewWithMnemonic("_Headers?")
	hbox$packStart(label,FALSE,FALSE,0)
	headersEntry <- gtkCheckButton()
	headersEntry$active <- TRUE
	hbox$packStart(headersEntry,FALSE,FALSE,0)
	label$setMnemonicWidget(headersEntry)
	
	# are headers included in the file?
	label <- gtkLabelNewWithMnemonic("Col. _Separator?")
	hbox$packStart(label,FALSE,FALSE,0)
	sepEntry <- gtkEntryNew()
	sepEntry$setWidthChars(1)
	sepEntry$setText(",")
	hbox$packStart(sepEntry,FALSE,FALSE,0)
	label$setMnemonicWidget(sepEntry)

	# what's the character used for decimal points?
	label <- gtkLabelNewWithMnemonic("_Dec. character?")
	hbox$packStart(label,FALSE,FALSE,0)
	decEntry <- gtkEntryNew()
	decEntry$setWidthChars(1)
	decEntry$setText(".")
	hbox$packStart(decEntry,FALSE,FALSE,0)
	label$setMnemonicWidget(decEntry)

	# Add separator
	vbox$packStart(gtkHSeparatorNew(), FALSE, FALSE, 0)
	
	# Add two horizontal containers to check if the results has to be exported in a file and if so, to specify file named
	hbox <- gtkHBoxNew(FALSE,8)
	vbox$packStart(hbox, FALSE, FALSE, 0)
	label <- gtkLabelNewWithMnemonic("Save _Results?")
	hbox$packStart(label,FALSE,FALSE,0)
	toSave <- gtkCheckButton()
	hbox$packStart(toSave,FALSE,FALSE,0)
	label$setMnemonicWidget(toSave)
	label <- gtkLabelNewWithMnemonic("_Export file name?")
	hbox$packStart(label,FALSE,FALSE,0)
	exportFileName <- gtkEntryNew()
	exportFileName$setWidthChars(50)
	exportFileName$setText("outputs")
	hbox$packStart(exportFileName,FALSE,FALSE,0)
	label$setMnemonicWidget(exportFileName)
	label <- gtkLabel(".csv")
	hbox$packStart(label,FALSE,FALSE,0)
	
	# Add button
	the.buttons <- gtkHButtonBoxNew()
	the.buttons$setBorderWidth(5)
  vbox$add(the.buttons)
  the.buttons$setLayout("spread")
  the.buttons$setSpacing(40)
	buttonOK <- gtkButtonNewFromStock("gtk-ok")
	gSignalConnect(buttonOK, "clicked", performStatistics)
	the.buttons$packStart(buttonOK,fill=F)
	buttonCancel <- gtkButtonNewFromStock("gtk-close")
	gSignalConnect(buttonCancel, "clicked", window$destroy)
	the.buttons$packStart(buttonCancel,fill=F)
}
