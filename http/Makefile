CC = g++ -g
CFLAGS = -std=c++17
SRC_FILES = server.cpp httpStatus.cpp routerAlgorithm.cpp
OUT = server

all: $(OUT)

$(OUT): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f $(OUT)
