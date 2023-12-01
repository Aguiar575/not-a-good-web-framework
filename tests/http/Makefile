CXX := g++
CXXFLAGS := -std=c++11 -Wall
TARGET := test_program
SRCS := notATestFrameworkTests.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)

