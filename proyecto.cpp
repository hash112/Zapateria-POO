// Alan
// Raul
// POO 3-5
// Proyecto

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
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

void crearAdmin()
{
    ifstream fi("empleados.csv");
    fi.seekg(0, ios::end);
    int contar = fi.tellg();
    fi.close();
    if(contar == 0)
    {
        fstream fout;
        fout.open("empleados.csv", ios::out | ios::app);
        fout << 1 << ", " << "admin" << ", " << 1234 << ", " << 100 << ", " << 1 << ", " << 0 << ", " << 2 << ", ";
        for(int i=0; i<7; i++)
        {
            if(i == 6) fout << 1 << "\n";
            else fout << 1 << ", ";
        }
        fout.close();
    }
}

void siExiste()
{
    string archivos[3] = {"empleados.csv", "zapatos.csv", "tickets.csv"};
    for(int i=0; i<3; i++)
    {
        ifstream file;
        file.open(archivos[i]);
        if(!file)
        {
            ofstream crear(archivos[i]);
            crear.close();
        }
        else file.close();
    }
    crearAdmin();
}

vector <string> TxtSecundario(int opc)
{
    vector <string> txt;
    switch (opc)
    {
    case 0:
        txt.push_back("Mujer");
        txt.push_back("Hombre");
        break;

    case 1:
        txt.push_back("Lunes");
        txt.push_back("Martes");
        txt.push_back("Mi\x82rcoles");
        txt.push_back("Jueves");
        txt.push_back("Viernes");
        txt.push_back("S\xA0""bado");
        txt.push_back("Domingo");
        txt.push_back("Confirmar");
        break;

    default:
        break;
    }
    return txt;
}

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
                    case 0:
                        break;

                    case 1:
                        opciones.push_back("Ingresa el c\xA2""digo del zapato");
                        numOpciones = 1;
                        break;

                    case 2:
                        break;

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
                    case 0:
                        opciones.push_back("Ingresa el c\xA2""digo del zapato");
                        opciones.push_back("Confirmar");
                        numOpciones = 2;
                        break;

                    case 1:
                        opciones.push_back("Nombre");
                        opciones.push_back("Contrase\xA4""a");
                        opciones.push_back("Edad");
                        opciones.push_back("G\x82nero");
                        opciones.push_back("Salario");
                        opciones.push_back("Horario");
                        opciones.push_back("Confirmar");
                        numOpciones = 7;
                        break;

                    case 2:
                        opciones.push_back("Ingresa el c\xA2""digo del empleado");
                        opciones.push_back("Motivo (Opcional)");
                        opciones.push_back("Confirmar");
                        numOpciones = 3;
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
                numOpciones = 1;
                return 1;
            
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
        void textoSecundario(int posicion_flecha, int n_txt, int max_pos)
        {
            vector <string> txt = TxtSecundario(n_txt);
            y = POSICION_Y+5;
            for(int i=0; i<=max_pos; i++)
            {
                gotoxy(POSICION_X+30, y);
                if(i == posicion_flecha) cout << txt[i] << " <---";
                else cout << txt[i];
                y += 2;
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
        int posicionSecundaria(int tecla, int posicion, int max_pos)
        {
            switch (tecla)
            {
            case ARRIBA:
                posicion--;
                if(posicion < 0) posicion = max_pos;
                break;
            
            case ABAJO:
                posicion++;
                if(posicion > max_pos) posicion = 0;
                break;

            default:
                break;
            }
            return posicion;
        }
        ~Menu(){}
        
};

class Zapato
{ // Clase para identificar los zapatos a vender
    private:
        string modelo, color;
        int numero_serie;
        int cantidad;
        float precio, talla;
        vector <string> datosZapato;

    public:
        Zapato(string _modelo, string _color, float _talla, int _cantidad, float _precio)
        {
            modelo = _modelo;
            color = _color;
            talla = _talla;
            cantidad = _cantidad;
            precio = _precio;
        }
        int estaVacio()
        {
            ifstream fi("zapatos.csv");
            fi.seekg(0, ios::end);
            int contar = fi.tellg();
            if(contar == 0)
            {
                fi.close();
                return 1;
            }
            else return 0;
        }
        int recuperarDeArchivo(int nZapato)
        {
            if(estaVacio()) return 0;
            fstream fin("zapatos.csv", ios::in);
            string temp, linea, dato;
            while(fin.eof() == 0)
            {
                datosZapato.clear();
                getline(fin, linea);
                stringstream s(linea);
                while(getline(s, dato, ','))
                {
                    datosZapato.push_back(dato);
                }
                numero_serie = stoi(datosZapato[0]);
                if(numero_serie == nZapato)
                {
                    fin.close();
                    break;
                }
            }
            fin.close();
            return numero_serie;
        }
        void alta()
        {
            numero_serie = recuperarDeArchivo(0);
            fstream fout;
            fout.open("zapatos.csv", ios::out | ios::app);
            fout << numero_serie+1 << ", " << modelo << ", " << color << ", " << talla << ", " << cantidad << ", " << precio << "\n";
            fout.close();
        }
        void baja(int nSerie)
        {
            fstream fout;
            fout.open("temp.csv", ios::out | ios::app);
            fstream fin("zapatos.csv", ios::in);
            string temp, linea, dato;
            while(fin.eof() == 0)
            {
                datosZapato.clear();
                getline(fin, linea);
                stringstream s(linea);
                while(getline(s, dato, ','))
                {
                    datosZapato.push_back(dato);
                }
                numero_serie = stoi(datosZapato[0]);
                if(nSerie != numero_serie && linea.compare("") != 0) fout << linea << "\n";
                else
                {
                    gotoxy(POSICION_X, 15);
                    cout << "No se pudo borrar el usuario";
                    fin.close();
                    fout.close();
                    remove("temp.csv");
                    return;
                }
            }
            fin.close();
            fout.close();
            remove("zapatos.csv");
            rename("temp.csv", "zapatos.csv");
        }
            
        int buscar(int nSerie)
        {
            int y = 15;
            recuperarDeArchivo(nSerie);
            if(nSerie == numero_serie)
            {
                for(int i=1; i<=5; i++)
                {
                    gotoxy(POSICION_X, y);
                    cout << datosZapato[i];
                    y += 2;
                }
            }
            else return 0;
        }
        ~Zapato(){}
};

class Empleado
{
    private:
        string nombre, password;
        int codigo, edad, genero;
        float salario;
        vector <string> datosEmpleado;

    public:
        Empleado(string _nombre, string _password, int _edad, float _salario, int _genero)
        {
            nombre = _nombre;
            password = _password;
            edad = _edad;
            genero = _genero;
            salario = _salario;
        }
        int recuperarDeArchivo(int usuario)
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
            return codigo;
            fin.close();
        }
        void alta(int* horario)
        {
            codigo = recuperarDeArchivo(0);
            fstream fout;
            fout.open("empleados.csv", ios::out | ios::app);
            fout << codigo+1 << ", " << nombre << ", " << password << ", " << edad << ", " << genero << ", " << salario << ", " << 1 << ", ";
            for(int i=0; i<7; i++)
            {
                if(i == 6) fout << horario[i] << "\n";
                else fout << horario[i] << ", ";
            }
            fout.close();
        }
        void baja(int usuario)
        {
            fstream fout;
            fout.open("temp.csv", ios::out | ios::app);
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
                if(codigo != usuario && linea.compare("") != 0 && usuario != 1) fout << linea << "\n";
                else
                {
                    gotoxy(POSICION_X, 15);
                    cout << "No se pudo borrar el usuario";
                    fin.close();
                    fout.close();
                    remove("temp.csv");
                    return;
                }
            }
            fin.close();
            fout.close();
            remove("empleados.csv");
            rename("temp.csv", "empleados.csv");
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
        ~Empleado(){} // Destructor de la clase Empleado
};

