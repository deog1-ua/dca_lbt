#include <iostream>
#include "usuario.h"
#include "bug.h"
#include <vector>
#include <ctime>
#include <iomanip> // Para std::put_time
#include <sstream> // Para std::ostringstream
#include "comentario.h"

using namespace std;

void imprimeMenu(Usuario *u)
{
    if (u == nullptr)
    {
        cout << "1. Nuevo Bug/Issue" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Entrar/registrarse" << endl;
        cout << "4. Salir" << endl;
    }
    else if (u->getTipoUsuario() == "cliente")
    {
        cout << "1. Nuevo Bug/Issue" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Cerrar sesion" << endl;
        cout << "4. Salir" << endl;
    }
    else
    {
        cout << "1. Bugs/Issues" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Dar de alta Administrador" << endl;
        cout << "4. Salir" << endl;
    }
}

void imprimeMenuAdmin()
{
    cout << "1. Cambiar estado" << endl;
    cout << "2. Asignar Desarrollador" << endl;
    cout << "3. Añadir Comentario" << endl;
    cout << "4. Salir" << endl;
}

void usuariosIni(vector<Usuario> &usuarios)
{
    Usuario u1("dani@gmail.com", "1234", "admin");
    Usuario u2("pepe@gmail.com", "1234", "admin");
    Usuario u3("juan@gmail.com", "1234", "cliente");
    Usuario u4("luis@gmail.com", "1234", "cliente");

    usuarios.push_back(u1);
    usuarios.push_back(u2);
    usuarios.push_back(u3);
    usuarios.push_back(u4);
};

// Función auxiliar para eliminar espacios en blanco alrededor de una cadena
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos)
    {
        return ""; // En caso de que la cadena solo contenga espacios
    }
    return str.substr(first, last - first + 1);
}

bool nuevoUsuario(vector<Usuario> &usuarios, string correo, string contrasena, Usuario *&u)
{
    // Elimina espacios en blanco en el correo
    correo = trim(correo);

    bool existe = false;

    for (auto &usuario : usuarios)
    {
        // También elimina espacios del correo almacenado antes de comparar
        if (trim(usuario.getCorreo()) == correo)
        {
            existe = true;
            if (usuario.getContrasena() == contrasena)
            {
                cout << "Bienvenido, " << usuario.getNombre() << endl;
                u = &usuario;
                return true;
            }
            else
            {
                cout << "Contraseña incorrecta." << endl;
                return false;
            }
        }
    }

    if (!existe)
    {
        Usuario nuevoUsuario(correo, contrasena, "cliente");
        usuarios.push_back(nuevoUsuario);
        cout << "Usuario creado exitosamente. Bienvenido, " << nuevoUsuario.getNombre() << endl;
        u = &usuarios.back();
        return true;
    }

    return false;
}

bool nuevoAdmin(vector<Usuario> &usuarios, string correo, string contrasena)
{
    // Elimina espacios en blanco en el correo
    correo = trim(correo);

    bool existe = false;

    for (auto &usuario : usuarios)
    {
        // También elimina espacios del correo almacenado antes de comparar
        if (trim(usuario.getCorreo()) == correo)
        {
            existe = true;
            cout << "El correo ya está registrado." << endl;
        }
    }

    if (!existe)
    {
        Usuario nuevoUsuario(correo, contrasena, "admin");
        usuarios.push_back(nuevoUsuario);
        cout << "Administrador creado exitosamente." << endl;
        return true;
    }

    return false;
}

bool nuevaIssue(vector<Bug> &bugs, string descripcion, Usuario *creador)
{
    int prioridad;

    if (creador == nullptr)
    {
        cout << "Debe estar autenticado para crear un nuevo bug." << endl;
        return false;
    }

    do
    {
        cout << "Elija una prioridad para el bug:" << endl;
        cout << "1. Importante" << endl;
        cout << "2. Normal" << endl;
        cout << "3. Menor" << endl;
        cout << "4. Petición" << endl;
        cin >> prioridad;
        cout << "************************************" << endl;

        if (prioridad < 1 || prioridad > 4)
        {
            cout << "Opción inválida. Por favor, elija un valor entre 1 y 4." << endl;
        }
    } while (prioridad < 1 || prioridad > 4);

    string id = to_string(bugs.size() + 1);
    string estadoInicial = "Abierto";

    Bug nuevoBug(id, *creador, prioridad, descripcion);
    nuevoBug.setEstado(estadoInicial);
    bugs.push_back(nuevoBug);

    return true;
}

Bug *buscarBugPorId(vector<Bug> &bugs, const string &id)
{
    for (auto &bug : bugs)
    {
        if (bug.getId() == id)
        {
            return &bug; 
        }
    }
    return nullptr; 
}

