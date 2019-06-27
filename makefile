CC=gcc -std=c99
PATHC=./ledProject/
CFLAGS=-I$(PATHC)
SRC=$(wildcard $(PATHC)*.c)
OBJ=$(foreach var, $(SRC), $(var:.c=.o))

.PHONY:clean

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

ledproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -nostartfiles
  
clean :
	rm  $(PATHC)*.o $(PATHC)*.exe
