CC=clang

DEPS = src/terminalutils.h src/fileutils.h src/texteditor.h src/logger/logger.h src/inputhandler.h
OBJ = src/main.o src/terminalutils.o src/fileutils.o src/texteditor.o src/logger/logger.o src/inputhandler.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

ced: $(OBJ)
	$(CC) -o $@ $^