#ifndef UNTITLED_MODEL3D_H
#define UNTITLED_MODEL3D_H

#include <vector>

struct Layer {
    double temperature = 0; //температура в Кельвинах
    double conductivity = 1; //теплопроводность Кельвинах
    double depth = 1; //толщина в мм
};

class model3D {
public:
    model3D(int numLayersX, int numLayersY, int numLayersZ)  //задаем количество слоев в плоскостях XYZ
            : numLayersX_(numLayersX), numLayersY_(numLayersY), numLayersZ_(numLayersZ) {
        temperature_.resize(numLayersZ_, std::vector<std::vector<Layer>>(numLayersY_, std::vector<Layer>(numLayersX_)));
    }

    void SetLayerProperties(int layerX, int layerY, int layerZ, double conductivity,
                            double depth) { //Записываем значения теплопроводности и толщины для каждой точки
        temperature_[layerZ][layerY][layerX].conductivity = conductivity; //теплопроводность
        temperature_[layerZ][layerY][layerX].depth = depth; //толщина
    }

    void SetLayerPropertiesUniform(double conductivity, double depth) { //Записываем значения теплопроводности и толщины для каждой точки (однородная структура)
        for (int z = 1; z < numLayersZ_ - 1; ++z) {
            for (int y = 1; y < numLayersY_ - 1; ++y) {
                for (int x = 1; x < numLayersX_ - 1; ++x) {
                    SetLayerProperties(x, y, x, conductivity, depth);
                }
            }
        }
    }

    void SetInitialTemperature(int layerX, int layerY, int layerZ,
                               double temperature) { //Записываем значения температуры для каждой точки
        temperature_[layerZ][layerY][layerX].temperature = temperature;
    }

    void SetInitialTemperatureUniform(double temperature) { //Записываем значения температуры для каждой точки (однородная структура)
        for (int z = 1; z < numLayersZ_ - 1; ++z) {
            for (int y = 1; y < numLayersY_ - 1; ++y) {
                for (int x = 1; x < numLayersX_ - 1; ++x) {
                    SetInitialTemperature(x, y, x, temperature);
                }
            }
        }
    }

    // Метод для получения текущей температуры слоя
    double GetDotTemperature(int layerX, int layerY, int layerZ) const {
        return temperature_[layerZ][layerY][layerX].temperature;
    }

    // Метод для получения количества слоев по оси X
    int GetNumLayersX() const {
        return numLayersX_;
    }

    // Метод для получения количества слоев по оси Y
    int GetNumLayersY() const {
        return numLayersY_;
    }

    // Метод для получения количества слоев по оси Z
    int GetNumLayersZ() const {
        return numLayersZ_;
    }

    //Следующий метод решает уравнение теплопроводности для модели, используя метод продольно-поперечной прогонки. Он проходится по всем внутренним слоям модели и для каждого слоя вычисляет изменение температуры на основе соседних слоев и их свойств.
    //Неприменим для однородных (идеальных) тел
    void SolveHeatEquation(double dt, double dx, double dy, double dz, double tStart, double tEnd) {
        double t = tStart;
        while (t <= tEnd) {
            for (int k = 1; k < numLayersZ_ - 1; ++k) {
                for (int j = 1; j < numLayersY_ - 1; ++j) {
                    for (int i = 1; i < numLayersX_ - 1; ++i) {
                        double alpha =
                                dt / (dx * dx) *
                                (temperature_[k - 1][j][i].temperature + temperature_[k + 1][j][i].temperature +
                                 temperature_[k][j - 1][i].temperature + temperature_[k][j + 1][i].temperature +
                                 temperature_[k][j][i - 1].temperature + temperature_[k][j][i + 1].temperature -
                                 (6.0 + temperature_[k][j][i].conductivity * dt / temperature_[k][j][i].depth) *
                                 temperature_[k][j][i].temperature);

                        temperature_[k][j][i].temperature += alpha;
                    }
                }
            }

            t += dt;
        }
    }

private:
    int numLayersX_;
    int numLayersY_;
    int numLayersZ_;
    std::vector<std::vector<std::vector<Layer>>> temperature_;
};


#endif
