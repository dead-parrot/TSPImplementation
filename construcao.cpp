#include <vector>
#include <math.h>
#include <time.h>
#include <algorithm>

int matrizAdj[301][301];

typedef struct Solution{
    std::vector<int> sequence;
    double cost;
} Solution;

typedef struct InsertionInfo{
    int noInserido; // no k a ser inserido
    int arestaRemovida[2]; // aresta {i,j} na qual o no k sera inserido
    double custo; // delta ao inserir k na aresta {i,j}
} InsertionInfo;

std::vector<InsertionInfo> calcularCustoInsercao(Solution* sol, std::vector<int>* CL){
    std::vector<InsertionInfo> tabela;
    InsertionInfo linha;
    for(int a = 0, b = 1; a < sol->sequence.size()-1; a++,b++){
        int i = sol->sequence[a];
        int j = sol->sequence[b];
        for(auto k: *CL){
            linha.noInserido = k;
            linha.arestaRemovida[0] = i;
            linha.arestaRemovida[1] = j;
            linha.custo = matrizAdj[i][j] + matrizAdj[i][k] - matrizAdj[i][j];
        }
        tabela.push_back(linha);
    }
    return tabela;
}

std::vector<int> escolher3NosAleatorios(){
    std::vector<int> choosen;
    choosen.push_back(1);
    for(int i = 1; i < 3; i++){
        srand(time(0));
        choosen.push_back((rand()%301)+1); //De acordo com o número de dim
        if (i == 1){
            while(choosen[1] == choosen[0]){
                srand(time(0));
                choosen.push_back((rand()%301)+1);
            }
        }
        else if(i == 2){
            while(choosen[2] == choosen[1] || choosen[2] == choosen[0]){
                srand(time(0));
                choosen.push_back((rand()%301)+1);
            }
        }
    }
    choosen.push_back(1);
    return choosen;
}

std::vector<int> nosRestantes(Solution* sol){
    std::vector<int> seq;
    for(int i = 1; i<301; i++){
        if (i != sol->sequence[0] &&
            i != sol->sequence[1] &&
            i != sol->sequence[2] &&
            i != sol->sequence[3])
            seq.push_back(i);
    }
    return seq;
}

bool compare(InsertionInfo a, InsertionInfo b){
    if (a.custo < b.custo)
        return 1;
    else
        return 0;
}

void ordenarEmOrdemCrescente(std::vector<InsertionInfo>* tabela){
    std::sort(tabela->begin(), tabela->end(), compare);
}

void inserirNaSolucao(Solution* solucao, std::vector<InsertionInfo>* tabela, int selecionado){
    int i = (*tabela)[selecionado].arestaRemovida[0];
    int j = (*tabela)[selecionado].arestaRemovida[1];
    int k = (*tabela)[selecionado].noInserido;
    
    auto it = std::find((solucao->sequence).begin(), (solucao->sequence).end(), j);
    int localParaInserir = it - (solucao->sequence).begin();
    solucao->sequence.insert(solucao->sequence.begin()+localParaInserir, k);
}

void atualizarCL(std::vector<int>* CL, int noRemover){
    std::remove((*CL).begin(), (*CL).end(), noRemover);
}

Solution Construcao(){
    Solution s;
    s.sequence = escolher3NosAleatorios();
    std::vector<int> CL = nosRestantes(&s);
    while(!CL.empty()) {
        std::vector<InsertionInfo> tabela = calcularCustoInsercao(&s, &CL);
        ordenarEmOrdemCrescente(&tabela);
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * tabela.size()));
        inserirNaSolucao(&s, &tabela, selecionado);
        atualizarCL(&CL, tabela[selecionado].noInserido);
    }

    return s;
}