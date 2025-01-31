#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

template<typename T>
class Sortowanie
{
public:
    virtual void posortuj(T* tablica, int rozmiar) = 0;
};

template<typename T>
class SortowanieRosnace : public Sortowanie<T>
{
public:
    void posortuj(T* tablica, int rozmiar) override
    {
        sort(tablica, tablica + rozmiar);
    }
};

template<typename T>
class SortowanieMalejace : public Sortowanie<T>
{
public:
    void posortuj(T* tablica, int rozmiar) override
    {
        sort(tablica, tablica + rozmiar, greater<T>());
    }
};

template<typename T, class Sort>
class Kolekcja
{
protected:
    Sort rodzajSortowania;
    T tablicaDanych[100];
    int rozmiar;

public:
    Kolekcja() : rozmiar(0) {}
    virtual void dodaj(T wartosc) = 0;
    virtual T zdejmij() = 0;
    virtual void posortuj() = 0;
    virtual void wydrukuj() = 0;
    virtual void oproznij() = 0;

};

template<typename T, class Sort>
class LIFO : public Kolekcja<T, Sort>
{
public:
    LIFO(Sort rdzjSort) { this->rodzajSortowania = rdzjSort; }

    void dodaj(T wartosc) override
    {
        if (this->rozmiar < 100) {
            this->tablicaDanych[this->rozmiar++] = wartosc;
        }
        else {
            cout << "Kolekcja jest pelna!" << endl;
        }
    }

    T zdejmij() override
    {
        if (this->rozmiar > 0) {
            return this->tablicaDanych[--this->rozmiar];
        }
        else {
            cout << "Kolekcja jest pusta!" << endl;
            return T();
        }
    }

    void posortuj() override
    {
        this->rodzajSortowania.posortuj(this->tablicaDanych, this->rozmiar);
    }

    void wydrukuj() override
    {
        for (int i = 0; i < this->rozmiar; ++i) {
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }

    void oproznij() override
    {
        this->rozmiar = 0;
    }


};

template<typename T, class Sort>
class FIFO : public Kolekcja<T, Sort>
{
public:
    FIFO(const Sort& rdzjSort)
    {
        this->rodzajSortowania = rdzjSort;
    }

    void dodaj(T wartosc) override
    {
        if (this->rozmiar < 100) {
            this->tablicaDanych[this->rozmiar++] = wartosc;
        }
        else {
            cout << "Kolekcja jest pelna!" << endl;
        }
    }

    T zdejmij() override
    {
        if (this->rozmiar > 0) {
            T wartosc = this->tablicaDanych[0];
            for (int i = 1; i < this->rozmiar; ++i) {
                this->tablicaDanych[i - 1] = this->tablicaDanych[i];
            }
            --this->rozmiar;
            return wartosc;
        }
        else {
            cout << "Kolekcja jest pusta!" << endl;
            return T();
        }
    }

    void posortuj() override
    {
        this->rodzajSortowania.posortuj(this->tablicaDanych, this->rozmiar);
    }

    void wydrukuj() override
    {
        for (int i = 0; i < this->rozmiar; ++i) {
            cout << this->tablicaDanych[i] << " ";
        }
        cout << endl;
    }

    void oproznij() override
    {
        this->rozmiar = 0;
    }

};

int main()
{
    SortowanieRosnace<double> sortRosnaco;
    LIFO<double, SortowanieRosnace<double>> lifo(sortRosnaco);

    lifo.dodaj(3.2);
    lifo.dodaj(1.5);
    lifo.dodaj(7.8);

    cout << "Zawartosc LIFO przed sortowaniem: ";
    lifo.wydrukuj();

    lifo.posortuj();
    cout << "Zawartosc LIFO po sortowaniu rosnaco: ";
    lifo.wydrukuj();

    cout << "Zdejmowanie elementu: " << lifo.zdejmij() << endl;

    lifo.wydrukuj();

    SortowanieMalejace<double> sortMalejaco;
    FIFO<double, SortowanieMalejace<double>> fifo(sortMalejaco);

    fifo.dodaj(4.1);
    fifo.dodaj(2.3);
    fifo.dodaj(5.9);

    cout << "\\nZawartosc FIFO przed sortowaniem: ";
    fifo.wydrukuj();

    fifo.posortuj();
    cout << "Zawartosc FIFO po sortowaniu malejaco: ";
    fifo.wydrukuj();

    cout << "Zdejmowanie elementu: " << fifo.zdejmij() << endl;

    fifo.wydrukuj();


    return 0;
}
