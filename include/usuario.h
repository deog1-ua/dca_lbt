#ifndef _USUARIO_H_
#define _USUARIO_H_

using namespace std;
#include<string>

class Usuario{
    private:
        string nombre;
        string correo;
        string contrasena;
        string tipoUsuario;

    public:
        Usuario();
        Usuario(string correo, string contrasena, string tipoUsuario);
        string getNombre();
        string getCorreo();
        string getContrasena();
        string getTipoUsuario();
        bool operator==(Usuario u) ;     
};

#endif