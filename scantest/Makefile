scankeys.o: scankeys.c
	gcc -o scankeys.o -c scankeys.c

scan_test.o: scan_test.c
	gcc -o scan_test.o -c scan_test.c

scan_test: scankeys.o scan_test.o
	gcc -o scan_test scankeys.o scan_test.o -l wiringPi

clean:
	rm *.o scan_test
