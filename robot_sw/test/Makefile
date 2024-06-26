# cls; make; ./test.exe

# Global configs
CXX       = g++
CFLAGS    = -Wall -O3

# Libraries
EXT_LIB   = 
EXT_INC   = 

SRC = main.cpp
OUT = test.exe

all: $(SRC)
	$(CXX) $(CFLAGS) $(SRC) -o $(OUT)
	@echo Done. Run using: "./test.exe"

#	$(CXX) $(CFLAGS) $(SRC) $(EXT_LIB) -I $(EXT_INC) -o $(OUT) -fopenmp
#	@echo Done. Run using: "test.exe
