CC=cc
CXX=g++
FLAGS=-g -Wall -Wextra
CFLAGS=$(FLAGS) -std=gnu11
CXXFLAGS=$(FLAGS) -std=gnu++11
LIBS=-pthread
LINTFILTERS=$\
	-build/c++11,$\
	-build/header_guard,$\
	-build/include_subdir,$\
	-readability/casting,$\
	-runtime/references

APPNAME:=$(shell basename $(shell pwd))
APPARGS=8081 300 700
HEADERS:=$(wildcard src/*.hpp src/network/*.hpp src/http/*.hpp src/models/*.hpp src/factorization_app/*.hpp src/common/Thread.hpp src/common/Semaphore.hpp)
SOURCES:=$(wildcard src/*.cpp src/network/*.cpp src/http/*.cpp src/models/*.cpp src/factorization_app/*.cpp src/common/Thread.cpp src/common/Semaphore.cpp)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)
INCLUDES=-Isrc -Isrc/common -Isrc/network -Isrc/http -Isrc/models -Isrc/factorization_app

.SECONDEXPANSION:

bin/$(APPNAME): $(OBJECTS) | $$(@D)/.
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

build/%.o: src/%.cpp $(HEADERS) | $$(@D)/.
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

.PRECIOUS: %/.
%/.:
	mkdir -p $(dir $@)

all: bin/$(APPNAME) lint memcheck helgrind

.PHONY: lint
lint:
	cpplint --filter=$(LINTFILTERS) $(HEADERS) $(SOURCES)

.PHONY: memcheck
memcheck:
	valgrind --tool=memcheck bin/$(APPNAME) $(APPARGS)

.PHONY: helgrind
helgrind:
	valgrind --quiet --tool=helgrind bin/$(APPNAME) $(APPARGS)

.PHONY: gitignore
gitignore:
	echo bin > .gitignore
	echo build >> .gitignore

.PHONY: clean
clean:
	rm -rf bin build
