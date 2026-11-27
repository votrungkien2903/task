#include <iostream>
#include <memory>
#include <stdexcept>

#include "ConstantGenerator.h"
#include "Doctor.h"
#include "Exercise.h"
#include "Hospital.h"
#include "KeyboardGenerator.h"
#include "Matrix.h"
#include "Nurse.h"
#include "Patient.h"
#include "RandomGenerator.h"

static int failures = 0;

#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            ++failures;                                                          \
            std::cerr << "ПРОВАЛ: " #cond " (строка " << __LINE__ << ")\n";     \
        }                                                                        \
    } while (0)

#define CHECK_THROWS(expr, ExType)                                               \
    do {                                                                         \
        bool thrown = false;                                                     \
        try { expr; } catch (const ExType&) { thrown = true; }                   \
        CHECK(thrown);                                                           \
    } while (0)

/// Создаёт тестовую больницу: врач (id 1), медсестра (id 2), пациенты id 1 и 2, палаты 10 (1 место) и 20 (2 места).
static Hospital MakeHospital() {
    Hospital h;
    h.AddWorker(std::make_shared<Doctor>(1, "Врач1", "Терапевт"));
    h.AddWorker(std::make_shared<Nurse>(2, "Сестра1", "Терапия"));
    h.AddPatient(std::make_shared<Patient>(1, "Пациент1", "Грипп"));
    h.AddPatient(std::make_shared<Patient>(2, "Пациент2", "Ангина"));
    h.AddWard(Ward(10, 1));
    h.AddWard(Ward(20, 2));
    return h;
}

static void TestPolymorphicInfo() {
    std::unique_ptr<Person> p = std::make_unique<Doctor>(1, "Иванов", "Хирург");
    CHECK(p->GetInfo().find("Хирург") != std::string::npos);
    p = std::make_unique<Nurse>(2, "Петрова", "Терапия");
    CHECK(p->GetInfo().find("Терапия") != std::string::npos);
    p = std::make_unique<Patient>(1, "Сидоров", "Грипп");
    CHECK(p->GetInfo().find("не размещён") != std::string::npos);
}

static void TestMatrix() {
    Matrix m(2, 3);
    CHECK(m.GetRows() == 2 && m.GetCols() == 3 && m.Get(1, 2) == 0);
    m.Set(1, 2, 5);
    CHECK(m.Get(1, 2) == 5);
    CHECK_THROWS(m.Get(2, 0), std::out_of_range);
    CHECK_THROWS(m.Set(0, 3, 1), std::out_of_range);
    CHECK_THROWS(Matrix(0, 3), std::invalid_argument);
}

static void TestGenerators() {
    Matrix m(2, 2);
    ConstantGenerator(7).Fill(m);
    CHECK(m.Get(0, 0) == 7 && m.Get(1, 1) == 7);

    Matrix big(20, 20);
    RandomGenerator(0, 1).Fill(big);
    bool zero = false, one = false, inRange = true;
    for (std::size_t r = 0; r < 20; ++r)
        for (std::size_t c = 0; c < 20; ++c) {
            int v = big.Get(r, c);
            zero = zero || v == 0;
            one = one || v == 1;
            inRange = inRange && (v == 0 || v == 1);
        }
    CHECK(zero && one && inRange);
    CHECK_THROWS(RandomGenerator(5, 1), std::invalid_argument);

    int counter = 0;
    KeyboardGenerator k([&counter](std::size_t, std::size_t) { return ++counter; });
    k.Fill(m);
    CHECK(m.Get(0, 0) == 1 && m.Get(0, 1) == 2 && m.Get(1, 1) == 4);
    CHECK_THROWS(KeyboardGenerator(nullptr), std::invalid_argument);
}

