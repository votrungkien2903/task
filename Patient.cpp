#include "Patient.h"
#include <utility>

Patient::Patient(int id, std::string name, std::string diagnosis)
    : Person(id, std::move(name)), diagnosis_(std::move(diagnosis)), wardNumber_(NoWard) {}

int Patient::GetWardNumber() const { return wardNumber_; }

void Patient::SetWardNumber(int wardNumber) { wardNumber_ = wardNumber; }

std::string Patient::GetInfo() const {
    std::string ward = (wardNumber_ == NoWard) ? "не размещён" : "палата " + std::to_string(wardNumber_);
    return "Пациент [id=" + std::to_string(GetId()) + "] " + GetName() +
           ", диагноз: " + diagnosis_ + ", " + ward;
}
