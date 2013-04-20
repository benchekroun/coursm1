# This is an example of using RGtk to create a simple command-line
# interface for R. This has a value in addition to being a simple
# example of RGtk. We can use it (or something similar) to conveniently
# provide a command line interface when R is embedded in another application
# which does not provide access to executing R commands directly by the user.
# For example, when running Gnumeric, or R inside GGobi (as opposed to
# using the Rggobi package), one often wants to be able to debug code,
# or simply interact with the interpreter directly.

#
# If help() had been written with a separation of a) find the contents
# b) show the contents, we would be able to trap calls to help from the menu
# and display them using gtkhtml. Then we would be able to do some interesting
# things such as i) handle links in special ways e.g. for running code examples
# ii) embedding elements in the HTML such as devices, etc.
# iii) we can use HTML forms, etc.

# This gives a local version of what we have in the SNetscape package
# only here we don't need the browser, JavaScript, JNI/JRI, etc.
# Obviously we give up the ``browser'' interface.  

# We can experiment with the filtering ideas that are in Omegahat and
# TILE that allow us to keep a live transcript of the session in HTML
# with links, etc. to previous commands.  We can use the RSXMLObjects
# to serialize the expressions to HTML and the output.  We can even
# convert the S objects to XML and then use XSLT to generate the HTML
# and then append it to the HTML widget.  #


# This is also in RGtkViewers and should eventually move to
# RGtkUtils. Especially if we split RGtk into different packages.
library(RGtkViewers)