int confirmar()
{
    Menu guardar = Menu("\xA8Quieres guardar los cambios?", -10);
    guardar.obtenerTexto(4, 0);
    int posicion = 0;
    int tecla;
    while(1)
    {
        guardar.dibujarCuadrado();
        guardar.imprimirTexto(posicion);
        tecla = getch();
        posicion = guardar.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion) return 1;
            else return 0;
        }
    }
}

int bajas(int menu, int submenu, int margen)
{
    string titulo;
    if(submenu == 2) titulo = "Baja Empleados";
    else titulo = "Baja Productos";
    Menu bajas = Menu(titulo, margen);
    string razon = "";
    int codigo = 0, posicion = 0, tecla, conf;
    bajas.obtenerTexto(menu, submenu);
    while(1)
    {
        bajas.dibujarCuadrado();
        bajas.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << codigo;
        if(submenu == 2)
        {
            gotoxy(POSICION_X, 8);
            cout << razon;
        }
        tecla = getch();
        posicion = bajas.cambiarPosicion(tecla, posicion);
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
                if(submenu == 2)
                {
                    gotoxy(POSICION_X, 8);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 8);
                    getline(cin, razon);
                }
                else
                {
                    conf = confirmar();
                    if(conf)
                    {
                        Zapato baja = Zapato("x", "x", 0, 0, 0);
                        baja.baja(codigo);
                        baja.~Zapato();
                        bajas.~Menu();
                        return 0;
                    }
                }
                break;
            
            case 2:
                if(submenu == 0)
                {
                    bajas.~Menu();
                    return 0;
                }
                else
                {
                    conf = confirmar();
                    if(conf)
                    {
                        Empleado baja = Empleado("x", "x", 0, 0, 0);
                        baja.baja(codigo);
                        baja.~Empleado();
                        bajas.~Menu();
                        return 0;
                    }
                }
                break;
            
            case 3:
                bajas.~Menu();
                return 0;

            default:
                break;
            }
        }
    }
    
}

