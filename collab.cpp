#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "models.h"

using namespace std;

static double cosineSimilarity(const User& a, const User& b) {
    double dot = 0.0, magA = 0.0, magB = 0.0;

    for (const auto& [movieId, ratingA] : a.ratings) {
        if (b.ratings.count(movieId)) {
            double ratingB = b.ratings.at(movieId);
            dot += ratingA * ratingB;
        }
        magA += ratingA * ratingA;
    }
    for (const auto& [_, ratingB] : b.ratings) {
        magB += ratingB * ratingB;
    }

    if (magA == 0 || magB == 0) return 0.0;
    return dot / (sqrt(magA) * sqrt(magB));
}

vector<int> getCFRecommendations(int targetUserId,
                                 const unordered_map<int, User>& users)
{
    const User& target = users.at(targetUserId);
    vector<pair<double, int>> similarityList;

    for (const auto& [id, user] : users) {
        if (id == targetUserId) continue;
        double sim = cosineSimilarity(target, user);
        if (sim > 0)
            similarityList.push_back({ sim, id });
    }

    sort(similarityList.begin(), similarityList.end(),
         [](auto& a, auto& b){ return a.first > b.first; });

    vector<double> movieScore(1001, 0.0);
    vector<double> movieWeight(1001, 0.0);

    int neighbors = min((int)similarityList.size(), 20);

    for (int i = 0; i < neighbors; i++) {
        double sim = similarityList[i].first;
        int uid = similarityList[i].second;

        for (auto& [movieId, rating] : users.at(uid).ratings) {
            if (target.ratings.count(movieId)) continue;
            movieScore[movieId] += sim * rating;
            movieWeight[movieId] += sim;
        }
    }

    vector<pair<double,int>> ranking;
    for (int movieId = 1; movieId <= 1000; movieId++) {
        if (movieWeight[movieId] > 0) {
            double score = movieScore[movieId] / movieWeight[movieId];
            ranking.push_back({ score, movieId });
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

