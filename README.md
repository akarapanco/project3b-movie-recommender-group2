# Movie Recommender – Group 2

This project is a movie recommendation system. It helps users find great movies based on their answers to a 7-question quiz. The quiz matches them to a simulated user profile from a dataset of 100,000+ ratings, and shows personalized movie recommendations.

---

##Purpose

We created this project to explore recommendation systems in a creative and fun way. By building a quiz-based experience and tying it to a large dataset, we learned how to connect user preferences to real movie data and simulate a realistic recommendation engine.

---

## Project Files

- `ui.cpp` – Main file that runs the quiz and handles user input/output  
- `match_user.cpp` – Matches the quiz taker to the most similar user from the dataset  
- `compare.cpp` – Compares quiz answers to user genre profiles  
- `collab.cpp` – Collaborative filtering logic (Option 1)  
- `knn.cpp` – Used to calculate distances for similarity  
- `data_loader.cpp` – Loads all data files (CSV)  
- `models.h` – Struct definitions (Movie, UserRating, etc.)  
- `utils.h` – Utility functions  
- `generate_ratings.cpp` – Script used to generate fake user rating data (not used in final build)  
- `user_ratings.csv` – 100,001 movie ratings (user_id, movie_id, rating)  
- `user_genres.csv` – Primary genre preference for each user  
- `movies.csv` – Movie titles and genre categories  

---

## ▶️ How to Compile and Run

1. Open your terminal  
2. Navigate to the folder containing the files:
   ```bash
   cd ~/Desktop/MovieProject
   ```

3. Compile the code using:
   ```bash
   g++ -std=c++20 -o recommender ui.cpp knn.cpp collab.cpp compare.cpp match_user.cpp data_loader.cpp -Wall -O2
   ```

4. Run the program:
   ```bash
   ./recommender
   ```

---

## How It Works

- The quiz asks 7 questions about movie preferences (genre, themes, pace, characters).
- Your answers are compared to thousands of simulated users using cosine similarity.
- You are matched to the user whose preferences are closest to yours.

After that, you’ll get two recommendation options:

1. **People With Similar Taste Also Liked**  
   Uses collaborative filtering to recommend movies rated highly by users similar to your match.

2. **Movies We Think You’ll LOVE**  
   Shows the top-rated movies from your matched user's favorite genre.

---

## Team Members

- Aleksia
- Isa  
---

## Notes

- Ratings and genres are fake but realistically generated
- The dataset simulates over 5,000 unique users  
- Project built entirely in C++  
