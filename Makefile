CC=gcc
CF=-c -Wall -Wextra -pedantic -std=c99
F=-Wall -Wextra -pedantic -std=c99

all: BC

force:getmain.c getnext.c infix.c infixmain.c number.c numbermain.c operations_main.c operations.c 
	$(CC) $(F) getmain.c getnext.c infix.c infixmain.c number.c numbermain.c operations_main.c operations.c -o bc

BC:getmain.o getnext.o infix.o infixmain.o number.o numbermain.o operations_main.o operations.o
	$(CC) getmain.o getnext.o infix.o infixmain.o number.o numbermain.o operations_main.o operations.o -o bc

getmain.o:getmain.c
	$(CC) $(CF) getmain.c

getnext.o:getnext.c
	$(CC) $(CF) getnext.c

infix.o: infix.c
	$(CC) $(CF) infix.c

infixmain.o: infixmain.c
	$(CC) $(CF) infixmain.c

number.o:number.c
	$(CC) $(CF) number.c

numbermain.o:numbermain.c
	$(CC) $(CF) numbermain.c

operations_main.o:operations_main.c
	$(CC) $(CF) operations_main.c

operations.o:operations.c
	$(CC) $(CF) operations.c

clean:
	rm -rf *.o bc
