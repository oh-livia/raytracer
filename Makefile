raytra:
	g++ -O2 *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

debug:
	g++ -g *.cc -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o debug

.PHONY clean:
clean:
	rm -f *.o *~ raytra debug
