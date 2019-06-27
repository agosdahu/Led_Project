CC=gcc
PATHC=./ledProject/
CFLAGS=-I$(PATHC)
SRC=$(wildcard $(PATHC)*.c)
OBJ=$(foreach var, $(SRC), $(var:.c=.o))

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

ledproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -nostartfiles
  
clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info
