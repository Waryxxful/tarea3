#include <iostream>
#include <fstream>
#include <climits>

using namespace std;
#define VISITADO 1
typedef int tVertice;
typedef int tipoClave;
const int INFINITO = INT_MAX;

struct data{
    tVertice numVertice;
    string nombre;
    int id;
    int grado = 0;
    int marca = 0;
};


class Graph{
    private:
        int vertices;
        int **matrix;
        data *info; // se crea tabla hash para almacenar datos asociados a cada vertice
        
    public:
        Graph(int n);
        ~Graph();
        void setVertices(int num, int id);
        void setVertices(int num, string name);
        void setEdges(int i, int j, int weight);
        data getData(int num);
        int nVertex();
        void setMark(tVertice v, int marca);
        int weight(tVertice v1, tVertice v2);
        void floydsWarshalls(int** matriz);


};

Graph::Graph(int n){
    vertices = n; 
    matrix = new int*[n]; 
    for(int i = 0; i<n;i++){ // se crea la matriz adyacente de tamaño [n][n]
        matrix[i] = new int[n];
    }
    info = new data[vertices]; //tabla hash de tamaño n con la informacion de cada vertice

}

Graph::~Graph(){
    for(int i = 0; i<vertices;i++){ // se crea la matriz adyacente de tamaño [n][n]
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] info;
    
}

void Graph::setVertices(int num, int id){
    info[num].id = id; //guarda id del vertice correspondiente
    info[num].numVertice = num; //guarda num del vertice correspondiente
}

void Graph::setVertices(int num, string name){
    info[num].nombre = name; // guarda el nombre del vertice
}

void Graph::setEdges(int i, int j, int weight){
    matrix[i][j] = weight; // agrega el peso 
    if(weight != 0){ info[j].grado++; } //si el peso es distinto de 0 existe un arco, por lo que el grado aumenta
}

int Graph::nVertex(){ return vertices; }

data Graph::getData(int num){ return info[num];}

void Graph::setMark(tVertice v, int marca){ info[v].marca = marca;}

int Graph::weight(tVertice v1, tVertice v2){ return matrix[v1][v2]; }

void Graph::floydsWarshalls(int** matriz){
    int size = nVertex();
    int i,j,k;
    for(i = 0; i < size; i++){
        for(j = 0; j<size; j++){
            if(matrix[i][j]!=0){ //si existe un arco
                matriz[i][j] = matrix[i][j];
            }else if(i == j){
                matriz[i][j] = 0;
            }else{
                matriz[i][j] = INFINITO;
            }
        }
    }
    for(k = 0; k < size; k++){
        for(i = 0; i < size; i++){
            for(j=0 ; j < size; j++){
                if(matriz[i][j] > (matriz[i][k] + matriz[k][j]) && matriz[i][k] != INFINITO && matriz[k][j] != INFINITO){
                    matriz[i][j] = (matriz[i][k] + matriz[k][j]);
                }
            }
        }
    }

    for(i = 0; i < size; i++){ //como es simetrica, si una fila queda con valores infinitos se soluciona 
        for(j = 0; j<size; j++){
            matriz[i][j] = matriz[i][j] < matriz[j][i] ? matriz[i][j] : matriz[j][i];
            matriz[j][i] = matriz[i][j] < matriz[j][i] ? matriz[i][j] : matriz[j][i];
        }
    }
}   


