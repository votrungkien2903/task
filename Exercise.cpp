#include "Exercise.h"
#include <stdexcept>
#include <utility>

namespace {
/// Преобразует коллекцию людей в список их описаний (GetInfo).
template <typename T>
std::vector<std::string> ToLines(const std::vector<std::shared_ptr<const T>>& items) {
    std::vector<std::string> lines;
    for (const auto& item : items) lines.push_back(item->GetInfo());
    return lines;
}
}  // namespace

Exercise::Exercise(Hospital& hospital, std::shared_ptr<Generator> generator)
    : hospital_(hospital), generator_(std::move(generator)) {
    if (!generator_) throw std::invalid_argument("Генератор не задан");
}

void Exercise::Execute() { hospital_.FillLinks(*generator_); }

std::vector<std::string> Exercise::WorkersInfo() const { return ToLines(hospital_.GetWorkers()); }

std::vector<std::string> Exercise::WorkersOfPatientInfo(int patientId) const {
    return ToLines(hospital_.GetWorkersOfPatient(patientId));
}

std::vector<std::string> Exercise::PatientsInfo() const { return ToLines(hospital_.GetPatients()); }

std::vector<std::string> Exercise::PatientsOfWorkerInfo(int workerId) const {
    return ToLines(hospital_.GetPatientsOfWorker(workerId));
}

std::vector<std::string> Exercise::WardsInfo() const {
    std::vector<std::string> lines;
    for (const auto& [number, patients] : hospital_.GetPatientsByWard()) {
        if (patients.empty()) {
            lines.push_back("Палата " + std::to_string(number) + ": свободна");
            continue;
        }
        lines.push_back("Палата " + std::to_string(number) + ":");
        for (const auto& p : patients) lines.push_back("  " + p->GetInfo());
    }
    return lines;
}
