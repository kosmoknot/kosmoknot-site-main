# Compiler settings - Can be customized.
CC = g++
INCLD = -I ./code/include/
CXXFLAGS = -std=c++17 -Wall $(INCLD) -g -ggdb
LDFLAGS = -g -ggdb

# Makefile settings - Can be customized.
APPNAME = meengi
EXT = .cpp
SRCDIR = ./code/src
OBJDIR = ./code/bin
DEPDIR = ./code/bin
TESTDIR = ./tests
TESTBIN = meengi_tests

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
SRC_NO_MAIN = $(filter-out $(SRCDIR)/main$(EXT), $(SRC))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
TEST_SRCS = $(wildcard $(TESTDIR)/*$(EXT))
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)
# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TESTBIN): $(TEST_SRCS) $(SRC_NO_MAIN)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TESTBIN)
	./$(TESTBIN)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME) $(TESTBIN)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE) $(TESTBIN)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)
