/*
Hacer un programa que sirva para reservar vuelos.
Las opciones que tiene un usuario son:
a) buscar vuelos.
  * Indicar fecha de salida
  * Indicar Origen
  * Indicar destino
  * el sistema retorna una lista de vuelos.
  * el usuario elige un vuelo
  * el sistema confirma la reservacion y vuelve al menu original.
  * en cualquier momento, el usuario puede elegir la opcion 0 y volver al menu anterior.
b) mostrar reservaciones pendientes
c) mostrar vuelos pasados.
*/

#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;
class Usuario {
    private:
        int clave_usuario;
        string nombre;
        string apellido;
        string celular;
    public:
        Usuario(int clave, string nom, string ape, string cel) {
            clave_usuario = clave;
            nombre = nom;
            apellido = ape;
            celular = cel;
        }
        Usuario() {
        }
        string getNombre() {
            return nombre;
        }
        string getApellido() {
            return apellido;
        }
        string getCelular() {
            return celular;
        }
        int getClaveUsuario() {
            return clave_usuario;
        }

};

class Dates {
    private:
        int year;
        int month;
        int day;
    public:
        Dates() {
            day = 12;
            month = 11;
            year = 2017;
        }
        Dates(int d, int m, int y) {
                //check the month
            if(m >= 1 && m <= 12) {
                month = m;
            }
            else {
                month = 0;
            }
            if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
                if(d >= 1 && d <= 31) {
                    day = d;
                }
                else {
                    day = 0;
                }
            }
            else if(m != 2) {
                if(d >= 1 && d <= 30 ) {
                    day = d;
                }
                else {
                    day = 0;
                }
            }
            else {
                if(d >= 1 && d <= 28 ) {
                    day = d;
                }
                else {
                    day = 0;
                }
            }
            if(y >= 2017 && y <= 2032) {
                year = y;
            }
            else {
                year = 0;
            }
        }

};


class Vuelo {
    private:
        int clave_vuelo;
        string origen;
        string destino;
        Dates fecha;
        int asientos_disponibles;
    public:
        Vuelo(int clave, string ori, string dest, Dates fec, int asi_disp) {
            clave_vuelo = clave;
            origen = ori;
            destino = dest;
            fecha = fec;
            asientos_disponibles = asi_disp;
        }
        Vuelo() {

        }
        int getClaveVuelo() {
            return clave_vuelo;
        }
        string getOrigen() {
            return origen;
        }
        string getDestino() {
            return destino;
        }
        Dates getFecha() {
            return fecha;
        }
        int getAsientosDisponibles() {
            return asientos_disponibles;
        }
};

class Reservacion {
    private:
        int clave_vuelo;
        int clave_usuario;

    public:
        Reservacion(int cv, int cu) {
            clave_vuelo = cv;
            clave_usuario = cu;
        }
        Reservacion() {

        }
        int getClaveUsuario() {
            return clave_usuario;
        }
        int getClaveVuelo() {
            return clave_vuelo;
        }
};


Usuario *current_user = NULL;
Reservacion *current_reservac = NULL;
int current_reservac_counter;


string name, lastname, clave_usuario, celular;
Usuario *users = NULL;
int user_counter;
Vuelo *vuelos = NULL;
int vuelo_counter;
Reservacion *reservas = NULL;
int reserva_counter;

void greet();
void login();
void buffer_user_info(string name, string lastname);
void display_main_menu();
int get_option(int max_option);
void reservar_vuelo();
void mostrar_vuelos_pendientes();
void mostrar_vuelos_pasados();
void leer_base_datos();
int get_day(string fecha);
int get_month(string fecha);
int get_year(string fecha);

int main(void) {
    int option = -1;
    //saludo
    leer_base_datos();
    greet();

    login();

    //leer opcion
    while(option != 0) {
         //menu de bienvenida
         display_main_menu();
         option = get_option(3);
         switch(option) {
             case 1:
                reservar_vuelo();
                break;
            case 2:
                mostrar_vuelos_pendientes();
                break;
            case 3:
                mostrar_vuelos_pasados();
                break;
         }
    }
}

int get_option(int max_option) {
    int opt = -1;
    cin >> opt;
    while(opt < 0 || opt > max_option) {
        cout << " Ingresa una opcion valida entre 0 y " << max_option << ": ";
        cin >> opt;
    }
}

void greet() {

    cout<<"Welcome to Mexican Airlines"<<endl;

}

