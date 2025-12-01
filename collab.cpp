
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include "models.h"
#include "utils.h"

std::vector<int> getCFRecommendations(
    int userId,
    const std::unordered_map<int, User>& users,
    const std::vector<Movie>& movies,
    const std::string& preferredGenre,
    const std::vector<int>& excludeMovieIds = {}
) {

    if (!users.count(userId)) return {};

    const auto& target = users.at(userId);
    std::unordered_map<int, double> predSum, simSum;

    for (const auto& [otherId, otherUser] : users) {
        if (otherId == userId) continue;
        double sim = cosineSimilarity(target, otherUser);
        if (sim <= 0) continue;

        for (const auto& [movieId, rating] : otherUser.ratings) {
            if (target.ratings.count(movieId)) continue;

            auto it = std::find_if(movies.begin(), movies.end(),
                [&](const Movie& m) { return m.id == movieId && m.genre == preferredGenre; });

            if (it == movies.end()) continue;

            predSum[movieId] += rating * sim;
            simSum[movieId] += sim;
        }
    }

    std::vector<std::pair<int, double>> predictions;
    for (const auto& [movieId, sum] : predSum) {
        if (simSum[movieId] > 0) {
            predictions.emplace_back(movieId, sum / simSum[movieId]);
        }
    }

    std::sort(predictions.begin(), predictions.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::unordered_set<int> excluded(excludeMovieIds.begin(), excludeMovieIds.end());
    std::vector<int> recommendations;

    for (const auto& [movieId, _] : predictions) {
        if (excluded.count(movieId)) continue;
        recommendations.push_back(movieId);
        if (recommendations.size() == 5) break;
    }

    return recommendations;
}
