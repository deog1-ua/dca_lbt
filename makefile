# Nombre del compilador
CXX = g++

CXXFLAGS = -Wall -std=c++11 -Iinclude

OBJS = main.o bug.o usuario.o comentario.o

TARGET = bugtracker

$(TARGET): $(OBJS)
	# Enlaza los objetos para crear el ejecutable
	$(CXX) -o $(TARGET) $(OBJS)

main.o: src/main.cpp include/bug.h include/usuario.h include/comentario.h
	# Compila el archivo main.cpp en main.o
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

usuario.o: lib/usuario.cpp include/usuario.h
	# Compila el archivo usuario.cpp en usuario.o
	$(CXX) $(CXXFLAGS) -c lib/usuario.cpp -o usuario.o

bug.o: lib/bug.cpp include/bug.h include/usuario.h
	# Compila el archivo bug.cpp en bug.o
	$(CXX) $(CXXFLAGS) -c lib/bug.cpp -o bug.o

comentario.o: lib/comentario.cpp include/comentario.h include/bug.h include/usuario.h
	# Compila el archivo comentario.cpp en comentario.o
	$(CXX) $(CXXFLAGS) -c lib/comentario.cpp -o comentario.o

clean:
	# Borra los archivos objeto (.o) y el ejecutable
	rm -f $(OBJS) $(TARGET)

tar:
	# Crea un archivo tar.gz con el nombre dca-lbt.tgz
	tar -czvf dca-lbt.tgz src/ lib/ include/ Makefile aclaraciones.txt