void login() {
    string name, lastname;
    string clave_usuario, celular;
    cout<< "Enter your name: ";
    cin>>name;
    cout << "Enter your lastname: ";
    cin>> lastname;
    buffer_user_info(name, lastname);
}

int exists(string name, string lastname) {
    bool found = false;
    for(int i = 0; i < user_counter; i++) {
        if(users[i].getNombre() == name && users[i].getApellido() == lastname) {
            found = true;
            return i;
            break;
        }
    }
    return -1;
}
void buffer_user_info(string name, string lastname) {
    //checar si usuario existe
    current_reservac = new Reservacion[50];
    current_reservac_counter = 0;
    int ex = exists(name, lastname);
    if(ex >= 0) {
        current_user = &users[ex];

            for(int j = 0; j < reserva_counter; j++) {
                if(reservas[j].getClaveUsuario() == (*current_user).getClaveUsuario()) {
                    current_reservac[current_reservac_counter] = reservas[j];
                    current_reservac_counter++;
                }
            }
    }
    else {
        //no existe
            cout<< "Ingresa tu celular: ";
            cin>> celular;
            Usuario myUser(user_counter + 1, name, lastname, celular);
            current_user = &myUser;
            users[user_counter] = *current_user;
            user_counter++;
    }
}

void display_main_menu() {

    string options = "0. Exit\n1. Reservar vuelo\n2. Mostrar Reservaciones Pendientes\n3. Mostrar vuelos pasados\nElija una opcion: ";
    cout << options;
}

void reservar_vuelo()  {
    cout <<"reservando vuelo"<<endl;
    //pedir la fecha
    //Date salida = pedir_fecha();
    //buscar en la bd. los vuelos disponibles en esa fecha.
    //string vuelos[100] = obtener_vuelos(salida);
    //obtener opcion de vuelo
    //modificar la base de datos con la disponibilidad de asientos, la reservacion de esta persona.
    //confirmar vuelo
}
void mostrar_vuelos_pendientes() {
    cout <<"mostrando vuelos pendientes"<<endl;
}
void mostrar_vuelos_pasados() {
    cout <<"mostrando vuelos pasados"<<endl;

}

void leer_base_datos() {
    //abrir archivo
     // open a file in read mode.
       ifstream infile;
       infile.open("usuario_db.csv");
       int clave_usuario;
    string nombre;
    string apellido;
    string cel;
    users = new Usuario[50];
    user_counter = 0;
       while(!infile.eof()) {
           infile >> clave_usuario;
           infile >> nombre;
           infile >> apellido;
           infile >> cel;
           Usuario user(clave_usuario, nombre, apellido, cel);

            users[user_counter] = user;
            user_counter++;
       }

       infile.close();


    //leer linea por linea,
    //construir el objeto
    //agregarlo a la lista
    //cerrar archivo de db.
    infile.open("vuelos_db.csv");
     int clave_vuelo;
     string origen;
     string destino;
     string fecha_str;

     int asientos_disponibles;

    vuelos = new Vuelo[250];
     vuelo_counter = 0;
       while(!infile.eof()) {
           infile >> clave_vuelo;
           infile >> origen;
           infile >> destino;
           infile >> fecha_str;
           Dates fecha(get_day(fecha_str), get_month(fecha_str), get_year(fecha_str));
           infile >> asientos_disponibles;
           Vuelo vol(clave_vuelo, origen, destino, fecha, asientos_disponibles);
           vuelos[vuelo_counter] = vol;
            vuelo_counter++;
       }

       infile.close();


    //abrir archivo
    //leer linea por linea,
    //construir el objeto
    //agregarlo a la lista
        //cerrar archivo de db.
    infile.open("reservaciones_db.csv");
    reservas = new Reservacion[1000];
     reserva_counter = 0;
       while(!infile.eof()) {
           infile >> clave_vuelo;
           infile >> clave_usuario;

           Reservacion r(clave_vuelo, clave_usuario);
           reservas[reserva_counter] = r;
            reserva_counter++;
       }

       infile.close();

}

int get_day(string fecha) {
    istringstream is(fecha.substr(0, 2));
    int day;
    is>> day;
    return day;
}

int get_month(string fecha) {
    stringstream ss(fecha.substr(3, 2));
    int month;
    ss>> month;
    return month;
}

int get_year(string fecha) {
    istringstream is(fecha.substr(7, 4));
    int year;
    is>> year;
    return year;
}