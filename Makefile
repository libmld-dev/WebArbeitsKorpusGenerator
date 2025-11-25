CXX ?= g++
CXX_FLAGS = -Wall -Wextra -Weffc++ -Werror -Wsuggest-override -Wconversion -O3 -march=native

all: preanna anna postanna

preanna: preanna.cpp
	$(CXX) $(CXX_FLAGS) preanna.cpp -o preanna

anna: anna.cpp
	$(CXX) $(CXX_FLAGS) anna.cpp -o anna

postanna: postanna.cpp
	$(CXX) $(CXX_FLAGS) postanna.cpp -o postanna

clean:
	rm -f preanna anna postanna

.PHONY: all clean