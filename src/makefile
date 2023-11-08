OPTIMIZATION_LEVELS := O3 O2 O1
DEFAULT_OPTIMIZATION_LEVEL := O3

$(info Prieinami optimizacijos lygiai: $(OPTIMIZATION_LEVELS))

ifdef OPT
ifeq ($(filter $(OPT),$(OPTIMIZATION_LEVELS)),)
$(error Neinkamas optimizacijos lygis: $(OPT))
endif
OPTIMIZATION_LEVEL := $(OPT)
else
OPTIMIZATION_LEVEL := $(DEFAULT_OPTIMIZATION_LEVEL)
endif

CXXFLAGS := -$(OPTIMIZATION_LEVEL)

main: functions.o hashFunction.o
	g++ $(CXXFLAGS) -fopenmp -o program main.cpp functions.o hashFunction.o

functions.o: functions.cpp
	g++ $(CXXFLAGS) -c functions.cpp

hashFunction.o: hashFunction.cpp
	g++ $(CXXFLAGS) -c hashFunction.cpp

clean:
	del -f *.o *.exe

cleanBlocks:
	del /S /Q ..\blocks\*