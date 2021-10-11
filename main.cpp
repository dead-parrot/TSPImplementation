#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "construcao.cpp"

using namespace std;

typedef struct Solucao{
    vector<int> sequencia;
    double valorObj;
} Solucao;

void calcularValorObj(Solucao *s){
    s->valorObj = 0;
    //for(int i = 0; i < s->sequencia.size() - 1; i++)
        //s->valorObj += matrizAdj[s->sequencia[i]][s->sequencia[i+1]];
}

void exibirSolucao(Solucao *s)
{
    for(int i = 0; i < s->sequencia.size() - 1; i++)
        std::cout << s->sequencia[i] << " -> ";
    std::cout << s->sequencia.back() << std::endl;
}

int main(){
    // Exemplo de inicializacao
    Solucao s1 = {{1,6,3,2,5,4,1}, 0};
    // Iterando pelos vertices da solucao

    exibirSolucao(&s1);
    // RESULTADO: "1 -> 6 -> 3 -> 2 -> 5 -> 4 -> 1"

    // Inicializando uma solucao vazia
    Solucao s2 = {{}, 0.0};

    // Adicionando vertices na solucao
    s2.sequencia.push_back(1);
    s2.sequencia.push_back(3);
    s2.sequencia.push_back(1);
    exibirSolucao(&s2);
    // RESULTADO: "1 -> 3 -> 1"


    s2.sequencia.insert(s2.sequencia.begin() + 1, 4);
    s2.sequencia.insert(s2.sequencia.end() - 1, 5);
    s2.sequencia.insert(s2.sequencia.begin() + 2, 2);
    exibirSolucao(&s2);
    // RESULTADO: "1 -> 4 -> 2 -> 3 -> 5 -> 1"

    return 0;
}