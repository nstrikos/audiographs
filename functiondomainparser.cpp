#include "functiondomainparser.h"
#include "math.h"
#include "algorithm"
#include "iomanip"

FunctionDomainParser::FunctionDomainParser()
{

}

double FunctionDomainParser::getResult()
{
    return this->result;
}

std::vector<std::__cxx11::string> FunctionDomainParser::getDenominators()
{
    return this->denominators;
}

void FunctionDomainParser::evaluate(std::string input)
{
    // Preprocess->get expression tokens->infix to rpn->rpn to double
    // for more information look at
    // http://www.technical-recipes.com/2011/a-mathematical-expression-parser-in-java-and-cpp/
    if (denominators.size() > 0)
        denominators.clear();

    preprocessExpression(input);
    std::vector<std::string> tokens = getExpressionTokens( this->expression );

    std::vector<std::string> rpn;
    if ( infixToRPN( tokens, tokens.size(), rpn ) )
        RPNtoDouble( rpn, result, denominators ); //this function evaluates denominators and result
    else
        std::cout << "Mis-match in parentheses" << std::endl;
}

void FunctionDomainParser::preprocessExpression(std::__cxx11::string input)
{

    this->expression = "(" + removeSpaces(input) + ")"; //Remove space, add parethenses
    this->expression = handleUnaryMinus(this->expression); //Handle unary minus
}

std::string FunctionDomainParser::removeSpaces(std::string input)
{
    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
    return input;
}

std::__cxx11::string FunctionDomainParser::handleUnaryMinus(std::__cxx11::string input)
{
    //I couldn't find a better solution
    //If - is an unary minus, then multiply everything after it with -1
    //until you find another operand different than ^ eg +,-,*,/

    std::string previousToken = "";
    std::string uMinus = "((0-1)*(";

    for ( int i = 0; i < (int) input.length(); ++i )
    {
        const std::string token( 1, input[ i ] );
        if ( token == "-")
        {
            if (previousToken == "" || isOperator(previousToken) || previousToken == "(")
            {
                input.replace(i,1,uMinus);
                int countParentheses = 0;
                int place = i + uMinus.length();
                for (unsigned int l = place; l < input.length(); l++)
                {

                    std::string ch (1, input[l]);
                    if ( isOperator(ch) && ch!= "^" && countParentheses == 0 )
                    {
                        if ( (ch == "-" && !isUnaryMinus(input, l)) || ch=="*" || ch=="+" || ch=="/")
                        {
                            input.insert(l,"))");
                            break;
                        }
                    }
                    if (ch == "(")
                        countParentheses++;
                    else if (ch == ")")
                    {
                        countParentheses--;
                        if (countParentheses <= 0)
                        {
                            input.insert(l,"))");
                            break;
                        }

                    }
                    if (l == input.length() - 1)
                    {
                        input.insert(l,"))");
                        break;
                    }
                }
            }
        }
        previousToken = token;
    }
    return input;
}

std::vector<std::string> FunctionDomainParser::getExpressionTokens( const std::string& expression )
{
    std::vector<std::string> tokens;
    std::string str = "";

    for ( int i = 0; i < (int) expression.length(); ++i )
    {
        const std::string token( 1, expression[ i ] );

        if ( isOperator( token ) || isParenthesis( token ) )
        {
            if ( !str.empty() )
            {
                tokens.push_back( str ) ;
            }
            str = "";
            tokens.push_back( token );
        }
        else
        {
            // Append the numbers
            if ( !token.empty() && token != " " )
            {
                str.append( token );
            }
            else
            {
                if ( str != "" )
                {
                    tokens.push_back( str );
                    str = "";
                }
            }
        }
    }

    return tokens;
}

// Test if token is an operator
bool FunctionDomainParser::isOperator( const std::string& token)
{
    return token == "+" || token == "-" ||
            token == "*" || token == "/" ||
            token == "^" || token == "!";
}

