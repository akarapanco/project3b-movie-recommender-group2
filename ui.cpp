#include <iostream>
#include <vector>
#include <unordered_map>
#include "models.h"

using namespace std;

std::vector<Movie> loadMovies(const std::string& filename);
std::unordered_map<int, User> loadUserRatings(const std::string& filename);
std::vector<int> getRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users,
    int k
);

// Isa: implement this function in collab.cpp
std::vector<int> getCFRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users
);

void showMenu() {
    cout << "\n=============================\n";
    cout << "     Movie Recommender\n";
    cout << "=============================\n";
    cout << "1. List all movies\n";
    cout << "2. List all users\n";
    cout << "3. Get KNN recommendations\n";
    cout << "4. Get Collaborative Filtering recommendations\n";
    cout << "5. Exit\n";
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

    while (choice != 5) {
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
                         << " | Ratings: " << user.ratings.size() << endl;
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

                cout << "\nKNN Recommended Movies:\n";
                for (int id : recs) {
                    for (const Movie& m : movies) {
                        if (m.id == id) {
                            cout << m.title << " (" << m.genre << ")\n";
                        }
                    }
                }
                break;
            }

            case 4: {
                int userId;
                cout << "Enter user ID: ";
                cin >> userId;

                if (users.find(userId) == users.end()) {
                    cout << "User not found!\n";
                    break;
                }

                cout << "\nCollaborative Filtering Recommended Movies:\n";

// ISA: This section will use your collaborative filtering function.

                vector<int> recsCF = getCFRecommendations(userId, users);

                for (int id : recsCF) {
                    for (const Movie& m : movies) {
                        if (m.id == id) {
                            cout << m.title << " (" << m.genre << ")\n";
                        }
                    }
                }
                break;
            }

            case 5:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
