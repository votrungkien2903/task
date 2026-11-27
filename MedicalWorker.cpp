#include "MedicalWorker.h"
#include <utility>

MedicalWorker::MedicalWorker(int id, std::string name) : Person(id, std::move(name)) {}
