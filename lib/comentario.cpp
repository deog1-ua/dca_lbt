// Comentario.cpp
#include "comentario.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Comentario::Comentario(Usuario autor, std::string contenido) {
    this->autor = autor;
    this->contenido = contenido;

    // Obtener la fecha actual del sistema
    time_t now = time(0);  
    tm *ltm = localtime(&now); 

    // Formatear la fecha
    std::ostringstream oss;
    oss << std::put_time(ltm, "%d-%m-%Y %H:%M:%S");  // Fecha y hora
    this->fechaComentario = oss.str();
}

Usuario Comentario::getAutor() {
    return this->autor;
}

std::string Comentario::getContenido() {
    return this->contenido;
}

std::string Comentario::getFechaComentario() {
    return this->fechaComentario;
}
