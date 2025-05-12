TARGET = cstat
CC = gcc
FLAGS = -Wall
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

clean: 
	rm -f $(OBJ) $(TARGET)

