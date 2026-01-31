// proyecto 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale.h>
#include <limits> 

using namespace std;


float convertirNota(const string& s) {
    try {
        return stof(s);
    } catch (...) {
        return -1;  // valor inválido
    }
}


string notas[100][100];
int totalNotas = 0;

void cargarNotas() {  //en chat gpt  4 modificar 
    ifstream archivo("notas.csv");
    string linea;
    totalNotas = 0;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        for (int j = 0; j < 8; j++) {
            getline(ss, notas[totalNotas][j], ';');
        }
        totalNotas++;
    }
    archivo.close();
}




void mostrarNotas() {
    cargarNotas();
    cout << "\n--- LISTA DE NOTAS ---\n";
    for (int i = 0; i < totalNotas; i++) {
        for (int j = 0; j < 9; j++)
            cout << notas[i][j] << " | ";
        cout << endl;
    }
}



void mostrarNotasOrdenadas() { /// se agregó
    cout << "\n--- LISTA DE NOTAS ORDENADAS ---\n";
    for (int i = 0; i < totalNotas; i++) {
        for (int j = 0; j < 9; j++)
            cout << notas[i][j] << " | ";
        cout << endl;
    }
}

void registrarNota() {
    string tipo, nombre, apellido, cedula, codigo;
    string correoInst, correoPers, materia;
    float nota;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Tipo (Estudiante/Docente): ";
    getline(cin, tipo);

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Apellido: ";
    getline(cin, apellido);

    do {
        cout << "Cedula (10 digitos): ";
        getline(cin, cedula);
    } while (cedula.length() != 10);

    do {
        cout << "Codigo unico (9 digitos): ";
        getline(cin, codigo);
    } while (codigo.length() != 9);

    cout << "Correo institucional: ";
    getline(cin, correoInst);

    cout << "Correo electronico personal: ";
    getline(cin, correoPers);

    cout << "Materia: ";
    getline(cin, materia);

    cout << "Nota: ";
    cin >> nota;

    ofstream archivo("notas.csv", ios::app);
    archivo << tipo << ";" << nombre << ";" << apellido << ";"
            << cedula << ";" << codigo << ";" << correoInst << ";"
            << correoPers << ";" << materia << ";" << nota << endl;
    archivo.close();

    cout << "Nota registrada correctamente.\n";
}



void registrarInvestigacion() {
    string tipo, autor, titulo;

    cin.ignore();
    cout << "Tipo (Estudiante/Docente): ";
    getline(cin, tipo);

    cout << "Autor: ";
    getline(cin, autor);

    cout << "Titulo de la investigacion: ";
    getline(cin, titulo);

    ofstream archivo("investigaciones.csv", ios::app);
    archivo << tipo << ";" << autor << ";" << titulo << endl;
    archivo.close();

    cout << "Investigacion registrada correctamente.\n";
}

void mostrarInvestigaciones() {
    ifstream archivo("investigaciones.csv");
    string linea;

    cout << "\n--- INVESTIGACIONES ---\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}

void eliminarInvestigacion() {
    string titulo;
    cin.ignore();
    cout << "ENTRE A ELIMINAR INVESTIGACION\n";

    cout << "Ingrese titulo a eliminar: ";
    getline(cin, titulo);

    ifstream archivo("investigaciones.csv");
    ofstream temp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        if (linea.find(titulo) == string::npos)
            temp << linea << endl;
        else
            encontrado = true;
    }

    archivo.close();
    temp.close();
    remove("investigaciones.csv");
    rename("temp.csv", "investigaciones.csv");

    if (encontrado)
        cout << "Investigacion eliminada.\n";
    else
        cout << "No encontrada.\n";
}


void actualizarInvestigacion() {
    string buscar, nuevoTitulo;
    cin.ignore();
    
    cout << "ENTRE A ACTUALIZAR INVESTIGACION\n";

    cout << "Titulo a actualizar: ";
    getline(cin, buscar);
    cout << "Nuevo titulo: ";
    getline(cin, nuevoTitulo);

    ifstream archivo("investigaciones.csv");
    ofstream temp("temp.csv");
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        if (linea.find(buscar) != string::npos) {
            temp << nuevoTitulo << endl;
            encontrado = true;
        } else {
            temp << linea << endl;
        }
    }

    archivo.close();
    temp.close();
    remove("investigaciones.csv");
    rename("temp.csv", "investigaciones.csv");

    if (encontrado)
        cout << "Investigacion actualizada.\n";
    else
        cout << "No encontrada.\n";
}




