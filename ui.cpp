#include <iostream>
#include <vector>
#include <unordered_map>
#include "models.h"

std::vector<Movie> loadMovies(const std::string& filename);
std::unordered_map<int, User> loadUserRatings(const std::string& filename);
std::vector<int> getRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users,
    int k
);

using namespace std;

void showMenu() {
    cout << "\n=============================\n";
    cout << "     Movie Recommender\n";
    cout << "=============================\n";
    cout << "1. List all movies\n";
    cout << "2. List all users\n";
    cout << "3. Get recommendations for a user\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Movie> movies = loadMovies("resources/movies.csv");
    unordered_map<int, User> users = loadUserRatings("resources/user_ratings.csv");

    if (movies.empty() || users.empty()) {
        cout << "Error: Could not load required data.\n";
        return 1;
    }

    int choice = 0;

    while (choice != 4) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- All Movies ---\n";
                for (const Movie& m : movies) {
                    cout << m.id << " - " << m.title << " (" << m.genre << ")\n";
                }
                break;

            case 2:
                cout << "\n--- All Users ---\n";
                for (const auto& [uid, user] : users) {
                    cout << "User " << uid
                         << " | Ratings: " << user.ratings.size() << "\n";
                }
                break;

            case 3: {
                int userId, k;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter k (neighbors): ";
                cin >> k;

                if (users.find(userId) == users.end()) {
                    cout << "User not found!\n";
                    break;
                }

                vector<int> recs = getRecommendations(userId, users, k);

                cout << "\nRecommended movies:\n";
                for (int id : recs) {
                    for (const Movie& m : movies) {
                        if (m.id == id) {
                            cout << m.title << " (" << m.genre << ")\n";
                        }
                    }
                }
                break;
            }

            case 4:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
