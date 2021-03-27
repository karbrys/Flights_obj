#ifndef Klasy_hpp
#define Klasy_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Pasazer;
class Ladunek;

class Lot
{
protected:
    string ID_LOTU;
    string symbol_lotu;
public:
    Lot(string symbol_lotu_="", string ID_LOTU_="")
    {
        symbol_lotu = symbol_lotu_;
        ID_LOTU = ID_LOTU_;
    }
    Lot *nastepny_Lot = NULL;
    Pasazer *lista_Pasazerow = NULL;
    Ladunek *lista_Ladunkow = NULL;
    
    void wczytywanie_lotow_pasazerow_lub_Ladunkow(string sciezka);
    
    void dodaj_lot_pasazera_lub_Ladunek(Lot *&lista_Lotow, string nazwisko, int nr_miejsca, string ID_LOTU, string symbol_lotu, string nazwa, string rodzaj, string zagrozenie, int masa);

    void zapis_list_lotow_i_Pasazerow(Lot *lista_Lotow);

    void zapis_list_lotow_i_Ladunkow(Lot *lista_Lotow);

    void dodaj_pasazera_do_Listy(Pasazer *&lista_Pasazerow, string nazwisko, int nr_miejsca);

    void dodaj_ladunek_do_Listy(Ladunek *&lista_Ladunkow, string nazwa, string rodzaj, string zagrozenie, int masa);

    void usun_liste_Pasazerow(Pasazer *&lista_Pasazerow);

    void usun_liste_Ladunkow(Ladunek *&lista_Ladunkow);

    void usun_liste_LotowP(Lot *&lista_Lotow);

    void usun_liste_LotowC(Lot *&lista_Lotow);

    friend Lot *nowy_Lot(string symbol_lotu, string ID_LOTU_);

    ~Lot();
};


class Pasazer
{
    friend class Lot;
protected:
    string nazwisko;   
    int nr_miejsca;
public:
    Pasazer(string nazwisko_, int nr_miejsca_)
    {
        nazwisko = nazwisko_;
        nr_miejsca = nr_miejsca_;
    }
    Pasazer *nastepny_Pasazer = NULL;
    
    friend Pasazer *nowy_Pasazer(string nazwisko, int nr_miejsca);

    ~Pasazer();
};

class Ladunek
{
    friend class Lot;
protected:
    string nazwa;
    string rodzaj;
    string zagrozenie;
    int masa;
public:
    Ladunek(string nazwa_, string rodzaj_, string zagrozenie_, int masa_)
    {
        nazwa = nazwa_;
        rodzaj = rodzaj_;
        zagrozenie = zagrozenie_;
        masa = masa_;
    }
    Ladunek *nastepny_Ladunek = NULL;

    friend Ladunek *nowy_Ladunek(string nazwa, string rodzaj, string zagrozenie, int masa);

    ~Ladunek();
};

#endif /* Klasy_hpp */
