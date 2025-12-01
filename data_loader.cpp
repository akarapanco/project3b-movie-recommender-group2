#include "models.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <algorithm>

std::vector<Movie> loadMovies(const std::string& filename) {
    std::vector<Movie> list;
    std::ifstream file(filename);
    if (!file.is_open()) return list;

    std::string line;
    getline(file, line); 

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id, t, g;

        getline(ss, id, ',');
        getline(ss, t, ',');
        getline(ss, g, ',');

        if (id.empty() || !std::all_of(id.begin(), id.end(), ::isdigit)) {
            std::cerr << "[loadMovies] Skipping bad line: " << line << "\n";
            continue;
        }

        try {
            Movie m;
            m.id = std::stoi(id);
            m.title = t;
            m.genre = g;
            list.push_back(m);
        } catch (...) {
            std::cerr << "[loadMovies] Failed to parse line: " << line << "\n";
        }
    }
    return list;
}

std::unordered_map<int, User> loadUserRatings(const std::string& filename) {
    std::unordered_map<int, User> map;
    std::ifstream file(filename);
    if (!file.is_open()) return map;

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string u, m, r;

        getline(ss, u, ',');
        getline(ss, m, ',');
        getline(ss, r, ',');

        if (u.empty() || m.empty() || r.empty()) {
            std::cerr << "[loadUserRatings] Incomplete line: " << line << "\n";
            continue;
        }

        try {
            int uid = std::stoi(u);
            int mid = std::stoi(m);
            double rating = std::stod(r);

            map[uid].id = uid;
            map[uid].ratings[mid] = rating;
        } catch (...) {
            std::cerr << "[loadUserRatings] Failed to parse line: " << line << "\n";
            continue;
        }
    }

    return map;
}
