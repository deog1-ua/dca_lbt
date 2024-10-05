#ifndef _BUG_H_
#define _BUG_H_

using namespace std;
#include<string>
#include "usuario.h"
#include "comentario.h"
#include <vector>

class Bug{
    private:
        string id;
        Usuario creador;
        string prioridad;
        string descripcion;
        string estado;
        string fechaActualización;
        Usuario asignado;
        vector<Comentario> comentarios;

    public:
        Bug();
        Bug(string id, Usuario creador, int prioridad, string descripcion);
        string getId();
        Usuario getCreador();
        string getPrioridad();
        string getDescripcion();
        string getEstado();
        string getFechaActualización();
        Usuario getAsignado();
        void setId(string id);
        void setCreador(Usuario creador);
        void setPrioridad(string prioridad);
        void setDescripcion(string descripcion);
        void setEstado(string estado);
        void setFechaActualización(string fechaActualización);
        void setAsignado(Usuario asignado);
        bool operator==(Bug b);  
        void operator=(Bug b);
        void agregarComentario(Comentario comentario);
        void mostrarComentarios();
};

#endif