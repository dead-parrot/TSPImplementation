#include <algorithm>
#include <vector>
#include "construcao.cpp"

int matrizAdj[301][301];

/*FUNÇÕES A IMPLEMENTAR
bestImprovement2Opt
bestImprovementOrOpt - 1
bestImprovementOrOpt - 2
bestImprovementOrOpt - 3

*/

double calculateSwapCost(int i, int j, Solution* s){
    auto it = std::find(s->sequence.begin(), s->sequence.end(), i);
    int indexi = it - s->sequence.begin();
    auto it2 = std::find(it, s->sequence.end(), j);
    int indexj = it2 - s->sequence.begin(); 
    double novos = (matrizAdj[i-1][j] + matrizAdj[j][i+1] + matrizAdj[j-1][i] + matrizAdj[i][j+1]);
    double atuais = (matrizAdj[i-1][i] + matrizAdj[i][i+1] + matrizAdj[j-1][j] + matrizAdj[j][j+1]);
    double delta = novos - atuais;
    return delta;
}


bool bestImprovementSwap(Solution* s){
    double bestDelta = 0;
    double delta = 0;
    int best_i, best_j;
    for(int i = 1; i < s->sequence.size()-1; i++){
        for(int j = i+1; j < s->sequence.size()-1; j++){
            delta = calculateSwapCost(i,j, s);
            if (delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    if (bestDelta < 0){
        std::swap(s->sequence[best_i], s->sequence[best_j]);
        s->cost = s->cost - delta;
        return true;
    }
    return false;
}


void BuscaLocal(Solution* s){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false){
        int n = rand() % NL.size();
        switch(NL[n]){
            case 1:
                improved = bestImprovementSwap(s);
                break;
            case 2:
                improved = bestImprovement2Opt(s);
                break;
            case 3:
                improved = bestImprovementOrOpt(s,1); //Reinsertion
                break;
            case 4:
                improved = bestImprovementOrOpt(s,2); //Or-opt2
                break;
            case 5:
                improved = bestImprovementOrOpt(s,3); //Or-opt3
        }

        if(improved)
            NL = {1,2,3,4,5};
        else
            NL.erase(NL.begin() + n);
    }
}