#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "models.h"
#include <unordered_set>


using namespace std;

vector<Movie> loadMovies(const string& filename);
unordered_map<int, User> loadUserRatings(const string& filename);
int matchUserProfile(const string& q1, const string& q2, const string& q3,
                     const string& q4, const string& q5,
                     const string& q6, const string& q7);
vector<int> getKNNRecommendations(int userId, const unordered_map<int, User>& users,
                                  const vector<Movie>& movies, const string& preferredGenre);

vector<int> getCFRecommendations(int userId, const unordered_map<int, User>& users,
                                  const vector<Movie>& movies, const string& preferredGenre,
                                  const vector<int>& alreadyRecommended);



void clearScreen() {
    cout << string(1, '\n');
}

int main() {
    vector<Movie> movies = loadMovies("movies.csv");
    unordered_map<int, User> users = loadUserRatings("user_ratings.csv");
    
    if (movies.empty() || users.empty()) {
        cout <<  "Error: Could not load required data.\n";
        return 1;
    }
    
    clearScreen();
    
    cout << R"(
    __        __   _                            _          _   _             
    \ \      / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___    
     \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  | __| '_ \ / _ \   
      \ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/   
       \_/\_/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/   \__|_| |_|\___|   

             "WHAT SHOULD YOU WATCH?" — Movie Recommender Quiz
    )";

    cout << "\n=============================================================\n";
    cout << "✨ Ready to discover your next favorite movie?\n";
    cout << "✨ Answer 7 quick questions and get personalized picks!\n";
    cout << "=============================================================\n\n";
    
    string q1, q2, q3, q4, q5, q6, q7;
    

    cout << "\n";
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│                ✨ QUESTION 1: MOVIE WORLD ✨                │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ What type of movie world pulls you in the most?            │\n";
    cout << "│ a) A cozy, heart-melting world full of romance             │\n";
    cout << "│ b) A mind-bending, futuristic universe of big ideas        │\n";
    cout << "│ c) A magical, whimsical animated world                     │\n";
    cout << "│ d) A thrilling, mysterious world full of suspense          │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q1;
    
    cout << "\n";
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│            ✨ QUESTION 2: EMOTIONAL EXPERIENCE ✨           │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ What emotional experience are you looking for today?       │\n";
    cout << "│ a) Romantic, sweet, or emotionally deep                    │\n";
    cout << "│ b) Exciting, intense, or action-packed                     │\n";
    cout << "│ c) Comforting, adorable, or lighthearted                   │\n";
    cout << "│ d) Surprising, dark, or thought-provoking                  │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q2;
    
    cout << "\n";
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│               ✨ QUESTION 3: FAVORITE MOMENT ✨             │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ Which movie moment would you enjoy the most?               │\n";
    cout << "│ a) Two characters finally confessing their love            │\n";
    cout << "│ b) A high-stakes chase or dramatic showdown                │\n";
    cout << "│ c) A funny sidekick or heartwarming animated moment        │\n";
    cout << "│ d) A shocking reveal that changes everything               │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q3;
    
    cout << "\n";
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│               ✨ QUESTION 4: STORY VALUES ✨                │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ What do you value most in a movie’s story?                 │\n";
    cout << "│ a) Romance, relationships, and emotions                    │\n";
    cout << "│ b) Adventure, tension, and adrenaline                      │\n";
    cout << "│ c) Creativity, imagination, and world-building             │\n";
    cout << "│ d) Mystery, suspense, and clever storytelling              │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q4;
    
    cout << "\n";
    cout << "┌──────────────────────────────────────────────────────────────────────────┐\n";
    cout << "│                      ✨ QUESTION 5: DESERT ISLAND ✨                      │\n";
    cout << "├──────────────────────────────────────────────────────────────────────────┤\n";
    cout << "│ If you were stranded and could only watch one genre forever, pick one:   │\n";
    cout << "│ a) Romance  b) Thriller  c) Sci-Fi  d) Animation                         │\n";
    cout << "└──────────────────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q5;
    
    cout << "\n";
    cout << "┌───────────────────────────────────────────────────────────────┐\n";
    cout << "│              ✨ QUESTION 6: PACE PREFERENCE ✨                 │\n";
    cout << "├───────────────────────────────────────────────────────────────┤\n";
    cout << "│ What pace do you prefer your movies to have?                  │\n";
    cout << "│ a) Slow, emotional, and character-driven                      │\n";
    cout << "│ b) Fast, energetic, and unpredictable                         │\n";
    cout << "│ c) Light, easy to follow, and fun                             │\n";
    cout << "│ d) Medium pace but full of tension and buildup                │\n";
    cout << "└───────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q6;
    
    cout << "\n";
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│          ✨ QUESTION 7: MAIN CHARACTER VIBES ✨             │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│ What kind of main character do you connect with most?      │\n";
    cout << "│ a) Someone falling in love or growing emotionally          │\n";
    cout << "│ b) A brave hero fighting through danger                    │\n";
    cout << "│ c) A lovable, quirky, animated character                   │\n";
    cout << "│ d) A smart thinker solving mysteries or secrets            │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n→ ";
    cin >> q7;
    
    clearScreen();
    
    int matchedUserId = matchUserProfile(q1, q2, q3, q4, q5, q6, q7);
    if (!users.count(matchedUserId)) {
        cout << "❌ Sorry, we couldn't match your preferences to a known user.\n";
        return 1;
    }
    
    bool knnShown = false;
    bool cfShown = false;
    int choice = 0;
    
    unordered_set<int> shownIds;
    vector<int> knnRecs;
    vector<int> cfRecs;
    
    while (choice != 3) {
        cout << "\n";
        cout << "╔═════════════════════════════════════════════════════════════╗\n";
        cout << "║               🎬 WHAT SHOULD YOU WATCH NEXT?                ║\n";
        cout << "╠═════════════════════════════════════════════════════════════╣\n";
        
        if (!knnShown)
            cout << "║ 1. People With Similar Taste Also Liked (KNN)               ║\n";
        if (!cfShown)
            cout << "║ 2. We Think You Would LOVE These ❤️ (CF)                     ║\n";
        
        cout << "║ 3. Exit                                                     ║\n";
        cout << "╚═════════════════════════════════════════════════════════════╝\n→ ";
        
        cin >> choice;
        
        clearScreen();
        string preferredGenre;
        if (q5 == "a") preferredGenre = "Romance";
        else if (q5 == "b") preferredGenre = "Thriller";
        else if (q5 == "c") preferredGenre = "Sci-Fi";
        else if (q5 == "d") preferredGenre = "Animation";
        
        if (choice == 1 && !knnShown) {
            cout << "\n🎥 People With Similar Taste Also Liked:\n\n";
            
            vector<int> rawKnn = getKNNRecommendations(matchedUserId, users, movies, preferredGenre);
            
            for (int id : rawKnn) {
                if (!shownIds.count(id)) {
                    knnRecs.push_back(id);
                    shownIds.insert(id);
                }
                if (knnRecs.size() >= 5) break;
            }
            
            if (knnRecs.empty()) {
                cout << "⚠️ No recommendations found. Showing top movies instead:\n";
                for (int i = 0; i < 5 && i < movies.size(); ++i)
                    cout << "• " << movies[i].title << "\n";
            } else {
                for (int id : knnRecs)
                    for (const Movie& m : movies)
                        if (m.id == id)
                            cout << "• " << m.title << "\n";
            }
            
            knnShown = true;
        }
        
        else if (choice == 2 && !cfShown) {
            cout << "\n❤️ Movies We Think You'll LOVE:\n\n";
            
            vector<int> rawCf = getCFRecommendations(matchedUserId, users, movies, preferredGenre, knnRecs);
            
            for (int id : rawCf) {
                if (!shownIds.count(id)) {
                    cfRecs.push_back(id);
                    shownIds.insert(id);
                }
                if (cfRecs.size() >= 5) break;
            }
            
            if (cfRecs.empty()) {
                cout << "⚠️ No CF results found. Here's what's trending:\n";
                for (int i = 0; i < 5 && i < movies.size(); ++i)
                    cout << "• " << movies[i].title << "\n";
            } else {
                for (int id : cfRecs)
                    for (const Movie& m : movies)
                        if (m.id == id)
                            cout << "• " << m.title << "\n";
            }
            
            cfShown = true;
        }
        
        else if (choice == 3) {
            cout << "\n╔═════════════════════════════════════════════════╗\n";
            cout << "║    👋 THANK YOU FOR USING THE RECOMMENDER!        ║\n";
            cout << "║            Enjoy your movie night! 🍿✨            ║\n";
            cout << "╚═══════════════════════════════════════════════════╝\n";
            break;
        }
        
        else {
            cout << "⚠️ Invalid or already used option. Try again.\n";
        }
        
        if (knnShown && cfShown) {
            cout << "\n🎉 You've seen all available recommendations!\n";
            cout << "You may now choose '3' to exit.\n";
        }
    }
    
    return 0;
    
}
