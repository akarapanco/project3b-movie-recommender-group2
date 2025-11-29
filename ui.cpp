#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "models.h"

using namespace std;

vector<Movie> loadMovies(const string& filename);
unordered_map<int, User> loadUserRatings(const string& filename);
unordered_map<int, string> loadUserGenres(const string& filename);
int matchUserToProfile(const string& favGenre, int favMovie,
                       const unordered_map<int, string>& genres,
                       const unordered_map<int, User>& users);

vector<int> getRecommendations(int userId,
                               const unordered_map<int, User>& users,
                               int k);

vector<int> getCFRecommendations(int userId,
                                 const unordered_map<int, User>& users);

void showMenu() {
    cout << "\nWhat should I watch next?\n";
    cout << "1. People With Similar Taste Also Liked (KNN)\n";
    cout << "2. We Think You Would LOVE These ❤️ (CF)\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Movie> movies = loadMovies("resources/movies.csv");
    unordered_map<int, User> users = loadUserRatings("resources/user_ratings.csv");
    unordered_map<int, string> genres = loadUserGenres("resources/user_genres.csv");

    if (movies.empty() || users.empty() || genres.empty()) {
        cout << "Error loading data.\n";
        return 1;
    }

    string name;
    cout << "Enter your name: ";
    cin >> name;

    string favGenre;
    cout << "Enter your favorite genre: ";
    cin >> favGenre;

    int favMovieId;
    cout << "Enter your favorite movie ID: ";
    cin >> favMovieId;

    int matchedUserId = matchUserToProfile(favGenre, favMovieId, genres, users);
    if (matchedUserId == -1) {
        cout << "Could not match you to a viewer profile.\n";
        return 0;
    }

    cout << "\nProfile matched. Let's find your next movie.\n";

    int choice = 0;
    while (choice != 3) {
        showMenu();
        cin >> choice;

        switch (choice) {

            case 1: {
                vector<int> recs = getRecommendations(matchedUserId, users, 5);
                cout << "\nPeople With Similar Taste Also Liked:\n";
                for (int id : recs) {
                    for (auto& m : movies) {
                        if (m.id == id)
                            cout << m.title << " (" << m.genre << ")\n";
                    }
                }
                break;
            }

            case 2: {
                vector<int> recs = getCFRecommendations(matchedUserId, users);
                cout << "\nWe Think You Would LOVE These ❤️:\n";
                for (int id : recs) {
                    for (auto& m : movies) {
                        if (m.id == id)
                            cout << m.title << " (" << m.genre << ")\n";
                    }
                }
                break;
            }

            case 3:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}
