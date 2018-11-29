build:
	gcc encoder.c -o encoder && echo "*** Done build encoder ***\n" || exit 1;
	gcc decoder.c -o decoder && echo "*** Done build decoder ***\n" || exit 1;

clean: 
	rm -rf *.o encoder decoder socOUT.bmp && echo "*** Done cleaning project dir ***\n" || exit 1;

test: encoder decoder
	./encoder ${bmp_in} ${bmp_out} ${secretMsg} && echo "*** Done test encoder ***\n" || exit 1;
	./decoder ${bmp_out} && echo "*** Done test decoder ***\n" || exit 1;