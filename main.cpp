// main.cpp

#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
	SmartPlayer bp("Homer");
	SmartPlayer hp("Marge");
	Game g(4, 4, 4, &bp, &hp);
	g.play();
}