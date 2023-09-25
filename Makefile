PROJECT_DIR=.

CFLAGS=-I${PROJECT_DIR}/include/
CC=gcc
CXX=g++
LDFLAGS=

# Using OpenCV for Visualization
OPENCV=0
OPENCV4=0

ifeq ($(OPENCV), 1)
	ifeq ($(OPENCV4), 0)
		LDFLAGS+=  `pkg-config --libs opencv`
		CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv`
	else
		LDFLAGS+= -std=c++11 `pkg-config --libs opencv4`
		CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv4`
	endif
endif

SRC_DIR=${PROJECT_DIR}/src


all: run

compile: main

run: compile
	./bin/main

main: ${SRC_DIR}/linked_list.cpp ${SRC_DIR}/graph.cpp ${SRC_DIR}/stack.cpp ${SRC_DIR}/main.cpp
	${CXX} ${CFLAGS} $^ ${LDFLAGS} -o bin/$@ 


