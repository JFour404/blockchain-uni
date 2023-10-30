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

main: functions.o
	g++ $(CXXFLAGS) -o program main.cpp functions.o

functions.o: functions.cpp
	g++ $(CXXFLAGS) -c functions.cpp

clean:
	del -f *.o *.exe