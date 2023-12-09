CXX = g++
CXXFLAGS = -std=c++17
TARGET = notATestFramework
SOURCE = notATestFramework.cpp

.PHONY: all run clean

all: $(TARGET) run clean

$(TARGET): $(SOURCE)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
	@rm -rf build

