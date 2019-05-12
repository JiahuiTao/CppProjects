#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "bogglegui.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col) const;
    bool humanWordSearch(string word);
    void computerWordSearch();
    int getScoreHuman() const;
    int getScoreComputer() const;
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    Grid<char>* board_p;
    Grid<char> board;
    int human_score;
    int compt_score;
    Set<string> your_words;
    Set<string> compt_words;
    Lexicon dictionary;
    bool checkWord(string word) const;
    bool humanWordSearch(int row, int col, string rest, Grid<int>& mark);
    void computerWordSearch(int row, int col, string pre, Grid<int>& mark);
};

#endif // _boggle_h
