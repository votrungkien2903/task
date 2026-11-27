#include "Doctor.h"
#include <utility>

Doctor::Doctor(int id, std::string name, std::string specialization)
    : MedicalWorker(id, std::move(name)), specialization_(std::move(specialization)) {}

std::string Doctor::GetInfo() const {
    return "Врач [id=" + std::to_string(GetId()) + "] " + GetName() +
           ", специализация: " + specialization_;
}
