#include "models.h"
#include <unordered_map>
#include <vector>


std::vector<int> getCFRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users {
  
}
// ISA: This file is where you build the collaborative filtering system.
// For the target user, compare their rating patterns to other users,
// estimate what rating the target user would give to movies they haven't rated,
// and then return the movie IDs with the strongest predicted ratings.
// This should be a full second algorithm so we can compare it against KNN.
