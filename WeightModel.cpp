#include "WeightModel.h"

namespace {

// Коэффициенты пересчета одной единицы веса в килограммы.
// Забавные единицы взяты как усредненные справочные значения.
double factorToKg(WeightUnit unit)
{
    switch (unit) {
    case WeightUnit::Kilogram:        return 1.0;
    case WeightUnit::Pound:           return 0.453592;   // 1 фунт
    case WeightUnit::PolarBear:       return 450.0;       // средний вес белого медведя
    case WeightUnit::AfricanElephant: return 6000.0;      // средний вес африканского слона
    case WeightUnit::Zhiguli:         return 1030.0;      // средний вес автомобиля ВАЗ "Жигули"
    case WeightUnit::BeerCan:         return 0.5;         // банка пива 0.5 л
    case WeightUnit::Chicken:         return 2.0;         // средний вес курицы (бройлер)
    case WeightUnit::PaperSheet:      return 0.005;       // лист бумаги А4, 80 г/м²
    }
    return 1.0;
}

} // namespace

WeightModel::WeightModel(QObject *parent) : QObject(parent) {}

double WeightModel::toKilograms(double value, WeightUnit unit)
{
    return value * factorToKg(unit);
}

double WeightModel::fromKilograms(double kg, WeightUnit unit)
{
    return kg / factorToKg(unit);
}

QString WeightModel::unitName(WeightUnit unit)
{
    switch (unit) {
    case WeightUnit::Kilogram:        return QObject::tr("Килограмм");
    case WeightUnit::Pound:           return QObject::tr("Фунт");
    case WeightUnit::PolarBear:       return QObject::tr("Белый медведь");
    case WeightUnit::AfricanElephant: return QObject::tr("Африканский слон");
    case WeightUnit::Zhiguli:         return QObject::tr("Жигули");
    case WeightUnit::BeerCan:         return QObject::tr("Банка пива");
    case WeightUnit::Chicken:         return QObject::tr("Цыпленок");
    case WeightUnit::PaperSheet:      return QObject::tr("Лист бумаги");
    }
    return QString();
}

QList<WeightUnit> WeightModel::allUnits()
{
    return {
        WeightUnit::Kilogram,
        WeightUnit::Pound,
        WeightUnit::PolarBear,
        WeightUnit::AfricanElephant,
        WeightUnit::Zhiguli,
        WeightUnit::BeerCan,
        WeightUnit::Chicken,
        WeightUnit::PaperSheet
    };
}

void WeightModel::setInput(double value, WeightUnit sourceUnit, WeightUnit targetUnit)
{
    if (value <= 0.0) {
        // Модель сама обнаруживает некорректные данные и сама сообщает об этом
        emit errorOccurred(QObject::tr("Вес должен быть положительным числом."));
        return;
    }

    m_lastValue = value;
    m_lastSourceUnit = sourceUnit;
    m_lastTargetUnit = targetUnit;

    const double kg = toKilograms(value, sourceUnit);
    m_convertedValue = fromKilograms(kg, targetUnit);
    m_hasData = true;

    // Ключевой момент "активной" модели: она сама, без запроса от
    // контроллера, оповещает всех подписчиков (View) о готовности данных.
    emit dataChanged();
}
