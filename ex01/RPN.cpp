#include "RPN.hpp"

double performOperation(char op, double a, double b)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/': 
            if (b == 0)
                throw std::runtime_error("Division by zero");
            return a / b;
        default:
            throw std::runtime_error("Invalid operator");
    }
}



double evaluateRPN(std::string& expression)
{
    std::istringstream iss(expression);
    std::stack<double> stack;
    std::string token;

    while (iss >> token)
    {
        if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1])))
        {
            if (token.find_first_not_of("0123456789") != std::string::npos)
            {
                if (token[0] == '-' || token[0] == '+')
                {
                    std::string temp = &token[1];
                    if (temp.find_first_not_of("0123456789") != std::string::npos)
                        throw std::runtime_error("Invalid token");
                }
                else
                    throw std::runtime_error("Invalid token");
            }
            stack.push(atof(token.c_str()));
            if (stack.top() >= 10)
                throw std::runtime_error("The number is more than 10");

        }
        else if (token.length() == 1 && std::string("+-*/").find(token[0]) != std::string::npos)
        {
            if (stack.size() < 2)
                throw std::runtime_error("Insufficient operands");
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();
            stack.push(performOperation(token[0], operand1, operand2));
        }
        else
            throw std::runtime_error("Invalid token");
    }
    if (stack.size() != 1)
        throw std::runtime_error("Invalid expression");
    return stack.top();
}