static void TestWards() {
    Hospital h = MakeHospital();
    h.PlacePatientInWard(1, 10);
    CHECK_THROWS(h.PlacePatientInWard(2, 10), std::runtime_error);  // палата на 1 место
    h.PlacePatientInWard(2, 20);
    auto byWard = h.GetPatientsByWard();
    CHECK(byWard.size() == 2 && byWard[10].size() == 1 && byWard[20].size() == 1);
    h.PlacePatientInWard(1, 20);  // переселение
    CHECK(h.GetPatientsByWard()[10].empty());
    CHECK_THROWS(h.PlacePatientInWard(1, 999), std::invalid_argument);
    CHECK_THROWS(h.PlacePatientInWard(99, 10), std::invalid_argument);
}

static void TestDuplicates() {
    Hospital h = MakeHospital();
    CHECK_THROWS(h.AddWorker(std::make_shared<Doctor>(1, "Дубль", "X")), std::invalid_argument);
    CHECK_THROWS(h.AddPatient(std::make_shared<Patient>(1, "Дубль", "X")), std::invalid_argument);
    CHECK_THROWS(h.AddWard(Ward(10, 3)), std::invalid_argument);
    CHECK_THROWS(h.AddWard(Ward(30, 0)), std::invalid_argument);
    CHECK_THROWS(h.AddWorker(nullptr), std::invalid_argument);
}

static void TestLinks() {
    Hospital h = MakeHospital();
    CHECK_THROWS(h.GetLinks(), std::logic_error);               // связи ещё не заполнены
    CHECK_THROWS(h.GetWorkersOfPatient(1), std::logic_error);

    ConstantGenerator all(1);
    h.FillLinks(all);
    CHECK(h.GetWorkersOfPatient(1).size() == 2 && h.GetPatientsOfWorker(1).size() == 2);

    // Диагональная матрица: работник 1 - пациент 1, работник 2 - пациент 2.
    KeyboardGenerator diagonal([](std::size_t r, std::size_t c) { return r == c ? 1 : 0; });
    h.FillLinks(diagonal);
    auto workers = h.GetWorkersOfPatient(2);
    CHECK(workers.size() == 1 && workers[0]->GetId() == 2);
    auto patients = h.GetPatientsOfWorker(1);
    CHECK(patients.size() == 1 && patients[0]->GetId() == 1);
    CHECK_THROWS(h.GetWorkersOfPatient(99), std::invalid_argument);
    CHECK_THROWS(h.GetPatientsOfWorker(99), std::invalid_argument);

    h.AddPatient(std::make_shared<Patient>(3, "Пациент3", "Ожог"));  // размеры изменились
    CHECK_THROWS(h.GetLinks(), std::logic_error);

    Hospital empty;
    CHECK_THROWS(empty.FillLinks(all), std::logic_error);
}

static void TestExercise() {
    Hospital h = MakeHospital();
    h.PlacePatientInWard(1, 10);
    Exercise e(h, std::make_shared<KeyboardGenerator>([](std::size_t r, std::size_t c) { return r == c ? 1 : 0; }));
    CHECK_THROWS(e.WorkersOfPatientInfo(1), std::logic_error);  // до Execute
    e.Execute();
    CHECK(e.WorkersInfo().size() == 2);
    CHECK(e.PatientsInfo().size() == 2);
    CHECK(e.WorkersOfPatientInfo(1).size() == 1);
    CHECK(e.PatientsOfWorkerInfo(2).size() == 1);
    auto wards = e.WardsInfo();  // «Палата 10:», пациент, «Палата 20: свободна»
    CHECK(wards.size() == 3 && wards[2].find("свободна") != std::string::npos);
    CHECK_THROWS(Exercise(h, nullptr), std::invalid_argument);
}

int main() {
    TestPolymorphicInfo();
    TestMatrix();
    TestGenerators();
    TestWards();
    TestDuplicates();
    TestLinks();
    TestExercise();
    std::cout << (failures == 0 ? "Все тесты пройдены\n" : "Есть ошибки\n");
    return failures == 0 ? 0 : 1;
}
