#include <iostream>
#include <string>


using namespace std;


class ProduktPapierniczy {





};




class SklepPapierniczy {

private:
    ProduktPapierniczy* produktNaStanie[1500];
    int aktualnaLiczbaProduktow;

public:

    SklepPapierniczy() {};


    void dodajNaStan(ProduktPapierniczy* produkt) {};
    void zdejmijZeStanu(ProduktPapierniczy* produkt) {};
    ProduktPapierniczy* znajdzProdukt(string rodzaj, string nazwa) {};
    void wyswietlProdukt() {};
};



class Pracownik {

private:
    string imie;
    string nazwisko;
    SklepPapierniczy* sklep;
public:
    Pracownik(string imie, string nazwisko, SklepPapierniczy* sklep) {};
    string getimie();
    string getNazwisko() {};
    SklepPapierniczy* getSklep() {};
    void setSklep(SklepPapierniczy* sklep) {};



    friend class Sprzedawca;
    friend class Zaopatrzeniowiec;

};


class Sprzedawca {
public:
    Sprzedawca(string imie, string nazwisko, SklepPapierniczy* sklep) {};
    void sprzedajProdukt(string rodzaj, string nazwa) {};

};

class Zaopatrzeniowiec {
private:
    ProduktPapierniczy* produktyNaPace[200];
    int aktualnaLiczbaProduktow;
public:

    Zaopatrzeniowiec(string imie, string nazwisko, SklepPapierniczy* sklep) {};

    void zalodujProduktnaPake(ProduktPapierniczy* produkt) {};
    void dostaczWszystkieProdukty() {};

};






int main() {
  

    return 0;
}
