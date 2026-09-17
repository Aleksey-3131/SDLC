#pragma once
#include <QMainWindow>
#include "WeightModel.h"

class QLabel;
class QPushButton;
class WeightController;

// ==========================================================================
// VIEW (главное окно).
// Подписывается НАПРЯМУЮ на сигналы модели (dataChanged / errorOccurred)
// и обновляет себя, когда модель сама об этом сообщает — это и есть
// пассивное поведение View при активной модели: View не запрашивает
// данные сама, а реагирует на оповещения.
// ==========================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onEnterDataClicked();
    void onModelDataChanged();
    void onModelError(const QString &message);

private:
    WeightModel *m_model;
    WeightController *m_controller;

    QPushButton *m_enterButton;
    QLabel *m_inputLabel;
    QLabel *m_resultLabel;
    QLabel *m_allUnitsLabel;

    // Запоминание последних введенных данных для восстановления в диалоге
    QString m_lastRawValue;
    WeightUnit m_lastSourceUnit = WeightUnit::Kilogram;
    WeightUnit m_lastTargetUnit = WeightUnit::Pound;
    bool m_hasLastData = false;
};
