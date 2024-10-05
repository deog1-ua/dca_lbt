#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <string>
#include "usuario.h"

class Comentario {
private:
    Usuario autor;
    string contenido;
    string fechaComentario;

public:
    Comentario(Usuario autor, string contenido);
    Usuario getAutor();
    string getContenido();
    string getFechaComentario();
};

#endif
