#include "Hospital.h"
#include <stdexcept>

void Hospital::AddWorker(std::shared_ptr<MedicalWorker> worker) {
    if (!worker) throw std::invalid_argument("Пустой указатель на работника");
    for (const auto& w : workers_)
        if (w->GetId() == worker->GetId()) throw std::invalid_argument("Работник с таким id уже существует");
    workers_.push_back(std::move(worker));
    links_.reset();  // размеры матрицы изменились
}

void Hospital::AddPatient(std::shared_ptr<Patient> patient) {
    if (!patient) throw std::invalid_argument("Пустой указатель на пациента");
    for (const auto& p : patients_)
        if (p->GetId() == patient->GetId()) throw std::invalid_argument("Пациент с таким id уже существует");
    patients_.push_back(std::move(patient));
    links_.reset();  // размеры матрицы изменились
}

void Hospital::AddWard(const Ward& ward) {
    if (ward.GetCapacity() <= 0) throw std::invalid_argument("Вместимость палаты должна быть положительной");
    for (const auto& w : wards_)
        if (w.GetNumber() == ward.GetNumber()) throw std::invalid_argument("Палата с таким номером уже существует");
    wards_.push_back(ward);
}

void Hospital::PlacePatientInWard(int patientId, int wardNumber) {
    auto& patient = patients_[FindPatientIndex(patientId)];
    const Ward& ward = FindWard(wardNumber);

    int occupied = 0;
    for (const auto& p : patients_)
        if (p->GetWardNumber() == wardNumber && p->GetId() != patientId) ++occupied;
    if (occupied >= ward.GetCapacity()) throw std::runtime_error("В палате нет свободных мест");

    patient->SetWardNumber(wardNumber);
}

void Hospital::FillLinks(Generator& generator) {
    if (workers_.empty() || patients_.empty())
        throw std::logic_error("Для матрицы связей нужен хотя бы один работник и один пациент");
    Matrix matrix(workers_.size(), patients_.size());
    generator.Fill(matrix);
    links_ = std::move(matrix);
}

const Matrix& Hospital::GetLinks() const {
    if (!links_) throw std::logic_error("Матрица связей не заполнена: вызовите FillLinks()");
    return *links_;
}

std::vector<std::shared_ptr<const MedicalWorker>> Hospital::GetWorkers() const {
    return {workers_.begin(), workers_.end()};
}

std::vector<std::shared_ptr<const MedicalWorker>> Hospital::GetWorkersOfPatient(int patientId) const {
    const std::size_t column = FindPatientIndex(patientId);
    const Matrix& links = GetLinks();
    std::vector<std::shared_ptr<const MedicalWorker>> result;
    for (std::size_t r = 0; r < workers_.size(); ++r)
        if (links.Get(r, column) != 0) result.push_back(workers_[r]);
    return result;
}

std::vector<std::shared_ptr<const Patient>> Hospital::GetPatients() const {
    return {patients_.begin(), patients_.end()};
}

std::vector<std::shared_ptr<const Patient>> Hospital::GetPatientsOfWorker(int workerId) const {
    const std::size_t row = FindWorkerIndex(workerId);
    const Matrix& links = GetLinks();
    std::vector<std::shared_ptr<const Patient>> result;
    for (std::size_t c = 0; c < patients_.size(); ++c)
        if (links.Get(row, c) != 0) result.push_back(patients_[c]);
    return result;
}

std::map<int, std::vector<std::shared_ptr<const Patient>>> Hospital::GetPatientsByWard() const {
    std::map<int, std::vector<std::shared_ptr<const Patient>>> result;
    for (const auto& w : wards_) result[w.GetNumber()];  // включаем пустые палаты
    for (const auto& p : patients_)
        if (p->GetWardNumber() != Patient::NoWard) result[p->GetWardNumber()].push_back(p);
    return result;
}

std::size_t Hospital::FindWorkerIndex(int id) const {
    for (std::size_t i = 0; i < workers_.size(); ++i)
        if (workers_[i]->GetId() == id) return i;
    throw std::invalid_argument("Медицинский работник не найден");
}

std::size_t Hospital::FindPatientIndex(int id) const {
    for (std::size_t i = 0; i < patients_.size(); ++i)
        if (patients_[i]->GetId() == id) return i;
    throw std::invalid_argument("Пациент не найден");
}

const Ward& Hospital::FindWard(int number) const {
    for (const auto& w : wards_)
        if (w.GetNumber() == number) return w;
    throw std::invalid_argument("Палата не найдена");
}
