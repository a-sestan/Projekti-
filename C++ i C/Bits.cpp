#include<iostream>
#include<bitset>

using namespace std;

void printBits(unsigned short reg){
    bitset<16> bits(reg);
    cout << bits << endl;
}

int main(){
     unsigned short broj=0;

           while (true)  {
                    cout << "1. Ispiši registar" << endl;
                    cout << "2. Postavi bit u registar" << endl;
                    cout << "3. Resetuj bit u registru" << endl;
                    cout << "4. Izlaz iz programa" << endl;
                    cout << endl << "Odaberi opciju: ";

           int meni;
           cin>>meni;
   
             if(meni==1){
                printBits(broj);
            }
             else if (meni==2){
                   int setovanjeBitaNaNekoMjesto;
                   cout<<"Unesite bit za setovanje"<<endl;
                   cin>>setovanjeBitaNaNekoMjesto;

                         if(setovanjeBitaNaNekoMjesto>=0 && setovanjeBitaNaNekoMjesto <= 15){               
                              unsigned short bit = 1 << setovanjeBitaNaNekoMjesto;
                              broj = broj | bit;
                              printBits(broj);
                         }
                         else
                            cout<<"Pogresan unos"<<endl;
            }
             else if(meni==3){
                    int bitZaReset;
                    cout<<"Unesite bit za resetovanje"<<endl;

                          if(bitZaReset>=0 && bitZaReset<=15){
                               unsigned short bit=~(1<<bitZaReset);
                               broj = broj & bit;
                               printBits(broj);
                            }
                          else 
                             cout<<"Pogresan unos"<<endl;
            }
             else if(meni==4){
                  exit(0);
            }
             else {
                  cout<<"Pogresan unos"<<endl;
            }
                      }
   return 0;
}