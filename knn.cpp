#include "models.h"
#include <vector>
#include <cmath>
#include <algorithm>

double euclideanDistance(const User& a, const User& b) {
    double sum = 0.0;
    for (const auto& [movieId, rating] : a.ratings) {
        if (b.ratings.count(movieId)) {
            double diff = rating - b.ratings.at(movieId);
            sum += diff * diff;
        }
    }
    return std::sqrt(sum);
}

std::vector<int> recommendMoviesKNN(
    const std::unordered_map<int, User>& users,
    const std::vector<Movie>& movies,
    int targetUserId,
    int k
) {
    std::vector<std::pair<double, int>> distances;

    const User& targetUser = users.at(targetUserId);

    for (const auto& [userId, user] : users) {
        if (userId == targetUserId) continue;
        double dist = euclideanDistance(targetUser, user);
        distances.push_back({dist, userId});
    }

    std::sort(distances.begin(), distances.end());

    std::unordered_map<int, int> recommendationCount;

    for (int i = 0; i < k && i < distances.size(); ++i) {
        const User& neighbor = users.at(distances[i].second);
        for (const auto& [movieId, rating] : neighbor.ratings) {
            if (targetUser.ratings.count(movieId) == 0) {
                recommendationCount[movieId]++;
            }
        }
    }

    std::vector<std::pair<int, int>> recommendations(recommendationCount.begin(), recommendationCount.end());
    std::sort(recommendations.begin(), recommendations.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<int> result;
    for (const auto& [movieId, _] : recommendations) {
        result.push_back(movieId);
        if (result.size() == 5) break;
    }

    return result;
}
