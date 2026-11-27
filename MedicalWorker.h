#pragma once
#include "Person.h"

/// Абстрактный медицинский работник: общий предок врача и медсестры.
/// Позволяет хранить и обрабатывать всех работников единым списком.
class MedicalWorker : public Person {
public:
    /// Конструктор: идентификатор и ФИО.
    MedicalWorker(int id, std::string name);
};
