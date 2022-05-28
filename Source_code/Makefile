##
# DAA Assignment 234
#
# @file
# @version 0.1


all: a.exe

a.exe: PES2UG20CS401.o client.o
	gcc PES2UG20CS401.o client.o

client.o: client.c
	gcc -c client.c

PES2UG20CS401.o: PES2UG20CS401.c
	gcc -c -Wall -pedantic PES2UG20CS401.c

.PHONEY: clean

clean:
	rm client.o PES2UG20CS401.o a.exe

# end
