#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main() {
    const int NUM_USERS = 1000;    
    const int NUM_MOVIES = 100;      
    const int RATINGS_PER_USER = 120; 

    ofstream out("user_ratings.csv");
    if (!out.is_open()) {
        cout << "Error opening file.\n";
        return 1;
    }

    out << "user_id,movie_id,rating\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> movieDist(1, NUM_MOVIES);
    uniform_real_distribution<> ratingDist(1.0, 5.0);

    for (int user = 1; user <= NUM_USERS; user++) {
        for (int r = 0; r < RATINGS_PER_USER; r++) {
            int movie = movieDist(gen);
            double rating = ratingDist(gen);

            out << user << "," << movie << "," << rating << "\n";
        }
    }

    out.close();
    
    return 0;
}
