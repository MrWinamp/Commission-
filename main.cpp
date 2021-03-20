#include <QCoreApplication>

class Employee
{
   int employee_Id;
  std::string employeeName;
public:
// Этот метод вставляет работника в таблицу некоторой БД
  bool InsertIntoEmployeeTable(Employee &em);

};

class ReportGenerator
{
public:
// Этот метод генерирует отчет относительно заданного работника
    void GenerateReport(Employee &em);
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
