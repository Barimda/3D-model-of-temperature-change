#ifndef UNTITLED_STENA_H
#define UNTITLED_STENA_H

#include <iostream>
#include "progonka.h"

class stena {
    progonka prog;

    int dots_count = 100;
    double tolshina = 1;
    double temperature_left = 0;
    double temperature_right = 0;

public:
    stena(int dots_count, double tolshina) {
        stena(dots_count, tolshina, 0, 0);
    }

public:
    stena(int dots_count, double tolshina, double temperature_left, double temperature_right) {
        this->dots_count = dots_count;
        this->tolshina = tolshina;
        this->temperature_left = temperature_left;
        this->temperature_right = temperature_right;
    }

public:
    double getTemperatureLeft() {
        return temperature_left;
    }

public:
    double getTemperatureRight() {
        return temperature_right;
    }

public:
    void setTemperatureLeft(double temperature) {
        temperature_left = temperature;
    }

public:
    void setTemperatureRight(double temperature) {
        temperature_right = temperature;
    }

public:
    void
    calculateDots() {
        int n = dots_count; //количество точек
        double L = tolshina; //длина отрезка стена + утеплитель в метрах

        double h = L / n; //щаг по отрезку L
        double r[n + 1];
        double a[n + 1];
        double b[n + 1];
        double c[n + 1];
        double f[n + 1];
        double y[n + 1];

        int i;
        double lambda[i + 1];

        std::cout << "\n======= DOTS =======\n";
        for (int i = 0; i <= n; ++i) {
            r[i] = h * i;
            f[i] = 0;

            if (r[i] <= 0.5)
                lambda[i] = 1E-2;
            else
                lambda[i] = 1E-4;
            std::cout << r[i] << "\n";
        }
        std::cout << "\n======= DOTS END =======\n";
        std::cout << "\n======= DOTS TEMPERATURE =======\n";
        //граничные точки
        double mu1 = temperature_left; // граница слева
        double kappa1 = 0;
        double mu2 = temperature_right; //граница справа
        double kappa2 = 0;

        prog.solveEqProgonka(n, h, r, a, b, c, f, mu1, kappa1, mu2, kappa2, y, lambda);

        for (int i = 0; i <= n; ++i) {
            std::cout << y[i] << "\n";
        }
        std::cout << "\n======= DOTS TEMPERATURE END =======\n";
    }

//todo доавить формулы для расчета со временем
public:
    void
    calculateDotsWithTime(double timeEnd) {
        int n = dots_count; //количество точек
        double L = tolshina; //длина отрезка стена + утеплитель в метрах

        double h = L / n; //щаг по отрезку L
        double tau = h / 100; //шаг во времени

        double r[n + 1];
        double a[n + 1];
        double b[n + 1];
        double c[n + 1];
        double f[n + 1];
        double y[n + 1];
        double y_old[n + 1];

        int i;
        double lambda[i + 1];

        std::cout << "\n======= DOTS =======\n";
        for (int i = 0; i <= n; ++i) {
            r[i] = h * i;
            f[i] = 0;
            y_old[i] = -(600 / 7) * r[i] + 30;

            if (r[i] <=
                0.5) //здесь указано процентное соотношение стены и утеплителя (утеплитель указан в правой части)
                lambda[i] = 0.76;//1E-2; Теплопроодность стены
            else
                lambda[i] = 0.04; //теплопроводность стены
            std::cout << r[i] << "\n";
        }
        std::cout << "\n======= DOTS END =======\n";
        std::cout << "\n======= DOTS TEMPERATURE =======\n";
        //граничные точки
        double mu1 = temperature_left; // граница слева
        double kappa1 = 0;
        double mu2 = temperature_right; //граница справа
        double kappa2 = 0;

        for (int j = 0; j <= (int)(timeEnd / tau); ++j) {
            prog.solveEqProgonka(n, h, r, a, b, c, f, mu1, kappa1, mu2, kappa2, y, lambda, tau, y_old);
            for (int i = 0; i <= n; ++i) {
                y_old[i] = y[i];
            }
        }


        for (int i = 0; i <= n; ++i) {
            std::cout << y[i] << "\n";
        }
        std::cout << "\n======= DOTS TEMPERATURE END =======\n";
    };
};


#endif
