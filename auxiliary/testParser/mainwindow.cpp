#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../src/audiographs/atmsp.h"
#include "../../src/audiographs/functiondomainparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ATMSP<long double> atmspParser;
    ATMSB<long double> byteCode;
    double atmspResult;
    size_t atmspCheck;

    FunctionDomainParser functionDomainParser;
    double fdParserResult;

    std::vector<std::string> expressions = fillValueExpressions();


    for (unsigned int i = 0; i < expressions.size(); i++)
    {

        std::string expression = expressions.at(i);
        size_t atmspErr = atmspParser.parse(byteCode, expression, "x");

        functionDomainParser.evaluate(expression);
        fdParserResult = functionDomainParser.getResult();

        if ( atmspErr == 0)
        {
            atmspResult = byteCode.run();
            atmspCheck = byteCode.fltErr;
            if (atmspCheck == 0)
            {
                QString outcome;
                double diff = fabs(atmspResult - fdParserResult);
                if ( diff > 0.0001 )
                {
                    outcome = "Failure";
                    ui->plainTextEdit->appendPlainText(outcome
                                                       + " Expression: "
                                                       + QString::fromStdString(expression)
                                                       + " atmParser:" + QString::number(atmspResult, 'f', 20)
                                                       + " fdParser: "
                                                       + QString::number(fdParserResult, 'f', 20)
                                                       + " diff:"
                                                       +  QString::number(diff, 'f', 20));
                }
                else
                {
                    outcome = "Success";
                    ui->plainTextEdit_2->appendPlainText(outcome
                                                         + " Expression: "
                                                         + QString::fromStdString(expression)
                                                         + " atmParser:" + QString::number(atmspResult)
                                                         + " fdParser: "
                                                         + QString::number(fdParserResult)
                                                         + " diff:"
                                                         +  QString::number(diff));
                }


            }
            else
            {
                ui->plainTextEdit->appendPlainText("Result is not a number");
            }
        }
        else
        {
            ui->plainTextEdit->appendPlainText ("Error in parsing:" + QString::number(atmspErr) + " " + QString::fromStdString(expression));
        }
    }
    std::vector<std::string> stringExpressions = fillStringExpressions();

    for (unsigned int i = 0; i < stringExpressions.size(); i++)
    {

        std::string expression = stringExpressions.at(i);
        functionDomainParser.evaluate(expression);
        std::vector<std::string> denominators = functionDomainParser.getDenominators();
        for (unsigned int i = 0; i < denominators.size(); i++)
            std::cout << denominators.at(i) << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<std::__cxx11::string> MainWindow::fillValueExpressions()
{
    std::vector<std::string> list;
    list.push_back("1 -(-2^2) -1");
    list.push_back("((2*(6-1))/2)*4");
    list.push_back("((2*(6-1))/2)*4");
    list.push_back("-11 ^ -7");
    list.push_back("-11 ^ 7");
    list.push_back("-1*- sin( 3.14159265359 / -2)");
    list.push_back("-8 + 5");
    list.push_back("5 + (-1 + 2 )");
    list.push_back("cos ( ( 1.3 + 1 ) ^ ( 1 / 3 ) )");
    list.push_back("( 1.3 + -1 ) ^ ( 1 / 3 )");
    list.push_back("2*-2");
    list.push_back("2--2");
    list.push_back("exp( 1.11 )");
    list.push_back("sin( cos( 90 * 3.14159265359 / 180  ) )");
    list.push_back("34.5*(23+1.5)/2");
    list.push_back("5 + ((1 + 2) * -4) - 3");
    list.push_back("( 1 + 2 ) * ( 3 / 4 ) ^ ( 5 + 6 )");
    list.push_back("3/2 + 4*(12+3)");
    list.push_back("((2*(6-1))/2)*4");
    list.push_back("log(2)+3^5");
    list.push_back("log(2)");
    list.push_back("3^5");
    list.push_back("-8+3");
    list.push_back("cos(- 1.32001)");
    list.push_back("5 + ((1 + 2) * 4) - 3 ");
    list.push_back("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    list.push_back("2.5^3");
    list.push_back("-cos(1/-20)+sin(1/30)+cos(1/50)");
    list.push_back("--cos(1/-20)+-sin(1/30)");
    list.push_back("--cos(1/-20)--sin(1/30)");
    list.push_back("--cos(1/--20)");
    list.push_back("sqrt(4 )");
    list.push_back("5 + (-1 + 2 )");
    list.push_back("-(2+3)*(4*-10-1)+100");
    list.push_back("(2+3)*-(4*10-1)+100");
    list.push_back("1 - (-2^2) - 1");
    list.push_back("1 - (--2^2) -- 1");
    list.push_back("(4*-10-1)");
    list.push_back("-(2+3)*(4*-10-1)");
    list.push_back("-3/2 + 4*-( 12+3)");
    list.push_back("-3/2 + 4*(-12-3)");
    list.push_back("-3/2 + -4*(-12-3)");
    list.push_back("1--cos($PI)");
    list.push_back("1+-cos($pi)");
    list.push_back("$e*log(100)");
    list.push_back("$e+ln(100)");
    list.push_back("-2^2");
    list.push_back("(1 - 5 ) ^ 2 ^ 3");
    list.push_back("(-0.5^-2/-(4^-3-6-7))^--3");
    return list;
}

std::vector<std::__cxx11::string> MainWindow::fillStringExpressions()
{
    std::vector<std::string> list;
    list.push_back("x/(-5*x^2)");
    list.push_back("sqrt(log(x^2))");
    list.push_back("x/(-5*x^2)/x - 2log(x)/x^5");
    list.push_back("x/sin(x)");
    list.push_back("x/(cos(x)*sin(x))");
    list.push_back("5/-x");
    list.push_back("-2/-x^2");
    list.push_back("5/89/sin(x/-2*sin(-x))");
    list.push_back("2/(x-$e)");
    return list;
}
