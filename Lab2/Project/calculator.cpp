#include <QtWidgets>
#include <QObject>
#include <cmath>
#include "calculator.h"


    static double sumSoFar = 0.0;
    static double factorSoFar = 0.0;
    static bool waitingForOperand = true;


    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;

void setWaitOperand(bool x){waitingForOperand = x;}
bool getWaitOperand(){return waitingForOperand;}


double unaryOperatorClicked(double operand, QString &clickedOperator)


{
    double result = 0.0;

    if (clickedOperator == "Sqrt") {
        if (operand < 0.0) {
            clearAll();
            return NULL;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == "x\302\262") {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == "1/x") {
        if (operand == 0.0) {
            clearAll();
            return NULL;
        }
        result = 1.0 / operand;
    }
    return result;
}

double additiveOperatorClicked(double operand, QString &clickedOperator)

{
    if (!pendingMultiplicativeOperator.isEmpty() && !waitingForOperand) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            clearAll();
            return 0;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
        return operand;
    }


    if (!pendingAdditiveOperator.isEmpty() && !waitingForOperand) {

        if (!calculate(operand, pendingAdditiveOperator)) {
            clearAll();
            return 0;
        }
        return sumSoFar;
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;

    return sumSoFar;
}

double multiplicativeOperatorClicked(double operand, QString &clickedOperator)
{
    if (!pendingMultiplicativeOperator.isEmpty() && !waitingForOperand) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            clearAll();
            return 0;
        }
        pendingMultiplicativeOperator = clickedOperator;
        return factorSoFar;
    }
    else {
        factorSoFar = operand;  // return same number
    }
    pendingMultiplicativeOperator = clickedOperator;
    return factorSoFar;
}

double equalClicked(double operand, QString &clickedOperator)
{
    if (clickedOperator == "+" || clickedOperator == "-") {
    return additiveOperatorClicked(operand,clickedOperator);
    } else if (clickedOperator == "\303\227" || clickedOperator == "\303\267") {
    return multiplicativeOperatorClicked(operand,clickedOperator);
    } else return 0;
}

void clear()
{
    if (waitingForOperand)
        return;

    waitingForOperand = true;
}

void clearAll()
{
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    waitingForOperand = true;
}

void abortOperation()
{
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    waitingForOperand = true;
}

bool calculate(double rightOperand, const QString &pendingOperator)
{

    if (pendingOperator == "+") {
        sumSoFar += rightOperand;
    } else if (pendingOperator == "-") {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == "\303\227") {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == "\303\267") {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}
