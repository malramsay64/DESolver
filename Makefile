CXX=g++
CXXFLAGS= -Ofast -std=c++11
LDFLAGS= -lm

LIB=lib
MODULES=$(wildcard $(LIB)/*.cpp)
MODULES:=$(MODULES:.cpp=.o)
MODULES:=$(notdir $(MODULES))
BIN_PATH=bin


%.o : $(LIB)/%.cpp | $(BIN_PATH)
	@echo CC $@
	$(CXX) $(CXXFLAGS) -c $< -o $(BIN_PATH)/$@

program: $(MODULES) $(HEADERS)
	@echo CC $@
	@$(CXX) -o program $(addprefix $(BIN_PATH)/, $(MODULES)) $(CXXFLAGS) $(LDFLAGS)

$(BIN_PATH):
	mkdir -p $(BIN_PATH)

