// Alan
// Raul
// POO 3-5
// Proyecto

//-------------------------------------------------------------------

// MI RULAS, LEE HASTA ABAJO LO QUE HACE FALTA
// TODOS LOS COMENTARIOS ESCRITOS EN MAYUSCULA SON PARA NOSOTROS

//-------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include <algorithm>

#define POSICION_X 27
#define POSICION_Y 4
#define POSICION_TITULO 49
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ENTER 13
#define ESPACIO "                                                      "
#define LINEA "_________________________________________________________________"
#define INSTRUCCIONES "Mover cursor: Arriba / Abajo | Entrar: Enter | Cambiar P\xA0g: Izquierda / Derecha"

using namespace std;
void abrirMenu(int menu, int submenu);
void gotoxy(int x, int y)
{ // Esta funcion nos permite escribir texto en cualquier parte de la consola
    HANDLE ventana;
    ventana = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordenadas;
    coordenadas.X = x;
    coordenadas.Y = y;
    SetConsoleCursorPosition(ventana, coordenadas);
}

string quitarEspacio(string str) 
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

class Menu 
{ // Esta es la clase estandard de los menus
    private:
        int regresar, numOpciones, margenTitulo, y;
        string nombreMenu;
        vector <string> opciones;

    public:
        Menu(string _nombre_menu, int _margen_titulo) 
        { // El constructor consta del titulo del menu y su acomodo con respecto a la posicion titulo
            nombreMenu = _nombre_menu;
            margenTitulo = _margen_titulo;
        }
        void dibujarCuadrado()
        { // Este cuadrado será el principal canvas del programa
            system("cls");
            gotoxy(25, 1);
            cout << LINEA;
            for(int i=2; i<27; i++)
            {
                gotoxy(24, i);
                cout << "|";
                gotoxy(90, i);
                cout << "|";
            }
            gotoxy(25, 26);
            cout << LINEA;
            gotoxy(POSICION_X-7, 28);
            cout << INSTRUCCIONES;
        }
        int obtenerTexto(int menu, int submenu)
        { // En este metodo obtendremos los textos necesarios para cada menu y submenu
            switch(menu)
            {
            case 1:
                switch(submenu)
                {
                    case 3:
                        opciones.push_back("Nombre");
                        opciones.push_back("Talla");
                        opciones.push_back("Color");
                        opciones.push_back("Cantidad");
                        opciones.push_back("Precio");
                        opciones.push_back("Confirmar");
                        numOpciones = 6;
                        break;

                    case 10:
                        opciones.push_back("Ventas");
                        opciones.push_back("Buscar producto");
                        opciones.push_back("Devoluciones");
                        opciones.push_back("Inventario");
                        numOpciones = 4;
                        break;
                }
                break;

            case 2:
                switch(submenu)
                {
                    case 1:
                        break;

                    case 10:
                        opciones.push_back("Baja productos");
                        opciones.push_back("Alta empleados");
                        opciones.push_back("Baja empleados");
                        opciones.push_back("Tickets");
                        numOpciones = 4;
                        break;
                }
                break;

            case 3:
                opciones.push_back("Usuario");
                opciones.push_back("Contrase\xA4""a");
                opciones.push_back("Ingresar");
                numOpciones = 3;
                break;

            case 4:
                opciones.push_back("NO");
                opciones.push_back("S\xD6");
                return 1;
                break;
            
            default:
                break;
            }
            opciones.push_back("Salir");
            return numOpciones;
        }
        void imprimirTexto(int posicion_flecha)
        { // Se imprimen los textos obtenidos en la funcion obtenerTexto
            y = POSICION_Y;
            gotoxy(POSICION_TITULO+margenTitulo, 2);
            cout << nombreMenu;
            for(int i=0; i<=numOpciones; i++)
            {
                gotoxy(POSICION_X, y);
                if(i == posicion_flecha) cout << opciones[i] << " <---";
                else cout << opciones[i];
                y += 3;
            }
        }
        int cambiarPosicion(int tecla, int posicion)
        { // Metodo que retorna la posicion del cursor
            switch (tecla)
            {
            case ARRIBA:
                posicion--;
                if(posicion < 0) posicion = numOpciones;
                break;
            
            case ABAJO:
                posicion++;
                if(posicion > numOpciones) posicion = 0;
                break;

            default:
                break;
            }
            return posicion;
        }
        int confirmar()
        {
            const int confirmar = obtenerTexto(4, 0);
            int posicion_conf = 0;
            int tecla_conf;
            while(1)
            {
                dibujarCuadrado();
                imprimirTexto(posicion_conf);
                tecla_conf = getch();
                posicion_conf = cambiarPosicion(tecla_conf, posicion_conf);
                if(tecla_conf == ENTER)
                {
                    if(posicion_conf) return 1;
                    else return 0;
                }
            }
        }
};