bool FunctionDomainParser::isUnaryMinus(const std::__cxx11::string &expression, int position)
{
    //unary minus if a. at the beginning (eg -5, position = 0)
    //b. previous token is operator (eg 5*-6)
    //c. previous token is parentheses (eg 5*(-6+2))
    const std::string ch( 1, expression[ position ] );
    if (ch == "-")
    {
        if (position > 0)
        {
            const std::string previous(1, expression[position - 1]);
            if (isOperator(previous) || previous == "(")
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

// Test if token is an pathensesis
bool FunctionDomainParser::isParenthesis( const std::string& token)
{
    return token == "(" || token == ")";
}

bool FunctionDomainParser::isAssociative( const std::string& token, const int& type)
{
    const std::pair<int,int> p = opmap.find( token )->second;
    return p.second == type;
}

bool FunctionDomainParser::isFunction( const std::string& token)
{
    return token == "abs"  ||
            token == "acos" ||
            token == "asin" ||
            token == "atan" ||
            token == "cos"  ||
            token == "cosh" ||
            token == "exp"  ||
            token == "log"  ||
            token == "log10"||
            token == "sin"  ||
            token == "sinh" ||
            token == "sqrt" ||
            token == "tan" ||
            token == "tanh";

}

int FunctionDomainParser::cmpPrecedence( const std::string& token1, const std::string& token2 )
{
    const std::pair<int,int> p1 = opmap.find( token1 )->second;
    const std::pair<int,int> p2 = opmap.find( token2 )->second;

    return p1.first - p2.first;
}

// Convert infix expression format into reverse Polish notation
bool FunctionDomainParser::infixToRPN( const std::vector<std::string>& inputTokens,
                                       const int& size,
                                       std::vector<std::string>& strArray )
{
    bool success = true;

    std::list<std::string> out;
    std::stack<std::string> stack;
    std::string previousToken = "";

    // While there are tokens to be read
    for ( int i = 0; i < size; i++ )
    {
        // Read the token
        std::string token = inputTokens[ i ];

        if (token == "$pi")
            token = "3.141592653589793238462643383279";
        else if (token == "$e")
            token = "2.718281828459045235360287471353";

        // If token is an operator
        if ( isOperator( token ) )
        {
            // While there is an operator token, o2, at the top of the stack AND
            // either o1 is left-associative AND its precedence is equal to that of o2,
            // OR o1 has precedence less than that of o2,
            std::string o1 = token;

            //Take care of unary operator
            // minus is considered unary operator if it is placed after an operator
            //or at the beginning of the expression
            //minus is considered subtraction if it is placed after a number or a parenthesis
            //if (o1 == "-" && (isOperator(previousToken) || previousToken == "") || previousToken == "(")
            //    o1 = "!";

            if ( !stack.empty() )
            {
                std::string o2 = stack.top();

                while ( isOperator( o2 ) &&
                        ( ( isAssociative( o1, LEFT_ASSOC ) &&  cmpPrecedence( o1, o2 ) == 0 ) ||
                          ( cmpPrecedence( o1, o2 ) < 0 ) ) )
                {
                    // pop o2 off the stack, onto the output queue;
                    stack.pop();
                    out.push_back( o2 );

                    if ( !stack.empty() )
                        o2 = stack.top();
                    else
                        break;
                }
            }

            // push o1 onto the stack.
            stack.push( o1 );
        }
        // If the token is a left parenthesis, then push it onto the stack.
        else if ( token == "(" )
        {
            // Push token to top of the stack
            stack.push( token );
        }
        // If token is a right bracket ')'
        else if ( token == ")" )
        {
            // Until the token at the top of the stack is a left parenthesis,
            // pop operators off the stack onto the output queue.
            std::string topToken  = stack.top();

            while ( topToken != "(" )
            {
                out.push_back(topToken );
                stack.pop();

                if ( stack.empty() ) break;
                topToken = stack.top();
            }

            // Pop the left parenthesis from the stack, but not onto the output queue.
            if ( !stack.empty() ) stack.pop();

            // If the stack runs out without finding a left parenthesis,
            // then there are mismatched parentheses.
            if ( topToken != "(" )
            {
                return false;
            }

            if ( stack.empty() ) break;
            topToken = stack.top();
            if (isFunction(topToken))
            {
                out.push_back(topToken);
                stack.pop();
            }

        }

        else if ( isFunction(token) )
        {
            stack.push(token);
        }

        // If the token is a number, then add it to the output queue.
        else
        {
            out.push_back( token );
        }
        previousToken = token;
    }

    // While there are still operator tokens in the stack:
    while ( !stack.empty() )
    {
        const std::string stackToken = stack.top();

        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if ( isParenthesis( stackToken )   )
        {
            return false;
        }

        // Pop the operator onto the output queue./
        out.push_back( stackToken );
        stack.pop();
    }

    strArray.assign( out.begin(), out.end() );

    return success;
}

double FunctionDomainParser::evaluateFunction(double value, const std::__cxx11::string &token)
{

    if (token == "abs")
        return abs(value);
    else if (token == "acos")
        return acos(value);
    else if (token == "asin")
        return asin(value);
    else if (token == "atan")
        return atan(value);
    else if (token == "cos")
        return cos(value);
    else if (token == "cosh")
        return cosh(value);
    else if (token == "exp")
        return exp(value);
    else if (token == "log")
        return log(value);
    else if (token == "log10")
        return log10(value);
    else if (token == "sin")
        return sin(value);
    else if (token == "sinh")
        return sinh(value);
    else if (token == "sqrt")
        return sqrt(value);
    else if (token == "tan")
        return tan(value);
    else if (token == "tanh")
        return tanh(value);
    else return 0;
}

std::__cxx11::string FunctionDomainParser::functionToString(const std::__cxx11::string &function, const std::__cxx11::string &token)
{
    return function + "(" + token + ")";
}

void FunctionDomainParser::RPNtoDouble( std::vector<std::string> inTokens, double &outResult, std::vector<std::string> &outDenominators )
{
    std::stack<std::string> stValue;
    std::stack<std::string> stString;


    // For each token
    for ( int i = 0; i < (int) inTokens.size(); ++i )
    {
        const std::string token = inTokens[ i ];

        if ( isFunction(token))
        {
            double result =  0.0;
            std::string res = "";

            const std::string val2 = stValue.top();
            const std::string val2String = stString.top();
            stValue.pop();
            stString.pop();
            const double d2 = strtod( val2.c_str(), NULL );
            result = evaluateFunction(d2, token);
            res = functionToString(token, val2String);
            // Push result onto stack
            std::ostringstream sValue;
            std::ostringstream sString;
            sValue << std::setprecision(20)  << result;
            sString << res;
            stValue.push( sValue.str() );
            stString.push( sString.str());
        }
        // If the token is a value push it onto the stack
        else if ( !isOperator(token) )
        {
            stValue.push(token);
            stString.push(token);
        }
        else
        {
            double result =  0.0;
            std::string res = "";

            // Token is an operator: pop top two entries
            std::string val2 = stValue.top();
            std::string val2String = stString.top();
            stValue.pop();
            stString.pop();
            const double d2 = strtod( val2.c_str(), NULL );

            if ( !stValue.empty() )
            {
                const std::string val1 = stValue.top();
                const std::string val1String = stString.top();
                stValue.pop();
                stString.pop();
                const double d1 = strtod( val1.c_str(), NULL );

                //Get the result
                result = token == "+" ? d1 + d2 :
                                        token == "-" ? d1 - d2 :
                                                       token == "*" ? d1 * d2 :
                                                                      token == "/" ? d1 / d2 :
                                                                                     pow(d1,d2);

                res = token == "+" ? val1String + "+" + val2String :
                                     token == "-" ? val1String + "-" + val2String :
                                                    token == "*" ? val1String + "*" + val2String :
                                                                   token == "/" ? val1String + "/" + "(" + val2String + ")":
                                                                                  val1 + "^" + val2;

                if (token == "/")
                {
                    val2String = "(" + val2String + ")";
                    //std::cout << "token:" << val2 << std::endl;
                    outDenominators.push_back(val2String);
                }
            }
            else
            {
                if ( token == "-" )
                    result = d2 * -1;
                else
                    result = d2;
            }


            std::ostringstream sValue;
            std::ostringstream sString;
            sValue << std::setprecision(20)  << result;
            sString << res;
            stValue.push( sValue.str() );
            stString.push( sString.str());
        }
    }
    outResult = strtod( stValue.top().c_str(), NULL );
}
