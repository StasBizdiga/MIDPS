#ifndef CALCULATOR_H
#define CALCULATOR_H



    void setWaitOperand(bool);
    bool getWaitOperand();
    double unaryOperatorClicked(double, QString &clickedOperator);
    double additiveOperatorClicked(double, QString &clickedOperator);
    double multiplicativeOperatorClicked(double, QString &clickedOperator);
    double equalClicked(double, QString &clickedOperator);
    void clear();
    void clearAll();
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);

#endif
