#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "models.h"

using namespace std;

vector<Movie> loadMovies(const string& filename);
unordered_map<int, User> loadUserRatings(const string& filename);
string matchUserProfile(const string& genre, const string& mood, const string& time, const string& rewatch, const string& island, const string& comfort, const string& energy);

vector<int> getRecommendations(int userId, const unordered_map<int, User>& users, int k);
vector<int> getCFRecommendations(int userId, const unordered_map<int, User>& users);

void clearScreen() {
    cout << string(50, '\n');
}

string askQuestion(const string& box) {
    cout << box;
    string answer;
    cout << " → ";
    cin >> answer;
    return answer;
}

int main() {
    vector<Movie> movies = loadMovies("resources/movies.csv");
    unordered_map<int, User> users = loadUserRatings("resources/user_ratings.csv");

    if (movies.empty() || users.empty()) {
        cout << "Error: Could not load data.\n";
        return 1;
    }

    clearScreen();

    cout << "=============================================================\n";
    cout << "            ✨ WELCOME TO WHAT SHOULD I WATCH ✨              \n";
    cout << "=============================================================\n\n";

    string genre = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ 💖  WHAT'S YOUR ALL-TIME FAVORITE MOVIE GENRE?        ║\n"
        "║    A) Romance                                         ║\n"
        "║    B) Thriller / Horror                               ║\n"
        "║    C) Sci-Fi / Action                                 ║\n"
        "║    D) Animation / Disney                              ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string mood = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ 🎭  WHAT MOOD ARE YOU IN TONIGHT?                     ║\n"
        "║    A) Emotional / Crying                              ║\n"
        "║    B) Excited / Edge of seat                          ║\n"
        "║    C) Dreamy / Escaping reality                       ║\n"
        "║    D) Light / Comfort                                 ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string time = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ ⏳  HOW MUCH TIME DO YOU HAVE RIGHT NOW?              ║\n"
        "║    A) Under 90 minutes                                ║\n"
        "║    B) About 2 hours                                   ║\n"
        "║    C) A long movie is fine                            ║\n"
        "║    D) Anything works                                  ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string rewatch = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ 🔁  NEW MOVIE OR A COMFORT REWATCH?                   ║\n"
        "║    A) Brand new                                       ║\n"
        "║    B) Classic but not boring                          ║\n"
        "║    C) Total comfort movie                             ║\n"
        "║    D) Surprise me                                     ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string island = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ 🏝️  STRANDED FOREVER — WHAT GENRE DO YOU PICK?       ║\n"
        "║    A) Romance                                         ║\n"
        "║    B) Thriller / Horror                               ║\n"
        "║    C) Sci-Fi / Action                                 ║\n"
        "║    D) Animation / Disney                              ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string comfort = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ 🍿  WHAT IS *YOUR* IDEA OF A COMFORT MOVIE?           ║\n"
        "║    A) Rom-Com                                         ║\n"
        "║    B) Thriller                                        ║\n"
        "║    C) Sci-Fi / Fantasy                                ║\n"
        "║    D) Disney / Animation                              ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string energy = askQuestion(
        "╔═══════════════════════════════════════════════════════╗\n"
        "║ ⚡  WHAT'S YOUR ENERGY LEVEL TONIGHT?                 ║\n"
        "║    A) Low – something chill                           ║\n"
        "║    B) Medium – can handle a plot                      ║\n"
        "║    C) High – give me excitement                       ║\n"
        "║    D) Depends on the movie                            ║\n"
        "╚═══════════════════════════════════════════════════════╝\n"
    );

    clearScreen();

    string matchedUserIdStr =
        matchUserProfile(genre, mood, time, rewatch, island, comfort, energy);
    int matchedUserId = stoi(matchedUserIdStr);

    int choice = 0;

    while (choice != 3) {
        cout << "=============================================================\n";
        cout << "             🎬 WHAT SHOULD YOU WATCH NEXT? 🎬               \n";
        cout << "=============================================================\n";
        cout << "1. People With Similar Taste Also Liked (KNN)\n";
        cout << "2. We Think You Would LOVE These ❤️ (CF)\n";
        cout << "3. Exit\n";
        cout << "\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            vector<int> recs = getRecommendations(matchedUserId, users, 5);
            cout << "\n🎥 People With Similar Taste Also Liked:\n\n";
            for (int id : recs) {
                for (const Movie& m : movies)
                    if (m.id == id) cout << "• " << m.title << " (" << m.genre << ")\n";
            }
            cout << "\n";
        }

        else if (choice == 2) {
            vector<int> recs = getCFRecommendations(matchedUserId, users);
            cout << "\n❤️ Movies We Think You'll LOVE:\n\n";
            for (int id : recs) {
                for (const Movie& m : movies)
                    if (m.id == id) cout << "• " << m.title << " (" << m.genre << ")\n";
            }
            cout << "\n";
        }

        else if (choice == 3) {
            cout << "\nGoodbye! 🍿✨\n";
        }
    }

    return 0;
}

