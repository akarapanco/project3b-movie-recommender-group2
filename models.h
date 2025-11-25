#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <unordered_map>
#include <vector>

struct Movie {
    int id;
    std::string title;
    std::string genre;
    double averageRating;
};

struct User {
    int id;
    std::unordered_map<int, double> ratings;
};

#endif
