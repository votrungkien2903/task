#pragma once
#include "MedicalWorker.h"

/// Медицинская сестра: медицинский работник, закреплённый за отделением.
class Nurse : public MedicalWorker {
public:
    /// Конструктор: идентификатор, ФИО и название отделения.
    Nurse(int id, std::string name, std::string department);

    /// Возвращает описание медсестры.
    std::string GetInfo() const override;

private:
    std::string department_;
};
