CFLAGS			=	-std=c++11 -g -Wall 
LIBS			= 	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
TARGET			=	Tetris
SRCDIR			= 	src
OBJDIR			= 	obj
INCLUDE_PATH	=	./include
DOC				=	doc_file
DOCDIR			=	doc

SOURCES			:=	$(wildcard $(SRCDIR)/*.cc)
INCLUDES		:=	$(wildcard $(INCLUDE_PATH)/*.hpp)
OBJECTS			:=	$(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(TARGET) :	$(OBJECTS)
	g++		-o $@ $^ $(CFLAGS) $(LIBS)
	@echo " ----- \e[32mLinking complete\e[39m ----- "

$(OBJECTS):				$(OBJDIR)/%.o:	$(SRCDIR)/%.cc
	mkdir	-p $(OBJDIR)
	g++		-o $@ -c $< $(CFLAGS) $(LIBS) -I $(INCLUDE_PATH)

$(DOC) :
	@doxygen $(DOCDIR)/$(DOC)

all : $(TARGET) $(DOC)

clean :
	rm -rf doc/html/
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(TARGET)
	@echo " ----- \e[32mCleaning complete\e[39m ----- "

open_doc :
	@sensible-browser $(DOCDIR)/html/index.html