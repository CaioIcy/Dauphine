## Edit this to fit your settings ##

## Lua settings
LUA_DIR := /usr/local
LUA_LIBDIR := $(LUA_DIR)/lib
LUA_INCDIR := $(LUA_DIR)/include
LUA_LINK := -llua -ldl
##

# Folders containing files
INCLUDES	:= include
SOURCES		:= src
RESOURCES	:= res
BUILD		:= build

# Lib settings
LIB_DIR := $(CURDIR)/lib
LINK_LIBS := -L$(LUA_LIBDIR) -L$(LIB_DIR) $(LUA_LINK) -lm -ltmxparser -ltinyxml -lz

# Compiler
export LD := $(CXX)
# Compiler flags
CPPFLAGS=-O2 -g -W -Wall -pedantic -ansi -std=c++11 -Wextra -Wshadow
# Linking flags
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lstdc++ $(LINK_LIBS)

# Target program name
TARGET := Dauphine
# Automatically build a list of object files
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
# Object files
export OFILES := $(addprefix $(BUILD)/,$(CPPFILES:.cpp=.o))
# 
CPPFILES := $(addprefix $(SOURCES)/,$(CPPFILES))
# Build a list of include paths
export INCLUDE := $(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) -I$(CURDIR)/$(BUILD)
INCLUDE += -I$(LUA_INCDIR)

$(BUILD)/%.o:$(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	@echo Building $^ ...
	@$(LD) $(CPPFLAGS) -c $^ -o $@ $(INCLUDE)

main:$(LIB_DIR)/libtinyxml.a $(LIB_DIR)/libtmxparser.a $(OFILES)
	@mkdir -p $(BUILD)
	@echo Linking necessary libraries...
	@$(LD) $(OFILES) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET)
	@echo Built executable "$(TARGET)"

$(LIB_DIR)/libtinyxml.a:
	@echo --- Creating libtinyxml.a ...
	@cd $(LIB_DIR)/tinyxml && $(MAKE)
	@cd $(LIB_DIR)/tinyxml && ar rcs libtinyxml.a *.o
	@cd $(LIB_DIR)/tinyxml && mv libtinyxml.a ../
	@cd $(LIB_DIR)/tinyxml && $(MAKE) clean
	@echo --- Done.

$(LIB_DIR)/libtmxparser.a:
	@echo --- Creating libtmxparser.a ...
	@cd $(LIB_DIR)/ && $(MAKE) -f Makefile.tmxparser
	@cd $(LIB_DIR)/ && $(MAKE) -f Makefile.tmxparser clean
	@echo --- Done.

clean:
	@echo Cleaning build folder...
	@rm -rf $(BUILD)/
	@echo Cleaning executables...
	@rm -f $(TARGET)
	@rm -f $(TARGET).exe
	@echo Cleaning others...
	@rm -f *.dll
	@rm -f LICENSES.txt
	@echo Done.

hardclean: clean
	@echo Deleting static libraries...
	@rm -f $(LIB_DIR)/*.a
	@echo Done.
