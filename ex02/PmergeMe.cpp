#include "PmergeMe.hpp"

void insertPairs(std::deque<int>& sequence, int start, int end)
{
    while (start > 2 && start < end)
    {
        if (sequence[start - 2] > sequence[start])
        {
            std::swap(sequence[start - 2], sequence[start]);
            std::swap(sequence[start - 1], sequence[start - 3]);
        }
        start -= 2;
    }
}

void sortInserPairs(std::deque<int>& sequence)
{
    int size = sequence.size();
    for (int i = 0; i < size; i += 2)
    {
        if (i + 1 < size)
        {
            if (sequence[i] > sequence[i + 1])
                std::swap(sequence[i], sequence[i + 1]);
        }
    }
    for (int i = 1; i < size; i += 2)
        insertPairs(sequence, i, size);
}

void prepareAndSortPairs(std::deque<int>& sequence, std::deque<int>& largGroup, std::deque<int>& midle, int& size)
{
    sortInserPairs(sequence);
    for (int i = 0; i < size; i += 2) {
        midle.push_back(sequence[i]);
        largGroup.push_back(sequence[i + 1]);
    }
    largGroup.insert(largGroup.begin(), *midle.begin());
}

std::deque<int> mergeGroups(std::deque<int>& largGroup, std::deque<int>& midle, bool oddFlag, int store)
{
    std::deque<int>::iterator hold;
    for (size_t i = 1; i < midle.size(); i++) {
        hold = std::lower_bound(largGroup.begin(), largGroup.end(), midle[i]);
        largGroup.insert(hold, midle[i]);
    }
    if (oddFlag) {
        hold = std::lower_bound(largGroup.begin(), largGroup.end(), store);
        largGroup.insert(hold, store);
    }
    return largGroup;
}

std::deque<int> mergeInsertionSort(std::deque<int>& sequence)
{
    int size = sequence.size();
    if (size <= 1)
        return sequence;

    bool oddFlag = false;
    int store = 0;
    if (size % 2)
    {
        store = sequence[size - 1];
        sequence.pop_back();
        oddFlag = true;
        size--;
    }
    std::deque<int> largGroup, midle;
    prepareAndSortPairs(sequence, largGroup, midle, size);
    return mergeGroups(largGroup, midle, oddFlag, store);
}


//==================================================================================

void insertPairsV(std::vector<int>& sequence, int start, int end)
{
    while (start > 2 && start < end)
    {
        if (sequence[start - 2] > sequence[start])
        {
            std::swap(sequence[start - 2], sequence[start]);
            std::swap(sequence[start - 1], sequence[start - 3]);
        }
        start -= 2;
    }
}

void sortInserPairsV(std::vector<int>& sequence)
{
    int size = sequence.size();
    for (int i = 0; i < size; i += 2)
    {
        if (i + 1 < size)
        {
            if (sequence[i] > sequence[i + 1])
                std::swap(sequence[i], sequence[i + 1]);
        }
    }
    for (int i = 1; i < size; i += 2)
        insertPairsV(sequence, i, size);
}

void prepareAndSortPairsV(std::vector<int>& sequence, std::vector<int>& largGroup, std::vector<int>& midle, int& size)
{
    sortInserPairsV(sequence);
    for (int i = 0; i < size; i += 2) {
        midle.push_back(sequence[i]);
        largGroup.push_back(sequence[i + 1]);
    }
    largGroup.insert(largGroup.begin(), *midle.begin());
}

std::vector<int> mergeGroupsV(std::vector<int>& largGroup, std::vector<int>& midle, bool oddFlag, int store)
{
    std::vector<int>::iterator hold;
    for (size_t i = 1; i < midle.size(); i++) {
        hold = std::lower_bound(largGroup.begin(), largGroup.end(), midle[i]);
        largGroup.insert(hold, midle[i]);
    }
    if (oddFlag) {
        hold = std::lower_bound(largGroup.begin(), largGroup.end(), store);
        largGroup.insert(hold, store);
    }
    return largGroup;
}

std::vector<int> mergeInsertionSortV(std::vector<int>& sequence)
{
    int size = sequence.size();
    if (size <= 1)
        return sequence;

    bool oddFlag = false;
    int store = 0;
    if (size % 2)
    {
        store = sequence[size - 1];
        sequence.pop_back();
        oddFlag = true;
        size--;
    }
    std::vector<int> largGroup, midle;
    prepareAndSortPairsV(sequence, largGroup, midle, size);
    return mergeGroupsV(largGroup, midle, oddFlag, store);
}