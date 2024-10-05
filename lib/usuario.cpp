#include<iostream>
#include "usuario.h"

using namespace std;

Usuario::Usuario(){
    this->nombre = "";
    this->correo = "";
    this->contrasena = "";
    this->tipoUsuario = "";
}
Usuario::Usuario(string correo, string contrasena, string tipoUsuario){
    size_t pos = correo.find('@');
    if (pos != std::string::npos) {
        this->nombre = correo.substr(0, pos);
    } else {
        this->nombre = "Usuario";
    }
    this->correo = correo;
    this->contrasena = contrasena;
    this->tipoUsuario = tipoUsuario;
}

string Usuario::getNombre(){
    return this->nombre;
}
string Usuario::getCorreo(){
    return this->correo;
}
string Usuario::getContrasena(){
    return this->contrasena;
}
string Usuario::getTipoUsuario(){
    return this->tipoUsuario;
} 

bool Usuario::operator==(Usuario u){
    return this->correo == u.getCorreo() && this->contrasena == u.getContrasena();
}