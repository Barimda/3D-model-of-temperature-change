#ifndef UNTITLED_PROGONKA_H
#define UNTITLED_PROGONKA_H

#include <iostream>

class progonka {
    void solveMatrix(int n, double *a, double *b, double *c, double *f,
                     double mu1, double kappa1, double mu2, double kappa2, double *y) {
        double alpha[n + 1];
        double betta[n + 1];

        alpha[n] = kappa2;
        betta[n] = mu2;
        for (int i = n - 1; i >= 1; i--) {
            alpha[i] = a[i] / (c[i] - alpha[i + 1] * b[i]);
            betta[i] = (b[i] * betta[i + 1] + f[i]) / (c[i] - alpha[i + 1] * b[i]);
        }
        y[0] = (mu1 + kappa1 * betta[1]) / (1 - alpha[1] * kappa1);
        for (int i = 0; i <= n - 1; i++)
            y[i + 1] = alpha[i + 1] * y[i] + betta[i + 1];
    };

public:
    void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f,
                         double mu1, double kappa1, double mu2, double kappa2, double *y) {
        for (int i = 1; i <= n - 1; i++) {
            a[i] = 1;
            b[i] = 1;
            c[i] = 2;
        };
        solveMatrix(n, a, b, c, f, mu1, kappa1, mu2, kappa2, y);
    }
//stena
public:
    void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f,
                         double mu1, double kappa1, double mu2, double kappa2, double *y, double *lambda) {
        for (int i = 1; i <= n - 1; i++) {
            a[i] = (lambda[i] + lambda[i - 1]) / 2;
            b[i] = (lambda[i] + lambda[i + 1]) / 2;
            c[i] = a[i] + b[i];
        };
        solveMatrix(n, a, b, c, f, mu1, kappa1, mu2, kappa2, y);
    };
//with time
public:
    void solveEqProgonka(int n, double h, double *r, double *a, double *b, double *c, double *f,
                         double mu1, double kappa1, double mu2, double kappa2, double *y, double *lambda,
                         double tau, double *y_old) {
        for (int i = 1; i <= n - 1; i++) {
            a[i] = -(lambda[i] + lambda[i - 1]) / (2 * h * h);
            b[i] = -(lambda[i] + lambda[i + 1]) / (2 * h * h);
            c[i] = a[i] + b[i] - 1 / tau;
            f[i] = -y_old[i] / tau;
        };
        solveMatrix(n, a, b, c, f, mu1, kappa1, mu2, kappa2, y);
    };

public:
    void showTemplate() {
        int n = 100;
        double L = 3.14 / 2;

        double h = L / n;
        double r[n + 1];
        double a[n + 1];
        double b[n + 1];
        double c[n + 1];
        double f[n + 1];
        double y[n + 1];

        std::cout << "======= TEMPLATE SIN =======\n Dots count: " << n << "\n L = 3.14 / 2 \n Shag: " << h
                  << "\n r[i] = h * i\n f[i] = h * h * sin(h * i)\n mu1 = 0\n kappa1 = 0\n mu2 = 1\n kappa2 = 0\n======= TEMPLATE SIN PARAMS END =======\n";

        for (int i = 0; i <= n; ++i) {
            r[i] = h * i;
            f[i] = h * h * sin(h * i);
        }

        double mu1 = 0;
        double kappa1 = 0;
        double mu2 = 1;
        double kappa2 = 0;

        solveEqProgonka(n, h, r, a, b, c, f, mu1, kappa1, mu2, kappa2, y);
        std::cout << "\n======= DOTS =======\n";
        for (int i = 0; i <= n; ++i) {
            std::cout << y[i] << "\n";
        }
        std::cout << "\n======= DOTS END =======\n";
        std::cout << "\n======= DOTS TEMPERATURE =======\n";
        for (int i = 0; i <= n; ++i) {
            std::cout << f[i] << "\n";
        }
        std::cout << "\n======= DOTS TEMPERATURE END =======\n";
        std::cout << "\n======= TEMPLATE SIN END =======\n";
    }
};


#endif