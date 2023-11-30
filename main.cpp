#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Osoba {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

string wczytajLinie() {
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

int generujNoweID(const vector<Osoba>& osoby) {
    int noweID = 1;
    for (const Osoba& osoba : osoby) {
        if (osoba.id >= noweID) {
            noweID = osoba.id + 1;
        }
    }
    return noweID;
}

int dodajOsobe(vector<Osoba>& osoby) {
    Osoba nowaOsoba;
    nowaOsoba.id = generujNoweID(osoby);
    cout << "Podaj imie: ";
    nowaOsoba.imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nowaOsoba.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    nowaOsoba.numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    nowaOsoba.email = wczytajLinie();
    cout << "Podaj adres: ";
    nowaOsoba.adres = wczytajLinie();

    osoby.push_back(nowaOsoba);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << nowaOsoba.id << "|" << nowaOsoba.imie << "|" << nowaOsoba.nazwisko << "|"
             << nowaOsoba.numerTelefonu << "|" << nowaOsoba.email << "|" << nowaOsoba.adres << "|" << endl;
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku!" << endl;
        system("pause");
    }

    cout << endl << "Osoba zostala dodana" << endl;
    system("pause");
    return osoby.size();
}


void odczytajDaneZPliku(vector<Osoba>& osoby) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()) {
        Osoba nowaOsoba;
        string linia;
        while (getline(plik, linia)) {
            string fragment;
            int licznikFragmentow = 0;
            stringstream ss(linia);
            while (getline(ss, fragment, '|')) {
                switch (licznikFragmentow) {
                    case 0:
                        nowaOsoba.id = stoi(fragment);
                        break;
                    case 1:
                        nowaOsoba.imie = fragment;
                        break;
                    case 2:
                        nowaOsoba.nazwisko = fragment;
                        break;
                    case 3:
                        nowaOsoba.numerTelefonu = fragment;
                        break;
                    case 4:
                        nowaOsoba.email = fragment;
                        break;
                    case 5:
                        nowaOsoba.adres = fragment;
                        break;
                }
                licznikFragmentow++;
            }
            osoby.push_back(nowaOsoba);
        }
        plik.close();
    }
}

void zapiszOsobyDoPliku(const vector<Osoba>& osoby) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::trunc);

    if (plik.good()) {
        for (const Osoba& osoba : osoby) {
            plik << osoba.id << "|" << osoba.imie << "|" << osoba.nazwisko << "|"
                 << osoba.numerTelefonu << "|" << osoba.email << "|" << osoba.adres << "|" << endl;
        }
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku!" << endl;
        system("pause");
    }
}

void wyswietlInformacjeOsoby(const Osoba& osoba) {
    cout << "ID: " << osoba.id << endl;
    cout << "Imie: " << osoba.imie << endl;
    cout << "Nazwisko: " << osoba.nazwisko << endl;
    cout << "Numer telefonu: " << osoba.numerTelefonu << endl;
    cout << "Email: " << osoba.email << endl;
    cout << "Adres: " << osoba.adres << endl;
    cout << "------------------------" << endl;
}

void wyswietlWszystkieOsoby(const vector<Osoba>& osoby) {
    for (const Osoba& osoba : osoby) {
        wyswietlInformacjeOsoby(osoba);
    }
    system("pause");
}

void wyszukajPoImieniu(const vector<Osoba>& osoby) {
    string szukaneImie;
    cout << "Podaj imie do wyszukania: ";
    cin >> szukaneImie;

    bool znaleziono = false;

    for (const Osoba& osoba : osoby) {
        if (osoba.imie == szukaneImie) {
            wyswietlInformacjeOsoby(osoba);
            znaleziono = true;
        }
    }

    if (!znaleziono) {
        cout << "Nie znaleziono osob o podanym imieniu." << endl;
    }
    system("pause");
}

void wyszukajPoNazwisku(const vector<Osoba>& osoby) {
    string szukaneNazwisko;
    cout << "Podaj nazwisko do wyszukania: ";
    cin >> szukaneNazwisko;

    bool znaleziono = false;

    for (const Osoba& osoba : osoby) {
        if (osoba.nazwisko == szukaneNazwisko) {
            wyswietlInformacjeOsoby(osoba);
            znaleziono = true;
        }
    }

    if (!znaleziono) {
        cout << "Nie znaleziono osob o podanym nazwisku." << endl;
    }
    system("pause");
}

void edytujOsobe(vector<Osoba>& osoby) {
    int id;
    cout << "Podaj ID osoby do edycji: ";
    cin >> id;

    for (Osoba& osoba : osoby) {
        if (osoba.id == id) {
            cout << "Wybierz numer pola do edycji:" << endl;
            cout << "1  imie" << endl;
            cout << "2  nazwisko" << endl;
            cout << "3  numer telefonu" << endl;
            cout << "4  email" << endl;
            cout << "5  adres" << endl;
            cout << "6  powrot do menu" << endl;

            int numerPola;
            cin >> numerPola;

            if (numerPola == 6) {
                return;
            }

            string nowaWartosc;
            cout << "Podaj nowa wartosc: ";
            cin.ignore();
            getline(cin, nowaWartosc);

            switch (numerPola) {
                case 1:
                    osoba.imie = nowaWartosc;
                    break;
                case 2:
                    osoba.nazwisko = nowaWartosc;
                    break;
                case 3:
                    osoba.numerTelefonu = nowaWartosc;
                    break;
                case 4:
                    osoba.email = nowaWartosc;
                    break;
                case 5:
                    osoba.adres = nowaWartosc;
                    break;
                default:
                    cout << "Niepoprawny numer pola." << endl;
            }
            cout << "Dane zostaly zaktualizowane." << endl;
            system("pause");
            return;
        }
    }

    cout << "Nie znaleziono osoby o podanym ID." << endl;
    system("pause");
}

void usunOsobe(vector<Osoba>& osoby) {
    int id;
    cout << "Podaj ID osoby do usuniecia: ";
    cin >> id;

    for (auto it = osoby.begin(); it != osoby.end(); ++it) {
        if (it->id == id) {
            cout << "Czy na pewno chcesz usunac te osobe? (t/n): ";
            char potwierdzenie;
            cin >> potwierdzenie;
            if (potwierdzenie == 't' || potwierdzenie == 'T') {
                osoby.erase(it);
                cout << "Osoba zostala usunieta." << endl;
                zapiszOsobyDoPliku(osoby);
            } else {
                cout << "Usuniecie anulowane." << endl;
            }
            system("pause");
            return;
        }
    }

    cout << "Nie znaleziono osoby o podanym ID." << endl;
    system("pause");
}

int main() {
    vector<Osoba> osoby;

    odczytajDaneZPliku(osoby);

    while (1) {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Edytuj osobe" << endl;
        cout << "6. Usun osobe" << endl;
        cout << "7. Zakoncz program" << endl;

        char wybor;
        cin >> wybor;

        switch (wybor) {
            case '1':
                dodajOsobe(osoby);
                break;
            case '2':
                wyszukajPoImieniu(osoby);
                break;
            case '3':
                wyszukajPoNazwisku(osoby);
                break;
            case '4':
                wyswietlWszystkieOsoby(osoby);
                break;
            case '5':
                edytujOsobe(osoby);
                break;
            case '6':
                usunOsobe(osoby);
                break;
            case '7':
                exit(0);
                break;
            default:
                cout << "Nie ma takiej opcji." << endl;
        }

        getchar();
        getchar();
        system("cls");
    }

    return 0;
}
