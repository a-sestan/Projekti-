#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
using namespace std;

class vektor{
    private:
        int duzina;
        int *data;
        int kapacitet;
    public:
        vektor() : duzina(0), data(nullptr), kapacitet(duzina) {};
        vektor (const initializer_list<int> &lista) 
        : duzina(lista.size()), data(new int [duzina]), kapacitet(duzina){
            copy(lista.begin(), lista.end(), data);
        };
        vektor(const vektor& drugi){
            duzina = drugi.duzina;
            kapacitet = drugi.kapacitet;
            data = new int[duzina];
            copy(drugi.data, drugi.data + duzina, data);
        }
        vektor(vektor&& drugi ) noexcept{
            duzina = drugi.duzina;
            kapacitet = drugi.kapacitet;
            data = drugi.data;

            drugi.data = nullptr;
            drugi.duzina = 0;
            drugi.kapacitet = 0;
        }
        ~vektor() {
            delete [] data;
            duzina = 0;
        }

        vektor &operator=(const vektor& drugi){
            if( this != &drugi ){
                delete [] data;
                duzina = drugi.duzina;
                kapacitet = drugi.duzina;
                data = new int [duzina];
                copy(drugi.data, drugi.data + duzina, data);
            } return *this;
        }
        vektor &operator=(vektor&& drugi) noexcept {
            if( this != &drugi ){
                delete [] data;

                duzina = drugi.duzina;
                kapacitet = drugi.kapacitet;
                data = drugi.data;

                drugi.data = nullptr;
                drugi.kapacitet = 0;
                drugi.duzina = 0;
            } return *this;
        }
        bool operator==(const vektor& drugi) const {
            if ( duzina != drugi.duzina)
                return false;
            for ( int i = 0; i < duzina; i++)
                if ( data [i] != drugi.data[i])
                    return false;
            return true;
            
        }
        int &operator[](const int &i) { // citanje i pisanje
            if ( i >= 0 && i < duzina)
                return data[i];
            else throw logic_error("Ne postoji indeks");
        }
        const int& operator[](const int& i) const { // samo za citanje, za const vektor
            if (i >= 0 && i < duzina)
                return data[i];
            else throw logic_error("Ne postoji indeks");
            }

        void print() const {
            for ( auto i = 0; i < duzina; i++)
                cout << data[i] << " " ;
            cout << endl;
        }
        int velicina() const { return duzina;}
        int* begin() { return data; }
        int* end() { return data + duzina;}
        int kapacitet_vektora (){ return kapacitet; }

        void push_back(const int& novi_element){
            if ( duzina == kapacitet){
                int novi_kapacitet = (kapacitet == 0) ? 1 : kapacitet * 2;
                int *novo_data = new int [novi_kapacitet];
                for (int i = 0; i < duzina; i++)
                    novo_data[i] = data[i];
                delete [] data;
                data = novo_data;
                kapacitet = novi_kapacitet;
            }
            data[duzina] = novi_element;
            duzina++;
        }

          void push_front(const int& novi_element){
            vektor v;
            v.push_back(novi_element);
            for (int i = 0; i < duzina; i++) 
                v.push_back(data[i]);
            
            //*this = std::move(v) - ovo je najbolja opcija
            delete[]data;
            data = v.data;
            duzina = v.duzina;
            kapacitet = v.kapacitet;
            v.data = nullptr;
        }
        void pop_back(){
            if ( duzina == 0)
                throw logic_error("Vektor je prazan");
            duzina--;
        
            if( duzina < kapacitet / 4){
                int novi_kapacitet = kapacitet / 2;
                
                int *novo_data = new int[novi_kapacitet];
                for (int i = 0; i < duzina; i++)          
                    novo_data[i] = data[i];

                delete [] data;
                data = novo_data;
                kapacitet = novi_kapacitet;
            }
        }
        void pop_front(){
            if ( duzina == 0 )
                throw logic_error("Vektor je prazan");
            for ( int i = 1; i < duzina; i++)
                data[i - 1] = data[i];
            duzina--;  

            if( duzina < kapacitet / 4){
                int novi_kapacitet = kapacitet / 2;
                
                int *novo_data = new int[novi_kapacitet];
                for (int i = 0; i < duzina; i++)          
                    novo_data[i] = data[i];

                delete [] data;
                data = novo_data;
                kapacitet = novi_kapacitet;
            }
        }
        int front(){ // ako stavim int& front vracam referencu i mogu mijenjat onda
            if ( duzina == 0)
                throw logic_error("Prazan vektor");
            return data[0];
        }
        int back(){
            if ( duzina == 0)
                throw logic_error ("Prazan vektor");
            return data[duzina - 1];
        }
        bool empty() const {
            if ( duzina == 0 )
                return true;
            else return false;
        }
        void clear(){
            delete [] data;
            data = nullptr;
            duzina = 0;
            kapacitet = 0;
        }
        void insert(const int& indeks, const int& vrijednost){
            if ( indeks < 0 || indeks >= duzina)
                throw logic_error("Neispravan indeks");
            vektor v;
            for( int i = 0; i < indeks; i++)
                v.push_back(data[i]);
            v.push_back(vrijednost);
            for( int i = indeks; i < duzina; i ++)
                v.push_back(data[i]);

            delete[] data;
            data = v.data;
            duzina = v.duzina;
            kapacitet = v.kapacitet;
            v.data = nullptr;
        }
        void erase( const int& indeks ){
            if ( indeks < 0 || indeks >= duzina)
                throw logic_error("Neispravan indeks");
            vektor v;
            for ( int i = 0; i < indeks; i++)
                v.push_back(data[i]);
            for ( int i = indeks + 1; i < duzina; i++)
                v.push_back(data[i]);

            delete [] data;
            data = v.data;
            duzina = v.duzina;
            kapacitet = v.kapacitet;
            v.data = nullptr;
        }
        void kompresija(){
            if ( duzina < kapacitet){
                int *novo_data = new int[duzina];
                for ( int i = 0; i < duzina; i++){
                    novo_data[i] = data[i];
                }
                delete[] data;
                data = novo_data;
                kapacitet = duzina;
            }
        }
};

int main() {
    vektor v;
    v = {1, 2, 3, 4, 5};
    cout << endl;
    v.push_back(6);
    v.print();
    cout << endl;
    cout << v.kapacitet_vektora();
    cout << endl;
    v.kompresija();
    cout <<v.kapacitet_vektora();
    

    return 0;
}