void menuInvestigaciones() { //recien agg
    int opcion;
    do {
        cout << "\n--- INVESTIGACIONES ---\n";
        cout << "1. Registrar investigacion\n";
        cout << "2. Mostrar investigaciones\n";
        cout << "3. Actualizar investigacion\n";
        cout << "4. Eliminar investigacion\n";
        cout << "5. Volver\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
        case 1: registrarInvestigacion(); break;
        case 2: mostrarInvestigaciones(); break;
        case 3: actualizarInvestigacion(); break;  
        case 4: eliminarInvestigacion(); break;    
        case 5: break;
        default: cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}



void buscarPorCedula() { //se agregó
    cargarNotas();
    string cedula;
    bool encontrado = false;

    cout << "Ingrese cedula: ";
    cin >> cedula;

    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][3] == cedula) {
            cout << notas[i][1] << " "
                 << notas[i][2] << " | "
                 << notas[i][6] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No existe registro con esa cedula.\n";
    }
}

void buscarPorCodigo() { // se agregó
    cargarNotas();
    string codigo;
    bool encontrado = false;

    cout << "Ingrese codigo unico: ";
    cin >> codigo;

    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][4] == codigo) {
            cout << notas[i][1] << " "
                 << notas[i][2] << " | "
                 << notas[i][6] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No existe registro con ese codigo.\n";
    }
}


void buscarPorNombre() { // se agregó
    cargarNotas();
    string nombre;
    bool encontrado = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Ingrese nombre: ";
getline(cin, nombre);


    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][1] == nombre) {
            cout << notas[i][2] << " | "
                 << notas[i][6] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No existe registro con ese nombre.\n";
    }
}


void buscarPorMateria() { // se agregó
    cargarNotas();
    string materia;
    bool encontrado = false;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Ingrese materia: ";
getline(cin, materia);



    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][6] == materia) {
            cout << notas[i][1] << " "
                 << notas[i][2] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay registros para esa materia.\n";
    }
}


void buscarPorCorreoInstitucional() {
    cargarNotas();
    string correo;
    bool encontrado = false;

    cin.ignore();
    cout << "Ingrese correo institucional: ";
    getline(cin, correo);

    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][5] == correo) {
            cout << notas[i][1] << " "
                 << notas[i][2] << " | "
                 << notas[i][6] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No existe registro con ese correo institucional.\n";
    }
}



void buscarPorCorreoElectronico() {
    cargarNotas();
    string dominio;
    bool encontrado = false;

    cin.ignore();
    cout << "Ingrese dominio de correo (ej: @epn.edu.ec): ";
    getline(cin, dominio);

    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][5].find(dominio) != string::npos) {
            cout << notas[i][1] << " "
                 << notas[i][2] << " | "
                 << notas[i][5] << " | "
                 << notas[i][6] << " | Nota: "
                 << notas[i][7] << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay registros con ese dominio de correo.\n";
    }
}



// ORDENAMIENTOS 
 void ordenarNombreAZ() { // se sgregó
    cargarNotas();
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = i + 1; j < totalNotas; j++) {
            if (notas[i][1] > notas[j][1]) {
                for (int k = 0; k < 8; k++)
                    swap(notas[i][k], notas[j][k]);
            }
        }
    }
     mostrarNotasOrdenadas();
}

void ordenarNombreZA() { // se agregó
    cargarNotas();
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = i + 1; j < totalNotas; j++) {
            if (notas[i][1] < notas[j][1]) {
                for (int k = 0; k < 8; k++)
                    swap(notas[i][k], notas[j][k]);
            }
        }
    }
    mostrarNotasOrdenadas();
}


void ordenarNotaAsc() { // recien agg
    cargarNotas();
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = i + 1; j < totalNotas; j++) {
            if (convertirNota(notas[i][7]) > convertirNota(notas[j][7])) {
    for (int k = 0; k < 8; k++)
        swap(notas[i][k], notas[j][k]);
           }

        }
    }
    mostrarNotasOrdenadas();  
}


void ordenarNotaDesc() { // recien agg
    cargarNotas();
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = i + 1; j < totalNotas; j++) {
            if (convertirNota(notas[i][7]) < convertirNota(notas[j][7])) {
    for (int k = 0; k < 8; k++)
        swap(notas[i][k], notas[j][k]);
        }

        }
    }
    mostrarNotasOrdenadas();  
}

void ordenarMateria() { //recien agg
    cargarNotas();
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = i + 1; j < totalNotas; j++) {
            if (notas[i][6] > notas[j][6]) {
                for (int k = 0; k < 9; k++)
                    swap(notas[i][k], notas[j][k]);
            }
        }
    }
    mostrarNotasOrdenadas();  
}



   
   
