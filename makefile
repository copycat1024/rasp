OBJ = main.o sound.o screen.o
APPNAME = wave.a

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm

%.o : %.c
	gcc -c -o $@ $< -std=c99

clean :
	rm $(OBJ) $(APPNAME) sound.tar *.wav

archive :
	tar cf sound.tar *.c *.h makefile

send :
	scp sound.tar e1601116@shell.puv.fi:.