class Zapato
{ // Clase para identificar los zapatos a vender
    private:
        string modelo, color;
        long int numero_serie;
        int talla, cantidad;
        float precio;

    public:
        Zapato(string _modelo, string _color, int _talla, int _cantidad, float _precio)
        {
            modelo = _modelo;
            color = _color;
            talla = _talla;
            cantidad = _cantidad;
            precio = _precio;
        }
        void obtenerDeArchivo(int nZapato)
        {
            fstream fin("empleados.csv", ios::in);
            string temp, linea, dato;
            while(fin.eof() == 0)
            {
                datosEmpleado.clear();
                getline(fin, linea);
                stringstream s(linea);
                while(getline(s, dato, ','))
                {
                    datosEmpleado.push_back(dato);
                }
                codigo = stoi(datosEmpleado[0]);
                if(codigo == usuario)
                {
                    fin.close();
                    break;
                }
            }
            fin.close();
        }
        void alta()
        {
            recuperarDeArchivo(0);
            fstream fout;
            fout.open("zapatos.csv", ios::out | ios::app);
            fout << codigo++ << ", " << modelo << ", " << color << ", " << talla << ", " << cantidad << ", " << precio <<"\n";
            fout.close();
        }
        void reestock()
        {

        }
        void buscar()
        {

        }
};

class Empleado
{
    private:
        string nombre, password;
        int codigo, tipoEmpleado;
        float salario;
        char genero;
        int horario[7];
        vector <string> datosEmpleado;

    public:
        Empleado(string _nombre, string _password, int _salario, int _tipoEmpledo)
        {
            nombre = _nombre;
            password = _password;
            salario = _salario;
            tipoEmpleado = _tipoEmpledo;
        }
        void recuperarDeArchivo(int usuario)
        { // Esta funcion nos ayuda a recuperar datos del archivo y reutilizarlos a lo largo del objeto
            fstream fin("empleados.csv", ios::in);
            string temp, linea, dato;
            while(fin.eof() == 0)
            {
                datosEmpleado.clear();
                getline(fin, linea);
                stringstream s(linea);
                while(getline(s, dato, ','))
                {
                    datosEmpleado.push_back(dato);
                }
                codigo = stoi(datosEmpleado[0]);
                if(codigo == usuario)
                {
                    fin.close();
                    break;
                }
            }
            fin.close();
        }
        void alta()
        {
            recuperarDeArchivo(0);
            fstream fout;
            fout.open("empleados.csv", ios::out | ios::app);
            fout << codigo++ << ", " << nombre << ", " << password << ", " << salario << ", " << tipoEmpleado <<"\n";
            fout.close();
        }
        void baja()
        {

        }
        int comprobarPass(int usuario)
        { // Esta funcion comprueba el usuario y la contraseña del usuario
            string pass;
            int comparar;
            recuperarDeArchivo(usuario);
            codigo = stoi(datosEmpleado[0]);
            password = quitarEspacio(password);
            pass = quitarEspacio(datosEmpleado[2]);
            comparar = pass.compare(password);
            if(usuario == codigo && comparar == 0)
            {
                Sleep(1000);
                return stoi(datosEmpleado[4]);
            }
            gotoxy(POSICION_X, 23);
            cout << "Datos incorrectos";
            Sleep(1000);
            return 0;
        }
        void mostrarEmpleados(int cantidadMostrar)
        {

        }
        ~Empleado(){} // Destructor de la clase Empleado
};

int buscar()
{
    Menu buscar = Menu("Buscar Empleados", 0);
    int codigo;
    int posicion = 0;
    while(1)
    {
        buscar.dibujarCuadrado();
    }
}

