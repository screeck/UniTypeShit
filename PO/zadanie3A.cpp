#include <iostream>
#include <string>

using namespace std;

class Silnik;
class Samochod;

class Samochod {
private:
    string marka;
    string model;
    bool czyPrzykreconeKola;
    Silnik* silnik;

    friend class Mechanik;
    friend void fn_zamontuj_silnik_w_samochodzie(Silnik* silnik, Samochod* samochod);

public:
    Samochod(string mar = "Ford", string mod = "Mustang", bool czyKola = false, Silnik* sil = nullptr)
        : marka(mar), model(mod), czyPrzykreconeKola(czyKola), silnik(sil) {}
};

class Silnik {
private:
    string VIN;
    double maxPojemnosciOleju;
    double aktPojemnosciOleju;
    Samochod* samochod;

    friend class Mechanik;
    friend void fn_zamontuj_silnik_w_samochodzie(Silnik* silnik, Samochod* samochod);

public:
    Silnik(string vin = "b.d.", double maxPoOleju = 6.2, double aktPoOleju = 2.5, Samochod* sam = nullptr)
        : VIN(vin), maxPojemnosciOleju(maxPoOleju), aktPojemnosciOleju(aktPoOleju), samochod(sam) {}
};

class Mechanik {
private:
    string imie;
    string nazwisko;

public:
    Mechanik(string i, string n) : imie(i), nazwisko(n) {}

    void dolejOlejSilnikowy(Silnik* silnik, double pojemnosc) {
        if (silnik->aktPojemnosciOleju + pojemnosc <= silnik->maxPojemnosciOleju) {
            silnik->aktPojemnosciOleju += pojemnosc;
            cout << "Dolano " << pojemnosc << "L oleju. Aktualny poziom: " << silnik->aktPojemnosciOleju << "L.\n";
        }
        else {
            cout << "Nie mozna dolac tyle oleju. Maksymalna pojemnosc: " << silnik->maxPojemnosciOleju << "L.\n";
        }
    }

    void przykrecKola(Samochod* samochod) {
        samochod->czyPrzykreconeKola = true;
        cout << "Kola zostaly przykrecane do samochodu " << samochod->marka << " " << samochod->model << ".\n";
    }
};

void fn_zamontuj_silnik_w_samochodzie(Silnik* silnik, Samochod* samochod) {
    if (silnik && samochod) {
        silnik->samochod = samochod;
        samochod->silnik = silnik;
        cout << "Silnik o VIN " << silnik->VIN << " zostal zamontowany w samochodzie " << samochod->marka << " " << samochod->model << ".\n";
    }
    else {
        cout << "Nie mozna zamontowac silnika - brak poprawnych danych.\n";
    }
}

int main() {
    // Tworzenie obiektow
    Samochod mojSamochod;
    Silnik mojSilnik("ABC123", 5.0, 1.5);
    Mechanik mechanik("Jan", "Kowalski");

    // Test funkcji i metod
    fn_zamontuj_silnik_w_samochodzie(&mojSilnik, &mojSamochod);
    mechanik.dolejOlejSilnikowy(&mojSilnik, 2.0);
    mechanik.przykrecKola(&mojSamochod);

    return 0;
}
