#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Profesor{
    public:
    string ime;

    Profesor(string n) : ime(n) {};

    void promjeniIme(const string& drugoIme){
        ime = drugoIme;
    }
};

class Predmet{
    public:
    string ime;
    vector<Profesor*> profesori;

    Predmet(string n) : ime(n) {};

    void dodajProfesora(Profesor& p){
        profesori.push_back(&p);
    }
};


class Fakultet{
    public:
    string ime;
    vector<Predmet> listaPredmeta;
    vector<Profesor> listaProfesora;

    Fakultet (string a) : ime(a){};

    void dodajPredmet(const Predmet& p){
        listaPredmeta.push_back(p);
    }

    void dodajProfesora(const Profesor& p){
        listaProfesora.push_back(p);
    }

    Profesor& pronadjiProfesora(const string& trazenoIme){
        for ( Profesor& p : listaProfesora)
            if(p.ime == trazenoIme)
                return p;
        
        throw runtime_error("Nema profesora : " + trazenoIme);
    }

    Predmet& pronadjiPredmet(const string& trazenoIme){
        for ( Predmet& p : listaPredmeta)
            if (p.ime == trazenoIme)
                return p;
            
        throw std::runtime_error("Nema predmeta: " + trazenoIme);
    }
};

int main(){

  Fakultet f("FET");

  f.dodajPredmet(Predmet("Strukture"));
  f.dodajPredmet(Predmet("OOP"));
  f.dodajProfesora(Profesor("Amer"));
  f.dodajProfesora(Profesor("Edin"));

  try {
    auto& edin = f.pronadjiProfesora("Edin");
    auto& amer = f.pronadjiProfesora("Amer");

    f.pronadjiPredmet("Strukture").dodajProfesora(edin);
    f.pronadjiPredmet("OOP").dodajProfesora(edin);
    f.pronadjiPredmet("OOP").dodajProfesora(amer);

    amer.promjeniIme("Amer H.");

    cout << "OOP nastavnici: " << endl;
    for( const auto& p : f.pronadjiPredmet("OOP").profesori )
      cout << "  " << p->ime << endl;

    cout << "Strukture nastavnici: " << endl;
    for( const auto& p : f.pronadjiPredmet("Strukture").profesori )
      cout << "  " << p->ime << endl;

    cout << "Baze nastavnici: " << endl;
    for( const auto& p : f.pronadjiPredmet("Baze").profesori )
      cout << "  " << p->ime << endl;
  }
  catch (const std::runtime_error& e) {
    cout << e.what() << endl;
  }
}

    
