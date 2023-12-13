#include "RecommenderSystem.h"
#include <iostream>

recommender::RecommenderSystem::RecommenderSystem()
{
}

recommender::RecommenderSystem::~RecommenderSystem()
{
}

std::pair<int, int> recommender::RecommenderSystem::getMoveRecommendation()
{
	return std::pair<int, int>();
}

void recommender::RecommenderSystem::requestHint()
{
    std::cout << "Ganditi-va la urmatoarea mutare sau apasati 'h' pentru un hint." << std::endl;
    char userInput;
    std::cin >> userInput;
    if (userInput == 'h' || userInput == 'H') {
        std::pair<int, int> hint = getMoveRecommendation(/* parametrii necesari */);
        std::cout << "Hint: Plasati un pilon la linia " << hint.first
            << " si coloana " << hint.second << "." << std::endl;
    }
}

void recommender::RecommenderSystem::displayRecommendation(const std::pair<int, int>& move)
{
}
