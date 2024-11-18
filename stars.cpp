#define _CRT_SECURE_NO_WARNINGS
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int runOneRound(const char words[][7], int nWords, int wordnum)
{
    // Validate parameters
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
        return -1;

    int tries = 0;

    while (true)
    {
        cout << "Trial word: ";
        char guess[100];
        cin.getline(guess, 100);

        // Validate word format
        int len = strlen(guess);
        bool validLength = (len >= 4 && len <= 6);

        if (validLength)
        {
            // Check all characters are lowercase letters
            bool validWord = true;
            for (int i = 0; i < len && validWord; i++)
            {
                if (!islower(guess[i]))
                    validWord = false;
            }

            if (validWord)
            {
                // Check if word is in list
                bool found = false;
                for (int i = 0; i < nWords; i++)
                {
                    if (strcmp(guess, words[i]) == 0)
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    // Valid guess - increment tries
                    tries++;

                    // If correct guess, return number of tries
                    if (strcmp(guess, words[wordnum]) == 0)
                        return tries;

                    // Count stars and planets
                    int stars = 0;
                    int planets = 0;
                    bool targetUsed[7] = { false };
                    bool guessUsed[7] = { false };

                    // First pass: count stars
                    for (int i = 0; guess[i] != '\0'; i++)
                    {
                        if (guess[i] == words[wordnum][i])
                        {
                            stars++;
                            targetUsed[i] = true;
                            guessUsed[i] = true;
                        }
                    }

                    // Second pass: count planets
                    for (int i = 0; guess[i] != '\0'; i++)
                    {
                        if (!guessUsed[i])
                        {
                            for (int j = 0; words[wordnum][j] != '\0'; j++)
                            {
                                if (!targetUsed[j] && i != j && guess[i] == words[wordnum][j])
                                {
                                    planets++;
                                    targetUsed[j] = true;
                                    guessUsed[i] = true;
                                    break;
                                }
                            }
                        }
                    }

                    cout << "Stars: " << stars << ", Planets: " << planets << endl;
                }
                else
                    cout << "I don't know that word." << endl;
            }
            else
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
        }
        else
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
    }
}

int main()
{
    const int MAXWORDS = 8000;
    char wordList[MAXWORDS][7];

    const char WORDFILENAME[] = "C:/Users/benjaminmoon/Documents/P5/smallwords.txt";
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);

    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }

    cout << "How many rounds do you want to play? ";
    int numRounds;
    cin >> numRounds;
    cin.ignore(10000, '\n');

    if (numRounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return 1;
    }

    int totalScore = 0;
    int minScore = 10000;
    int maxScore = 0;

    for (int round = 1; round <= numRounds; round++)
    {
        cout << "\nRound " << round << endl;
        int secretWordIndex = randInt(0, nWords - 1);
        int wordLen = strlen(wordList[secretWordIndex]);
        cout << "The secret word is " << wordLen << " letters long." << endl;

        int score = runOneRound(wordList, nWords, secretWordIndex);

        if (score == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << score << " tries." << endl;

        totalScore += score;
        if (score < minScore)
            minScore = score;
        if (score > maxScore)
            maxScore = score;

        double average = static_cast<double>(totalScore) / round;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << average << ", minimum: " << minScore
            << ", maximum: " << maxScore << endl;
    }

    return 0;
}