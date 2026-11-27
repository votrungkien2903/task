#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

#include "ConstantGenerator.h"
#include "Doctor.h"
#include "Exercise.h"
#include "Hospital.h"
#include "KeyboardGenerator.h"
#include "Nurse.h"
#include "Patient.h"
#include "RandomGenerator.h"

/// Выводит заголовок и список строк в стандартный поток вывода.
static void PrintLines(const std::string& title, const std::vector<std::string>& lines) {
    std::cout << "\n=== " << title << " ===\n";
    if (lines.empty()) std::cout << "  (нет)\n";
    for (const auto& line : lines) std::cout << "  " << line << '\n';
}

/// Выводит матрицу связей «работник - пациент» с подписями идентификаторов.
static void PrintLinks(const Hospital& hospital) {
    const auto workers = hospital.GetWorkers();
    const auto patients = hospital.GetPatients();
    const Matrix& links = hospital.GetLinks();

    std::cout << "\nМатрица связей (1 - работник наблюдает пациента):\n  id пациентов:  ";
    for (const auto& p : patients) std::cout << std::setw(3) << p->GetId();
    std::cout << '\n';
    for (std::size_t r = 0; r < workers.size(); ++r) {
        std::cout << "  id работника " << workers[r]->GetId() << ":";
        for (std::size_t c = 0; c < patients.size(); ++c) std::cout << std::setw(3) << links.Get(r, c);
        std::cout << '\n';
    }
}

/// Создаёт генератор по выбору пользователя: 1 - константа, 3 - клавиатура, иначе - случайный.
static std::shared_ptr<Generator> ChooseGenerator(int choice, const Hospital& hospital) {
    if (choice == 1) return std::make_shared<ConstantGenerator>(1);
    if (choice == 3) {
        const auto workers = hospital.GetWorkers();
        const auto patients = hospital.GetPatients();
        return std::make_shared<KeyboardGenerator>([workers, patients](std::size_t r, std::size_t c) {
            int value = 0;
            std::cout << "  Работник id=" << workers[r]->GetId() << " наблюдает пациента id="
                      << patients[c]->GetId() << "? (1 - да, 0 - нет): ";
            if (!(std::cin >> value)) value = 0;
            return value;
        });
    }
    return std::make_shared<RandomGenerator>(0, 1);
}

/// Точка входа: демонстрация работы библиотеки HospitalLib.
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    auto doctor1 = std::make_shared<Doctor>(1, "Иванов Иван Иванович", "Терапевт");
    auto doctor2 = std::make_shared<Doctor>(2, "Петрова Анна Сергеевна", "Хирург");
    auto nurse1 = std::make_shared<Nurse>(3, "Сидорова Мария Павловна", "Хирургическое отделение");
    auto patient1 = std::make_shared<Patient>(1, "Кузнецов Алексей", "Пневмония");
    auto patient2 = std::make_shared<Patient>(2, "Смирнова Ольга", "Аппендицит");
    auto patient3 = std::make_shared<Patient>(3, "Орлов Дмитрий", "Перелом руки");

    Hospital hospital;
    hospital.AddWorker(doctor1);
    hospital.AddWorker(doctor2);
    hospital.AddWorker(nurse1);
    hospital.AddPatient(patient1);
    hospital.AddPatient(patient2);
    hospital.AddPatient(patient3);
    hospital.AddWard(Ward(101, 2));
    hospital.AddWard(Ward(102, 1));
    hospital.AddWard(Ward(103, 3));
    hospital.PlacePatientInWard(1, 101);
    hospital.PlacePatientInWard(2, 102);
    hospital.PlacePatientInWard(3, 101);

    // Коллекция объектов базового типа, заполненная объектами-наследниками.
    std::vector<std::shared_ptr<Person>> people = {doctor1, doctor2, nurse1, patient1, patient2, patient3};
    std::cout << "=== Все люди (итерация по коллекции базового класса) ===\n";
    for (const auto& person : people) std::cout << person->GetInfo() << '\n';

    std::cout << "\nСпособ заполнения матрицы связей:\n"
                 "  1 - константа (все связи есть)\n"
                 "  2 - случайно\n"
                 "  3 - с клавиатуры\n"
                 "Ваш выбор: ";
    int choice = 2;
    if (!(std::cin >> choice)) choice = 2;

    Exercise exercise(hospital, ChooseGenerator(choice, hospital));
    exercise.Execute();
    PrintLinks(hospital);

    PrintLines("1. Медицинские работники", exercise.WorkersInfo());
    PrintLines("2. Работники, наблюдающие пациента id=3", exercise.WorkersOfPatientInfo(3));
    PrintLines("3. Пациенты", exercise.PatientsInfo());
    PrintLines("4. Пациенты работника id=2", exercise.PatientsOfWorkerInfo(2));
    PrintLines("5. Нахождение пациентов по палатам", exercise.WardsInfo());
    return 0;
}
