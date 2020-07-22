
source = fancy_buffer.c memory.c string.c
#source = buffer.c fancy_buffer.c memory.c string.c
flags = -Wall -Wextra -g
header = $(wildcard *.h)
test_run = test_run.o
objects = $(source:.c=.o)

all: test

%.o : %.c $(header)
	gcc $(flags) -c $^

test: $(objects) $(test_run) $(header)
	gcc $(flags) $(objects) $(test_run) -o test_run

clean:
	rm -f *.o

fclean:
	make clean
	rm -f test_run

re:
	make fclean
	make all