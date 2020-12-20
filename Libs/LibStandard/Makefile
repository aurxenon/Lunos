include ../../Kernel/kernel.mk

CWD = $(shell /bin/pwd)
LOCAL_OBJDIR = $(TOPDIR)/obj

LIBSTANDARD_OBJECTS =  $(OBJDIR)/PString.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/CString.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/stdlib.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/ConvertNums.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/sstream.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/Vector.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/DoublyLinkedList.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/new.o
LIBSTANDARD_OBJECTS += $(OBJDIR)/Bitmap.o

LIBSTANDARD_TEST_DIR = $(CWD)/Tests

.PHONY: all $(LIBSTANDARD_TEST_DIR)
all : LibStandard $(LIBSTANDARD_TEST_DIR)

LibStandard : $(LIBSTANDARD_OBJECTS)

all : $(LIBSTANDARD_OBJECTS) $(LIBSTANDARD_TEST_DIR)

#RIGHT NOW LIBSTANDARD IS BUILT UNDER KERNEL ASSUMPTIONS

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ]   $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<
	@echo "[ LOCAL ] $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${SYS_CXX} ${TEST_CFLAGS} -o $(LOCAL_OBJDIR)/$(notdir $@) -c $<

$(LIBSTANDARD_TEST_DIR) :
	@echo "[ MAKE ]  $(shell realpath --relative-to=$(TOPDIR) $@)"
	@$(MAKE) --directory=$@