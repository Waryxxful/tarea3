#include "graph.h"

using namespace std;

Graph* csvToGraph(){
    ifstream csv;
    string line = "";
    string aux = "";

    csv.open("miserables.csv");
    int size = -1;
    int cont = -1;
    while(getline(csv,line)){ size++; } // obtiene cantidad de vectores
    Graph* graph = new Graph(size);
    csv.clear();
    csv.seekg(0); //el puntero ahora es el primer caracter del texto

    getline(csv,line); //obtiene primera linea
    for(unsigned int i = 0; i<line.length(); i++){ // agrega vectores correspondientes a la tabla hash
        if(line[i] != ';' && line[i] != '\r'){ // cuando encuentre un ; se detiene debido a que ya obtuvo el ID
            aux+=line[i]; //obtiene el id
        }else{
            if(cont != -1){ // se salta el [0][0] del csv, ya que no es un vertice y no tampoco un peso
                graph->setVertices(cont, stoi(aux));
            }
            aux = "";
            cont++;
        }
    }

    int cont2 = -1; // contador que va indicar la posicion [cont1][cont2]
    aux = ""; 
    while(getline(csv,line)){
        cont2++;
        cont = -1;
        for(unsigned int i = 0; i<line.length(); i++){
            if(line[i] != ';' && line[i] != '\r'){
                aux+=line[i]; //agrega peso de cada arco
            }else{
                if(cont != -1){ // se salta el 0, ya que el [0][x] no es un vertice ni un peso
                    graph->setEdges(cont, cont2, stoi(aux)); // agrega peso a la matriz
                }
                aux = "";
                cont++;
            }
        }
    }
    csv.close();

    csv.open("miserables_id_to_names.csv");
    cont = -1;
    getline(csv,line); //se salta la primera linea

    while (getline(csv,line)){
        cont++;
        cont2 = 0;
        for(unsigned int i = 0; i<line.length(); i++){
            if(line[i] != ',' && line[i] != '\r'){
                aux+=line[i];   
            }else{
                cont2++;
                if(cont2 == 2){ //si cont2 == 2 significa que saltó el id y pasó al nombre
                    graph->setVertices(cont,aux); // guarda nombre del vertice
                }
                aux = "";
            }
        }
    }
    csv.close();
    return graph; //retorna un grafo creado a partir de los datos del csv
}   

int mainChar(Graph* graph){
    data info;
    int gradoMayor = -INFINITO;
    int numVertice;
    for(int i = 0; i < graph->nVertex(); i++){ //busca el vertice de grado mayor
        info = graph->getData(i);
        if(info.grado > gradoMayor){
            gradoMayor = info.grado;
            numVertice = info.numVertice;
        }
    }
    return numVertice;
}

int secRelevante(Graph* graph, int principal, int** matriz){
    int size = graph->nVertex();
    int mayor = -INFINITO;
    int secundario;
    for(int i = 0; i<size; i++){ //busca quien tiene el mayor camino de menor costo respecto del principal
        if(matriz[principal][i] > mayor){
            mayor = matriz[principal][i];
            secundario = i;
        }
    }
    return secundario;
}

double factorial(int n){
    if (n > 1)
        return factorial(n-1) * n;
    return 1;
}

double averageDistance(Graph* graph, int **matriz){
    double suma = 0;
    double combinatoria;
    int size = graph->nVertex();
    for(int i = 0; i<size;i++){
        for(int j = 0; j<size;j++){ //recorre la matriz de menores costos entre par de vertices sumando 1 si el camino existe
            if(matriz[i][j] != 0 && matriz[i][j] != INFINITO){
                suma++;
            }
        }
    }
    suma/=2; //divide en 2 para no considerar 2 veces los pesos
    combinatoria = factorial(size)/(factorial(2)*factorial(size-2)); //combinaciones de pares de vertices
    suma = suma/combinatoria;

    return suma;
}

double averageWeightedDistance(Graph* graph, int** matriz){
    double suma = 0;
    double pesoArcos = 0;
    int size = graph->nVertex();
    for(int i = 0; i<size;i++){ 
        for(int j = 0; j<size;j++){ // va sumando el peso del costo minimo entre cada par de vertices
            if(matriz[i][j] != 0 && matriz[i][j] != INFINITO){
                suma+= matriz[i][j];
            }
        }
    }
    suma/=2; //divide en 2 para no considerar 2 veces los pesos
    for(int i = 0; i< size; i++){ //suma el peso de todos los arcos 
        for(int j =0; j<size; j++){
            pesoArcos+=graph->weight(i,j);
        }
    }
    pesoArcos/=2; //divide en 2 para no considerar 2 veces los pesos
    suma = suma/pesoArcos;
    return suma;
}

void salida(){
    Graph* grafo = csvToGraph();
    data info;
    int size = grafo->nVertex();
    int** costosMin = new int*[size]; //matriz que va a contener costos minimos de cada par de vertices
    for(int i = 0; i<size;i++){ // se crea matriz [n][n]
        costosMin[i] = new int[size];
    }
    grafo->floydsWarshalls(costosMin); //se obtiene costo minimo de cada par de vertices

    int principal = mainChar(grafo);
    int secRel = secRelevante(grafo, principal, costosMin);
    double diametro = averageDistance(grafo,costosMin);
    double diametroPeso = averageWeightedDistance(grafo,costosMin);

    info = grafo->getData(principal);
    cout<<"Personaje principal: " << info.nombre<<endl;

    info = grafo->getData(secRel);
    cout<<"Personaje secundario mas relevante: " << info.nombre<<endl;

    cout<<"Diametro: " << diametro<<endl;

    cout<<"Diametro (con pesos): " << diametroPeso<<endl;

    for(int i = 0; i<size;i++){ // se elimina matriz [n][n]
        delete[] costosMin[i];
    }
    delete[] costosMin;

}

int main(){
    salida();
}