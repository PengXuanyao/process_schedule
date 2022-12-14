# objects = main.o pro_sch.o
# 
# run : $(objects)
# 	cc -o run $(objects)
# 
# main.o : pro_sch.h
# pro_sch.o : pro_sch.h
# 
# .phony : clean
# clean :
# 	rm run $(objects)

DIR_INC = ./inc
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ)  -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {}
