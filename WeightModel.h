#pragma once
#include <QObject>
#include <QString>
#include <QList>

// Поддерживаемые единицы измерения веса
enum class WeightUnit {
    Kilogram,
    Pound,
    PolarBear,
    AfricanElephant,
    Zhiguli,
    BeerCan,
    Chicken,
    PaperSheet
};

// ==========================================================================
// МОДЕЛЬ (Model) — АКТИВНАЯ.
// Она не просто хранит данные: как только данные обновляются через
// setInput(), модель сама (без участия контроллера) рассылает сигнал
// dataChanged() всем подписанным View. Также сама проверяет корректность
// значения и в случае ошибки рассылает errorOccurred().
// ==========================================================================
class WeightModel : public QObject
{
    Q_OBJECT
public:
    explicit WeightModel(QObject *parent = nullptr);

    // Установить новые входные данные. Модель сама валидирует
    // и сама уведомляет подписчиков о результате.
    void setInput(double value, WeightUnit sourceUnit, WeightUnit targetUnit);

    double lastValue() const { return m_lastValue; }
    WeightUnit lastSourceUnit() const { return m_lastSourceUnit; }
    WeightUnit lastTargetUnit() const { return m_lastTargetUnit; }
    double convertedValue() const { return m_convertedValue; }
    bool hasData() const { return m_hasData; }

    // Вспомогательные статические функции пересчета
    static double toKilograms(double value, WeightUnit unit);
    static double fromKilograms(double kg, WeightUnit unit);
    static QString unitName(WeightUnit unit);
    static QList<WeightUnit> allUnits();

signals:
    // Активное оповещение подписчиков (View) об изменении состояния модели
    void dataChanged();
    void errorOccurred(const QString &message);

private:
    double m_lastValue = 0.0;
    WeightUnit m_lastSourceUnit = WeightUnit::Kilogram;
    WeightUnit m_lastTargetUnit = WeightUnit::Kilogram;
    double m_convertedValue = 0.0;
    bool m_hasData = false;
};
