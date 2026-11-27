#pragma once
#include <string>

/// Базовый абстрактный класс: человек, находящийся в системе больницы.
class Person {
public:
    /// Конструктор: задаёт идентификатор и ФИО.
    Person(int id, std::string name);

    /// Виртуальный деструктор (удаление через указатель на базовый класс).
    virtual ~Person() = default;

    /// Возвращает уникальный идентификатор.
    int GetId() const;

    /// Возвращает ФИО.
    const std::string& GetName() const;

    /// Возвращает строку с описанием объекта (полиморфный метод).
    virtual std::string GetInfo() const = 0;

private:
    int id_;
    std::string name_;
};
