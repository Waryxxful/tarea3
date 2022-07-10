//g++ pregunta1.cpp -o hash
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include "mergeSort.h"

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
        int nElem;
        int Ctotal;
        int Cconocidos;
        int Cdesconocidos;
    public:

    CacheDiccionario(){
        nElem = 0;
    }

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

    int h2(string termino){
        int contador = 0;
        for(int i = 0; i < termino.length(); i++){
            contador += termino[i];
        }
        return contador;
    }

    unsigned long p(string termino, int i){
        return i;
    }

    bool query(string termino, string &significado){
        Ctotal += 1;
        int inicio;
        int pos = inicio = h(termino.c_str());
        for(int i = 1; !HT[pos].termino.empty() && HT[pos].termino != termino; i++){
            pos = (inicio + p(termino, i)) % M;
        }
        
        if(HT[pos].termino == termino){
            significado = HT[pos].definicion;
            HT[pos].consultas += 1;
            if(HT[pos].definicion.length() > 0){
                Cconocidos += 1;
            }else{
                Cdesconocidos -=1;
            }
            return 1;
        }else{
            significado = "";
            return 0;
        }
    };

    void clean(){
        SortList list;
        for(int i = 0; i<M;i++){
            Index New;
            New.consultas = HT[i].consultas;
            New.key = i;
            
            list.Insert(New);
        }
        Index *arr = list.sort();

        for(int i = 0; i<M/2;i++){
            cout<<HT[arr[i].key].consultas<<endl;
            HT[arr[i].key].termino = "";
            HT[arr[i].key].definicion = "";
            HT[arr[i].key].consultas = 0;
            nElem-=1;
        }

        list.clear();

    }

    void insert(string termino, string significado){
        if(nElem == M){
            clean();
            cout<<"############################################################################################################"<<endl;
        }
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
            nElem+=1;
        }

    }

    void querystats(int &total, int &conocidos, int &desconocidos){
        total = Ctotal;
        conocidos = Cconocidos;
        desconocidos = Cdesconocidos;
    }

    void perfstats(int& accesses, int& hits, int& misses, int& cleanups){
        
    }
};

int main(){
    
    CacheDiccionario dictCache;

    string s[10000];
    for(int i = 0; i < 127; i++){
        char ch = rand() % 253 + 33;
        string p = "hash";
        p += ch;
        dictCache.insert(p, "i1");

    }   

    for(int i = 0; i < 10000; i++){
        char ch = rand() % 254 + 33;
        string p = "hash";
        p += ch;
        dictCache.query(p, s[i]);
    }
    for(int i = 0; i < 100; i++){
        for(int i = 0; i < 64; i++){
            char ch = rand() % 253 + 33;
            string p = "hash";
            p += ch;
            dictCache.insert(p, "i1");
        }   

        for(int i = 0; i < 10000; i++){
            char ch = rand() % 254 + 33;
            string p = "hash";
            p += ch;
            dictCache.query(p, s[i]);
        }
    }

    int conocidos;
    int desconocidos;
    int total;

    dictCache.querystats(total, conocidos, desconocidos);
    cout<<total<<endl;
    cout<<conocidos<<endl;
    cout<<desconocidos<<endl;

    

    return 0;
}
