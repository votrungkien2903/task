#include "Person.h"
#include <utility>

Person::Person(int id, std::string name) : id_(id), name_(std::move(name)) {}

int Person::GetId() const { return id_; }

const std::string& Person::GetName() const { return name_; }
