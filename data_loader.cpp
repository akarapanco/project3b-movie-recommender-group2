#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "models.h"

std::vector<Movie> loadMovies(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) return movies;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, genre, ratingStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, ratingStr, ',');

        Movie m;
        m.id = std::stoi(idStr);
        m.title = title;
        m.genre = genre;
        m.averageRating = std::stod(ratingStr);

        movies.push_back(m);
    }

    return movies;
}

std::unordered_map<int, User> loadUserRatings(const std::string& filename) {
    std::unordered_map<int, User> users;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) return users;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userIdStr, movieIdStr, ratingStr;

        std::getline(ss, userIdStr, ',');
        std::getline(ss, movieIdStr, ',');
        std::getline(ss, ratingStr, ',');

        int userId = std::stoi(userIdStr);
        int movieId = std::stoi(movieIdStr);
        double rating = std::stod(ratingStr);

        users[userId].id = userId;
        users[userId].ratings[movieId] = rating;
    }

    return users;
}
