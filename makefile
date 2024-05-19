CC=gcc
CFLAGS=-Wall -I src
LDFLAGS=-ll -lfl
EXEC=tpcc
SRC=src
BIN=bin
OBJ=obj
ASM=nasm
ANONYMOUS=assembly

all: $(BIN)/$(EXEC)

asm: $(BIN)/$(ANONYMOUS)

bin:
	mkdir -p bin

obj:
	mkdir -p obj


$(BIN)/$(EXEC): $(OBJ)/tree.o $(OBJ)/$(EXEC).o $(OBJ)/$(EXEC).yy.o $(OBJ)/compile.o $(OBJ)/parse.o $(OBJ)/semantic.o $(OBJ)/main.o | bin
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)/main.o: $(SRC)/main.c $(SRC)/compile.h | obj
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/$(EXEC).o: $(OBJ)/$(EXEC).c $(OBJ)/$(EXEC).h $(OBJ)/$(EXEC).tab.h | obj
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/$(EXEC).yy.o: $(OBJ)/$(EXEC).yy.c $(OBJ)/$(EXEC).h | obj
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/$(EXEC).c $(OBJ)/$(EXEC).h $(OBJ)/$(EXEC).tab.h: $(SRC)/$(EXEC).y | obj
	bison -d -o $(OBJ)/$(EXEC).c $(SRC)/$(EXEC).y

$(OBJ)/$(EXEC).yy.c: $(SRC)/$(EXEC).lex | obj
	flex -o $@ $(SRC)/$(EXEC).lex

$(OBJ)/tree.o: $(SRC)/tree.c $(SRC)/tree.h | obj
	$(CC) -o $@ -c $< $(CFLAGS)

$(BIN)/$(ANONYMOUS): $(OBJ)/getchar.o $(OBJ)/putchar.o $(OBJ)/putint.o $(OBJ)/getint.o $(OBJ)/_anonymous.o $(OBJ)/utils.o
	gcc -o $@ $^ -nostartfiles -no-pie

$(OBJ)/%.o: %.asm | obj
	$(ASM) -f elf64 -o $@ $<

$(OBJ)/_anonymous.o: _anonymous.asm | obj
	$(ASM) -f elf64 -o $@ $<

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h | obj
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f bin/*
	rm -f obj/*
	rm -f _anonymous.asm