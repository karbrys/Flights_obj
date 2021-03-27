#include "Klasy.hpp"
#include <fstream>
#include <iostream>
using namespace std;

void Lot::wczytywanie_lotow_pasazerow_lub_Ladunkow(string sciezka)
{
    Lot *lista_Lotow = nullptr;
    string wczytany_nazwisko, wczytany_ID_LOTU, wczytany_symbol_lotu, wczytany_nazwa, wczytany_rodzaj, wczytany_zagrozenie;
    int wczytany_nr_miejsca, wczytany_masa;
        
    ifstream plik;
    plik.open(sciezka);
    if (plik.good() == true)
    {
        while (plik)
        {
            plik >> wczytany_ID_LOTU;
            if(wczytany_ID_LOTU == "P")
            {
                plik >> wczytany_nazwisko >> wczytany_nr_miejsca >> wczytany_symbol_lotu;
                if (plik.eof()) break;
                dodaj_lot_pasazera_lub_Ladunek(lista_Lotow, wczytany_nazwisko, wczytany_nr_miejsca, wczytany_ID_LOTU, wczytany_symbol_lotu, "", "", "", 0);
            }
            else
            {
                plik >> wczytany_nazwa >> wczytany_rodzaj >> wczytany_zagrozenie >> wczytany_masa >> wczytany_symbol_lotu;
                if (plik.eof()) break;
                dodaj_lot_pasazera_lub_Ladunek(lista_Lotow, "", 0, wczytany_ID_LOTU, wczytany_symbol_lotu, wczytany_nazwa, wczytany_rodzaj, wczytany_zagrozenie, wczytany_masa);
            }
        }
        plik.close();
    }
    else
    {
        cout << "Nie odnaleziono pliku lub plik uszkodzony." << endl;
    }
    if(wczytany_ID_LOTU == "P")
    {
        zapis_list_lotow_i_Pasazerow(lista_Lotow);
        usun_liste_LotowP(lista_Lotow);
    }
    else
    {
        zapis_list_lotow_i_Ladunkow(lista_Lotow);
        usun_liste_LotowC(lista_Lotow);
    }
}

Lot *nowy_Lot(string symbol_lotu, string ID_LOTU)
{
    return new Lot(symbol_lotu,ID_LOTU);
}

void Lot::dodaj_lot_pasazera_lub_Ladunek(Lot *&lista_Lotow, string nazwisko, int nr_miejsca, string ID_LOTU, string symbol_lotu, string nazwa, string rodzaj, string zagrozenie, int masa)
{
    if(ID_LOTU == "P")
    {
        if (lista_Lotow == nullptr)
        {
            lista_Lotow = nowy_Lot(symbol_lotu, ID_LOTU);
            dodaj_pasazera_do_Listy(lista_Lotow->lista_Pasazerow, nazwisko, nr_miejsca);
        }
        else
        {
            Lot *p = lista_Lotow;
            while(p != nullptr)
            {
                if (p->symbol_lotu.compare(symbol_lotu) == 0)
                {
                    dodaj_pasazera_do_Listy(p->lista_Pasazerow, nazwisko, nr_miejsca);
                    return;
                }
                if (p->nastepny_Lot == nullptr)
                {
                    p->nastepny_Lot = nowy_Lot(symbol_lotu, ID_LOTU);
                    dodaj_pasazera_do_Listy(p->nastepny_Lot->lista_Pasazerow, nazwisko, nr_miejsca);
                    return;
                }
                p = p->nastepny_Lot;
            }
        }
    }
    else
    {
        if (lista_Lotow == nullptr)
        {
            lista_Lotow = nowy_Lot(symbol_lotu, ID_LOTU);
            dodaj_ladunek_do_Listy(lista_Lotow->lista_Ladunkow, nazwa, rodzaj, zagrozenie, masa);
        }
        else
        {
            Lot *p = lista_Lotow;
            while(p != nullptr)
            {
                if (p->symbol_lotu.compare(symbol_lotu) == 0)
                {
                    dodaj_ladunek_do_Listy(p->lista_Ladunkow, nazwa, rodzaj, zagrozenie, masa);
                    return;
                }
                if (p->nastepny_Lot == nullptr)
                {
                    p->nastepny_Lot = nowy_Lot(symbol_lotu, ID_LOTU);
                    dodaj_ladunek_do_Listy(p->nastepny_Lot->lista_Ladunkow, nazwa, rodzaj, zagrozenie, masa);
                    return;
                }
                p = p->nastepny_Lot;
            }
        }
    }
}

Pasazer *nowy_Pasazer(string nazwisko, int nr_miejsca)
{
    return new Pasazer(nazwisko,nr_miejsca);
}

void Lot::dodaj_pasazera_do_Listy(Pasazer *&lista_Pasazerow, string nazwisko, int nr_miejsca)
{
    if (lista_Pasazerow == nullptr)
    {
        lista_Pasazerow = nowy_Pasazer(nazwisko, nr_miejsca);
    }
    else
    {
        Pasazer *poprzedni_pasazer = nullptr;
        Pasazer *obecny_pasazer = lista_Pasazerow;
        while (obecny_pasazer != nullptr)
        {
            if (obecny_pasazer->nr_miejsca > nr_miejsca)
            {
                if (obecny_pasazer == lista_Pasazerow)
                {
                    lista_Pasazerow = nowy_Pasazer(nazwisko, nr_miejsca);
                    lista_Pasazerow->nastepny_Pasazer = obecny_pasazer;
                    return;
                }
                else
                {
                    poprzedni_pasazer->nastepny_Pasazer = nowy_Pasazer(nazwisko, nr_miejsca);
                    poprzedni_pasazer->nastepny_Pasazer->nastepny_Pasazer = obecny_pasazer;
                    return;
                }
                
            }
            if (obecny_pasazer->nastepny_Pasazer == nullptr)
            {
                obecny_pasazer->nastepny_Pasazer = nowy_Pasazer(nazwisko, nr_miejsca);
                return;
            }
            poprzedni_pasazer = obecny_pasazer;
            obecny_pasazer = obecny_pasazer->nastepny_Pasazer;
        }
    }
}

