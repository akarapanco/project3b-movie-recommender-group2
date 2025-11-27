#include "models.h"
#include <unordered_map>
#include <vector>
using namespace std;


std::vector<int> getCFRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users){
    set <int> list_of_movies;
    const User & target_user = users.at(targetUserId);
    vector < pair<double, int>> ratings_list;
    vector<int> movie_rec;

    // This will store the movies into a set
    for (auto a : users)
    {

        for (auto b : a.second.ratings)
        {
         

            list_of_movies.insert(b.first);
        }
   }

    // This code block will rate movies
    for (int id_num : list_of_movies)
    {
        long double rating_number=0;
        long double balancer=0;

        if (target_user.ratings.count(id_num)==0)

        {

            for (auto a : users)
            {

                if (targetUserId != a.first && a.second.ratings.count(id_num)!=0)
                {
                    long double count_1=0;
                    long double count_2=0;
                    for (auto b : target_user.ratings)
                    {

                        if (a.second.ratings.count(b.first))
                        {

                            count_1 = count_1 + 1;
                            long double temp = abs(a.second.ratings.at(b.first) - target_user.ratings.at(b.first ));
                            count_2 += (5 - temp) / 5;
                        }
                    }
                    if (count_1 >= 1)
                    {

                        
                        count_2 /= count_1;
                        balancer += count_2;
                        rating_number += count_2 * a.second.ratings.at(id_num);
                       
                    }

                }
           



            }


        }

        else
        {

            continue;
        }

        if (balancer >= 1)
        {

            long double final_rating = rating_number / balancer;
            rating_list.push_back({ final_rating,id_num });
        }


    }
 // This sorts are movie rating list.
    sort(rating_list.begin(), rating_list.end());
    reverse(rating_list.begin(), rating_list.end());
    for (auto [rating,movieId] : rating_list)
    {

        movie_rec.push_back(movieId);
    }
    return movie_rec;
}
// : This file is where you build the collaborative filtering system.
// For the target user, compare their rating patterns to other users,
// estimate what rating the target user would give to movies they haven't rated,
// and then return the movie IDs with the strongest predicted ratings.
// This should be a full second algorithm so we can compare it against KNN.

