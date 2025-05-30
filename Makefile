CC = gcc
CFLAGS = -Wall -Wextra

TARGET = hospital
SRCS = main.c doctor.c appointment.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c hospital.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del *.o $(TARGET).exe

.PHONY: clean