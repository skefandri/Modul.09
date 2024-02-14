#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <list>
#include <sstream>

void insertPairs(std::deque<int>& sequence, int start, int end);
void sortInserPairs(std::deque<int>& sequence);
void prepareAndSortPairs(std::deque<int>& sequence, std::deque<int>& largGroup, std::deque<int>& midle, int& size);
std::deque<int> mergeGroups(std::deque<int>& largGroup, std::deque<int>& midle, bool oddFlag, int store);
std::deque<int> mergeInsertionSort(std::deque<int>& sequence);

//=========================================================

void insertPairsV(std::vector<int>& sequence, int start, int end);
void sortInserPairsV(std::vector<int>& sequence);
void prepareAndSortPairsV(std::vector<int>& sequence, std::vector<int>& largGroup, std::vector<int>& midle, int& size);
std::vector<int> mergeGroupsV(std::vector<int>& largGroup, std::vector<int>& midle, bool oddFlag, int store) ;
std::vector<int> mergeInsertionSortV(std::vector<int>& sequence);

#endif