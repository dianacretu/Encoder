build: encoder.o
	gcc -Wall encoder.o -o encoder -lm

encoder.o: encoder.c
	gcc -c encoder.c 

run: encoder
	./encoder

clean:
	rm -f *.o
