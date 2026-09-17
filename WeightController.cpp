#include "WeightController.h"

WeightController::WeightController(WeightModel *model, QObject *parent)
    : QObject(parent), m_model(model)
{
}

void WeightController::handleUserInput(const QString &rawValue, WeightUnit sourceUnit, WeightUnit targetUnit)
{
    QString normalized = rawValue.trimmed();
    normalized.replace(',', '.');

    bool ok = false;
    const double value = normalized.toDouble(&ok);

    if (!ok || normalized.isEmpty()) {
        // Ошибка формата — контроллер не лезет во внутреннее состояние модели
        // напрямую, а использует тот же канал оповещения View, что и модель.
        emit m_model->errorOccurred(QObject::tr("Введите корректное число (например: 75.5)."));
        return;
    }

    // Дальнейшую проверку (например, что число положительное)
    // и оповещение View берет на себя сама модель.
    m_model->setInput(value, sourceUnit, targetUnit);
}
