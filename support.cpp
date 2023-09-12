#include"provided.h"
#include<iostream>
#include<climits>


int rate(Scaffold scaffold, int prevCol, int nToWin, int checker) {
    

    int realTurn = checker;
    //Checks Vertically Down
    int levelIterator = 0;
    levelIterator = scaffold.levels();
    int vertCounter = 0;
    for (levelIterator; levelIterator > 0; levelIterator--) {
        if (scaffold.checkerAt(prevCol, levelIterator) == realTurn) {
            vertCounter++;
        }
        else if (scaffold.checkerAt(prevCol, levelIterator) != realTurn) {
            break;
        }
    }
    if (vertCounter == nToWin) {
        return 1;
    }

    //Checks Horizontally
    int leftCol = prevCol;
    int rightCol = prevCol + 1;
    int rightColLim = scaffold.cols() + 1;
    int prevLevel = 0;
    prevLevel = scaffold.levels();
    int colCounter = 0;
    //Gives the level of the previous move
    for (prevLevel; prevLevel > 0; prevLevel--) {
        if (scaffold.checkerAt(prevCol, prevLevel) == realTurn) {
            break;
        }
    }
    //Looks at the left of the previous move
    for (leftCol; leftCol > 0; leftCol--) {
        if (scaffold.checkerAt(leftCol, prevLevel) == realTurn) {
            colCounter++;
        }
        else if (scaffold.checkerAt(leftCol, prevLevel) != realTurn) {
            break;
        }
    }
    //Looks at the right of the previous move
    for (rightCol; rightCol < rightColLim; rightCol++) {
        if (scaffold.checkerAt(rightCol, prevLevel) == realTurn) {
            colCounter++;
        }
        else if (scaffold.checkerAt(rightCol, prevLevel) != realTurn) {
            break;
        }
    }

    if (colCounter >= nToWin) {
        return 1;
    }

    //Looks diagonally top left to bottom right
    int diag_topleft_counter = 0;
    int diag_topleft_col = prevCol;
    int diag_topleft_level = prevLevel;

    for (diag_topleft_col, diag_topleft_level; diag_topleft_col > 0 && diag_topleft_level < scaffold.levels() + 1; diag_topleft_col--, diag_topleft_level++) {
        if (scaffold.checkerAt(diag_topleft_col, diag_topleft_level) == realTurn) {
            diag_topleft_counter++;
        }
        else if (scaffold.checkerAt(diag_topleft_col, diag_topleft_level) != realTurn) {
            break;
        }
    }

    int diag_botright_col = prevCol + 1;
    int diag_botright_level = prevLevel - 1;
    for (diag_botright_col, diag_botright_level; diag_botright_col < scaffold.cols() + 1 && diag_botright_level > 0; diag_botright_col++, diag_botright_level--) {
        if (scaffold.checkerAt(diag_botright_col, diag_botright_level) == realTurn) {
            diag_topleft_counter++;
        }
        else if (scaffold.checkerAt(diag_botright_col, diag_botright_level) != realTurn) {
            break;
        }
    }

    if (diag_topleft_counter >= nToWin) {
        return 1;
    }

    int diag_botleft_counter = 0;
    int diag_botleft_col = prevCol;
    int diag_botleft_level = prevLevel;
    for (diag_botleft_col, diag_botleft_level; diag_botleft_col > 0 && diag_botleft_level > 0; diag_botleft_col--, diag_botleft_level--) {
        if (scaffold.checkerAt(diag_botleft_col, diag_botleft_level) == realTurn) {
            diag_botleft_counter++;
        }
        else if (scaffold.checkerAt(diag_botleft_col, diag_botleft_level) != realTurn) {
            break;
        }
    }

    int diag_topright_col = prevCol + 1;
    int diag_topright_level = prevLevel + 1;
    for (diag_topleft_col, diag_topleft_level; diag_topleft_col < scaffold.cols() + 1 && diag_topleft_level < scaffold.levels() + 1; diag_topleft_col++, diag_topleft_level++) {
        if (scaffold.checkerAt(diag_topleft_col, diag_topleft_level) == realTurn) {
            diag_botleft_counter++;
        }
        else if (scaffold.checkerAt(diag_topleft_col, diag_topleft_level) != realTurn) {
            break;
        }
    }

    if (diag_botleft_counter >= nToWin) {
        return 1;
    }

    if (scaffold.numberEmpty() == 0) {
        return 0;
    }

    return -1;  
}

int determineBestMove(Scaffold scaffold, int depth, int color, bool isMax, int NtoWin, int prevCol, int alpha, int beta) 
{
    int otherColor = 0;
    if (color == RED) {
        otherColor = BLACK;
    }
    if (color == BLACK) {
        otherColor = RED;
    }

    int rateScore = rate(scaffold, prevCol, NtoWin, otherColor);
    if (rateScore == 1) {
        if (!isMax) {
            return INT_MAX - depth;
        }
        else {
            return INT_MIN + depth;
        }
    }
    else if (rateScore == 0) {
        if (!isMax) {
            return 0;
        }
        else {
            return 0;
        }
    }

    if (isMax) {
        int max = INT_MIN;
        int chosenCol = 1; 
        for (int i = 1; i < scaffold.cols() + 1; i++) {
            if (!scaffold.makeMove(i, color)) {
                continue;
            }
            int score = determineBestMove(scaffold, depth + 1, otherColor, false, NtoWin, i, alpha, beta);
            if (score >= max) {
                max = score;
                chosenCol = i;
            }
            scaffold.undoMove();
            alpha = std::max(alpha, score);
            if (beta <= alpha) {
                break;
            }
        }
        if (depth == 0) {
            return chosenCol;
        }
        return max;
    }
    else {
        int minVal = INT_MAX;
        for (int i = 1; i < scaffold.cols() + 1; i++) {
            if (!scaffold.makeMove(i, color)) {
                continue;
            }
            int minScore = determineBestMove(scaffold, depth + 1, otherColor, true, NtoWin, i, alpha, beta);
            if (minScore < minVal) {
                minVal = minScore;
            }
            scaffold.undoMove();
            beta = std::min(beta, minScore);
            if (beta <= alpha) {
                break;
            }
        }
        return minVal;
    }

}