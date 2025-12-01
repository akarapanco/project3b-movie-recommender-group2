#include "models.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>

using namespace std;


bool isNumeric(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

unordered_set<int> loadRatedUserIDs(const string& filename, int minRatings = 5) {
    unordered_map<int, int> countMap;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string uidStr;
        getline(ss, uidStr, ',');
        if (!isNumeric(uidStr)) continue;
        int uid = stoi(uidStr);
        countMap[uid]++;
    }

    unordered_set<int> validUsers;
    for (const auto& [uid, count] : countMap)
        if (count >= minRatings)
            validUsers.insert(uid);

    return validUsers;
}

int matchUserProfile(
    const string& q1, const string& q2, const string& q3,
    const string& q4, const string& q5, const string& q6,
    const string& q7
) {
    unordered_set<int> validUsers = loadRatedUserIDs("user_ratings.csv");

    ifstream file("user_genres.csv");
    if (!file.is_open()) {
        cerr << "❌ Error: Failed to open user_genres.csv\n";
        return -1;
    }

    string line;
    getline(file, line);

    string genrePref = q5 == "a" ? "Romance" :
                       q5 == "b" ? "Thriller" :
                       q5 == "c" ? "Sci-Fi" :
                       q5 == "d" ? "Animation" : "";

    int bestScore = -1;
    vector<int> bestUsers;

    while (getline(file, line)) {
        stringstream ss(line);
        string uidStr, g1, g2;
        getline(ss, uidStr, ',');
        getline(ss, g1, ',');
        getline(ss, g2, ',');

        if (!isNumeric(uidStr)) continue;
        int uid = stoi(uidStr);
        if (!validUsers.count(uid)) continue;

        int score = 0;
        if (g1 == genrePref) score += 2;
        if (g2 == genrePref) score += 2;

        if (score > bestScore) {
            bestScore = score;
            bestUsers = { uid };
        } else if (score == bestScore) {
            bestUsers.push_back(uid);
        }
    }

    if (bestUsers.empty()) return -1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, bestUsers.size() - 1);
    return bestUsers[dis(gen)];
}
