#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cstdlib>

double performOperation(char op, double a, double b);
double evaluateRPN(std::string& expression);

#endif