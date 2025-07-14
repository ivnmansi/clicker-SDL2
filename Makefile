CXX=g++
CXXFLAGS= -MMD -Wall -Wextra -pedantic -std=c++17 -O2
INCLUDES=-Iinclude -IC:/msys64/ucrt64/include/SDL2
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:src/%.cpp=obj/%.o)
DEP=$(OBJ:.o=.d)
EXE=game.exe

all: $(EXE)

folders:
	if not exist obj mkdir obj
	if not exist inc mkdir inc
	if not exist src mkdir src

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(EXE): $(OBJ)
	$(CXX) -o $@ $^ -LC:/msys64/ucrt64/lib $(LIBS)

-include $(DEP)

clean:
	del /Q obj\*.o obj\*.d $(EXE) 2>nul || true

run: $(EXE)
	.\$(EXE)

.PHONY: all folders clean run


