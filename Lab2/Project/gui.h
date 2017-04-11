#ifndef GUI_H
#define GUI_H

#include <calculator.h>
#include <QToolButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const override;
};


class CalculatorGUI
    : public QWidget
{
    Q_OBJECT

public:
    CalculatorGUI(QWidget *parent = 0);

private slots:
    void digitClickedGUI();
    void unaryOperatorClickedGUI();
    void additiveOperatorClickedGUI();
    void multiplicativeOperatorClickedGUI();
    void equalClickedGUI();
    void pointClickedGUI();
    void changeSignClickedGUI();
    void backspaceClickedGUI();
    void clearGUI();
    void clearAllGUI();

private:
    Button *createButton(const QString &text, const char *member);
    void abortOperationGUI();
    bool calculateGUI(double rightOperand, const QString &pendingOperator);

    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};

#endif
