This folder contains the code of the game Boggle! The Boggle game board is a square grid onto which you randomly distribute a set of letter cubes. The goal is to find words on the board by tracing a path through adjoining letters.

To begin a game, you shake up the letter cubes and lay them out on the board. The human player plays first, entering words one by one. Your code first verifies that the word is valid, then you add it to the player's word list and award the player points according to the word's length (one point per letter ≥ 4). A word is valid if it meets all of the following conditions:

-1.at least 4 letters long
-2.is a word found in the English dictionary
-3.can be formed by connecting neighboring letter cubes (using any given cube only once)
-4.has not already been formed by the player in this game (even if there are multiple paths on the board to form the same word, the word is counted at most once)

Once the player has found as many words as they can, the computer takes a turn. The computer searches through the board to find all the remaining words and awards itself points for those words. The computer typically beats the player, since you will program it to find all possible words left.
