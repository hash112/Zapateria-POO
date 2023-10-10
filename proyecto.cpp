// Cordero Ramirez Alan
// Plata Oropeza Raul David
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
        void obtenerTexto(int menu, int submenu)
        { // En este metodo obtendremos los textos necesarios para cada menu y submenu
            switch(menu)
            {
            case 0:
                break;

            case 1:
                opciones.push_back("Ingrese el nombre del empleado");

            case 6:
                opciones.push_back("Usuario");
                opciones.push_back("Contrase\xA4""a");
                opciones.push_back("Ingresar");
                opciones.push_back("Salir");
                numOpciones = 4;
                break;
            
            default:
                break;
            }
        }
        void imprimirTexto(int posicion_flecha)
        { // Se imprimen los textos obtenidos en la funcion obtenerTexto
            y = POSICION_Y;
            gotoxy(POSICION_TITULO+margenTitulo, 2);
            cout << nombreMenu;
            for(int i=0; i<numOpciones; i++)
            {
                gotoxy(POSICION_X, y);
                if(i == posicion_flecha) cout << opciones[i] << " <---";
                else cout << opciones[i];
                y += 3;
            }
        }
        int cambiarPosicion(int tecla, int posicion, int maxPosicion)
        { // Metodo que retorna la posicion del cursor
            switch (tecla)
            {
            case ARRIBA:
                posicion--;
                if(posicion < 0) posicion = maxPosicion-1;
                break;
            
            case ABAJO:
                posicion++;
                if(posicion == maxPosicion) posicion = 0;
                break;

            default:
                break;
            }
            return posicion;
        }
};

class Zapato
{ // Clase para identificar los zapatos a vender
    private:
        string modelo;
        string color;
        long int numero_serie;
        int talla;
        float precio;

    public:
        Zapato(void) {}
        void obtenerDeArchivo()
        {

        }
        void alta()
        {
            
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
        string nombre;
        string password;
        int codigo, salario, tipoEmpleado;
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
        { // AHORA ESTA FUNCION SOLO NOS VA A AYUDAR A RECUPERAR DATOS DEL ARCHIVO, PARA AHORRAR CODIGO EN LAS OTRAS FUNCIONES
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
        { // HARD CODEADO
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
                cout << "LOGRADO";
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
{ // TODA LA FUNCION ESTA HARD CODEADA
    Menu buscar = Menu("Buscar Empleados", 0);
    int codigo;
    int posicion = 0;
    while(1)
    {
        system("cls");
        buscar.dibujarCuadrado();
        //buscar.obtenerTexto(1);
        //buscar.imprimirTexto(posicion); POR ALGUNA PERRA RAZON EL PROGRAMA CRASHEBA SI DEJO ESAS 2 LINEAS
        gotoxy(POSICION_X, 2);
        cout << "Ingrese codigo de empleado";
        gotoxy(POSICION_X, 5);
        cin >> codigo;
        system("cls");
        buscar.dibujarCuadrado();
        Empleado empleado = Empleado("temp", "temp", 0, 0);
        getch();
        return 0;
    }
}

void menuOpciones(string titulo, int margen, int ID_menu, int submenu)
{
    Menu menuTexo = Menu(titulo, margen);
    int posicion = 0;
    int tecla;
}

void abrirMenu(int menu, int submenu)
{ // Funcion que abre los menus y submenus
    switch(menu)
    {
    case 0:
        break;

    case 1:
        break;
    
    case 2:
        break;

    case 3:
        break;

    case 4:
        menuOpciones("Men\xA3 principal", -5, menu, submenu);
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
    while(1)
    {
        system("cls");
        login.obtenerTexto(6, 0);
        login.dibujarCuadrado();
        login.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << codigo;
        gotoxy(POSICION_X, 8);
        cout << password;
        tecla = getch();
        posicion = login.cambiarPosicion(tecla, posicion, 4);
        if(tecla == ENTER)
        {
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
                    Empleado empleado = Empleado("temp", password, 0, 0); // CASE HARD CODEADO
                    iniciarMenu = empleado.comprobarPass(codigo);
                    if(iniciarMenu == 0) break;
                    empleado.~Empleado();
                    switch (iniciarMenu)
                    {
                        case 1:
                            break;

                        case 2:
                            break;
                        
                        case 3:
                            abrirMenu(4, 0);
                            break;

                        default:
                            break;
                    }
                    codigo = 0;
                    password = "";
                }

                case 3:
                    return 0;

                default:
                    break;
            }
        }

    }
}

int main()
{
    // Empleado empleado = Empleado("Admin", "1234", 900, 3);
    // empleado.alta();
    login();
}

// ------------------------------------------------------------------------------

// BASURA QUE HACE FALTA (POR AHORA)

/*
--------------------------------------------------------------------- 1era revisión
    > GUARDAR Y RECOLECTAR LOS DATOS DE LOS CHAMBEADORES EN UN ARCHIVO DE TEXTO PARA EL LOGIN (YA)
    > TERMINAR EL LOGIN Y SUS OPCIONES
    > PONER EN PRACTICA LA CLASE DE LOS MENUS
    > AL CHILE NI SE QUE TANTO LE VAMOS A METER AL PROYECTO

--------------------------------------------------------------------- 2da revisión
    > YA FUNCIONA EL LOGIN CON EL ADMIN, YA FALTARIA IMPLEMENTARLO EN LOS DEMAS EMPLEADOS
    > LA FUNCION ALTAS DE LOS EMPLEADOS POR AHORA ESTA HARD CODEADA, LUEGO LO CAMBIO YA QUE HAGAMOS LAS ALTAS
    > YA SE CREA EL ARCHIVO, Y LO LEE, PUTO DESMADRE HACER ESA MAMADA

--------------------------------------------------------------------- 3ra revisión
    > AHORA USAMOS UN GITHUB WUUUUUUUUUUUUUU
    > POR FAVOR APRENDE A USAR GIT QUE YA NO TE VOY A PASAR ARCHIVOS POR WHATS
    > PORFA SI QUIERA DIME QUE COSAS VAMOS A METERLE AL PROYECTO PARA TENER CLARO LO QUE VOY A PROGRAMAR
*/