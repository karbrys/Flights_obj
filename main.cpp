#include <iostream>
#include "Klasy.hpp"

int main(int argc, char** argv)
{
    // Optional:
    /*
    string pasazerowie = "";
    string ladunki = "";
    string samoloty = "";

    
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
        {
            pasazerowie = argv[i + 1];
            i++;
        }
        if (strcmp(argv[i], "-l") == 0 && i + 1 < argc)
        {
            ladunki = argv[i + 1];
            i++;
        }
    }
    */
    
    Lot pas;
    Lot lad;
    
    pas.wczytywanie_lotow_pasazerow_lub_Ladunkow("lista_pasazerow.txt");
    lad.wczytywanie_lotow_pasazerow_lub_Ladunkow("lista_ladunkow.txt");
    
    return 0;
}


