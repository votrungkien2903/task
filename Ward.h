#pragma once

/// Палата больницы.
class Ward {
public:
    /// Конструктор: номер палаты и вместимость (количество коек).
    Ward(int number, int capacity);

    /// Возвращает номер палаты.
    int GetNumber() const;

    /// Возвращает вместимость палаты.
    int GetCapacity() const;

private:
    int number_;
    int capacity_;
};
