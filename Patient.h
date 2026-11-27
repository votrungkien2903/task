#pragma once
#include "Person.h"

/// Пациент больницы.
class Patient : public Person {
public:
    /// Значение номера палаты для пациента, ещё не размещённого в палате.
    static constexpr int NoWard = -1;

    /// Конструктор: идентификатор, ФИО и диагноз.
    Patient(int id, std::string name, std::string diagnosis);

    /// Возвращает номер палаты (или NoWard, если пациент не размещён).
    int GetWardNumber() const;

    /// Устанавливает номер палаты.
    void SetWardNumber(int wardNumber);

    /// Возвращает описание пациента.
    std::string GetInfo() const override;

private:
    std::string diagnosis_;
    int wardNumber_;
};
