Botball: t1.o
	gcc -o Botball t1.o; rm *.o
	
t1.o:t1.c
	gcc -c -o t1.o t1.c

clean:
	rm *.o Botball