int altasProductos(int menu, int submenu, int margen)
{
    Menu altas = Menu("Altas productos", margen);
    string nombre = "", color = "";
    int talla = 0, cantidad = 0, tecla = 0, posicion = 0;
    float precio = 0;
    const int salir = altas.obtenerTexto(menu, submenu);
    while(1)
    {
        altas.dibujarCuadrado();
        altas.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << nombre;
        gotoxy(POSICION_X, 8);
        cout << talla;
        gotoxy(POSICION_X, 11);
        cout << color;
        gotoxy(POSICION_X, 14);
        cout << cantidad;
        gotoxy(POSICION_X, 17);
        cout << precio;
        tecla = getch();
        posicion = altas.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion == salir)
            {
                altas.~Menu();
                return 0;
            }
            switch (posicion)
            {
            case 0:
                gotoxy(POSICION_X, 5);
                cout << ESPACIO;
                gotoxy(POSICION_X, 5);
                cin >> nombre;
                break;

            case 1:
                gotoxy(POSICION_X, 8);
                cout << ESPACIO;
                gotoxy(POSICION_X, 8);
                cin >> talla;
                break;

            case 2:
                gotoxy(POSICION_X, 11);
                cout << ESPACIO;
                gotoxy(POSICION_X, 11);
                cin >> color;
                break;

            case 3:
                gotoxy(POSICION_X, 14);
                cout << ESPACIO;
                gotoxy(POSICION_X, 14);
                cin >> cantidad;
                break;

            case 4:
                gotoxy(POSICION_X, 17);
                cout << ESPACIO;
                gotoxy(POSICION_X, 17);
                cin >> precio;
                break;

            case 5:
                if(nombre.compare("") == 0 || color.compare("") == 0) cout << "Por favor rellena los campos";
                else
                {
                    if(altas.confirmar())
                    {
                        Zapato altaZapato = Zapato(nombre, color, talla, cantidad, precio);
                        altaZapato.alta()
                    }
                }
                break;

            default:
                break;
            }

        }
    }

}

int menuOpciones(string titulo, int margen, int ID_menu, int submenu)
{
    Menu menuTexto = Menu(titulo, margen);
    int posicion = 0;
    const int salir = menuTexto.obtenerTexto(ID_menu, submenu);
    int tecla;
    while(1)
    {
        menuTexto.dibujarCuadrado();
        menuTexto.imprimirTexto(posicion);
        tecla = getch();
        posicion = menuTexto.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion == salir)
            {
                menuTexto.~Menu();
                return 0;
            }
            abrirMenu(ID_menu, posicion);
        }
    }
}

void abrirMenu(int menu, int submenu)
{ // Funcion que abre los menus y submenus
    switch(menu)
    {
    case 1:
        switch(submenu)
        {
            case 0:
                break;

            case 1:
                break;

            case 2:
                break;

            case 3:
                
                break;

            case 10:
                menuOpciones("Men\xA3 principal", -5, menu, submenu);
                break;
        }
        break;

    case 2:
        switch(submenu)
        {
            case 0:
                break;

            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 10:
                menuOpciones("Men\xA3 de administradores", -5, menu, submenu);
                break;
        }
        break;

    default:
        break;
    }
}

int login()
{ // Inicio de sesion de los trabajadores
    Menu login = Menu("LOGIN", 5);
    string password = "";
    int codigo = 0;
    int posicion = 0;
    int tecla, iniciarMenu;
    int salir = login.obtenerTexto(3, 0);
    while(1)
    {
        login.dibujarCuadrado();
        login.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << codigo;
        gotoxy(POSICION_X, 8);
        cout << password;
        tecla = getch();
        posicion = login.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion == salir) return 0;
            switch(posicion)
            {
                case 0:
                    gotoxy(POSICION_X, 5);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 5);
                    cin >> codigo;
                    break;

                case 1:
                    gotoxy(POSICION_X, 8);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 8);
                    cin >> password;
                    break;

                case 2:
                {
                    Empleado empleado = Empleado("temp", password, 0, 0);
                    iniciarMenu = empleado.comprobarPass(codigo);
                    empleado.~Empleado();
                    if(iniciarMenu == 0) break;
                    abrirMenu(iniciarMenu, 10);
                    codigo = 0;
                    password = "";
                    break;
                }

                default:
                    break;
            }
        }
    }
}

int main()
{
    altasProductos(1, 3, -4);
    // login();
}
