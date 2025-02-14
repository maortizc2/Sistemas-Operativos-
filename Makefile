CC = g++
CFLAGS = -Wall -Wextra -std=c++11
OBJ = main.o rle.o
EXEC = rle

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o: main.cpp rle.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

rle.o: rle.cpp rle.h
	$(CC) $(CFLAGS) -c rle.cpp -o rle.o

# Reglas para comprimir, descomprimir y mostrar ayuda
c:
	@ if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "Uso: make c archivo.txt"; \
	else \
		./$(EXEC) -c $(filter-out $@,$(MAKECMDGOALS)); \
	fi

d:
	@ if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "Uso: make d archivo.rle"; \
	else \
		./$(EXEC) -x $(filter-out $@,$(MAKECMDGOALS)); \
	fi

h:
	./$(EXEC) -h

clean:
	rm -f $(OBJ) $(EXEC) *.rle Descomprimido*

# Permite pasar argumentos después del comando
%:
	@: