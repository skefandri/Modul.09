#include "PmergeMe.hpp"


bool parseInputDeque(int argc, char** argv, std::deque<int>& sequenced)
{
    for (int i = 1; i < argc; i++)
    {
        std::istringstream iss(argv[i]);
        int number;
        if (!(iss >> number) || iss.peek() != EOF)
        {
            std::cout << "Error: Invalid input. Please enter only integers." << std::endl;
            return false;
        }
        if (number <= 0)
        {
            std::cout << "Error: Only positive integers are allowed." << std::endl;
            return false;
        }
        sequenced.push_back(number);
    }
    return true;
}

bool parseInputVector(int argc, char** argv, std::vector<int>& sequence) {
    for (int i = 1; i < argc; i++) {
        std::istringstream iss(argv[i]);
        int number;
        if (!(iss >> number) || iss.peek() != EOF) {
            std::cout << "Error: Invalid input. Please enter only integers." << std::endl;
            return false;
        }
        if (number <= 0) {
            std::cout << "Error: Only positive integers are allowed." << std::endl;
            return false;
        }
        sequence.push_back(number);
    }
    return true;
}

void performSortAndDisplayResultsDeque(std::deque<int>& sequenced)
{
    std::cout << "Before: ";
    for (std::deque<int>::iterator it = sequenced.begin(); it != sequenced.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::clock_t start = std::clock();
    sequenced = mergeInsertionSort(sequenced);
    std::clock_t end = std::clock();

    std::cout << "After:  ";
    for (std::deque<int>::iterator it = sequenced.begin(); it != sequenced.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    double timed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "Time to process a range of " << sequenced.size() << " elements with std::deque: " << timed << " ms" << std::endl;
}

void performSortAndDisplayResultsVector(std::vector<int>& sequence)
{
    std::clock_t startv = std::clock();
    mergeInsertionSortV(sequence);
    std::clock_t endv = std::clock();

    double time = static_cast<double>(endv - startv) / CLOCKS_PER_SEC * 1000;
    std::cout << "Time to process a range of " << sequence.size() << " elements with std::vector: " << time << " ms" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [list of integers]" << std::endl;
        return 1;
    }
    std::deque<int> sequenced;
    if (!parseInputDeque(argc, argv, sequenced))
        return 2;
    performSortAndDisplayResultsDeque(sequenced);
    std::vector<int> sequence;
    if (!parseInputVector(argc, argv, sequence))
        return 3;
    performSortAndDisplayResultsVector(sequence);
    return 0;
}
