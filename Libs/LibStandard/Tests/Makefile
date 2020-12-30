include ../../../include.mk

CWD = $(shell /bin/pwd)
TEST_OUT = $(TOPDIR)/bin
LOCAL_OBJDIR = $(TOPDIR)/obj

LIBSTANDARD_TESTS = $(TEST_OUT)/CStringTests
LIBSTANDARD_TESTS += $(TEST_OUT)/BitmapTests
LIBSTANDARD_TESTS += $(TEST_OUT)/SinglyLinkedListTests

all : LibStandardTests

LibStandardTests : $(LIBSTANDARD_TESTS)

$(TEST_OUT)/% : $(CWD)/%.cpp
	@echo "[ TEST ]  $(shell realpath --relative-to=$(TOPDIR) $<)"
	@${SYS_CXX} ${TEST_CFLAGS} -o $@ $< $(wildcard $(LOCAL_OBJDIR)/*.o)
	@rm -rf $@.dSYM 2> /dev/null