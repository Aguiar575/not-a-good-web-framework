CC = g++
CFLAGS = -std=c++11
SRC_FILES = server.cpp httpStatus.cpp
OUT = server

all: $(OUT)

$(OUT): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f $(OUT)
