#include "Doctor.h"

Doctor::Doctor(const int id, const std::string name, const std::string specialization)
    : MedicalWorker(id, name), specialization_(specialization) {}

std::string Doctor::GetInfo() const {
    return "Врач [id=" + std::to_string(GetId()) + "] " + GetName() +
           ", специализация: " + specialization_;
}
