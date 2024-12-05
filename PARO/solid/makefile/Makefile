rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC=g++
FLAGS=-std=c++17
OBJDIR=obj
SRCDIR=src
CPP = $(filter-out "", $(call rwildcard,$(SRCDIR),*.cpp))
HPP = $(filter-out "", $(call rwildcard,$(SRCDIR),*.hpp))
HPPDIR = $(sort $(dir $(HPP)))
IDIRS=$(patsubst %, -I %, $(HPPDIR))
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(CPP:.cpp=.o))


$(info CPP="$(CPP)")

ifeq ($(OS), Windows_NT)
	MKDIR = mkdir $(OBJDIR)
	RMDIR = rmdir /s /q $(OBJDIR) 
else
	MKDIR = mkdir -p $(OBJDIR)
	RMDIR = rm -rf $(OBJDIR) 
endif

all: $(OBJDIR)/exec

DEPENDENCIES := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(CPP:.cpp=.d))
-include $(DEPENDENCIES)

directory:
	$(MKDIR)

$(OBJDIR)/exec: $(OBJ) | directory
	$(CC) $(FLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | directory
	$(CC) $(FLAGS) $(IDIRS) -c $< -o $@
	$(CC) $(FLAGS) $(IDIRS) -MP -MM -MT $@ -MF $(@:.o=.d) $<

run:
	$(OBJDIR)/exec

clean:
	$(RMDIR)

.PHONY: clean all directory
