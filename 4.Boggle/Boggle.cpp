#include "Boggle.h"
#include "random.h"
#include "shuffle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    board_p = new Grid<char>(4,4);
    board = *board_p;
    human_score = 0;
    compt_score = 0;
    this -> dictionary = dictionary;
    if(!BoggleGUI::isInitialized()){
        BoggleGUI::initialize(board.numRows(), board.numCols());
        BoggleGUI::setAnimationDelay(100);
    }
    if (boardText == "") {
        for (string cube : CUBES){
            boardText += cube[randomInteger(0,cube.length()-1)];
        }
        boardText = shuffle(boardText);
    }
    BoggleGUI::labelAllCubes(boardText);
    for (int r = 0; r < sqrt(boardText.length()); r++){
        for (int c = 0; c < sqrt(boardText.length()); c++){
            board[r][c] = boardText[r*sqrt(boardText.length())+c];
        }
    }
    cout << "It's your turn!" << endl;
    BoggleGUI::setStatusMessage("It's your turn!");
}

char Boggle::getLetter(int row, int col) const {
    if (row >= board.numRows()  || row < 0){
        throw row;
    }
    else if (col >= board.numCols() || col < 0) {
        throw col;
    }
    return board[row][col];
}

bool Boggle::checkWord(string word) const {
    if ((dictionary.contains(word)) && (word.length() >= 4) && (!your_words.contains(word))) {
        return true;
    }
    else {
        cout << "You must enter an unfound 4+ letter word from the dictionary." << endl;
        BoggleGUI::setStatusMessage("You must enter an unfound 4+ letter word from the dictionary.");
        return false;
    }
}

bool Boggle::humanWordSearch(int row, int col, string rest, Grid<int> &mark){
    bool result;
    if (rest.length() == 0){
        return true;
    }
    for (int r = -1; r < 2; r++){
        for (int c = -1; c < 2; c++){
            if((r!=0 || c!=0) && board.inBounds(row+r,col+c) && mark[row+r][col+c] == 0 && board[row+r][col+c] == rest[0]){
                mark[row+r][col+c] = 1;
                BoggleGUI::setHighlighted(row+r,col+c,true);
                result = humanWordSearch(row+r, col+c, rest.substr(1), mark);
                mark[row+r][col+c] = 0;
                BoggleGUI::setHighlighted(row+r,col+c,false);
                if(result) {break;}
            }
        }
    }
    return result;
}

bool Boggle::humanWordSearch(string word) {
    bool result = false;
    int row = 0;
    int col = 0;
    word = toUpperCase(word);
    Grid<int> mark(board.numRows(),board.numCols(),0); //mark 0 as doesn't touch
    if (checkWord(word)){
    while (!result && row < board.numRows()){
        if (board[row][col] == word[0]) {
            mark[row][col] = 1; //mark 1 as in route
            BoggleGUI::setHighlighted(row,col,true);
            result = result || humanWordSearch(row,col,word.substr(1),mark);
            mark[row][col] = 0;
            BoggleGUI::setHighlighted(row,col,false);
        }
        if (col < board.numCols()-1) {col += 1;}
        else {
            col = 0;
            row += 1;
        }
    }
    if (result) {
        your_words.add(word);
        human_score += word.length() - 3;
        cout << "You found a new word! \"" << word << "\"" << endl;
        BoggleGUI::recordWord(word, BoggleGUI::HUMAN);
        BoggleGUI::setScore(human_score, BoggleGUI::HUMAN);
        BoggleGUI::setStatusMessage("You found a new word! \""+word+"\"");
        return result;
    }
    else {
        cout << "That word can't be formed on this board." << endl;
        BoggleGUI::setStatusMessage("That word can't be formed on this board.");
        return result;
    }
    }
    return result;
}

int Boggle::getScoreHuman() const {
    return human_score;
}

void Boggle::computerWordSearch(int row, int col, string pre, Grid<int>& mark) {
    if ((dictionary.contains(pre)) && (pre.length() > 3) && (!your_words.contains(pre)) && (!compt_words.contains(pre))){
        compt_words.add(pre);
        compt_score += pre.length() - 3;
        BoggleGUI::recordWord(pre, BoggleGUI::COMPUTER);
        BoggleGUI::setScore(compt_score, BoggleGUI::COMPUTER);
    }
    if (!dictionary.containsPrefix(pre)) {return;}
    for (int r = -1; r < 2; r++){
        for (int c = -1; c < 2; c++){
            if((r!=0 || c!=0) && board.inBounds(row+r,col+c) && mark[row+r][col+c] == 0){
                mark[row+r][col+c] = 1;
                BoggleGUI::setHighlighted(row+r,col+c,true);
                pre += board[row+r][col+c];
                computerWordSearch(row+r, col+c, pre, mark);
                mark[row+r][col+c] = 0;
                BoggleGUI::setHighlighted(row+r,col+c,false);
                pre = pre.erase(pre.length()-1,1);
            }
        }
    }
}

void Boggle::computerWordSearch() {
    cout << "It's my turn!" << endl;
    BoggleGUI::setStatusMessage("It's my turn!");
    int row = 0;
    int col = 0;
    string pre;
    Grid<int> mark(board.numRows(),board.numCols(),0); //mark 0 as doesn't touch
    while (row < board.numRows()){
        pre += board[row][col];
        mark[row][col] = 1; //mark 1 as in route
        BoggleGUI::setHighlighted(row,col,true);
        computerWordSearch(row,col,pre,mark);
        mark[row][col] = 0;
        BoggleGUI::setHighlighted(row,col,false);
        pre = "";
        if (col < board.numCols()-1) {col += 1;}
        else {
            col = 0;
            row += 1;
        }
    }
    cout << "My words (" << compt_words.size() << "): " << compt_words << endl;
    cout << "My score: " << compt_score << endl;
}

int Boggle::getScoreComputer() const {
    return compt_score;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    for (int r = 0; r < boggle.board.numRows(); r++) {
        for (int c = 0; c < boggle.board.numCols(); c++) {
            out << boggle.getLetter(r,c);
        }
        out << endl;
    }
    out << "Your words (" << boggle.your_words.size() << "): " << boggle.your_words << endl;
    out << "Your score: " << boggle.human_score << endl;
    return out;
}
