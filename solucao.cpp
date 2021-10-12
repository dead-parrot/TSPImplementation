#include <main.cpp>
#include "construcao.cpp"
#include "buscalocal.cpp"
#include "perturbacao.cpp"

Solution ILS(int maxIter, int maxIterIls){
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;
    for(int i = 0; i < maxIter; i++){
        Solution s = Construcao();
        Solution best = s;

        int iterIls = 0;

        while(iterIls <= maxIterIls){
            BuscaLocal(&s); 
            if(s.valorObj < best.valorObj){
                best = s;
                iterIls = 0;
            }
            //s = Perturbacao(best);
            iterIls++;
        }
        if (best.valorObj < bestOfAll.valorObj)
            bestOfAll = best;
    }
    return bestOfAll;
    }