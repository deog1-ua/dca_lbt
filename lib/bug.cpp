#include<iostream>
#include <ctime>
#include <iomanip> // Para std::put_time
#include <sstream> // Para std::ostringstream
#include "bug.h"

using namespace std;

Bug::Bug(){
    this->id = "";
    this->creador = Usuario();
    this->prioridad = "";
    this->descripcion = "";
    this->estado = "nuevo";
    this->fechaActualización = "";
    this->asignado = Usuario();
}

Bug::Bug(string id, Usuario creador, int prioridad, string descripcion){
    this->id = id;
    this->creador = creador;
    if(prioridad == 1){
        this->prioridad = "Importante";
    }
    else if(prioridad == 2){
        this->prioridad = "Normal";
    }
    else if(prioridad == 3){
        this->prioridad = "Menor";
    }
    else{
        this->prioridad = "Peticion";
    }

    this->descripcion = descripcion;
    this->estado = "nuevo";
        // Obtener la fecha actual del sistema
    time_t now = time(0);  // Obtener el tiempo actual
    tm *ltm = localtime(&now);  // Convertir a tiempo local

    // Formatear la fecha como "dd-mm-aaaa"
    ostringstream oss;
    oss << put_time(ltm, "%d-%m-%Y");  // Formato de fecha
    this->fechaActualización = oss.str();   // Asignar la fecha formateada
    this->asignado = Usuario();
}
string Bug::getId(){
    return this->id;
}
Usuario Bug::getCreador(){
    return this->creador;
}
string Bug::getPrioridad(){
    return this->prioridad;
}
string Bug::getDescripcion(){
    return this->descripcion;
}
string Bug::getEstado(){
    return this->estado;    
}
string Bug::getFechaActualización(){
    return this->fechaActualización;
}
Usuario Bug::getAsignado(){
    return this->asignado;
}
void Bug::setId(string id){
    this->id = id;
}
void Bug::setCreador(Usuario creador){
    this->creador = creador;
}
void Bug::setPrioridad(string prioridad){
    this->prioridad = prioridad;
}
void Bug::setDescripcion(string descripcion){
    this->descripcion = descripcion;
}
void Bug::setEstado(string estado){
    this->estado = estado;
}
void Bug::setFechaActualización(string fechaActualización){
    this->fechaActualización = fechaActualización;
}
void Bug::setAsignado(Usuario asignado){
    this->asignado = asignado;
}
bool Bug::operator==(Bug b){
    return this->id == b.getId();
}
void Bug::operator=(Bug b){
    this->id = b.getId();
    this->creador = b.getCreador();
    this->prioridad = b.getPrioridad();
    this->descripcion = b.getDescripcion();
    this->estado = b.getEstado();
    this->fechaActualización = b.getFechaActualización();
    this->asignado = b.getAsignado();
}

void Bug::agregarComentario(Comentario comentario) {
    comentarios.push_back(comentario);
}

void Bug::mostrarComentarios() {
    if (comentarios.empty()) {
        std::cout << "Este bug no tiene comentarios aún." << std::endl;
    } else {
        std::cout << "Comentarios del bug:" << std::endl;
        for (auto &comentario : comentarios) {
            std::cout << "Autor: " << comentario.getAutor().getNombre() << std::endl;
            std::cout << "Fecha: " << comentario.getFechaComentario() << std::endl;
            std::cout << "Comentario: " << comentario.getContenido() << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }
}
