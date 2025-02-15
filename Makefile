CC=clang
CFLAGS= -lm -lncurses

DEPS = src/fileutils.h src/texteditor.h src/logger/logger.h src/inputhandler.h src/selectedtext.h
OBJ = src/main.o src/fileutils.o src/texteditor.o src/logger/logger.o src/inputhandler.o src/selectedtext.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

ced: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)