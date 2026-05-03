CC = gcc
CFLAGS = -Wall -Wextra

TARGET = file_system

OBJS = main.o file_manager.o search.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c file_manager.h
	$(CC) $(CFLAGS) -c main.c

file_manager.o: file_manager.c file_manager.h
	$(CC) $(CFLAGS) -c file_manager.c

search.o: search.c file_manager.h
	$(CC) $(CFLAGS) -c search.c

clean:
	rm -f *.o $(TARGET)