commandLine <-
function()
{
 win <- NULL
 historyWindow <- NULL
 libraryWindow <- NULL 
 ctr <- 1
 commands <- character(0)
 output <- NULL
 mbar <- NULL
 
 create <- function() {
  if(!is.null(win)) {
    win$Show()
    return(win)
  }

  top <- gtkWindow(show=FALSE)

  topBox <- gtkVBox(FALSE, 5)

  mbar <<- gtkMenuBar()

   # The File menu  
  item <- gtkMenuItem("File")
  item$SetSubmenu(createSimpleMenu(c("Open...",
                                     "Source...",
                                     "Library ...",
                                     "",
                                     "Save",
                                     "Save As...",
                                     "",
                                     "Close",
                                     "Quit"), fileMenuHandler)$menu)
  mbar$Append(item)

   # The Tools menu
  item <- gtkMenuItem("Tools")
  item$SetSubmenu(createSimpleMenu(list("History",
                                        "Library",
                                        "Devices"=c("New Device",
                                                    "Close Current Device",
                                                    "Close All Devices",
                                                    "Devices")),
                                   toolMenuHandler)$menu)
  mbar$Append(item)

    # The Settings menu
  item <- gtkMenuItem("Settings")  
  item$SetSubmenu(createSimpleMenu("Preferences", preferencesDialog)$menu)
  mbar$Append(item)

    # The Help menu
  item <- gtkMenuItem("Help")
  demoNames <- demo()$results[,"Item"]
  item$SetSubmenu(createSimpleMenu(
                     list("HTML Index",
                          "Text Index",
                          "",
                          "License",
                          "Contributors",
                          "",                          
                          Demos=demoNames,
                          "",                          
                          "About"), helpMenuHandler)$menu)
  mbar$Append(item)    



  topBox$PackStart(mbar, expand = FALSE)
  
  pane <- gtkHPaned()
  cmdBox <- gtkVBox(FALSE, 5)
  input <- gtkTextNew()
  input$SetEditable(TRUE)
  cmdBox$PackStart(input, fill = TRUE, expand = TRUE)

input$Insert(chars="1:10\n", length =-1)
  
  bbox <- gtkHBox(TRUE, 4)
  btn <- gtkButton("Evaluate")
  btn$AddCallback("clicked", function(obj) {
                  txt <- input$GetChars(0,-1)
                  txt <- gsub("(.*)\\\n$", "\\1", txt)
                  if(evalCommand(txt))
                    input$DeleteText(0, -1)                 
                 })
  bbox$PackStart(btn, fill = FALSE)

  btn <- gtkButton("Help")
  bbox$PackStart(btn, fill = FALSE)  

  cmdBox$PackStart(bbox, expand = FALSE)
  pane$Add(cmdBox)

  output <<- gtkTextNew()
  pane$Add(output)  
  topBox$PackStart(pane)
  top$Add(topBox)

  win <<- top
  win$Show()
 }

 fileMenuHandler <- function(w, cmd) {
    if(cmd == "Quit") {
      win$Destroy()
      win <<- NULL
    } else if(cmd == "Close") {
      win$Hide()
    } else if(cmd == "Save") {
       save.image()
    } else if(cmd == "Save As...") {
       dlg <- gtkFileSelection("Save session")
       dlg[["CancelButton"]]$AddCallback("clicked", function(w) { dlg$Hide() ; dlg$Destroy()})
       dlg[["OkButton"]]$AddCallback("clicked",
                                     function(w) {
                                       f <- dlg$GetFilename()
                                       if(nchar(f))
                                         save.image(f)
                                       dlg$Destroy()
                                     })       
       dlg$Show()
    }  else if(cmd == "Source..." || cmd == "Open...") {
      dlg <- gtkFileSelection("Source")
      dlg[["CancelButton"]]$AddCallback("clicked", function(w) dlg$Destroy(dlg))    
      dlg[["OkButton"]]$AddCallback("clicked",
                                     function(w) {
                                       f <- dlg$GetFilename()
                                       if(nchar(f)) {
                                         if(cmd == "Source...")
                                           source(f)
                                         else {
                                           cat("Loading image from",f,"\n")
#xxx                                       # This causes problems .....
                                           load(f)
                                         }
                                       }
                                       dlg$Destroy()
                                     })
      dlg$Show()
    }
  }

  toolMenuHandler <- function(w, cmd) {
   if(cmd == "New Device") {
        get(options()$device)()
   } else if(cmd == "Close Current Device") {
          dev.off()
   } else if(cmd == "Close All Devices") {
          graphics.off()
   } else if(cmd == "History") {
      if(is.null(historyWindow)) {
         historyWindow <<- showHistory(commands)
         historyWindow$l$AddCallback("select-child", function(l, kid) {
                                             kid <- gtkChildren(kid)[[1]]
                                             evalCommand(kid$GetArgs("label"))
                                         })
      }
      
      historyWindow$win$Show()      
    } else if(cmd == "Library") {
      if(is.null(libraryWindow)) {
       libraryWindow <<- showSearchPath()
       libraryWindow$win$AddCallback("delete_event", function(w, ev) {
                                        libraryWindow <<- NULL
                                      })
     }
     libraryWindow$win$Show(TRUE)
    }
  }

 evalCommand <- function(txt) {
         if(nchar(txt) == 0)
           return(FALSE)
         e <- parse(text = txt)
         val <- eval(e, env = globalenv())
         out <- paste(paste("<",ctr,">", txt,"\n", sep=""),
                      paste(as.character(val), sep="", collapse=" "),
                      "\n", collapse="", sep="")
         output$Insert(chars = out, length = -1)
         ctr <<- ctr + 1
         addToHistory(txt)
         return(TRUE)
   }

 addToHistory <- function(cmd) {
    commands <<- c(commands, cmd)
    if(!is.null(historyWindow)) {
      historyWindow$l$Add(gtkListItem(cmd))
    }
    return(length(commands))
 }

 about <-
   function() {
    cat("The R splash screen!\n")
   }
 
 helpMenuHandler <-
   function(w, cmd) {
     f <- switch(cmd, "HTML Index"= help.start,
                      "Text Index" = help,
                      License = "license",
                      Contributors = "contributors",
                      About = about,
                      NULL
                     )
     if(!is.null(f)) {
       if(is.function(f))
          f()
       else if(is.character(f)) {
         eval(substitute(help(topic), list(topic=f)))
       }
     } else {
       demo(cmd, character.only = TRUE)
     }
   }


 
 list(create=create,
#      addTool = addTool,
      menuBar = function() {mbar},
      outputArea = function() output,
      historyWindow = function() historyWindow,
      libraryWindow = function() libraryWindow
     )
}  

showHistory <-
function(cmds)
{
   vbox <- gtkVBox(FALSE, 1)  
   historyWin <- gtkWindow(show = FALSE)
   mbar <- createMenuBar("File"= c(Clear=0, Load=2, Save=2, Close=1, Quit=2),
                         "Load"= c(ok=1))$bar

   vbox$PackStart(mbar, expand = FALSE)

   l <- gtkList()
   for(i in cmds) {
     print(i)
     item <- gtkListItem(i)
     l$Add(item)
   }

   sw <- gtkScrolledWindow()
   sw$AddWithViewport(l)

   vbox$PackEnd(sw)
   
   historyWin$Add(vbox)
   historyWin$Show()

   invisible(list(win=historyWin,l = l))
}