Ladunek *nowy_Ladunek(string nazwa, string rodzaj, string zagrozenie, int masa)
{
    return new Ladunek(nazwa,rodzaj,zagrozenie,masa);
}

void Lot::dodaj_ladunek_do_Listy(Ladunek *&lista_Ladunkow, string nazwa, string rodzaj, string zagrozenie, int masa)
{
    if (lista_Ladunkow == nullptr)
    {
        lista_Ladunkow = nowy_Ladunek(nazwa, rodzaj, zagrozenie, masa);
    }
    else
    {
        Ladunek *obecny_ladunek = lista_Ladunkow;
        while (obecny_ladunek != nullptr)
        {
            if (obecny_ladunek->nastepny_Ladunek == nullptr)
            {
                obecny_ladunek->nastepny_Ladunek = nowy_Ladunek(nazwa, rodzaj, zagrozenie, masa);
                return;
            }
            obecny_ladunek = obecny_ladunek->nastepny_Ladunek;
        }
    }
}

void Lot::zapis_list_lotow_i_Pasazerow(Lot *lista_Lotow)
{
    ofstream plik;
    while (lista_Lotow != nullptr)
    {
        string nazwa_pliku = "P_" + lista_Lotow->symbol_lotu + ".txt";
        plik.open (nazwa_pliku);
        
        plik << left << setw(13) << setfill(' ') << "ID lotu: " << lista_Lotow->ID_LOTU << endl;
        plik << left << setw(13) << setfill(' ') << "Symbol lotu: " << lista_Lotow->symbol_lotu << endl;
        plik << endl;
        plik << "Lista pasazerow:" << endl;
        
        int liczba_rezerwacji = 0;
        Pasazer *p = lista_Lotow->lista_Pasazerow;
        
        while (p != NULL)
        {
            plik << right << setw(2) << setfill('0') << p->nr_miejsca << " " << p->nazwisko << endl;
            liczba_rezerwacji++;
            p=p->nastepny_Pasazer;
        }
        plik << endl;
        plik << "Liczba rezerwacji: " << liczba_rezerwacji << endl;
        plik.close();
        lista_Lotow=lista_Lotow->nastepny_Lot;
    }
}

void Lot::zapis_list_lotow_i_Ladunkow(Lot *lista_Lotow)
{
    ofstream plik;
    while (lista_Lotow != nullptr)
    {
        string nazwa_pliku = "C_" + lista_Lotow->symbol_lotu + ".txt";
        plik.open (nazwa_pliku);
        
        plik << left << setw(13) << setfill(' ') << "ID lotu: " << lista_Lotow->ID_LOTU << endl;
        plik << left << setw(13) << setfill(' ') << "Symbol lotu: " << lista_Lotow->symbol_lotu << endl;
        plik << endl;
        plik << "Lista ladunkow:" << endl;

        Ladunek *p = lista_Lotow->lista_Ladunkow;
        
        while (p != NULL)
        {
            plik << right << setw(2) << setfill('0') << p->masa << " " << p->nazwa << " " << p->zagrozenie << endl;
            p=p->nastepny_Ladunek;
        }
        plik << endl;
        plik.close();
        lista_Lotow=lista_Lotow->nastepny_Lot;
    }
}
void Lot::usun_liste_LotowP(Lot *&lista_Lotow)
{
    while (lista_Lotow != nullptr)
    {
        Lot *pl = lista_Lotow->nastepny_Lot;
        
        usun_liste_Pasazerow(lista_Lotow->lista_Pasazerow);
        delete lista_Lotow;
        lista_Lotow = pl;
    }
}
void Lot::usun_liste_LotowC(Lot *&lista_Lotow)
{
    while (lista_Lotow != nullptr)
    {
        Lot *pl = lista_Lotow->nastepny_Lot;
        
        usun_liste_Ladunkow(lista_Lotow->lista_Ladunkow);
        delete lista_Lotow;
        lista_Lotow = pl;
    }
}

void Lot::usun_liste_Pasazerow(Pasazer *&lista_Pasazerow)
{
    while (lista_Pasazerow != nullptr)
    {
        Pasazer *pp = lista_Pasazerow->nastepny_Pasazer;
        delete lista_Pasazerow;
        lista_Pasazerow = pp;
    }
}

void Lot::usun_liste_Ladunkow(Ladunek *&lista_Ladunkow)
{
    while (lista_Ladunkow != nullptr)
    {
        Ladunek *pp = lista_Ladunkow->nastepny_Ladunek;
        delete lista_Ladunkow;
        lista_Ladunkow = pp;
    }
}

Lot::~Lot()
{
    cout << "Usunieto" << endl;
}

Pasazer::~Pasazer()
{
    cout << "Usunieto" << endl;
}

Ladunek::~Ladunek()
{
    cout << "Usunieto" << endl;
}