void cambiarEstado(Bug *bug)
{
    int nuevoEstado;

    if (bug != nullptr)
    {
        cout << "Elija un nuevo estado para el bug:" << endl;
        cout << "1. Asignado" << endl;
        cout << "2. En progreso" << endl;
        cout << "3. Reabierto" << endl;
        cout << "4. Resuelto" << endl;
        cout << "5. Cerrado" << endl;
        cin >> nuevoEstado;

        if (nuevoEstado == 1)
        {
            bug->setEstado("Asignado");
        }
        else if (nuevoEstado == 2)
        {
            bug->setEstado("En progreso");
        }
        else if (nuevoEstado == 3)
        {
            bug->setEstado("Reabierto");
        }
        else if (nuevoEstado == 4)
        {
            bug->setEstado("Resuelto");
        }
        else if (nuevoEstado == 5)
        {
            bug->setEstado("Cerrado");
        }

        cout << "El estado del bug con ID " << bug->getId() << " ha sido cambiado a " << bug->getEstado() << endl;
    }
}

void imprimirBug(Bug *bug)
{
    if (bug != nullptr)
    {
        cout << left << setw(10) << "ID"
             << left << setw(20) << "Usuario"
             << left << setw(15) << "Prioridad"
             << left << setw(10) << "Estado"
             << left << setw(20) << "Fecha"
             << left << setw(20) << "Desarrollador Asignado"
             << endl;

        cout << left << setw(10) << bug->getId()
             << left << setw(20) << bug->getCreador().getNombre()
             << left << setw(15) << bug->getPrioridad()
             << left << setw(10) << bug->getEstado()
             << left << setw(20) << bug->getFechaActualización()
             << left << setw(20) << bug->getAsignado().getNombre()
             << endl;
    }
    else
    {
        cout << "Bug no encontrado." << endl;
    }
}

void asignarDesarrollador(Bug *bug, Usuario *desarrollador)
{
    if (bug != nullptr && desarrollador != nullptr)
    {
        bug->setAsignado(*desarrollador);
        cout << "El bug con ID " << bug->getId() << " ha sido asignado a " << desarrollador->getNombre() << endl;
    }
    else
    {
        cout << "Bug o desarrollador no encontrado." << endl;
    }
}

void listarAdmins(vector<Usuario> &usuarios)
{
    cout << left << setw(15) << "Nombre" 
         << left << setw(30) << "Correo" << endl;
    cout << string(45, '-') << endl;  // Línea divisoria

    for (auto &usuario : usuarios)
    {
        if (usuario.getTipoUsuario() == "admin")
        {
            cout << left << setw(15) << usuario.getNombre() 
                 << left << setw(30) << usuario.getCorreo() << endl;
        }
    }
}

Usuario* buscaAdmin(vector<Usuario> &usuarios, string correo)
{
    for (auto &usuario : usuarios)
    {
        if (usuario.getCorreo() == correo && usuario.getTipoUsuario() == "admin")
        {
            return  &usuario;
        }
    }

    cout << "No se encontró un administrador con ese correo." << endl;
    return nullptr;
}

