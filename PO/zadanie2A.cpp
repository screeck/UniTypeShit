#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Klasa reprezentująca węzeł listy dwukierunkowej
class WezelListy {
public:
    string imie;
    string nazwisko;
    char plec; // 'm' lub 'k'
    double sredniaOcen; // od 2.0 do 5.0
    WezelListy* poprzedni;
    WezelListy* nastepny;

    WezelListy(string im, string nz, char pl, double sr)
        : imie(im), nazwisko(nz), plec(pl), sredniaOcen(sr), poprzedni(nullptr), nastepny(nullptr) {}
};

// Klasa reprezentująca listę studentów
class ListaStudentow {
private:
    WezelListy* head;
    WezelListy* tail;

public:
    ListaStudentow() : head(nullptr), tail(nullptr) {}

    ~ListaStudentow() {
        while (head != nullptr) {
            WezelListy* temp = head;
            head = head->nastepny;
            delete temp;
        }
        cout << "Lista została usunięta z pamięci.\n";
    }

    void dodajStudentaNaKoniec() {
        string imie, nazwisko;
        char plec;
        double srednia;

        cout << "Podaj imię: ";
        cin >> imie;
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        do {
            cout << "Podaj płeć (m/k): ";
            cin >> plec;
        } while (plec != 'm' && plec != 'k');

        do {
            cout << "Podaj średnią ocen (2.0 - 5.0): ";
            cin >> srednia;
        } while (srednia < 2.0 || srednia > 5.0);

        WezelListy* nowyWezel = new WezelListy(imie, nazwisko, plec, srednia);

        if (head == nullptr) {
            head = tail = nowyWezel;
        }
        else {
            tail->nastepny = nowyWezel;
            nowyWezel->poprzedni = tail;
            tail = nowyWezel;
        }

        cout << "Student został dodany na koniec.\n";
    }

    void dodajStudentaNaPoczatek() {
        string imie, nazwisko;
        char plec;
        double srednia;

        cout << "Podaj imię: ";
        cin >> imie;
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        do {
            cout << "Podaj płeć (m/k): ";
            cin >> plec;
        } while (plec != 'm' && plec != 'k');

        do {
            cout << "Podaj średnią ocen (2.0 - 5.0): ";
            cin >> srednia;
        } while (srednia < 2.0 || srednia > 5.0);

        WezelListy* nowyWezel = new WezelListy(imie, nazwisko, plec, srednia);

        if (head == nullptr) {
            head = tail = nowyWezel;
        }
        else {
            nowyWezel->nastepny = head;
            head->poprzedni = nowyWezel;
            head = nowyWezel;
        }

        cout << "Student został dodany na początek.\n";
    }

    void usunStudenta(const string& imie, const string& nazwisko) {
        WezelListy* aktualny = head;

        while (aktualny != nullptr) {
            if (aktualny->imie == imie && aktualny->nazwisko == nazwisko) {
                if (aktualny->poprzedni != nullptr) aktualny->poprzedni->nastepny = aktualny->nastepny;
                if (aktualny->nastepny != nullptr) aktualny->nastepny->poprzedni = aktualny->poprzedni;
                if (aktualny == head) head = aktualny->nastepny;
                if (aktualny == tail) tail = aktualny->poprzedni;

                delete aktualny;
                cout << "Student został usunięty.\n";
                return;
            }
            aktualny = aktualny->nastepny;
        }

        cout << "Nie znaleziono studenta o podanym imieniu i nazwisku.\n";
    }

    void wyswietlNaPozycji(int pozycja) const {
        WezelListy* aktualny = head;
        int index = 0;

        while (aktualny != nullptr) {
            if (index == pozycja) {
                cout << "Imię: " << aktualny->imie
                    << ", Nazwisko: " << aktualny->nazwisko
                    << ", Płeć: " << (aktualny->plec == 'm' ? "Mężczyzna" : "Kobieta")
                    << ", Średnia ocen: " << aktualny->sredniaOcen << endl;
                return;
            }
            aktualny = aktualny->nastepny;
            index++;
        }

        cout << "Nie znaleziono studenta na podanej pozycji.\n";
    }

    void wyswietlSredniaWyzejNiz(double srednia) const {
        WezelListy* aktualny = head;
        bool znaleziono = false;

        while (aktualny != nullptr) {
            if (aktualny->sredniaOcen > srednia) {
                cout << "Imię: " << aktualny->imie
                    << ", Nazwisko: " << aktualny->nazwisko
                    << ", Płeć: " << (aktualny->plec == 'm' ? "Mężczyzna" : "Kobieta")
                    << ", Średnia ocen: " << aktualny->sredniaOcen << endl;
                znaleziono = true;
            }
            aktualny = aktualny->nastepny;
        }

        if (!znaleziono) cout << "Nie znaleziono studentów ze średnią wyższą niż " << srednia << ".\n";
    }

    void znajdzKobieteNajblizszaSrednia(double srednia) const {
        WezelListy* aktualny = head;
        WezelListy* najlepsza = nullptr;
        double minimalnaRoznica = 1e9;

        while (aktualny != nullptr) {
            if (aktualny->plec == 'k') {
                double roznica = fabs(aktualny->sredniaOcen - srednia);
                if (roznica < minimalnaRoznica) {
                    minimalnaRoznica = roznica;
                    najlepsza = aktualny;
                }
            }
            aktualny = aktualny->nastepny;
        }

        if (najlepsza != nullptr) {
            cout << "Najbliższa średnia: \n"
                << "Imię: " << najlepsza->imie
                << ", Nazwisko: " << najlepsza->nazwisko
                << ", Średnia ocen: " << najlepsza->sredniaOcen << endl;
        }
        else {
            cout << "Nie znaleziono kobiety spełniającej kryteria.\n";
        }
    }
};

void menu() {
    ListaStudentow lista;
    int wybor;

    do {
        cout << "\nProgram do zarządzania listą studentów\n";
        cout << "[0] -> Wyjście z programu\n";
        cout << "[1] -> Dodaj nowego studenta na początek listy\n";
        cout << "[2] -> Usuń studenta o podanym imieniu i nazwisku\n";
        cout << "[3] -> Wyświetl informacje o studencie na podanej pozycji listy\n";
        cout << "[4] -> Wyświetl studentów mających średnią wyższą od podanej\n";
        cout << "[5] -> Znajdź kobietę z najbliższą średnią ocen do podanej\n";
        cout << "=================================\n";
        cout << "Wprowadź numer operacji: ";
        cin >> wybor;

        switch (wybor) {
        case 0:
            cout << "Zamykanie programu.\n";
            break;
        case 1:
            lista.dodajStudentaNaPoczatek();
            break;
        case 2: {
            string imie, nazwisko;
            cout << "Podaj imię: ";
            cin >> imie;
            cout << "Podaj nazwisko: ";
            cin >> nazwisko;
            lista.usunStudenta(imie, nazwisko);
            break;
        }
        case 3: {
            int pozycja;
            cout << "Podaj pozycję: ";
            cin >> pozycja;
            lista.wyswietlNaPozycji(pozycja);
            break;
        }
        case 4: {
            double srednia;
            cout << "Podaj wartość średniej: ";
            cin >> srednia;
            lista.wyswietlSredniaWyzejNiz(srednia);
            break;
        }
        case 5: {
            double srednia;
            cout << "Podaj wartość średniej: ";
            cin >> srednia;
            lista.znajdzKobieteNajblizszaSrednia(srednia);
            break;
        }
        default:
            cout << "Nieprawidłowa opcja. Spróbuj ponownie.\n";
        }
    } while (wybor != 0);
}

int main() {
    menu();
    return 0;
}
