#ifndef FUNCTIONDOMAINPARSER_H
#define FUNCTIONDOMAINPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <sstream>

const int LEFT_ASSOC  = 0;
const int RIGHT_ASSOC = 1;

// Map the different operators: +, -, *, / etc
typedef std::map< std::string, std::pair< int,int >> OpMap;
typedef std::vector<std::string>::const_iterator cv_iter;
typedef std::string::iterator s_iter;

const OpMap::value_type assocs[] =
    {  OpMap::value_type( "+", std::pair<int,int>( 0, LEFT_ASSOC ) ),
       OpMap::value_type( "-", std::pair<int,int>( 0, LEFT_ASSOC ) ),
       OpMap::value_type( "*", std::pair<int,int>( 5, LEFT_ASSOC ) ),
       OpMap::value_type( "/", std::pair<int,int>( 5, LEFT_ASSOC ) ),
       OpMap::value_type( "^", std::pair<int,int>( 8, RIGHT_ASSOC ) ),
       OpMap::value_type( "!", std::pair<int,int>( 6, RIGHT_ASSOC ) )};



const OpMap opmap( assocs, assocs + sizeof( assocs ) / sizeof( assocs[ 0 ] ) );

class FunctionDomainParser
{
public:
    FunctionDomainParser();
    void evaluate(std::string input);
    double getResult();
    std::vector<std::string> getDenominators();

private:
    std::string expression;
    double result;
    void preprocessExpression(std::string input);
    std::string removeSpaces(std::string input);
    std::string handleUnaryMinus(std::string input);
    std::vector<std::string> denominators;
    std::vector<std::string> getExpressionTokens( const std::string& expression );
    bool isOperator( const std::string& token);
    bool isUnaryMinus( const std::string& expression, int position);
    bool isParenthesis( const std::string& token);
    bool isAssociative( const std::string& token, const int& type);
    bool isFunction( const std::string& token);
    bool infixToRPN( const std::vector<std::string>& inputTokens,
                     const int& size,
                     std::vector<std::string>& strArray );
    void RPNtoDouble( std::vector<std::string> inTokens, double &outResult, std::vector<std::string> &outDenominators );
    int cmpPrecedence( const std::string& token1, const std::string& token2 );
    double evaluateFunction(double value, const std::string& token);
    std::string functionToString(const std::string& function, const std::string& token);
};

#endif // FUNCTIONDOMAINPARSER_H
