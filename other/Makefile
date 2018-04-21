CC = clang++
CXX = clang++

INCLUDES =

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++11

LDFLAGs = -g
LDLIBS = 

executables = other
objects = other.o

.PHONY: default
default: $(executables)

$(objects):

.PHONY: clean
clean: 
	rm -f *~ a.out core other $(objects) $(excutables)

.PHONY: all
all: clean default
