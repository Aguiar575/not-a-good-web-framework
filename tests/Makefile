CXX := g++
CXXFLAGS := -std=c++11 -Wall
TARGET := test_program
SRCS := http/notATestFrameworkTests.cpp

MAKEFLAGS += --silent

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$(TARGET)
	rm -f $(TARGET)

