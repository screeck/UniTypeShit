#include <iostream>
#include <string>
#include <vector>

// Klasa abstrakcyjna ProduktPapierniczy
class ProduktPapierniczy {
public:
    virtual void wypiszInformacje() const = 0; // Metoda czysto wirtualna
    virtual ~ProduktPapierniczy() {} // Wirtualny destruktor
};

// Przykładowa klasa pochodna od ProduktPapierniczy
class Dlugopis : public ProduktPapierniczy {
    std::string kolorAtramentu;

public:
    Dlugopis(const std::string& kolor) : kolorAtramentu(kolor) {}

    void wypiszInformacje() const override {
        std::cout << "Długopis, kolor atramentu: " << kolorAtramentu << std::endl;
    }
};

class SklepPapierniczy {
    ProduktPapierniczy* produktyNaStanie[1600];
    int aktualnaLiczbaProduktow;

public:
    SklepPapierniczy() : aktualnaLiczbaProduktow(0) {
        for (int i = 0; i < 1600; ++i) {
            produktyNaStanie[i] = nullptr;
        }
    }

    bool dodajProdukt(ProduktPapierniczy* produkt) {
        if (aktualnaLiczbaProduktow < 1600) {
            produktyNaStanie[aktualnaLiczbaProduktow++] = produkt;
            return true;
        }
        return false;
    }

    void wypiszProdukty() const {
        std::cout << "Produkty w sklepie:" << std::endl;
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            if (produktyNaStanie[i]) {
                produktyNaStanie[i]->wypiszInformacje();
            }
        }
    }

    ~SklepPapierniczy() {
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            delete produktyNaStanie[i];
        }
    }
};

class Zaopatrzeniowiec {
    ProduktPapierniczy* produktyNaPace[200];
    int aktualnaLiczbaProduktow;

public:
    Zaopatrzeniowiec() : aktualnaLiczbaProduktow(0) {
        for (int i = 0; i < 200; ++i) {
            produktyNaPace[i] = nullptr;
        }
    }

    bool dodajNaPake(ProduktPapierniczy* produkt) {
        if (aktualnaLiczbaProduktow < 200) {
            produktyNaPace[aktualnaLiczbaProduktow++] = produkt;
            return true;
        }
        return false;
    }

    void wypiszPake() const {
        std::cout << "Produkty na pace zaopatrzeniowca:" << std::endl;
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            if (produktyNaPace[i]) {
                produktyNaPace[i]->wypiszInformacje();
            }
        }
    }

    ~Zaopatrzeniowiec() {
        for (int i = 0; i < aktualnaLiczbaProduktow; ++i) {
            delete produktyNaPace[i];
        }
    }
};

int main() {
    SklepPapierniczy sklep;
    Zaopatrzeniowiec zaopatrzeniowiec;

    // Tworzenie produktów
    ProduktPapierniczy* dlugopis1 = new Dlugopis("Niebieski");
    ProduktPapierniczy* dlugopis2 = new Dlugopis("Czarny");

    // Dodawanie produktów do zaopatrzeniowca
    zaopatrzeniowiec.dodajNaPake(dlugopis1);
    zaopatrzeniowiec.dodajNaPake(dlugopis2);

    // Wypisanie zawartości paki zaopatrzeniowca
    zaopatrzeniowiec.wypiszPake();

    // Dodawanie produktów do sklepu
    sklep.dodajProdukt(dlugopis1);
    sklep.dodajProdukt(dlugopis2);

    // Wypisanie zawartości sklepu
    sklep.wypiszProdukty();

    return 0;
}
