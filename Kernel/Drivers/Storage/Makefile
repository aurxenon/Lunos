include ../../kernel.mk

STORAGE_OBJECTS =  $(OBJDIR)/StorageDriver.o

all : Storage

Storage : $(STORAGE_OBJECTS)

CWD = $(shell /bin/pwd)

STORAGE_LEVEL_DIRS =  $(CWD)/PATA

.PHONY: all $(STORAGE_LEVEL_DIRS)
all : $(STORAGE_OBJECTS) $(STORAGE_LEVEL_DIRS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<

$(STORAGE_LEVEL_DIRS) : 
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@