#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "models.h"

using namespace std;

vector<Movie> loadMovies(const string& filename);
unordered_map<int, User> loadUserRatings(const string& filename);

vector<int> getRecommendations(int targetUserId,
                               const unordered_map<int, User>& users,
                               int k);

// Isa: implement Collaborative Filtering logic in collab.cpp
vector<int> getCFRecommendations(int targetUserId,
                                 const unordered_map<int, User>& users);

int main() {
    vector<Movie> movies = loadMovies("resources/movies.csv");
    unordered_map<int, User> users = loadUserRatings("resources/user_ratings.csv");

    if (movies.empty() || users.empty()) {
        cout << "Error loading data.\n";
        return 1;
    }

    string username;
    string favGenre;

    cout << "\n==============================\n";
    cout << "     What Should I Watch?\n";
    cout << "==============================\n\n";

    cout << "Enter your name: ";
    cin >> username;

    cout << "Enter your favorite genre: ";
    cin >> favGenre;

    int matchedUserId = -1;

    for (const auto& [uid, user] : users) {
        for (const auto& rating : user.ratings) {
            for (const Movie& m : movies) {
                if (m.id == rating.first && m.genre == favGenre) {
                    matchedUserId = uid;
                    break;
                }
            }
            if (matchedUserId != -1) break;
        }
        if (matchedUserId != -1) break;
    }

    if (matchedUserId == -1) {
        matchedUserId = 1001;
    }

    int choice = 0;

    while (choice != 3) {
        cout << "\n==============================\n";
        cout << "   What Should I Watch Next?\n";
        cout << "==============================\n";
        cout << "1. People With Similar Taste Also Liked (KNN)\n";
        cout << "2. We Think You Would LOVE These ❤️ (CF)\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        cin >> choice;

        if (choice == 1) {
            vector<int> recs = getRecommendations(matchedUserId, users, 5);

            cout << "\nPeople With Similar Taste Also Liked:\n";
            int count = 0;
            for (int id : recs) {
                for (const Movie& m : movies) {
                    if (m.id == id && count < 5) {
                        cout << "- " << m.title << " (" << m.genre << ")\n";
                        count++;
                    }
                }
            }
        }

        else if (choice == 2) {
            vector<int> recsCF = getCFRecommendations(matchedUserId, users);

            cout << "\nWe Think You Would LOVE These ❤️:\n";
            int count = 0;
            for (int id : recsCF) {
                for (const Movie& m : movies) {
                    if (m.id == id && count < 5) {
                        cout << "- " << m.title << " (" << m.genre << ")\n";
                        count++;
                    }
                }
            }
        }

        else if (choice == 3) {
            cout << "Goodbye!\n";
        }
    }

    return 0;
}
