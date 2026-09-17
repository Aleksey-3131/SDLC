#include "InputDialog.h"

#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>

InputDialog::InputDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Ввод данных"));

    m_valueEdit = new QLineEdit(this);
    m_valueEdit->setPlaceholderText(tr("Например: 75.5"));

    m_sourceCombo = new QComboBox(this);
    m_targetCombo = new QComboBox(this);
    fillCombo(m_sourceCombo);
    fillCombo(m_targetCombo);
    if (m_targetCombo->count() > 1)
        m_targetCombo->setCurrentIndex(1); // по умолчанию цель отличается от источника

    auto *form = new QFormLayout;
    form->addRow(tr("Вес:"), m_valueEdit);
    form->addRow(tr("Единица (откуда):"), m_sourceCombo);
    form->addRow(tr("Единица (куда):"), m_targetCombo);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons);
}

void InputDialog::fillCombo(QComboBox *combo)
{
    for (WeightUnit u : WeightModel::allUnits())
        combo->addItem(WeightModel::unitName(u), static_cast<int>(u));
}

void InputDialog::setLastData(const QString &value, WeightUnit sourceUnit, WeightUnit targetUnit)
{
    m_valueEdit->setText(value);

    const int srcIndex = m_sourceCombo->findData(static_cast<int>(sourceUnit));
    if (srcIndex >= 0)
        m_sourceCombo->setCurrentIndex(srcIndex);

    const int tgtIndex = m_targetCombo->findData(static_cast<int>(targetUnit));
    if (tgtIndex >= 0)
        m_targetCombo->setCurrentIndex(tgtIndex);
}

QString InputDialog::enteredValue() const
{
    return m_valueEdit->text();
}

WeightUnit InputDialog::sourceUnit() const
{
    return static_cast<WeightUnit>(m_sourceCombo->currentData().toInt());
}

WeightUnit InputDialog::targetUnit() const
{
    return static_cast<WeightUnit>(m_targetCombo->currentData().toInt());
}
