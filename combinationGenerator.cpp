#include "combinationGenerator.h"

template <typename T>
CombinationGenerator<T>::CombinationGenerator(std::vector<T> is, int ml): 
initialSet(is), maxLength(ml) {
    for (int i = 0; i < ml; ++i) {
        this->combinations.push_back(-1);
    }
    int comb = 1;
    for (int i = 2; i < ml; ++i) {
        comb*=i;
    }
    this->numCombinations = comb*ml; 
    this->setSize = is.size();
}

template <typename T>
std::vector<T> CombinationGenerator<T>::nextCombination() {
    int& elem = this->combinations[this->currentIndex];
    if (elem == this->setSize - 1) {
        elem = -1;
        this->currentIndex--;
        return nextCombination();
    } else {
        elem++;   
        if (this->currentIndex < this->maxLength - 1) {
            this->currentIndex++;
        }
    }
    std::vector<T> res;
    for (const int& index : this->combinations) {
        if (index > -1)
            res.push_back(this->initialSet[index]);
    }
    return res;
}

template <typename T>
bool CombinationGenerator<T>::isDone() {
    for (auto const& index : this->combinations) {
        if (index < this->setSize - 1) {
            return false;
        }
    }
    return true; 
}
// std::vector<T> CombinationGenerator<T>::getCombination()
