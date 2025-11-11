#include <iostream>
#include <vector>
#include "models.h"

std::vector<Movie> recommendKNN(int userId);
std::vector<Movie> recommendCollaborative(int userId);
void compareResults(const std::vector<Movie>& knn, const std::vector<Movie>& collab);

void showMenu(int userId) {
    std::cout << "Welcome! User ID: " << userId << "\n";
    std::cout << "Generating movie recommendations...\n\n";

    std::vector<Movie> knnResults = recommendKNN(userId);
    std::vector<Movie> collabResults = recommendCollaborative(userId);

    std::cout << "🔷 KNN Recommendations:\n";
    for (const auto& movie : knnResults) {
        std::cout << "- " << movie.title << " (" << movie.genre << ") - " << movie.averageRating << "\n";
    }

    std::cout << "\n🔶 Collaborative Filtering Recommendations:\n";
    for (const auto& movie : collabResults) {
        std::cout << "- " << movie.title << " (" << movie.genre << ") - " << movie.averageRating << "\n";
    }

    std::cout << "\n📊 Comparing both algorithms...\n";
    compareResults(knnResults, collabResults);
}

int main() {
    int userId;
    std::cout << "Enter your user ID: ";
    std::cin >> userId;

    showMenu(userId);

    return 0;
}
