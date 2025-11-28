#include <vector>
#include <unordered_map>
#include "models.h"
#include <cmath>
using namespace std;

// ISA: Your job in this file is to write the full KNN recommendation function.
std::vector<int> getRecommendations(
    int targetUserId,
    const std::unordered_map<int, User>& users,
    int k)
{


    vector <int> movie_IDs;
    // This checks if user exists
    if (users.count(targetUserId) == 0)
    {

        return movie_IDs;
    }

    vector<pair<double, int >> totals;
    const User& check = users.at(targetUserId);
    // the below code will do distance calculations and store into a vector.
    for (auto a : users)
    {

        if (a.first != targetUserId)
        {








            double total=0;
            int count=0;
            
            for (auto b : check.ratings)
            {

                if (a.second.ratings.count(b.first))
                {

                    double num = b.second - a.second.ratings.at(b.first);
                    count = count + 1;
                    total += num * num;
                }
            }
           
            if (count > 0)
            {
                totals.push_back({ sqrt(total / count),a.first });

            }
        }
    }

    sort(totals.begin(), totals.end());

    // The below code block will store the k nearest neighbors into a vector

  //  int min_num = min(totals.size(), k);
    vector <int> KN;

    for (int i = 0; i < min((int)totals.size(), k); i++)

    {

        KN.push_back(totals[i].second);
    }

    unordered_map <int, int> counter;
    unordered_map <int, double> numbers;
    // this block of code will store data into a map to help calculate ratings
    for (int c : KN)
    {

        const User& nearest = users.at(c);

        for (auto d : nearest.ratings)
        {
            if (check.ratings.count(d.first) == 0)
            {

                counter[d.first] = counter[d.first] + 1;
                numbers[d.first] = numbers[d.first]+ d.second;
            }

        }
    }
    // this section of code calculates ratings and stores into a vector
    vector<pair<double, int>> ratings;
    for (auto m : numbers)
    {
        long double x = m.second / counter[m.first];
        ratings.push_back({x,m.first });
    }

    sort(ratings.begin(), ratings.end());
    reverse(ratings.begin(), ratings.end());


    for (auto i : ratings)
    {

        movie_IDs.push_back(i.second);
    }
    
    return movie_IDs;
     }


// You will take the target user, measure how similar they are to every other user,
// pick the closest users, look at the movies those users rated, and recommend
// the movies the target user hasn’t seen yet. The function should return a list
// of movie IDs that you think the target user would like based on similar users.

