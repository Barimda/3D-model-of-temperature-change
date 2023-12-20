# О проекте
Данный проект позволяет создать математическую модель объекта для моделирования изменения температуры.
## Платформа на которой написан код
Clion 2023.2.2
# Описание файлов и классов
## main.cpp
Основной файл в котором реализуются классы
### Переменные
* отсутствуют
### Методы
* main() - метод для запуска консольного приложения

### Исполняемые методы
* prg.showTemplate(); //Запускает пример с использованием метода прогонки на синусоиде
* stena stenaN(int dots_count, double tolshina, double temperature_left, double temperature_right); //Запускает пример с расчетом теплопроводности стены с различными параметрами

_**int dots_count**_ - количество точек на отрезке стены

_**double tolshina**_ - толщина стены в метрах

_**double temperature_left**_ - температура стены в левой крайней точке (в Кельвинах или Цельсиях)

_**double temperature_right**_ - температура стены в правой крайней точке (в Кельвинах или Цельсиях)

* stenaN.calculateDots() // Запускает расчет температуры в точках используя метод прогонки
* stenaN.calculateDotsWithTime(int timeEnd) // Запускает расчет температуры в точках используя метод прогонки + время (нерабочий)

_**int timeEnd**_ - указывает прмежуток времени в котором происходит изменение температуры материала (`это не время расчета`)  

## progonka.h
Класс описывающий методы продольно-поперечной прогонки в разрезе 1Д (отрезки материала + температура + время)
### Переменные
* отсутсвтуют
### Методы

* void solveMatrix(int n, double *a, double *b, double *c, double *f, double mu1, double kappa1, double mu2, double kappa2, double *y)

Метод прогонки в различных реализациях:

Базовый пример:
* public: void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f, double mu1, double kappa1, double mu2, double kappa2, double *y)

Пример со стеной
* public: void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f, double mu1, double kappa1, double mu2, double kappa2, double *y, double *lambda)

Пример со стеной + привязка ко времени
* public: void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f, double mu1, double kappa1, double mu2, double kappa2, double *y, double *lambda, double tau, double *y_old)

Пример на синусоиде
* public: void showTemplate()

## stena.h

### Переменные
* progonka prog;

### Конструктор
Создает экземляр класса с температурой 0 указанной толщины разделенный на указанное количество точек:
* stena(int dots_count, double tolshina)

Создает экземляр класса с указанной температурой в крайних точках, указанной толщины разделенный на указанное количество точек:
* stena(int dots_count, double tolshina, double temperature_left, double temperature_right)
### Методы
Методы получения значений:
* double getTemperatureLeft()
* double getTemperatureRight()

Методы присвоения значений:
* void setTemperatureLeft(double temperature)
* void setTemperatureRight(double temperature)

Метод расчета без учета времени:
* void calculateDots()

Метод расчета с учетом времени (НЕРАБОЧИЙ):
* calculateDotsWithTime(double timeEnd)

## model3D.h
### Подкласс (структура) Layer
* double temperature = 0; //температура в Кельвинах
* double conductivity = 1; //теплопроводность Кельвинах
* double depth = 1; //толщина в мм
### Класс model3D
### Переменные
* int numLayersX_; //количество точек в разрезе X
* int numLayersY_; //количество точек в разрезе Y
* int numLayersZ_; //количество точек в разрезе Z
* std::vector<std::vector<std::vector<Layer>>> temperature_; //Векторы температуры
### Методы
Задание исходных параметров модели:
* void SetLayerProperties(int layerX, int layerY, int layerZ, double conductivity, double depth) //Задание свойств теплопроодности и тощины точки в объекте
* void SetLayerPropertiesUniform(double conductivity, double depth) //Задание свойств теплопроодности и тощины всех точек в объекте (для однородных объектов)
* void SetInitialTemperature(int layerX, int layerY, int layerZ, double temperature) //Задание температуры для точки
* void SetInitialTemperatureUniform(double temperature) //Задание температуры для всех точек объекта

Получение параметров модели:
* double GetDotTemperature(int layerX, int layerY, int layerZ) const //Получение температуры точки
* int GetNumLayersX() const //Получение количества точек по оси X
* int GetNumLayersY() const //Получение количества точек по оси Y
* int GetNumLayersZ() const //Получение количества точек по оси Z

Расчет уравнения распределния температуры методом продольно-поперечной прогонки:
* void SolveHeatEquation(double dt, double dx, double dy, double dz, double tStart, double tEnd)