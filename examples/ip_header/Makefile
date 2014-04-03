CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -MMD -MP -Wall
CXXFLAGS += $(addprefix -I, ${INCLUDE_PATH})
INCLUDE_PATH = ../.. ../../vendor/bandit

.PHONY: all
all: main

.PHONY: clean
clean:
	${RM} main main.d main.o

.PHONY: rebuild
rebuild: clean all

main: main.o
	${CXX} ${LDFLAGS} -o $@ $^

-include main.d
