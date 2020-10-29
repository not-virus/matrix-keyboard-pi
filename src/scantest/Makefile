ioif.o: ioif.c
	gcc $(CFLAGS) -o ioif.o -c ioif.c

scanner.o: scanner.c
	gcc -o scanner.o -c scanner.c

scanner: ioif.o scanner.o
	gcc -o scanner ioif.o scanner.o -l wiringPi

clean:
	rm *.o scanner
