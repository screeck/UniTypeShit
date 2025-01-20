#include <iostream>
#include <string>

using namespace std;

class ProduktPapierniczy {
protected:
    string rodzaj;
    string nazwa;
    double cena;

public:
    ProduktPapierniczy(string rodzaj, string nazwa, double cena) : rodzaj(rodzaj), nazwa(nazwa), cena(cena) {}

        virtual string getRodzaj() const = 0;
        virtual string getNazwa() const = 0;
        virtual double getCena() const = 0;

};

class Koperta : public ProduktPapierniczy {
private:
    string format;

public:
    Koperta(string rodzaj, string nazwa, double cena, string format) : ProduktPapierniczy(rodzaj, nazwa, cena), format(format) {}

    string getFormat() { return format; }
    string getRodzaj() const override { return rodzaj; }
    string getNazwa() const override { return nazwa; }
    double getCena() const override { return cena; }
};

class Zeszyt : public ProduktPapierniczy {
private:
    int liczbaStron;

public:
    Zeszyt(string rodzaj, string nazwa, double cena, int liczbaStron) : ProduktPapierniczy(rodzaj, nazwa, cena), liczbaStron(liczbaStron) {}
    string getRodzaj() const override { return rodzaj; }
    string getNazwa() const override { return nazwa; }
    double getCena() const override { return cena; }

    int getLiczbaStron() { return liczbaStron; }
};

class Kredki : public ProduktPapierniczy {
private:
    int liczbaSztuk;
    bool czyDrewniane;

public:
    Kredki(string rodzaj, string nazwa, double cena, int liczbaSztuk, bool czyDrewniane)
        : ProduktPapierniczy(rodzaj, nazwa, cena), liczbaSztuk(liczbaSztuk), czyDrewniane(czyDrewniane) {}

    string getRodzaj() const override { return rodzaj; }
    string getNazwa() const override { return nazwa; }
    double getCena() const override { return cena; }
    int getLiczbaSztuk() { return liczbaSztuk; }
    bool getCzyDrewniane() { return czyDrewniane; }
};

class SklepPapierniczy {
private:
    ProduktPapierniczy* produktNaStanie[1500];
    int aktualnaLiczbaProduktow;

public:
    SklepPapierniczy() : aktualnaLiczbaProduktow(0) {}

    void dodajNaStan(ProduktPapierniczy* produkt) {
        if (aktualnaLiczbaProduktow < 1500) {
            produktNaStanie[aktualnaLiczbaProduktow++] = produkt;
        }
    }

    void zdejmijZeStanu(ProduktPapierniczy* produkt) {
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            if (produktNaStanie[i] == produkt) {
               
                for (int j = i; j < aktualnaLiczbaProduktow - 1; ++j) {
                    produktNaStanie[j] = produktNaStanie[j + 1];
                }
              
                produktNaStanie[aktualnaLiczbaProduktow - 1] = nullptr;
                
                aktualnaLiczbaProduktow--;
                return;
            }
        }
        cout << "Produkt nie znaleziony!\n";
    }

    ProduktPapierniczy* znajdzProdukt(string rodzaj, string nazwa) {
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            if (produktNaStanie[i]->getRodzaj() == rodzaj && produktNaStanie[i]->getNazwa() == nazwa) {
                return produktNaStanie[i];
            }
        }
        return nullptr;
    }

    void wyswietlProdukt() {
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            cout << "Produkt: " << produktNaStanie[i]->getNazwa() << " (" << produktNaStanie[i]->getRodzaj() << ") - Cena: " << produktNaStanie[i]->getCena() << "\n";
        }
    }
};

class Pracownik {
private:
    string imie;
    string nazwisko;
    SklepPapierniczy* sklep;

public:
    Pracownik(string imie, string nazwisko, SklepPapierniczy* sklep) : imie(imie), nazwisko(nazwisko), sklep(sklep) {}

    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    SklepPapierniczy* getSklep() { return sklep; }
    void setSklep(SklepPapierniczy* nowySklep) { sklep = nowySklep; }
};

class Sprzedawca : public Pracownik {
public:
    Sprzedawca(string imie, string nazwisko, SklepPapierniczy* sklep) : Pracownik(imie, nazwisko, sklep) {}

    void sprzedajProdukt(string rodzaj, string nazwa) {
        SklepPapierniczy* sklep = getSklep();
        ProduktPapierniczy* produkt = sklep->znajdzProdukt(rodzaj, nazwa);
        if (produkt) {
            cout << "Sprzedano produkt: " << produkt->getNazwa() << "\n";
            sklep->zdejmijZeStanu(produkt);
        }
        else {
            cout << "Produkt nie znaleziony!\n";
        }
    }
};

class Zaopatrzeniowiec : public Pracownik {
private:
    ProduktPapierniczy* produktyNaPace[200];
    int aktualnaLiczbaProduktow;

public:
    Zaopatrzeniowiec(string imie, string nazwisko, SklepPapierniczy* sklep) : Pracownik(imie, nazwisko, sklep), aktualnaLiczbaProduktow(0) {}

    void zalodujProduktnaPake(ProduktPapierniczy* produkt) {
        if (aktualnaLiczbaProduktow < 200) {
            produktyNaPace[aktualnaLiczbaProduktow++] = produkt;
        }
    }

    void dostaczWszystkieProdukty() {
        SklepPapierniczy* sklep = getSklep();
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            sklep->dodajNaStan(produktyNaPace[i]);
        }
        aktualnaLiczbaProduktow = 0;
    }
};

int main() {
    SklepPapierniczy sklep;
    Koperta k1("Koperta", "C6", 0.5, "C6");
    Zeszyt z1("Zeszyt", "A5", 2.5, 32);
    Kredki kr1("Kredki", "Colorino", 5.0, 12, true);

    sklep.dodajNaStan(&k1);
    sklep.dodajNaStan(&z1);
    sklep.dodajNaStan(&kr1);

    sklep.wyswietlProdukt();

    Sprzedawca sprzedawca("Jan", "Kowalski", &sklep);
    sprzedawca.sprzedajProdukt("Zeszyt", "A5");
    
    sklep.zdejmijZeStanu(&kr1);

    sklep.wyswietlProdukt();

    return 0;
}
