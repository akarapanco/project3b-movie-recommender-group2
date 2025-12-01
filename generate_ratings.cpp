
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
#include <set>

struct Rating {
    int userId;
    int movieId;
    double rating;
};

std::vector<Rating> generateRatings(int numUsers, int numMovies, int ratingsPerUser) {
    std::vector<Rating> ratings;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> ratingDist(1.0, 5.0);
    std::uniform_int_distribution<int> movieDist(1, numMovies);

    for (int user = 1; user <= numUsers; ++user) {
        std::set<int> ratedMovies;
        while (ratedMovies.size() < ratingsPerUser) {
            int movieId = movieDist(generator);
            if (ratedMovies.insert(movieId).second) {
                double score = std::round(ratingDist(generator) * 2.0) / 2.0;
                ratings.push_back({ user, movieId, score });
            }
        }
    }
    return ratings;
}

void writeRatingsToCSV(const std::vector<Rating>& ratings, const std::string& filename) {
    std::ofstream file(filename);
    file << "user_id,movie_id,rating\n";
    for (const auto& r : ratings) {
        file << r.userId << "," << r.movieId << "," << r.rating << "\n";
    }
    file.close();
}

int main() {
    const int totalUsers = 5000;
    const int movies = 100;
    const int ratingsPerUser = 20;

    std::vector<Rating> ratings = generateRatings(totalUsers, movies, ratingsPerUser);
    writeRatingsToCSV(ratings, "user_ratings.csv");

    std::cout << "Finished: " << ratings.size()
              << " ratings written to user_ratings.csv for " << totalUsers << " users.\n";

    return 0;
}
