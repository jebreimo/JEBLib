#include "FresnelIntegrals.hpp"

namespace JEBMath {

double fresnelC(double t, size_t order)
{
    double sign = 1;
    double factorial = 1;
    int n = 1;
    double power = 1;
    double sum = t;
    for (size_t i = 1; i < order; i++)
    {
        sign = -sign;
        factorial *= n++;
        factorial *= n++;
        power += 4;
        sum += sign * std::pow(t, power) / (factorial * power);
    }
    return sum;
}

double fresnelS(double t, size_t order)
{
    double sign = 1;
    double factorial = 1;
    int n = 2;
    double power = 3;
    double sum = std::pow(t, power) / power;
    for (size_t i = 1; i < order; i++)
    {
        sign = -sign;
        factorial *= n++;
        factorial *= n++;
        power += 4;
        sum += sign * std::pow(t, power) / (factorial * power);
    }
    return sum;
}

std::pair<double, double> fresnelCS(double t, size_t order)
{
    double sign = 1;
    double factorialS = 1;
    int n = 2;
    double powerS = 3;
    double x = t, y = std::pow(t, powerS) / powerS;
    double tSquared = t * t;
    for (size_t i = 1; i < order; i++)
    {
        sign = -sign;

        double factorialC = factorialS *= n++;;
        double powerC = powerS + 2;
        double numeratorC = std::pow(t, powerC);
        x += sign * numeratorC / (factorialC * powerC);

        factorialS *= n++;
        powerS += 4;
        double numeratorS = numeratorC * tSquared;
        y += sign * numeratorS / (factorialS * powerS);
    }
    return std::pair<double, double>(x, y);
}

}
