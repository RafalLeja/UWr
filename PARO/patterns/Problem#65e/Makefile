rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC=g++
FLAGS=-std=c++17
OBJDIR=build
SRCDIR=src
CPP = $(filter-out "", $(call rwildcard,$(SRCDIR),*.cpp))
HPP = $(filter-out "", $(call rwildcard,$(SRCDIR),*.hpp))
HPPDIR = $(sort $(dir $(HPP)))
IDIRS=$(patsubst %, -I %, $(HPPDIR))
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(CPP:.cpp=.o))
EXEC = $(OBJDIR)/exec

$(info CPP="$(CPP)")

ifeq ($(OS), Windows_NT)
	MKDIR = mkdir
	RMDIR = rmdir /s /q
else
	MKDIR = mkdir -p
	RMDIR = rm -rf
endif

all: $(EXEC)

DEPENDENCIES := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(CPP:.cpp=.d))
-include $(DEPENDENCIES)

$(OBJDIR):
	@echo "  MKDIR  $@"
	@$(MKDIR) $@

$(EXEC): $(OBJ) | $(OBJDIR)
	@echo "  LD     $@"
	@$(CC) $(FLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "  CXX    $@"
	@$(CC) $(FLAGS) $(IDIRS) -c $< -o $@
	@$(CC) $(FLAGS) $(IDIRS) -MP -MM -MT $@ -MF $(@:.o=.d) $<

run: $(EXEC)
	@echo "  RUN    $<\n"
	@$<

clean:
	@echo "  RMDIR  $(OBJDIR)"
	@$(RMDIR) $(OBJDIR)

.PHONY: clean all run
