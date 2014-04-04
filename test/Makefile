CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -MMD -MP -Wall
CXXFLAGS += $(addprefix -I, ${INCLUDE_PATH})
INCLUDE_PATH = .. ../vendor/bandit
TARGET = spec_main
SRCS = ${TARGET} $(basename $(shell find spec -name '*_spec.cpp'))


.PHONY: all
all: ${TARGET}
	./$< ${args}

.PHONY: clean
clean:
	${RM} ${TARGET} $(addsuffix .d, ${SRCS}) $(addsuffix .o, ${SRCS})

.PHONY: rebuild
rebuild: clean all

${TARGET}: $(addsuffix .o, ${SRCS})
	${CXX} ${LDFLAGS} -o $@ $^

-include $(addsuffix .d, ${SRCS})
