# Nombre del ejecutable
TARGET = programa

# Archivos fuente
SRCS = main.c errors.c

# Archivos objeto (se generan a partir de los .c)
OBJS = $(SRCS:.c=.o)

# Compilador y flags
CC = gcc
CFLAGS = -Wall -g

# Regla por defecto
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar .c a .o
%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f *.o $(TARGET)