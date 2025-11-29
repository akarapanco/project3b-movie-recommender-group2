#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "models.h"

using namespace std;

static double euclideanDistance(const User& a, const User& b) {
    double sum = 0.0;

    for (const auto& [movieId, ratingA] : a.ratings) {
        if (b.ratings.count(movieId)) {
            double diff = ratingA - b.ratings.at(movieId);
            sum += diff * diff;
        }
    }

    return sqrt(sum);
}

vector<int> getKNN(int targetId,
                   const unordered_map<int, User>& users,
                   int K)
{
    const User& target = users.at(targetId);

    vector<pair<double,int>> distances;

    for (const auto& [uid, user] : users) {
        if (uid == targetId) continue;

        double dist = euclideanDistance(target, user);
        if (dist > 0)
            distances.push_back({ dist, uid });
    }

    sort(distances.begin(), distances.end(),
         [](auto& a, auto& b){ return a.first < b.first; });

    int neighbors = min(K, (int)distances.size());

    vector<double> score(1001, 0.0);
    vector<double> weight(1001, 0.0);

    for (int i = 0; i < neighbors; i++) {
        double dist = distances[i].first;
        int uid = distances[i].second;

        double w = 1.0 / (dist + 1e-6);

        for (auto& [movieId, rating] : users.at(uid).ratings) {
            if (target.ratings.count(movieId)) continue;

            score[movieId] += w * rating;
            weight[movieId] += w;
        }
    }

    vector<pair<double,int>> ranking;
    for (int movieId = 1; movieId <= 1000; movieId++) {
        if (weight[movieId] > 0) {
            double avg = score[movieId] / weight[movieId];
            ranking.push_back({ avg, movieId });
        }
    }

    sort(ranking.begin(), ranking.end(),
         [](auto& a, auto& b){ return a.first > b.first; });

    vector<int> top5;
    for (int i = 0; i < 5 && i < ranking.size(); i++) {
        top5.push_back(ranking[i].second);
    }

    return top5;
}


