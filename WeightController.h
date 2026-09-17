#pragma once
#include <QObject>
#include "WeightModel.h"

// ==========================================================================
// КОНТРОЛЛЕР (Controller).
// Получает "сырой" пользовательский ввод (текст) из View, разбирает его
// и передает уже проверенные на формат данные в модель. Дальнейшую
// валидацию (например, value > 0) и оповещение View модель делает сама
// (см. WeightModel::setInput) — в этом суть активной модели.
// ==========================================================================
class WeightController : public QObject
{
    Q_OBJECT
public:
    explicit WeightController(WeightModel *model, QObject *parent = nullptr);

    void handleUserInput(const QString &rawValue, WeightUnit sourceUnit, WeightUnit targetUnit);

private:
    WeightModel *m_model;
};
