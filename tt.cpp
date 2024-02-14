#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <list>
#include <sstream>


void insertPairs(std::deque<int>& sequence, int start, int end)
{
    //     std::cout << "\n*****befor: " << std::endl; 
    // for (int i = 0; i < sequence.size(); i += 1)
    //     std::cout << sequence[i] << " ";
    // std::cout << std::endl;
    while (start > 2 && start < end)
    {
        if (sequence[start - 2] > sequence[start])
        {
            std::swap(sequence[start - 2], sequence[start]);
            std::swap(sequence[start - 1], sequence[start - 3]);
        }
        start -= 2;
    }
    // std::cout << "*****after: " << std::endl; 
    // for (int i = 0; i < sequence.size(); i += 1)
    //     std::cout << sequence[i] << " ";
    // std::cout << std::endl;
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
    std::cout << std::endl;
    for (int i = 0; i < sequence.size(); i += 1)
        std::cout << sequence[i] << " ";
    std::cout << std::endl;
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
    sortInserPairs(sequence);
    // for (int i = 0; i < size; i += 2)
    // {
    //     if (i + 1 < size)
    //     {
    //         if (sequence[i] > sequence[i + 1])
    //             std::swap(sequence[i], sequence[i + 1]);
    //     }
    // }
    // for (int i = 1; i < size; i += 2)
    //     insertPairs(sequence, i, size);

    // std::cout << std::endl;
    // for (int i = 0; i < size; i += 1)
    //    std::cout << sequence[i] << " ";
    std::cout << std::endl;
    std::deque<int> largGroup;
    largGroup.clear();
    std::deque<int> midle;
    midle.clear();
    for (int i = 0; i < size; i += 2)
    {
        midle.push_back(sequence[i]);
        largGroup.push_back(sequence[i + 1]);
    }
    largGroup.insert(largGroup.begin(), *midle.begin());
    
    std::deque<int>::iterator hold;
    for (int i = 1; i < midle.size(); i++)
    {
        hold = std::lower_bound(largGroup.begin(),largGroup.end(), midle[i]);
        largGroup.insert(hold, midle[i]);
    }
    if (oddFlag)
    {
        hold = std::lower_bound(largGroup.begin(),largGroup.end(), store);
        largGroup.insert(hold, store);

    }
    return largGroup;
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cout << "Usage: " << av[0] << " [list of integers]" << std::endl;
        return 1;
    }
    std::deque<int> sequenced;
    int numberd;
    for (int i = 1; i < ac; i++)
    {
        std::istringstream iss(av[i]);
        if (!(iss >> numberd) || iss.peek() != EOF)
        {
            std::cout << "Error: Invalid input. Please enter only integers." << std::endl;
            return 2;
        }
        if (numberd <= 0)
        {
            std::cout << "Error: Only positive integers are allowed." << std::endl;
            return 3;
        }
        sequenced.push_back(numberd);
    }

    std::cout << "Before: ";
    for (std::deque<int>::iterator it = sequenced.begin(); it != sequenced.end(); it ++)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::clock_t start = std::clock();
    sequenced = mergeInsertionSort(sequenced);
    std::clock_t end = std::clock();

    std::cout << "\nAfter:  ";
    for (std::deque<int>::iterator it = sequenced.begin(); it != sequenced.end(); it ++)
        std::cout << *it << " ";
    double timed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "\nTime to process a range of " << sequenced.size() << " elements with std::deque : " << timed << " us" << std::endl;
    

    // std::vector<int> sequence;
    // int number;
    // for (int i = 1; i < ac; i++)
    // {
    //     std::istringstream iss(av[i]);
    //     if (!(iss >> number) || iss.peek() != EOF)
    //     {
    //         std::cout << "Error: Invalid input. Please enter only integers." << std::endl;
    //         return 2;
    //     }
    //     if (number <= 0)
    //     {
    //         std::cout << "Error: Only positive integers are allowed." << std::endl;
    //         return 3;
    //     }
    //     sequence.push_back(number);
    // }

    // std::clock_t startv = std::clock();
    // mergeInsertionSort(sequence);
    // std::clock_t endv = std::clock();
    // double time = static_cast<double>(endv - startv) / CLOCKS_PER_SEC * 1000000;
    // std::cout << "\nTime to process a range of " << sequence.size() << " elements with std::vector : " << time << " us" << std::endl;
    // return 0;
}
