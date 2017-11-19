#pragma once
#include "subpattern_info.h"

const int ENG_ALPH = 26;

struct bohr_vertex
{
	int next_vertex[ENG_ALPH];
	subpattern_info pattern_info;
	bool flag; //the indicator: is our vertex selected word
	int suff_link;
	int parrent;
	int auto_move[ENG_ALPH]; //contains the automatron moves  
	char symb; //the symbol on the edge from parrent to current vertex
	int suff_flink; //the nearest link to the suffix with flag = thue
};