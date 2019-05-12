#include "lexicon.h"
#include "bogglegui.h"
#include "Boggle.h"
#include "simpio.h"
#include "console.h"
#include "strlib.h"
#include <string>

using namespace std;

string getBoardInput(){
    if (getYesOrNo("Do you want to generate a random board?")){
        return "";
    }
    else {
        string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        while (true) {
            string boardText = getLine("Type the 16 letters to appear on the board:");
            if (boardText.length() != 16) {
                cout << "That is not a valid 16-letter board string. Try again." << endl;
                continue;
            }
            else {
                boardText = toUpperCase(boardText);
                bool valid = true;
                for (char c : boardText) {
                    if (s.find(c) == string::npos) {
                        cout << "That is not a valid 16-letter board string. Try again." << endl;
                        valid = false;
                        break;
                    }
                }
                if (valid) {return boardText;}
            }
         }
     }
}


void playOneGame(Lexicon& dictionary) {
    if(BoggleGUI::isInitialized()){
        BoggleGUI::reset();
        BoggleGUI::setStatusMessage("");
    }
    string boardText = getBoardInput();
    clearConsole();
    Boggle boggle(dictionary, boardText);
    while (true){
        cout << boggle << endl;
        string input = getLine("Type a word (or Enter to stop): ");
        if (input == "") {break;}
        clearConsole();
        boggle.humanWordSearch(input);
    }
    boggle.computerWordSearch();
    if (boggle.getScoreComputer() > boggle.getScoreHuman()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
        BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");
    }
    else {
        cout << "WOW, you defeated me! Congratulations!" << endl;
        BoggleGUI::setStatusMessage("WOW, you defeated me! Congratulations!");
    }
}


