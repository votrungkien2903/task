#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Generator.h"
#include "Hospital.h"

/// Упражнение «Больница»: заполняет матрицу связей выбранным генератором и
/// выдаёт пять требуемых заданием справок в виде списков строк (без ввода-вывода).
class Exercise {
public:
    /// Конструктор: больница (объект должен пережить Exercise) и генератор заполнения связей.
    /// Бросает std::invalid_argument, если generator пуст.
    Exercise(Hospital& hospital, std::shared_ptr<Generator> generator);

    /// Заполняет матрицу связей «работник - пациент» генератором.
    void Execute();

    /// Справка 1: сведения о медицинских работниках.
    std::vector<std::string> WorkersInfo() const;

    /// Справка 2: сведения о работниках, наблюдающих пациента patientId.
    std::vector<std::string> WorkersOfPatientInfo(int patientId) const;

    /// Справка 3: сведения о пациентах.
    std::vector<std::string> PatientsInfo() const;

    /// Справка 4: сведения о пациентах, наблюдаемых работником workerId.
    std::vector<std::string> PatientsOfWorkerInfo(int workerId) const;

    /// Справка 5: нахождение пациентов по палатам (строка «Палата N:» и по строке на пациента).
    std::vector<std::string> WardsInfo() const;

private:
    Hospital& hospital_;
    std::shared_ptr<Generator> generator_;
};
