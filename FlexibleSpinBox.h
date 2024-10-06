//==============================================================================

#ifndef FLEXIBLESPINBOX_H
#define FLEXIBLESPINBOX_H

//==============================================================================
#include <QDoubleSpinBox>
//==============================================================================
class FlexibleSpinBox : public QDoubleSpinBox {
public:
    FlexibleSpinBox() {};
    FlexibleSpinBox(QWidget *parent) : QDoubleSpinBox(parent) {}

    double valueFromText(const QString &text) const override;
    QString textFromValue(double val) const override;
    QValidator::State validate(QString &input, int &pos) const override;
};
//==============================================================================
#endif // FLEXIBLESPINBOX_H
