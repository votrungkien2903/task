#include "Nurse.h"
#include <utility>

Nurse::Nurse(int id, std::string name, std::string department)
    : MedicalWorker(id, std::move(name)), department_(std::move(department)) {}

std::string Nurse::GetInfo() const {
    return "Медсестра [id=" + std::to_string(GetId()) + "] " + GetName() +
           ", отделение: " + department_;
}
