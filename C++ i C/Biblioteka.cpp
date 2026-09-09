#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>
using namespace std;

class knjiga {
    string naslov;
    string autor;
public:
knjiga ( const string& naslov, const string& autor) : naslov(naslov), autor(autor){}
knjiga ( const knjiga& druga ){
 naslov = druga.naslov;
 autor = druga.autor;
}
knjiga ( knjiga&& druga ){
    naslov = move(druga.naslov);
    autor = move(druga.autor);
}
knjiga& operator=( const knjiga& druga){
    if ( this != &druga){
       naslov = druga.naslov;
       autor = druga.autor;
    }
    return *this;
}

void print() const {
 cout << "\"" << naslov << "\" od " << autor << endl;
 }
 string uzmiNaslov() const{
    return naslov;
 }
};

class biblioteka {
       vector<knjiga> knjige;
public:
void dodajKnjigu(const knjiga &knjiga){
    knjige.push_back(knjiga);
}

void dodajKnjigu(knjiga&& knjiga){
    knjige.push_back(move(knjiga));
}
void ukloniPoindeksu( const int &index){
    if ( index >= 0 && index <knjige.size())
      knjige.erase(knjige.begin() + index);
    else cout << "Nepostojeci indeks!" << endl;
}
void ispisKnjiga (){
    if (knjige.empty())
     cout << "Biblioteka je prazna!" << endl;
     else 
        for ( const auto& c : knjige)
         c.print();
     }
void pretragaPoNaslovu ( const string &naslov){
    bool nadjena = false;
    for ( const auto& c : knjige)
        if ( c.uzmiNaslov() == naslov){
            c.print();
            nadjena = true;
        }else if( nadjena = false)
            cout << "Nema knjige pod tim naslovom!" << endl;
          }
};

int main() {
    biblioteka biblioteka;

    knjiga book1("Mali princ", "Antonio");
    knjiga book2("1984", "George");
    knjiga book3("Antigona", "Sofoklo");

    biblioteka.dodajKnjigu(book1);
    biblioteka.dodajKnjigu(move(book2));

    cout << "Pretraga po naslovu:" << endl;
    biblioteka.pretragaPoNaslovu("1984");
    cout << endl;

    biblioteka.dodajKnjigu(book3);

    cout << "Knjige u biblioteci:" << endl;
    biblioteka.ispisKnjiga();

    return 0;
}
