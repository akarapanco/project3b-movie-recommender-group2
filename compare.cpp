#include "models.h"
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;
vector<int> getKNNRecommendations(int userId,
                                  const unordered_map<int, User>& users,
                                  const vector<Movie>& movies,
                                  const string& preferredGenre);

vector<int> getCFRecommendations(int userId,
                                 const unordered_map<int, User>& users,
                                 const vector<Movie>& movies,
                                 const string& preferredGenre,
                                 const vector<int>& excludeMovieIds);

vector<int> getRecommendations(int userId,
                               const unordered_map<int, User>& users,
                               const vector<Movie>& movies,
                               const string& preferredGenre,
                               int choice,
                               const vector<int>& exclude = {})
{
    if (choice == 1) {
        return getKNNRecommendations(userId, users, movies, preferredGenre);
    }
    else if (choice == 2) {
        return getCFRecommendations(userId, users, movies, preferredGenre, exclude);
    }
    return {}; 
}
