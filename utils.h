#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <cmath>
#include "models.h"

inline double cosineSimilarity(const User& a, const User& b) {
    double dot = 0, normA = 0, normB = 0;
    for (const auto& [movieId, ratingA] : a.ratings) {
        if (b.ratings.count(movieId)) {
            double ratingB = b.ratings.at(movieId);
            dot += ratingA * ratingB;
            normA += ratingA * ratingA;
            normB += ratingB * ratingB;
        }
    }
    if (normA == 0 || normB == 0) return 0.0;
    return dot / (sqrt(normA) * sqrt(normB));
}

#endif 

