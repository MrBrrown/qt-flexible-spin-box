/==============================================================================
#include "FlexibleSpinBox.h"
#include <QRegExp>
#include <iomanip>
//==============================================================================
double FlexibleSpinBox::valueFromText(const QString &text) const {
    bool ok;
    double number = text.toDouble(&ok);
    return ok? number : 0.0;
}

QString FlexibleSpinBox::textFromValue(double val) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimals()) << val;
    QString strNumber = QString::fromStdString(oss.str());
    QRegularExpression digitRegex("[0-9]");

    for (int i = strNumber.size() - 1; i >= 0 ; --i) {
        QChar ch = strNumber[i];

        if (!digitRegex.match(ch).hasMatch())
            return strNumber.left(i + 2);

        if (ch != '0')
            return strNumber.left(i + 1);
    }

    return strNumber;
}

QValidator::State FlexibleSpinBox::validate(QString &input, int &pos) const {
    if (input.isEmpty())
        return QValidator::Acceptable;

    QRegularExpression digitRegex("[0-9,.-]");
    QValidator::State res;
    if (digitRegex.match(input).hasMatch())
        res = QValidator::Acceptable;
    else
        return QValidator::Invalid;

    if (res == QValidator::Acceptable) {
        if (input.contains(',')) {
            input.replace(',', '.');

            QRegularExpression sepRegex(".?");
            if (sepRegex.match(text()).hasMatch())
                return QValidator::Invalid;
        }

        if (int i = text().indexOf('.'); i != -1) {
            if (pos - 1 - i > decimals())
                return QValidator::Invalid;
        }
    }

    return res;
}
//==============================================================================