showSearchPath <-
function(path = search(), createPage = showTable)
{
 win <- NULL
 win <- gtkWindow(show = FALSE)

 box <- gtkVBox(FALSE, 10)

 box$PackStart(createMenuBar(File=c(Close=function(w){
                                           win$Destroy()
                                          }))$bar, expand = FALSE)
 
 pkgs <- sort(.packages(all.available = TRUE))

 sw <- gtkScrolledWindow()
 l <- gtkList()
 for(i in pkgs) {
    l$Add(gtkListItem(i))
 }
 l$AddCallback("select-child", function(l, kid) {
                                pkg <- gtkChildren(kid)[[1]]$GetArg("label")
                                print(pkg)
                                library(pkg, character.only = TRUE)
                               })

 sw$AddWithViewport(l)
 
 book <- gtkNotebook()
 for(i in path) {
   w <- createPage(i)
   book$AppendPage(w, gtkLabel(i))
 }

 pane <- gtkHPaned()
 pane$Add(sw) 
 pane$Add(book)
 box$PackStart(pane)
 win$Add(box)
 list(win = win, l = l)
}  

showTable <-
function(name)
{
  els <- objects(all = T, pos = name)
  els <- els[1:(min(10, length(els)))]
  l <- gtkList()
  sw <- gtkScrolledWindow()  
  for(i in els) {
    l$Add(gtkListItem(i))
  }
  sw$AddWithViewport(l)
  return(sw)
}


appearanceFrame <-
function(els, name=NULL, callbacks = NULL, frame)
{

  fontHandler <-
    function(w, cbdata) {
      cat("fontHandler\n")
      dlg <- gtkFontSelectionDialog("Font selection")
      dlg[["OkButton"]]$AddCallback("clicked",
                                     function(w, data) {
                                        data[[1]](dlg)
                                        dlg$Destroy()
                                     })
      dlg[["CancelButton"]]$AddCallback("clicked", function(w) dlg$Destroy())     
      dlg$Show()
    }

  colorHandler <-
    function(w, cbdata) {
      dlg <- gtkColorSelectionDialog("Color selection")
      dlg[["OkButton"]]$AddCallback("clicked",
                                     function(w, data) {
                                        data[[1]](dlg)
                                        dlg$Destroy()
                                     })
      dlg[["CancelButton"]]$AddCallback("clicked", function(w) dlg$Destroy())     

      dlg$Show()
    }
  
  
  f <- gtkFrame(frame)
  bbox <- gtkVBox(TRUE, 3)
  for(i in names(els)) {
   box <- gtkHBox(TRUE, 3)   
   box$PackStart(gtkLabel(i))
   type <- ifelse(els[i],"font","color")
   btn <- gtkButton(type)
   box$PackEnd(btn, expand = FALSE, fill = FALSE)
   if(!is.null(callbacks)) {
    if(els[i])
     fun <- fontHandler
    else
     fun <- colorHandler
    btn$AddCallback("clicked", fun, data= list(callbacks[type], name))
   }

   bbox$PackStart(box)
  }

  f$Add(bbox)

  f
}

preferencesDialog <-
function(w = NULL, cmd)
{
 dlg <- gtkDialog(show = FALSE)
 book <- gtkNotebook()
  
  book$AppendPage(appearanceFrame(c("Font"=TRUE,
                                    "Output text color" = FALSE,
                                    "Input text color" = FALSE,
                                    "Background color" = FALSE),
                                  frame = "Text settings",
                                  callbacks=list(color=function(dlg){print("color")},
                                                 font = function(dlg){print("font")}
                                                )),
                              gtkLabel("Console")
                     )

  box <- gtkVBox(TRUE, 8)
  box$PackStart(appearanceFrame(c(Font=TRUE, "Text color"=FALSE, "Background color"=FALSE),
                                frame = "Title text settings"))
  box$PackEnd(appearanceFrame(c("Font" = TRUE,
                              "Text color" = FALSE,
                              "Background color" = FALSE),
                              frame = "Body text settings"))

  book$AppendPage(box, gtkLabel("Pager"))

  book$AppendPage(radioFrame(c("Always restore", "Never restore"), "Restore workspace"),
                  gtkLabel("Startup"))

  book$AppendPage(radioFrame(c("Prompt", "Always save", "Never save"), "Restore workspace"),
                  gtkLabel("Exit"))

  dlg[["ActionArea"]]$Add(book)
  dlg$Show()

  dlg
}  

radioFrame <-
function(buttonNames,  title)
{
 Startup <- gtkFrame("Restore workspace")  
 box <- gtkVBox(TRUE, 10)

 group <- NULL
 for(i in buttonNames) {
   b <- gtkRadioButton(group, i)
   box$PackStart(b, expand = FALSE)
 }

 Startup$Add(box)

 Startup
}  
