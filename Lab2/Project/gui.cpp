#include <ctype.h>
#include <QtWidgets>

#include "calculator.h"
#include "gui.h"

extern void setWaitOperand(bool);
extern bool getWaitOperand();
extern double unaryOperatorClicked(double, QString &clickedOperator);
extern double additiveOperatorClicked(double, QString &clickedOperator);
extern double multiplicativeOperatorClicked(double, QString &clickedOperator);
extern double equalClicked(double, QString &clickedOperator);
extern void clear();
extern void clearAll();
extern void abortOperation();
extern bool calculate(double, const QString &pendingOperator);

static QString clickedOperator;
static double operand;

Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize Button::sizeHint() const

{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}


CalculatorGUI::CalculatorGUI(QWidget *parent)
    : QWidget(parent)
{
    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClickedGUI()));
    }

    Button *pointButton = createButton(tr("."), SLOT(pointClickedGUI()));
    Button *signButton = createButton(tr("\302\261"), SLOT(changeSignClickedGUI()));
    Button *bkspButton = createButton(tr("Backspace"), SLOT(backspaceClickedGUI()));
    Button *CButton = createButton(tr("C"), SLOT(clearGUI()));
    Button *CEButton = createButton(tr("CE"), SLOT(clearAllGUI()));
    Button *divButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClickedGUI()));
    Button *mulButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClickedGUI()));
    Button *sbtButton = createButton(tr("-"), SLOT(additiveOperatorClickedGUI()));
    Button *addButton = createButton(tr("+"), SLOT(additiveOperatorClickedGUI()));
    Button *sqrtButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClickedGUI()));
    Button *powButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClickedGUI()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClickedGUI()));
    Button *equalButton = createButton(tr("="), SLOT(equalClickedGUI()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 1, 1, 5);
    mainLayout->addWidget(bkspButton, 1, 1, 1, 2);
    mainLayout->addWidget(CButton, 1, 3, 1, 1);
    mainLayout->addWidget(CEButton, 1, 4, 1, 2);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(signButton, 5, 3);
    mainLayout->addWidget(divButton, 2, 4);
    mainLayout->addWidget(mulButton, 3, 4);
    mainLayout->addWidget(sbtButton, 4, 4);
    mainLayout->addWidget(addButton, 5, 4);
    mainLayout->addWidget(sqrtButton, 2, 5);
    mainLayout->addWidget(powButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

void CalculatorGUI::digitClickedGUI()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0) //not to show multiple 0's
        return;

    if (display->text() == "0" || getWaitOperand())
    {display->clear();
        setWaitOperand(false);}

    display->setText(display->text() + QString::number(digitValue));

}

void CalculatorGUI::unaryOperatorClickedGUI()

{
    Button *clickedButton = qobject_cast<Button *>(sender());
    clickedOperator = clickedButton->text();
    operand = display->text().toDouble();
    double temp = unaryOperatorClicked(operand,clickedOperator);

    if (temp==NULL) abortOperationGUI();
    else display->setText(QString::number(temp));

    setWaitOperand(true);

}

void CalculatorGUI::additiveOperatorClickedGUI()

{
    Button *clickedButton = qobject_cast<Button *>(sender());
    clickedOperator = clickedButton->text();

    operand = display->text().toDouble();
    display->setText(QString::number(additiveOperatorClicked(operand,clickedOperator)));
    setWaitOperand(true);

}

void CalculatorGUI::multiplicativeOperatorClickedGUI()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    clickedOperator = clickedButton->text();

    operand = display->text().toDouble();
    display->setText(QString::number(multiplicativeOperatorClicked(operand,clickedOperator)));
    setWaitOperand(true);
}

void CalculatorGUI::equalClickedGUI()
{
    operand = display->text().toDouble();
    display->setText(QString::number(equalClicked(operand,clickedOperator)));
    setWaitOperand(true);

    clearAll();
}

void CalculatorGUI::pointClickedGUI()
{
    if (!display->text().contains('.')){
        setWaitOperand(false);
        display->setText(display->text() + tr("."));}
}

void CalculatorGUI::changeSignClickedGUI()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void CalculatorGUI::backspaceClickedGUI()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
       }
    display->setText(text);
}

void CalculatorGUI::clearGUI()
{
    clear();
    display->setText("0");
}

void CalculatorGUI::clearAllGUI()
{
    clearAll();
    display->setText("0");
}

Button *CalculatorGUI::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void CalculatorGUI::abortOperationGUI()
{
    clearAllGUI();
    display->setText(tr("####"));
}

bool CalculatorGUI::calculateGUI(double rightOperand, const QString &pendingOperator)
{
    calculate(rightOperand,pendingOperator);
    return true;

}

