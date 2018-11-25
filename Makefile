TEST_FILES = socIN.bmp socOUT.bmp
MESSAGE = "i love SoC"

build:
	gcc encoder.c -o encoder && echo "*** Done build ***" || exit 1;

clean: 
	rm -rf *.o encoder socOUT.bmp && echo "*** Done cleaning project dir ***" || exit 1;

test: encoder
	./encoder ${TEST_FILES} ${MESSAGE} && echo "*** Done test ***" || exit 1;