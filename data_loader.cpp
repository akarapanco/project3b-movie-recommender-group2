#include "resources/models.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Movie> loadMovies(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return movies;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, genre;

        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');

        Movie m;
        m.id = std::stoi(idStr);
        m.title = title;
        m.genre = genre;
        movies.push_back(m);
    }

    return movies;
}

std::unordered_map<int, User> loadUserRatings(const std::string& filename) {
    std::unordered_map<int, User> users;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return users;
    }

    std::string line;
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

int main() {
    std::vector<Movie> movies = loadMovies("resources/movies.csv");
    std::unordered_map<int, User> users = loadUserRatings("resources/user_ratings.csv");

    std::cout << "Movies loaded: " << movies.size() << std::endl;
    for (const Movie& m : movies) {
        std::cout << m.id << " - " << m.title << " (" << m.genre << ")\n";
    }

    std::cout << "\nUsers loaded: " << users.size() << std::endl;
    for (const auto& [id, user] : users) {
        std::cout << "User " << user.id << " rated " << user.ratings.size() << " movies.\n";
    }

    return 0;
}
