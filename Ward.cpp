#include "Ward.h"

Ward::Ward(int number, int capacity) : number_(number), capacity_(capacity) {}

int Ward::GetNumber() const { return number_; }

int Ward::GetCapacity() const { return capacity_; }
