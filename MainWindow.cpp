#include "MainWindow.h"
#include "WeightController.h"
#include "InputDialog.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Конвертер веса"));

    m_model = new WeightModel(this);
    m_controller = new WeightController(m_model, this);

    // View подписывается непосредственно на сигналы модели —
    // именно в этом заключается АКТИВНАЯ модель: она сама уведомляет
    // подписчиков об изменении состояния, без посредничества контроллера.
    connect(m_model, &WeightModel::dataChanged, this, &MainWindow::onModelDataChanged);
    connect(m_model, &WeightModel::errorOccurred, this, &MainWindow::onModelError);

    m_enterButton = new QPushButton(tr("Ввести данные"), this);
    connect(m_enterButton, &QPushButton::clicked, this, &MainWindow::onEnterDataClicked);

    m_inputLabel = new QLabel(tr("Данные еще не введены."), this);
    m_resultLabel = new QLabel(this);
    m_allUnitsLabel = new QLabel(this);
    m_allUnitsLabel->setWordWrap(true);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(m_enterButton);
    layout->addWidget(m_inputLabel);
    layout->addWidget(m_resultLabel);
    layout->addWidget(m_allUnitsLabel);
    layout->addStretch();
    setCentralWidget(central);

    resize(420, 280);
}

void MainWindow::onEnterDataClicked()
{
    InputDialog dialog(this);

    // Восстановление последних введенных данных при повторном открытии окна
    if (m_hasLastData)
        dialog.setLastData(m_lastRawValue, m_lastSourceUnit, m_lastTargetUnit);

    if (dialog.exec() == QDialog::Accepted) {
        m_lastRawValue = dialog.enteredValue();
        m_lastSourceUnit = dialog.sourceUnit();
        m_lastTargetUnit = dialog.targetUnit();
        m_hasLastData = true;

        // Контроллер передает "сырые" данные в модель
        m_controller->handleUserInput(m_lastRawValue, m_lastSourceUnit, m_lastTargetUnit);
    }
}

void MainWindow::onModelDataChanged()
{
    m_inputLabel->setText(tr("Введено: %1 %2")
        .arg(m_model->lastValue())
        .arg(WeightModel::unitName(m_model->lastSourceUnit())));

    m_resultLabel->setText(tr("Результат: %1 %2")
        .arg(m_model->convertedValue(), 0, 'f', 4)
        .arg(WeightModel::unitName(m_model->lastTargetUnit())));

    // Дополнительно показываем эквивалент во всех поддерживаемых единицах —
    // наглядно демонстрирует все "упомянутые величины" из задания.
    const double kg = WeightModel::toKilograms(m_model->lastValue(), m_model->lastSourceUnit());
    QString allText = tr("Эквивалент во всех единицах:\n");
    for (WeightUnit u : WeightModel::allUnits()) {
        allText += QString("  %1: %2\n")
            .arg(WeightModel::unitName(u))
            .arg(WeightModel::fromKilograms(kg, u), 0, 'f', 4);
    }
    m_allUnitsLabel->setText(allText);
}

void MainWindow::onModelError(const QString &message)
{
    QMessageBox::warning(this, tr("Ошибка"), message);
}
