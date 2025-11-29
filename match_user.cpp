#include "models.h"
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

int matchUserToProfile(const string& favGenre,
                       int favMovie,
                       const unordered_map<int, string>& genres,
                       const unordered_map<int, User>& users) 
{
    int bestMatch = -1;
    int bestScore = -1;

    for (auto& entry : users) {
        int uid = entry.first;

        int score = 0;

        auto it = genres.find(uid);
        if (it != genres.end()) {
            string g = it->second;

            if (g == favGenre) score += 2;
        }

        if (users.at(uid).ratings.count(favMovie)) {
            score += 3;
        }

        if (score > bestScore) {
            bestScore = score;
            bestMatch = uid;
        }
    }

    return bestMatch;
}
