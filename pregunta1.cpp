#include <iostream>
#include <cstring>
#include <string>

#define M 128

using namespace std;

struct ranura{
    string termino;
    string definicion;
    int consultas;
};

ranura HT[M];

class CacheDiccionario{
    private:
    public:

    int h(const char *t){
        unsigned int *aux = (unsigned int *)t;
        int len = strlen(t) / 4;
        unsigned int sum = 0;

        for(int i = 0; i < len; i++){
            sum += aux[i];
        }

        int extra = strlen(t) - len*4;
        char temp[4];
        aux = (unsigned int *)temp;
        aux[0] = 0;
        for(int i = 0; i < extra; i++){
            temp[i] = t[len*4+i];
        }

        sum+= aux[0];

        return sum % M;
    }

    int p(string termino, int i){
        return 3*i*i;
    }

    bool query(string termino, string &significado){
        h(termino.c_str());
        int inicio;
        int pos = inicio = h(termino.c_str());
        for(int i = 1; !HT[pos].termino.empty() && HT[pos].termino != termino; i++){
            pos = (inicio + p(termino, i)) % M;
        }

        if(HT[pos].termino == termino){
            significado = HT[pos].definicion;
            HT[pos].consultas += 1;
            return 1;
        }else{
            significado = "";
            return 0;
        }
    }

    void insert(string termino, string significado){
        int inicio;
        int pos = inicio = h(termino.c_str());
        for(int i = 1; !HT[pos].termino.empty() && HT[pos].termino != termino; i++){
            pos = (inicio + p(termino, i)) % M;
        }

        if(HT[pos].termino == termino){
            HT[pos].definicion = significado;
        }else{
            HT[pos].termino = termino;
            HT[pos].definicion = significado;
        }

    }
};
int main(){
    
    CacheDiccionario dictCache;

    dictCache.insert("hash", "Una función “hash” criptográfica es, como su nombre lo indica, una función matemática utilizada en criptografía donde las más comunes agarran entradas de longitudes versátiles para restituir salidas de una longitud permanente.");
    string def;
    dictCache.query("hash", def);
    cout<<def;

    return 0;
}

