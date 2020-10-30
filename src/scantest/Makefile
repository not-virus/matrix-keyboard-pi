ioif.o: ioif.c ioif.h
	gcc -DLEDS_COM_ANODE -o ioif.o -c ioif.c
	#gcc $(CFLAGS) -o ioif.o -c ioif.c

usbif.o: usbif.c usbif.h
	gcc -o usbif.o -c usbif.c

scanner.o: scanner.c
	gcc -o scanner.o -c scanner.c

scanner: ioif.o usbif.o scanner.o keymap.h connections.h
	gcc -o scanner ioif.o usbif.o scanner.o -l wiringPi

clean:
	rm *.o scanner
