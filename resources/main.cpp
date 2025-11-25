#include <iostream>
#include <vector>
#include <unordered_map>
#include "resources/models.h"
#include "data_loader.cpp"

int main() {
    std::vector<Movie> movies;
    std::unordered_map<int, User> users;

    loadData("resources/movies.csv", "resources/user_ratings.csv", movies, users);

    std::cout << "Movies loaded:\n";
    for (const Movie& movie : movies) {
        std::cout << movie.id << " - " << movie.title << " (" << movie.genre << ")\n";
    }

    std::cout << "\nUser ratings:\n";
    for (const auto& [userId, user] : users) {
        std::cout << "User " << userId << " rated:\n";
        for (const auto& [movieId, rating] : user.ratings) {
            std::cout << "  Movie " << movieId << " -> " << rating << "\n";
        }
    }

    return 0;
}
