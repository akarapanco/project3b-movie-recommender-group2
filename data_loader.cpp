#include "models.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<Movie> loadMovies(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, genre;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genre, ',');

        if (idStr == "id") continue;

        Movie m;
        m.id = stoi(idStr);
        m.title = title;
        m.genre = genre;
        movies.push_back(m);
    }

    return movies;
}

unordered_map<int, User> loadUserRatings(const string& filename) {
    unordered_map<int, User> users;
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string uStr, mStr, rStr;

        getline(ss, uStr, ',');
        getline(ss, mStr, ',');
        getline(ss, rStr, ',');

        if (uStr == "user_id") continue;

        int uid = stoi(uStr);
        int mid = stoi(mStr);
        double rating = stod(rStr);

        users[uid].id = uid;
        users[uid].ratings[mid] = rating;
    }

    return users;
}

unordered_map<int, string> loadUserGenres(const string& filename) {
    unordered_map<int, string> ug;
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string uStr, gStr;

        getline(ss, uStr, ',');
        getline(ss, gStr, ',');

        if (uStr == "user_id") continue;

        ug[stoi(uStr)] = gStr;
    }

    return ug;
}

