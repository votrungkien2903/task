#pragma once
#include "MedicalWorker.h"

/// Врач: медицинский работник с врачебной специализацией.
class Doctor : public MedicalWorker {
public:
    /// Конструктор: идентификатор, ФИО и специализация.
    Doctor(const int id, const std::string name, const std::string specialization);

    /// Возвращает описание врача.
    std::string GetInfo() const override;

private:
    std::string specialization_;
};
