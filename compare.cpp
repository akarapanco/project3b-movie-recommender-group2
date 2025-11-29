#include <vector>
#include <unordered_map>
#include "models.h"
#include "collab.h"
#include "knn.h"
using namespace std;

void compare_two_programs(unordered_map <int, User>& users, int k, int targetUserId)
{


	vector <int> first = getCFRecommendations(targetUserId, users);
	vector <int> second = getRecommendations(targetUserId, users, k);


	cout << "Collaborative filter recommendation system below:" << endl;
	for (int i = 1; i < (int)first.size()+1; i++)
	{

		cout <<i<< " Movie ID : " << first[i-1] <<endl;
	}

	cout << "KNN recommendation system below:" << endl;
	for (int i = 1; i < (int)second.size() + 1; i++)
	{

		cout << i << " Movie ID : " << second[i-1] << endl;
	}
	cout << "Collaborative filtering recommendation system takes the absolute value of the difference between the ratings.";
    cout <<"Then converts that difference into a score between 0 and 1."<<endl; 
	cout << "KNN calculates using the square of the difference between ratings , averages those squared distances and takes the square root of the average";
}

// ISA: This file compares the two algorithms you wrote.
// Call the KNN recommendations and your collaborative filtering recommendations,
// print both lists for the same user, and describe how the results differ.
// This will be used in our final report.