int buscar(int menu, int submenu, int margen)
{
    Menu buscar = Menu("Buscar Productos", margen);
    int codigo = 0, posicion = 0, encontrado = 0, tecla;
    const int salir = buscar.obtenerTexto(menu, submenu);
    while(1)
    {
        buscar.dibujarCuadrado();
        buscar.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << codigo;
        if(encontrado)
        {
            Zapato encontrar = Zapato("x", "x", 0, 0, 0);
            encontrado = encontrar.buscar(codigo);
            if(!encontrado)
            {
                gotoxy(POSICION_X, 10);
                cout << "Producto no encontrado";
                continue;
            }
            encontrar.~Zapato();
        }
        tecla = getch();
        posicion = buscar.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion == 1)
            {
                buscar.~Menu();
                return 0;
            }
            switch(posicion)
            {
            case 0:
                gotoxy(POSICION_X, 5);
                cout << ESPACIO;
                gotoxy(POSICION_X, 5);
                cin >> codigo;
                encontrado = 1;
                break;
            
            default:
                break;
            }
        }
    }
}

int altasEmpleados(int menu, int submenu, int margen)
{
    Menu altas = Menu("Altas empleados", margen);
    string nombre = "", password = "";
    char dias[7] = {'L', 'M', 'I', 'J', 'V', 'S', 'D'};
    int edad = 0, genero = 1;
    int movGenero = 0, movHorario = 0, conf = 0;
    int posicion = 0, posicion_genero = 0, posicion_horario = 0, tecla;
    int horario[7] = {0,0,0,0,0,0,0};
    float salario = 0.0;
    const int salir = altas.obtenerTexto(menu, submenu);
    while (1)
    {
        altas.dibujarCuadrado();
        altas.imprimirTexto(posicion);
        gotoxy(POSICION_X, 5);
        cout << nombre;
        gotoxy(POSICION_X, 8);
        cout << password;
        gotoxy(POSICION_X, 11);
        cout << edad;
        gotoxy(POSICION_X, 14);
        if(genero) cout << "Hombre";
        else cout << "Mujer";
        gotoxy(POSICION_X, 17);
        cout << salario;
        gotoxy(POSICION_X, 20);
        for(int i=0; i<7; i++) if(horario[i]) cout << dias[i] << ", "; 
        if(movGenero) altas.textoSecundario(posicion_genero, 0, 1);
        else if(movHorario) altas.textoSecundario(posicion_horario, 1, 7);
        tecla = getch();
        if(movGenero) posicion_genero = altas.posicionSecundaria(tecla, posicion_genero, 1);
        else if(movHorario) posicion_horario = altas.posicionSecundaria(tecla, posicion_horario, 7);
        else posicion = altas.cambiarPosicion(tecla, posicion);
        if(tecla == ENTER)
        {
            if(posicion == salir)
            {
                altas.~Menu();
                return 0;
            }
            if(movGenero)
            {
                genero = posicion_genero;
                movGenero = 0;
            }
            else if(movHorario)
            {
                if(posicion_horario == 7) movHorario = 0;
                else
                {
                    if(horario[posicion_horario]) horario[posicion_horario] = 0;
                    else horario[posicion_horario] = 1;
                }
            }
            else
            {
                switch(posicion)
                {
                case 0:
                    gotoxy(POSICION_X, 5);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 5);
                    getline(cin, nombre);
                    break;

                case 1:
                    gotoxy(POSICION_X, 8);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 8);
                    cin >> password;
                    break;

                case 2:
                    gotoxy(POSICION_X, 11);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 11);
                    cin >> edad;
                    break;

                case 3:
                    movGenero = 1;
                    break;

                case 4:
                    gotoxy(POSICION_X, 17);
                    cout << ESPACIO;
                    gotoxy(POSICION_X, 17);
                    cin >> salario;
                    break;

                case 5:
                    movHorario = 1;
                    break;

                case 6:
                    if(nombre.compare("") == 0 || password.compare("") == 0) 
                    {
                        gotoxy(POSICION_X, 20);
                        cout << "Por favor rellena los campos";
                        Sleep(1000);
                    }
                    else
                    {
                        conf = confirmar();
                        if(conf)
                        {
                            Empleado altaEmpleado = Empleado(nombre, password, edad, salario, genero);
                            altaEmpleado.alta(horario);
                            altaEmpleado.~Empleado();
                            altas.~Menu();
                            return 0;
                        }
                    }
                
                default:
                    break;
                }
            }
        }
    }
    
}

int altasProductos(int menu, int submenu, int margen)
{
    Menu altas = Menu("Altas productos", margen);
    string nombre = "", color = "";
    int cantidad = 0, tecla = 0, posicion = 0, conf = 0;
    float precio = 0, talla = 0;
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
                getline(cin, nombre);
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
                if(nombre.compare("") == 0 || color.compare("") == 0) 
                {
                    gotoxy(POSICION_X, 20);
                    cout << "Por favor rellena los campos";
                    Sleep(1000);
                }
                else
                {
                    conf = confirmar();
                    if(conf)
                    {
                        Zapato altaZapato = Zapato(nombre, color, talla, cantidad, precio);
                        altaZapato.alta();
                        altaZapato.~Zapato();
                        altas.~Menu();
                        return 0;
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
                buscar(menu, submenu, -5);
                break;

            case 2:
                break;

            case 3:
                altasProductos(menu, submenu, -4);
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
                altasEmpleados(menu, submenu, -4);
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
                    Empleado empleado = Empleado("temp", password, 0, 0, 0);
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
    siExiste();
    bajas(2, 2, -2);
    // login();
}
