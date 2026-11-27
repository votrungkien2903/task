#pragma once
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "Generator.h"
#include "Matrix.h"
#include "MedicalWorker.h"
#include "Patient.h"
#include "Ward.h"

/// Больница: хранит работников, пациентов, палаты и матрицу связей «работник - пациент».
/// Матрица связей: строка = работник, столбец = пациент (в порядке добавления),
/// ненулевой элемент = «работник наблюдает пациента». Заполняется генератором.
/// Добавление работника или пациента делает матрицу недействительной (её нужно заполнить заново).
/// Класс не выполняет ввод-вывод: сведения возвращаются в виде коллекций.
/// Идентификаторы работников и пациентов уникальны в пределах своей группы.
class Hospital {
public:
    /// Добавляет медицинского работника. Бросает std::invalid_argument при повторе id или nullptr.
    void AddWorker(std::shared_ptr<MedicalWorker> worker);

    /// Добавляет пациента. Бросает std::invalid_argument при повторе id или nullptr.
    void AddPatient(std::shared_ptr<Patient> patient);

    /// Добавляет палату. Бросает std::invalid_argument при повторе номера или вместимости <= 0.
    void AddWard(const Ward& ward);

    /// Размещает пациента в палате (при повторном вызове - переселяет).
    /// Бросает std::invalid_argument, если пациент или палата не найдены,
    /// и std::runtime_error, если в палате нет свободных мест.
    void PlacePatientInWard(int patientId, int wardNumber);

    /// Создаёт матрицу связей и заполняет её генератором (прежние связи заменяются).
    /// Бросает std::logic_error, если нет работников или пациентов.
    void FillLinks(Generator& generator);

    /// Возвращает матрицу связей. Бросает std::logic_error, если связи не заполнены.
    const Matrix& GetLinks() const;

    /// Возвращает всех медицинских работников.
    std::vector<std::shared_ptr<const MedicalWorker>> GetWorkers() const;

    /// Возвращает работников, наблюдающих за пациентом patientId.
    /// Бросает std::invalid_argument, если пациента нет, и std::logic_error, если связи не заполнены.
    std::vector<std::shared_ptr<const MedicalWorker>> GetWorkersOfPatient(int patientId) const;

    /// Возвращает всех пациентов.
    std::vector<std::shared_ptr<const Patient>> GetPatients() const;

    /// Возвращает пациентов, которых наблюдает работник workerId.
    /// Бросает std::invalid_argument, если работника нет, и std::logic_error, если связи не заполнены.
    std::vector<std::shared_ptr<const Patient>> GetPatientsOfWorker(int workerId) const;

    /// Возвращает размещение по палатам (номер палаты -> пациенты); пустые палаты включены.
    std::map<int, std::vector<std::shared_ptr<const Patient>>> GetPatientsByWard() const;

private:
    /// Возвращает индекс работника по id; бросает std::invalid_argument, если не найден.
    std::size_t FindWorkerIndex(int id) const;

    /// Возвращает индекс пациента по id; бросает std::invalid_argument, если не найден.
    std::size_t FindPatientIndex(int id) const;

    /// Возвращает палату по номеру; бросает std::invalid_argument, если не найдена.
    const Ward& FindWard(int number) const;

    std::vector<std::shared_ptr<MedicalWorker>> workers_;
    std::vector<std::shared_ptr<Patient>> patients_;
    std::vector<Ward> wards_;
    std::optional<Matrix> links_;
};
