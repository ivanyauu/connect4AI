// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <climits>
using namespace std;

class HumanPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int p_col;
    cout << "Choose a column 1 - " << s.cols() << endl;
    cin >> p_col;

    while (p_col < 1 || p_col > s.cols() || s.checkerAt(p_col, s.levels()) != VACANT) 
    {
        cout << "Choose a valid column 1 - " << s.cols() <<endl;
        cin >> p_col;
    }

    return p_col;  
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() > 0) {
        for (int i = s.levels(); i > 0; i--)
        {
            for (int j = 1; j < s.cols() + 1; j++) {
                if (s.checkerAt(j, i) == VACANT) {
                    return j;
                }
            }
        }
    }
    return -1;  
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int col = determineBestMove(s, 0, color, true, N, 1, INT_MIN, INT_MAX);
    return col;  
}

//******************** Player derived class functions *************************


HumanPlayer::HumanPlayer(string nm)
    : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
    : Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
    : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}