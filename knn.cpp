#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include "models.h"
#include "utils.h"
// Declaring KNN nearest neighbors function
std::vector<int> getKNNRecommendations(
    int userId,
    const std::unordered_map<int, User>& users,
    const std::vector<Movie>& movies,
    const std::string& preferredGenre
) {
    if (!users.count(userId)) return {};

    const User& target = users.at(userId);
    std::vector<std::pair<int, double>> similarities;

    for (const auto& [otherId, otherUser] : users) {
        if (otherId == userId) continue;
        double sim = cosineSimilarity(target, otherUser);
        if (sim > 0.0) similarities.emplace_back(otherId, sim);
    }

    std::sort(similarities.begin(), similarities.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::unordered_map<int, double> movieScores;
    int k = 5, neighborsChecked = 0;

    for (const auto& [neighborId, sim] : similarities) {
        if (neighborsChecked >= k) break;
        const auto& neighbor = users.at(neighborId);
        bool added = false;
        for (const auto& [movieId, rating] : neighbor.ratings) {
            if (target.ratings.count(movieId)) continue;

            auto it = std::find_if(movies.begin(), movies.end(),
                [&](const Movie& m) { return m.id == movieId && m.genre == preferredGenre; });

            if (it != movies.end()) {
                movieScores[movieId] += rating * sim;
                added = true;
            }
        }
        if (added) ++neighborsChecked;
    }

    std::vector<std::pair<int, double>> ranked(movieScores.begin(), movieScores.end());
    std::sort(ranked.begin(), ranked.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<int> recommendations;
    for (const auto& [movieId, _] : ranked) {
        if (recommendations.size() == 5) break;
        recommendations.push_back(movieId);
    }

    return recommendations;
}
