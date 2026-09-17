#pragma once
#include <QDialog>
#include "WeightModel.h"

class QLineEdit;
class QComboBox;

// ==========================================================================
// VIEW (вспомогательное окно).
// Дополнительное окно, открывающееся по кнопке "Ввести данные".
// Ничего не знает о модели, кроме списка допустимых единиц измерения —
// используется только для отображения и сбора пользовательского ввода.
// ==========================================================================
class InputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InputDialog(QWidget *parent = nullptr);

    // Восстановление последних введенных данных при повторном открытии
    void setLastData(const QString &value, WeightUnit sourceUnit, WeightUnit targetUnit);

    QString enteredValue() const;
    WeightUnit sourceUnit() const;
    WeightUnit targetUnit() const;

private:
    QLineEdit *m_valueEdit;
    QComboBox *m_sourceCombo;
    QComboBox *m_targetCombo;

    void fillCombo(QComboBox *combo);
};
