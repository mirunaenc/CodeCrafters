#ifdef RECOMMENDERSYSTEM_EXPORTS
#define RECOMMENDERSYSTEM_API __declspec(dllexport)
#else
#define RECOMMENDERSYSTEM_API __declspec(dllimport)
#endif
#include <utility>

namespace recommender {
    class RECOMMENDERSYSTEM_API RecommenderSystem {
    public:
        RecommenderSystem();
        ~RecommenderSystem();
        std::pair<int, int> getMoveRecommendation(/* parametrii necesari */);
        void requestHint();
        void displayRecommendation(const std::pair<int, int>& move);
    private:

    };
}