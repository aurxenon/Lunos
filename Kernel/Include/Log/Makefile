include ../../kernel.mk

LOG_OBJECTS = $(OBJDIR)/KLog.o

all : Log

Log : $(LOG_OBJECTS)

CWD = $(shell /bin/pwd)

all : $(LOG_OBJECTS)

$(OBJDIR)/%.o : $(CWD)/%.cpp
	@echo "[ CXX ] $@"
	@${CXX} ${KERNEL_CFLAGS} -o $@ -c $<