void menuBusquedasNotas() {// revisar 
    int op;
    do {
        cout << "\n--- BUSQUEDAS DE NOTAS ---\n";
        cout << "1. Buscar por cedula\n";
        cout << "2. Buscar por codigo\n";
        cout << "3. Buscar por nombre\n";
        cout << "4. Buscar por materia\n";
        cout << "5. Buscar por correo institucional\n";
        cout << "6.Buscar por correo electronico\n";
        cout << "11. Volver\n";
        cout << "Seleccione: ";
        cin >> op;

        switch (op) {
        case 1: buscarPorCedula(); break;
        case 2: buscarPorCodigo(); break;
        case 3: buscarPorNombre(); break;
        case 4: buscarPorMateria(); break;
        case 5: buscarPorCorreoInstitucional(); break;
        case 6: buscarPorCorreoElectronico(); break;
        }
    } while (op != 11);
}



void menuOrdenamientosNotas() { //recien agregado
    int op;
    do {
        cout << "\n--- ORDENAMIENTOS DE NOTAS ---\n";
        cout << "1. Nombre A-Z\n";
        cout << "2. Nombre Z-A\n";
        cout << "3. Nota Ascendente\n";
        cout << "4. Nota Descendente\n"; 
        cout << "5. Ordenar por materia\n";
        cout << "6. Volver\n";
        cout << "Seleccione: ";
        cin >> op;

        switch (op) {
        case 1: ordenarNombreAZ(); break;
        case 2: ordenarNombreZA(); break;
        case 3: ordenarNotaAsc(); break;
        case 4: ordenarNotaDesc(); break;
        case 5: ordenarMateria(); break;
        }
    } while (op != 6);
}


void actualizarNota() {
    cargarNotas();
    string codigo;
    cout << "Ingrese codigo unico: ";
    cin >> codigo;

    bool encontrado = false;

    for (int i = 0; i < totalNotas; i++) {
        if (notas[i][4] == codigo) {
            cin.ignore();
            cout << "Nuevo nombre: ";
            getline(cin, notas[i][1]);

            cout << "Nuevo apellido: ";
            getline(cin, notas[i][2]);

            cout << "Nueva materia: ";
            getline(cin, notas[i][7]);

            cout << "Nueva nota: ";
            getline(cin, notas[i][8]);

            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Codigo no encontrado.\n";
        return;
    }

    ofstream archivo("notas.csv");
    for (int i = 0; i < totalNotas; i++) {
        for (int j = 0; j < 9; j++) {
            archivo << notas[i][j];
            if (j < 8) archivo << ";";
        }
        archivo << endl;
    }
    archivo.close();

    cout << "Datos actualizados correctamente.\n";
}





void eliminarNota() {
    string codigoEliminar;
    bool encontrada = false;

    cout << "Ingrese el codigo unico de la nota a eliminar: ";
    cin >> codigoEliminar;

    ifstream archivo("notas.csv");
    ofstream temp("temp.csv");

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string tipo, nombre, apellido, cedula, codigo, correo, materia, nota;

        getline(ss, tipo, ';');
        getline(ss, nombre, ';');
        getline(ss, apellido, ';');
        getline(ss, cedula, ';');
        getline(ss, codigo, ';');
        getline(ss, correo, ';');
        getline(ss, materia, ';');
        getline(ss, nota, ';');

        if (codigo != codigoEliminar) {
            temp << linea << endl;
        } else {
            encontrada = true;
        }
    }

    archivo.close();
    temp.close();

    remove("notas.csv");
    rename("temp.csv", "notas.csv");

    if (encontrada)
        cout << "Nota eliminada correctamente.\n";
    else
        cout << "Codigo no encontrado.\n";
}




void MenuNotas() { // recien agtregado 
    int op;
    do {
        cout << "\n--- MENU NOTAS ---\n";
        cout << "1. Registrar nota\n";
        cout << "2. Mostrar notas\n";
        cout << "3. Buscar notas\n";
        cout << "4. Ordenar notas\n";
        cout << "5. Actualizar nota\n";
        cout << "6. Eliminar nota\n";
        cout << "7. Volver\n";
        cout << "Seleccione: ";
        cin >> op;

        switch (op) {
        case 1: registrarNota(); break;
        case 2: mostrarNotas(); break;
        case 3: menuBusquedasNotas(); break;
        case 4: menuOrdenamientosNotas(); break;
        case 5: actualizarNota(); break;
        case 6: eliminarNota(); break;
        }
    } while (op != 7);
}


int main() {
    setlocale(LC_ALL, "spanish");
    int opcion;

    do {
        cout << "\n===== SISTEMA DE LA UNIVERSIDAD =====\n";
        cout << "1. Notas\n";
        cout << "2. Investigaciones\n";
        cout << "3. Salir\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
        case 1: MenuNotas(); break;            // ✅ MENÚ COMPLETO
        case 2: menuInvestigaciones(); break;
        case 3: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida\n";
        }
    } while (opcion != 3);

    return 0;
}






