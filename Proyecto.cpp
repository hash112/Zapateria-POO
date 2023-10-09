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
        int regresar;
        int numOpciones;
        int margenTitulo;
        int y;
        string nombreMenu;
        vector <string> opciones;

    public:
        Menu(string nombre_menu, int margen_titulo) 
        { // El constructor consta del titulo del menu y su acomodo con respecto a la posicion titulo
            nombreMenu = nombre_menu;
            margenTitulo = margen_titulo;
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
        void obtenerTexto(int menu)
        { // En este metodo obtendremos los textos necesarios para cada menu y submenu
            switch(menu)
            {
            case 0:
                opciones.push_back("Usuario");
                opciones.push_back("Contrase\xA4""a");
                opciones.push_back("Ingresar");
                opciones.push_back("Salir");
                numOpciones = 4;
                break;

            case 1:
                opciones.push_back("Ingrese el nombre del empleado");
            
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
        int codigo;
        int salario;
        int tipoEmpleado;

    public:
        Empleado(string _nombre, string _password, int _salario, int _tipoEmpledo)
        {
            nombre = _nombre;
            password = _password;
            salario = _salario;
            tipoEmpleado = _tipoEmpledo;
        }
        void buscar(int usuario)
        { // PUES SUPONGO QUE ESTA YA DEBERIA JALAR, SOLO FALTARIA AJUSTARLA MEJOR PORQUE LO HICE A LO AHI SE VA
            fstream fin("empleados.csv", ios::in);
            vector <string> datosEmpleado;
            string temp, linea, dato;
            while(1)
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
                    int y = POSICION_Y;
                    for(int i=0; i<4; i++)
                    {
                        gotoxy(POSICION_X, y);
                        cout << datosEmpleado[i];
                        y += 3;
                    }
                }
            }
        }
        void alta()
        { // HARD CODEADO
            fstream fout;
            fout.open("empleados.csv", ios::out | ios::app);
            fout << 1 << ", " << nombre << ", " << password << ", " << salario << ", " << 3 <<"\n";
            fout.close();
        }
        void baja()
        {

        }
        int comprobarPass(int usuario)
        { // AUN TENGO MIS DUDAS SOBRE ESTA FUNCION, YA CUANDO PUEDA LA REVISO A DETALLE, PERO SE QUE FUNCIONA CON EL ADMIN
            string pass;
            int comparar;
            fstream fin("empleados.csv", ios::in);
            vector <string> datosEmpleado;
            string temp, linea, dato;
            while(1)
            {
                datosEmpleado.clear();
                getline(fin, linea);
                stringstream s(linea);
                while(getline(s, dato, ','))
                {
                    datosEmpleado.push_back(dato);
                }
                codigo = stoi(datosEmpleado[0]);
                password = quitarEspacio(password);
                pass = quitarEspacio(datosEmpleado[2]);
                comparar = pass.compare(password);
                if(usuario == codigo && comparar == 0)
                {
                    return stoi(datosEmpleado[4]);
                }
                else
                {
                    gotoxy(POSICION_X, 23);
                    cout << "Datos incorrectos";
                    Sleep(1000);
                    return 0;
                }
            }
        }
        void mostrarEmpleados()
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
        empleado.buscar(codigo);
        getch();
        return 0;
    }
}

void abrirMenu(int menu)
{ // Funcion que abre los menus y submenus
    switch(menu)
    {
    case 1:
        break;
    
    case 2:
        break;

    case 3:
        buscar(); // HARD CODEADO
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
        login.obtenerTexto(0);
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
                            abrirMenu(3);
                            break;

                        default:
                            break;
                    }
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
    Empleado empleado = Empleado("Admin", "1234", 900, 3);
    empleado.alta();
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
    > C++ == PYTHON >> JAVA

--------------------------------------------------------------------- 2da revisión
    > YA FUNCIONA EL LOGIN CON EL ADMIN, YA FALTARIA IMPLEMENTARLO EN LOS DEMAS EMPLEADOS
    > LA FUNCION ALTAS DE LOS EMPLEADOS POR AHORA ESTA HARD CODEADA, LUEGO LO CAMBIO YA QUE HAGAMOS LAS ALTAS
    > YA SE CREA EL ARCHIVO, Y LO LEE, PUTO DESMADRE HACER ESA MAMADA
    > LOS TUTORIALES PARA HACER ALGO NO SIRVEN, STACK ORVERFLOW NO SIRVE, VAYANSE TODOS A LA VERGA, TUVE QUE LEER LA DOCUMENTACION DE LAS MIERDAS QUE USE
    > LA NETA HAY MUCHAS PARTES HARD CODEADAS, PERO LO HICE PARA SEGUN ENTREGAR LA MIERDA ESTA PERO NO ALCANCE
*/