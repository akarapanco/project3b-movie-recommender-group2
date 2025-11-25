#include <string>
#include <unordered_map>
#include <vector>
#include "models.h"

struct UserProfile {
    int id;
    std::string genre;
};

std::unordered_map<int, std::string> loadUserGenres(const std::string& filename) {
    std::unordered_map<int, std::string> genreMap;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, genre;

        std::getline(ss, idStr, ',');
        std::getline(ss, genre, ',');

        genreMap[std::stoi(idStr)] = genre;
    }

    return genreMap;
}
int matchUserToProfile(
    const std::string& favGenre,
    int favMovie,
    const std::unordered_map<int, std::string>& genres,
    const std::unordered_map<int, User>& users
) {
    int bestUser = -1;
    int bestScore = -999;

    for (const auto& [uid, genre] : genres) {
        int score = 0;

        if (genre == favGenre)
            score += 5;
        auto it = users.find(uid);
        if (it != users.end()) {
            if (it->second.ratings.find(favMovie) != it->second.ratings.end()) {
                score += 3;
            }
        }

        if (score > bestScore) {
            bestScore = score;
            bestUser = uid;
        }
    }

    return bestUser;
}
