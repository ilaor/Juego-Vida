/**
 *
 * @file juegoVidaAlumnos.cpp
 *
 * @brief 
 *
 * Programa que simula el Juego de la vida mediante una matriz de booleanos
 *
 * @version 1
 * @authors Ivan Lara y Andrés Romero
 * @date 7 Enero 2023
 *
 * @copyright Universidad de Valencia
 */
 
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

const int TAM = 50;
typedef bool Malla[TAM][TAM];

void Mostrar(const Malla);
unsigned int NVecinas(const Malla, int, int);
int Actualiza(Malla);
void Inicializa(ifstream &, Malla);

// Funciones Auxiliares
void IrA (unsigned int, unsigned int);
void OcultaCursor();

int main()
{
    Malla m; // malla
    string nombre; //nombre del fichero con el patron
    ifstream f;
    int i = 0, nGeneraciones = 0, finJuego = 0;

    system("mode con:cols=50 lines=50"); //tamaño de la ventana
    OcultaCursor();

    // Empieza el juego
    cout << "Introduce nombre de fichero: ";
    // cin >> nombre;
    nombre = "Patrones/canon.txt";

    cout << "Introduce el número de pasos a simular (generaciones): ";
    // cin >> nGeneraciones;
    nGeneraciones = 130;
    system("cls");

    f.open(nombre.c_str());
    if (f.is_open())
    {
        Inicializa(f, m);
        f.close();

        do
        {
            Mostrar(m);
            finJuego = Actualiza(m);

            IrA (0, 0);
            cout  << "Generación: " << i << endl; // imprime ciclo actual
            Sleep(100); // espera 100 milisegundos
            i++;
    
        }
        while (i < nGeneraciones && finJuego == 0);

        switch (finJuego)
        {
            case 0: cout << "Fin." << endl; break;
            case -1: cout << "Fin. Se toco el fin del mundo por el Oeste." << endl; break;
            case -2: cout << "Fin. Se toco el fin del mundo por el Norte." << endl; break;
            case -3: cout << "Fin. Se toco el fin del mundo por el Este." << endl; break;
            case -4: cout << "Fin. Se toco el fin del mundo por el Sur." << endl; break;
        }
        cout  << "Generaciones simuladas: " << i - 1 << endl;
    }
    else
    {
        IrA (0, 0);
        cout << "Error al abrir el fichero: " << nombre << endl;
    }

    return 0;
}

void Inicializa(ifstream & f, Malla m)
{
    string ign, x, y;

    f >> ign;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            m[i][j] = false;
        }
    }

    for (int i = 0; i < stoi(ign); i++)
    {
        f >> x;
        f >> y;
        m[stoi(x)][stoi(y)] = true;
    }
}

unsigned int NVecinas(const Malla m, int f, int c)
{
    unsigned int vivas = 0;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;

            int ni = f + i;
            int nj = c + j;

            if (ni >= 0 && ni < TAM && nj >= 0 && nj < TAM)
            {
                if (m[ni][nj])
                    vivas++;
            }
        }
    }

    return vivas;
}

int Actualiza(Malla m)
{
    Malla m2;

    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            m2[i][j] = m[i][j];

    int res = 0;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            unsigned int vivas = NVecinas(m, i, j);

            if (m[i][j] == false && vivas == 3)
            {
                m2[i][j] = true;

                if (i == 0)
                    res = -2;
                else if (i == TAM - 1)
                    res = -4;
                else if (j == 0)
                    res = -1;
                else if (j == TAM - 1)
                    res = -3;
            }
            else if (m[i][j] == true && (vivas <= 1 || vivas > 3))
            {
                m2[i][j] = false;
            }
        }
    }

    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            m[i][j] = m2[i][j];

    return res;
}

void Mostrar(const Malla m)
{
    char cel(223);

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            IrA(j, i); // Cambiar las coordenadas para alinearse con la orientación de la consola

            if (m[i][j])
                cout << cel;
            else
                cout << " ";
        }
    }
}

void IrA(unsigned int x, unsigned int y)
{
    HANDLE h;
    COORD pos;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(h, pos);
}

void OcultaCursor()
{
    HANDLE h;
    CONSOLE_CURSOR_INFO cci;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    cci.bVisible = false;
    cci.dwSize = 2;
    SetConsoleCursorInfo(h, &cci);
}

