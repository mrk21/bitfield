CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -MMD -MP -Wall
CXXFLAGS += $(addprefix -I, ${INCLUDE_PATH})
INCLUDE_PATH = .. ../vendor/bandit

.PHONY: all
all: spec
	./spec ${args}

.PHONY: clean
clean:
	${RM} spec spec.d spec.o

.PHONY: rebuild
rebuild: clean all

spec: spec.o
	${CXX} ${LDFLAGS} -o $@ $^

-include spec.d
