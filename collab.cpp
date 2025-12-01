
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include "models.h"
#include "utils.h"

// This is Collaborative filter recommendation function. Based on user ratings it will return top 5 movie recommendations.
std::vector<int> getCFRecommendations(
    int userId,
    const std::unordered_map<int, User>& users,
    const std::vector<Movie>& movies,
    const std::string& preferredGenre,
    const std::vector<int>& excludeMovieIds = {}
) {
    // checks if user id exists
    if (!users.count(userId)) return {};

    const auto& target = users.at(userId);
    std::unordered_map<int, double> predSum, simSum;
    // goes through list of users. Loop will skip users that have already been rated.
    // If not skipped CosineSimilarity will between target and otherUser will be calculated. 
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
// This will sort predictions.
    std::sort(predictions.begin(), predictions.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::unordered_set<int> excluded(excludeMovieIds.begin(), excludeMovieIds.end());
    std::vector<int> recommendations;
    // Recomendation list being built and will be returned once it reaches a size of 5.
    for (const auto& [movieId, _] : predictions) {
        if (excluded.count(movieId)) continue;
        recommendations.push_back(movieId);
        if (recommendations.size() == 5) break;
    }

    return recommendations;
}
