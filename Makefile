
source = fancy_buffer.c memory.c string.c vector.c
flags = -Wall -Wextra -g
headers = $(wildcard *.h)
test_run = test_run.o
objects = $(source:.c=.o)
library_name = why_lib.a
test_run_name = test_run

all: test

%.o : %.c $(headers)
	gcc $(flags) -c $^

test: $(objects) $(test_run) $(headers)
	gcc $(flags) $(objects) $(test_run) -o $(test_run_name)

build: $(objects) $(headers)
	ar rcs $(library_name) $(objects)

clean:
	rm -f *.o

fclean:
	make clean
	rm -f $(test_run_name)
	rm -f $(library_name)

re:
	make fclean
	make all