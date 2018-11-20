TEST_FILES = socIN.bmp socOUT.bmp
MESSAGE = "i love SoC"

all: build test clean

build:
	gcc encoder.c -o encoder

clean: 
	rm -rf *.o encoder

test: encoder
	./encoder ${TEST_FILES} ${MESSAGE}