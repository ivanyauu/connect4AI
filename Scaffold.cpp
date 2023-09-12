// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    int m_columns;
    int m_levels;
    stack<int> s_column;
    stack<int> s_level;
    vector<vector<int>> board;

};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{

    if (nColumns <= 0 || nLevels <= 0) {
        cerr << "Level or Column cannot be negative";
        exit(1);
    }

    m_columns = nColumns;
    m_levels = nLevels;

    board.resize(m_levels);  
    for (int i = 0; i < m_levels; i++)
        board[i].resize(m_columns, VACANT);  

}

int ScaffoldImpl::cols() const
{
    return m_columns;  
}

int ScaffoldImpl::levels() const
{
    return m_levels;  
}

int ScaffoldImpl::numberEmpty() const
{
    int counter = 0;
    for (int i = 0; i < m_levels; i++) {
        for (int j = 0; j < m_columns; j++) {
            if (board[i][j] == VACANT) {
                counter++;
            }
        }
    }
    return counter;

}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column <= 0 || level <= 0) 
    {
        return -1;
    }
    int realCol = column - 1;
    int realLevel = levels() - level;
    if (board[realLevel][realCol] == RED)
        return RED;
    else if (board[realLevel][realCol] == BLACK)
        return BLACK;

    return VACANT;

}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < levels(); i++) {
        for (int j = 0; j < cols(); j++) {
            if (board[i][j] == VACANT) {
                cout << "| ";
            }
            else if (board[i][j] == RED) {
                cout << "|R";
            }
            else if (board[i][j] == BLACK) {
                cout << "|B";
            }
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < cols(); i++) 
    {
            cout << "+-";
    }
    cout << "+" << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column <= 0) {
        return false;
    }
    int realCol = column - 1;
    if (board[0][realCol] == VACANT) {
        int i;
        for (i = 0; board[i][realCol] == VACANT; i++) {
            if (i == m_levels - 1 && color == RED) {
                board[i][realCol] = RED;
                s_column.push(realCol);
                s_level.push(i);
                return true;
            }
            else if (i == m_levels - 1 && color == BLACK) {
                board[i][realCol] = BLACK;
                s_column.push(realCol);
                s_level.push(i);
                return true;
            }
        }
        i--;
        if (color == RED) {
            board[i][realCol] = RED;
            s_column.push(realCol);
            s_level.push(i);
            return true;
        }
        if (color == BLACK) {
            board[i][realCol] = BLACK;
            s_column.push(realCol);
            s_level.push(i);
            return true;
        }

    }
    return false;  
}

int ScaffoldImpl::undoMove()
{
    if (s_level.empty() && s_column.empty()) {
        return 0;
    }

    int currLevel = s_level.top();
    int currColumn = s_column.top();
    s_level.pop();
    s_column.pop();
    board[currLevel][currColumn] = VACANT;

    return currColumn + 1;  
}

//******************** Scaffold functions *******************************


Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}

Scaffold::~Scaffold()
{
    delete m_impl;
}

Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}

void Scaffold::display() const
{
    m_impl->display();
}

bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}

int Scaffold::undoMove()
{
    return m_impl->undoMove();
}