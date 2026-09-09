#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Tim {
    private:
        string imeTima;
        int bodovi;
        int datiGolovi;
        int primljeniGolovi;
    public:
        Tim (const string& n) : imeTima(n), bodovi(0), datiGolovi(0), primljeniGolovi(0) {};
        string getIme() const { return imeTima; }
        int getbodovi() const { return bodovi; }
        int getDatiGolovi() const { return datiGolovi; }
        int getPrimljeniGolovi() const { return primljeniGolovi;}

        void upisiRezultat(const int& dati, const int& primljeni) {
            datiGolovi += dati;
            primljeniGolovi += primljeni;

            if( dati > primljeni)
                bodovi += 3;
            else if ( dati == primljeni )
                bodovi += 1;
            else if ( dati < primljeni )
                bodovi += 0;
        }
 
    };

class Turnir {
    private:
        string ime;
        vector<Tim> timovi;
    public:
        Turnir (const string& s) : ime(s) {};
        void dodajTim( const Tim& tim){
            timovi.push_back(tim);
        }
        void odigraMec(const string& domacin, const string& gost, const int& golovi_domacin, const int& golovi_gost){
            for ( auto& e : timovi)
                if ( e.getIme() == domacin)
                    e.upisiRezultat(golovi_domacin, golovi_gost);
                else if (e.getIme() == gost)
                    e.upisiRezultat(golovi_gost, golovi_domacin);
        }

       void ispisiRangListu(){
            sort(timovi.begin(), timovi.end(), [](const Tim& a, const Tim& b){
                return a.getbodovi() > b.getbodovi();
            });
            cout << " -----Rang lista turnira-----" << endl;
            int pozicija = 1;
            for ( const auto& e : timovi ){
                cout << pozicija << ". " << e.getIme()
                     << " | Bodovi: " << e.getbodovi() 
             << " | Gol razlika: " << e.getDatiGolovi() << ":" << e.getPrimljeniGolovi() << endl;
             pozicija++;
            }

       }
};

int main() {
  Turnir t("Premijer liga BH");
  t.dodajTim(Tim("Bosna"));
  t.dodajTim(Tim("Celik"));
  t.dodajTim(Tim("Olimpic"));
  // (domacin, gost, golovi_domacin, golovi_gost)
  t.odigraMec("Bosna",   "Celik",   3, 1);
  t.odigraMec("Bosna",   "Olimpic", 2, 0);
  t.odigraMec("Bosna",   "Celik",   0, 0);
  t.odigraMec("Celik",   "Olimpic", 2, 0);
  t.odigraMec("Olimpic", "Celik",   0, 2);
  t.odigraMec("Olimpic", "Bosna",   0, 4);
  t.ispisiRangListu();

    return 0;
}