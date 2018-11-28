# BMP secret message encoder

## Usage
### Clean
4 First clean repo dir
```
make clean
```
### Build
4 Second build project
```
make build
```
### Test
4 Third run test with secret message "I love SoC" and socIN.bmp + socOUT.bmp files (check Makefile)
```
cat Makefile
build:
	gcc encoder.c -o encoder && echo "*** Done build ***" || exit 1;

clean: 
	rm -rf *.o encoder socOUT.bmp && echo "*** Done cleaning project dir ***" || exit 1;

test: encoder
	./encoder ${TEST_FILES} ${MESSAGE} && echo "*** Done test ***" || exit 1;
```
#### Test
```
make test

./encoder socIN.bmp socOUT.bmp "i love SoC" && echo "*** Done test ***" || exit 1;
*-* Secret message with 615350 bytes is storing in socOUT.bmp file *-*
*-* So you have to write decoder to check this =D *-*
i love SoC
*** Done test ***
```