int main(void)
{
    int opcion;
    vector<Usuario> usuarios;
    vector<Bug> bugs;

    cout << "Bienvenido a BugTracker" << endl;
    usuariosIni(usuarios);
    Usuario *u = nullptr;
    string descripcion;
    string id;

    while (opcion != 4)
    {
        imprimeMenu(u);
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            if (u == nullptr)
            {
                string correo, contrasena;
                cout << "Ingrese su correo: " << endl;
                cin >> correo;
                bool autenticado = false;

                while (!autenticado)
                {
                    cout << "Ingrese su contraseña: " << endl;
                    cin >> contrasena;
                    autenticado = nuevoUsuario(usuarios, correo, contrasena, u);

                    if (!autenticado)
                    {
                        cout << "Contraseña incorrecta. ¿Desea intentar de nuevo? (s/n): ";
                        char respuesta;
                        cin >> respuesta;
                        if (respuesta == 'n' || respuesta == 'N')
                        {
                            break;
                        }
                    }
                }
            }
            if (u != nullptr && u->getTipoUsuario() == "cliente")
            {
                cout << "Ingrese la descripción del bug:" << endl;
                cin.ignore();
                getline(cin, descripcion);
                nuevaIssue(bugs, descripcion, u);

                cout << "Se ha registrado un nuevo bug: " << endl;
                cout << "Tu bug tiene el ID: " << bugs.back().getId() << endl;
                cout << "La prioridad es: " << bugs.back().getPrioridad() << endl;
                cout << "El estado actual es: " << bugs.back().getEstado() << endl;
                cout << "La fecha de actualización es: " << bugs.back().getFechaActualización() << endl;
                cout << "El desarrollador asignado es: " << bugs.back().getAsignado().getNombre() << endl;
                cout << "********************************************" << endl;
                break;
            }
            if (u != nullptr && u->getTipoUsuario() == "admin")
            {
                cout << "Bugs/Issues" << endl;
                cout << left << setw(10) << "ID"
                     << left << setw(20) << "Usuario"
                     << left << setw(15) << "Prioridad"
                     << left << setw(10) << "Estado"
                     << left << setw(20) << "Fecha"
                     << left << setw(20) << "Desarrollador Asignado"
                     << endl;

                for (auto &bug : bugs)
                {
                    cout << left << setw(10) << bug.getId()
                         << left << setw(20) << bug.getCreador().getNombre()
                         << left << setw(15) << bug.getPrioridad()
                         << left << setw(10) << bug.getEstado()
                         << left << setw(20) << bug.getFechaActualización()
                         << left << setw(20) << bug.getAsignado().getNombre()
                         << endl;
                }
                cout << "********************************************" << endl;
                imprimeMenuAdmin();
                cin >> opcion;
                switch (opcion)
                {
                case 1:
                {
                    cout << "Introduzca el ID del bug que desea cambiar de estado: " << endl;
                    cin >> id;
                    Bug *bugEncontrado = buscarBugPorId(bugs, id);
                    if (bugEncontrado != nullptr)
                    {
                        cambiarEstado(bugEncontrado);
                    }
                    else
                    {
                        cout << "Bug no encontrado." << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "Introduzca el ID del bug que desea asignar a un desarrollador: " << endl;
                    cin >> id;
                    Bug *bugEncontrado2 = buscarBugPorId(bugs, id);
                    if (bugEncontrado2 != nullptr)
                    {
                        listarAdmins(usuarios);
                        cout << "Introduzca el correo del desarrollador: " << endl;
                        string correoDesarrollador;
                        cin >> correoDesarrollador;
                        Usuario *desarrollador = buscaAdmin(usuarios, correoDesarrollador);
                        asignarDesarrollador(bugEncontrado2, desarrollador);
                    }
                    else
                    {
                        cout << "Bug no encontrado." << endl;
                    }
                    break;
                }
                case 3:
                {
                    cout << "Introduzca el ID del bug al que desea añadir un comentario: " << endl;
                    cin >> id;
                    Bug *bugEncontrado3 = buscarBugPorId(bugs, id);
                    if (bugEncontrado3 != nullptr)
                    {
                        cout << "Introduzca el comentario: " << endl;
                        string contenido;
                        cin.ignore();
                        getline(cin, contenido);
                        Comentario nuevoComentario(*u, contenido);
                        bugEncontrado3->agregarComentario(nuevoComentario);
                    }
                    else
                    {
                        cout << "Bug no encontrado." << endl;
                    }
                    break;
                }
                }
            }
            break;

        case 2:
        {
            cout << "Introduzca el ID del bug que desea buscar: " << endl;
            cin >> id;
            cout << "********************************************" << endl;
            Bug *bugEncontrado = buscarBugPorId(bugs, id);
            imprimirBug(bugEncontrado);
            bugEncontrado->mostrarComentarios();
            cout << "********************************************" << endl;
            if (u != nullptr)
            {
                cout << "¿Desea añadir un comentario? (s/n): ";
                char respuesta;
                cin >> respuesta;
                if (respuesta == 's' || respuesta == 'S')
                {
                    cout << "Introduzca el comentario: " << endl;
                    string contenido;
                    cin.ignore();
                    getline(cin, contenido);
                    Comentario nuevoComentario(*u, contenido);
                    bugEncontrado->agregarComentario(nuevoComentario);
                }
            }
            break;
        }

        case 3:
            if (u != nullptr && u->getTipoUsuario() == "cliente")
            {
                cout << "Cerrando sesión..." << endl;
                u = nullptr;
            }
            else if (u != nullptr && u->getTipoUsuario() == "admin")
            {
                cout << "Ingrese el correo del nuevo administrador: " << endl;
                string correo;
                cin >> correo;
                cout << "Ingrese la contraseña del nuevo administrador: " << endl;
                string contrasena;
                cin >> contrasena;
                nuevoAdmin(usuarios, correo, contrasena);
            }
            else
            {
                cout << "Ingrese su correo: " << endl;
                string correo;
                cin >> correo;
                cout << "Ingrese su contraseña: " << endl;
                string contrasena;
                cin >> contrasena;
                nuevoUsuario(usuarios, correo, contrasena, u);
            }
            break;

        default:
            break;
        }
    }
    return 0;
}

