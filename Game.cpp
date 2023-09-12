// Game.cpp

#include "provided.h"
#include <iostream>
#include <climits>

using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~GameImpl();
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
 private:
    Scaffold* scaffold;
    Player* Red;
    Player* Black;
    int nToWin;
    int player_turn;
    int prevCol = 0;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    scaffold = new Scaffold(nColumns, nLevels);
    Red = red;
    Black = black;
    nToWin = N;
    player_turn = RED;
}

GameImpl::~GameImpl() {
    delete scaffold;
}

bool GameImpl::completed(int& winner) const
{
    if (scaffold->numberEmpty() == scaffold->cols() * scaffold->levels()) {
        return false;
    }

    int realTurn = VACANT;
    if (nToWin <= 0) {
        winner = RED;
        return true;
    }
    if (player_turn == RED) {
        realTurn = BLACK;
    }
    else if (player_turn == BLACK) {
        realTurn = RED;
    }
    //Checks Vertically Down
    int levelIterator = 0;
    levelIterator = scaffold->levels();
    int vertCounter = 0;
    for(levelIterator; levelIterator > 0; levelIterator--){
        if (checkerAt(prevCol, levelIterator) == realTurn) {
            vertCounter++;
        }
        else if(checkerAt(prevCol, levelIterator) == player_turn){
            break;
        }
    }
    if (vertCounter == nToWin) {
        winner = realTurn;
        return true;
    }
    
    //Checks Horizontally
    int leftCol = prevCol;
    int rightCol = prevCol + 1;
    int rightColLim = scaffold->cols() + 1;
    int prevLevel = 0;
    prevLevel = scaffold->levels();
    int colCounter = 0;
    //Gives the level of the previous move
    for (prevLevel; prevLevel > 0; prevLevel--) {
        if (checkerAt(prevCol, prevLevel) == realTurn) {
            break;
        }
    }
    //Looks at the left of the previous move
    for (leftCol; leftCol > 0; leftCol--) {
        if (checkerAt(leftCol, prevLevel) == realTurn) {
            colCounter++;
        }
        else if (checkerAt(leftCol, prevLevel) == player_turn || checkerAt(leftCol, prevLevel) == VACANT) {
            break;
        }
    }
    //Looks at the right of the previous move
    for (rightCol; rightCol < rightColLim; rightCol++) {
        if (checkerAt(rightCol, prevLevel) == realTurn) {
            colCounter++;
        }
        else if (checkerAt(rightCol, prevLevel) == player_turn || checkerAt(rightCol, prevLevel) == VACANT) {
            break;
        }
    }

    if (colCounter >= nToWin) {
        winner = realTurn;
        return true;
    }

    //Looks diagonally top left to bottom right
    int diag_topleft_counter = 0;
    int diag_topleft_col = prevCol;
    int diag_topleft_level = prevLevel;

    for (diag_topleft_col, diag_topleft_level; diag_topleft_col > 0 && diag_topleft_level < scaffold->levels() + 1; diag_topleft_col--, diag_topleft_level++) {
        if (checkerAt(diag_topleft_col, diag_topleft_level) == realTurn) {
            diag_topleft_counter++;
        }
        else if (checkerAt(diag_topleft_col, diag_topleft_level) == player_turn || checkerAt(diag_topleft_col, diag_topleft_level) == VACANT) {
            break;
        }
    }

    int diag_botright_col = prevCol + 1;
    int diag_botright_level = prevLevel - 1;
    for (diag_botright_col, diag_botright_level; diag_botright_col < scaffold->cols() + 1 && diag_botright_level > 0; diag_botright_col++, diag_botright_level--) {
        if (checkerAt(diag_botright_col, diag_botright_level) == realTurn) {
            diag_topleft_counter++;
        }
        else if (checkerAt(diag_botright_col, diag_botright_level) == player_turn || checkerAt(diag_botright_col, diag_botright_level) == VACANT) {
            break;
        }
    }

    if (diag_topleft_counter >= nToWin) {
        winner = realTurn;
        return true;
    }

    int diag_botleft_counter = 0;
    int diag_botleft_col = prevCol;
    int diag_botleft_level = prevLevel;
    for (diag_botleft_col, diag_botleft_level; diag_botleft_col > 0 && diag_botleft_level > 0; diag_botleft_col--, diag_botleft_level--) {
        if (checkerAt(diag_botleft_col, diag_botleft_level) == realTurn) {
            diag_botleft_counter++;
        }
        else if (checkerAt(diag_botleft_col, diag_botleft_level) == player_turn || checkerAt(diag_botleft_col, diag_botleft_level) == VACANT) {
            break;
        }
    }

    int diag_topright_col = prevCol + 1;
    int diag_topright_level = prevLevel + 1;
    for (diag_topleft_col, diag_topleft_level; diag_topleft_col < scaffold->cols() + 1 && diag_topleft_level < scaffold->levels() + 1; diag_topleft_col++, diag_topleft_level++) {
        if (checkerAt(diag_topleft_col, diag_topleft_level) == realTurn) {
            diag_botleft_counter++;
        }
        else if (checkerAt(diag_topleft_col, diag_topleft_level) == player_turn || checkerAt(diag_topleft_col, diag_topleft_level) == VACANT) {
            break;
        }
    }

    if (diag_botleft_counter >= nToWin) {
        winner = realTurn;
        return true;
    }

    if (scaffold->numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }

    return false;  //  This is not always correct; it's just here to compile
}

bool GameImpl::takeTurn()
{
    if (player_turn == RED) 
    {
        int chosenCol;
        cout << "Red's Turn" << endl;
        chosenCol = Red->chooseMove(*scaffold, nToWin, RED);
        scaffold->makeMove(chosenCol, RED);
        prevCol = chosenCol;
        cout << "Red drops a checker at column: " << chosenCol << endl;
        player_turn = BLACK;
        return true;
    }
    if (player_turn == BLACK)
    {
        int chosenCol;
        cout << "Black's Turn" << endl;
        chosenCol = Black->chooseMove(*scaffold, nToWin, BLACK);
        scaffold->makeMove(chosenCol, BLACK);
        prevCol = chosenCol;
        cout << "Black drops a checker at column: " << chosenCol << endl;
        player_turn = RED;
        return true;
    }
    return false;  
}

void GameImpl::play()
{
    int i = TIE_GAME;
    cout << "Welcome to Connect " << nToWin << endl;
    scaffold->display();
    while (!completed(i)) 
    {
        takeTurn();
        scaffold->display();
        cout << "Press enter to continue." << endl;
        cin.ignore(10000, '\n');
    }
    scaffold->display();
    if (i == RED) {
        cout << "Red wins!" << endl;
    }
    else if (i == BLACK) {
        cout << "Black wins!" << endl;
    }
    else {
        cout << "Tie game!" << endl;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    return scaffold->checkerAt(c,r);  
}

//******************** Game functions *******************************


Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}