OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
v.out : $(OBJ)
	gcc -o $@ $^
delete :
	rm *.o *.out
