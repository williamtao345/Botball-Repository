Botball: t3.o
	gcc -o Botball t3.o; rm *.o
	
t3.o:t3.c
	gcc -c -o t3.o t3.c

clean:
	rm *.o Botball