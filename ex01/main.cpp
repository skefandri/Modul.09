#include "RPN.hpp"


int main(int ac, char* av[])
{
    if (ac != 2)
    {
        std::cerr << "Invalid Parametre" << std::endl;
        return 1;
    }
    try
    {
        std::string eval = av[1];
        double result = evaluateRPN(eval);
        std::cout << result << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}
