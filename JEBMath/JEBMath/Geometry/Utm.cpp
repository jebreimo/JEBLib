#include <cmath>

namespace JEBMath {

template <size_t N>
static void ComputePowers(double (&arr)[N])
{
    for (size_t i = 1; i < N; i++)
        arr[i] = arr[i - 1] * arr[0];
}

void UtmToGeo(double& lat, double& lon, double northing, double easting, int utmZone)
{
    const double PI = 3.14159265358979323846264338328;
    const double f =  1 / 298.257222101;
    const double k0 = 0.9996;
    const double a  = 6378137;
    const double eccSquared = 2.0 * f - f * f;
    const double eccPrimeSquared = eccSquared / (1 - eccSquared);
    double e[4] = {(1. - std::sqrt(1. - eccSquared)) / (1.0 + std::sqrt(1.0 - eccSquared))};
    ComputePowers(e);

    double M = northing / k0;
    double mu = M / (a * (1 - eccSquared * (1 + eccSquared * (3 + 5 * eccSquared / 4) / 16) / 4));
    double phi1Rad = mu + (  3 * e[0] /  2 - 27 * e[2] / 32) * std::sin(2 * mu)
                        + ( 21 * e[1] / 16 - 55 * e[3] / 32) * std::sin(4 * mu)
                        + (151 * e[2] / 96)                  * std::sin(6 * mu);

    double N1 = a / std::sqrt(1 - eccSquared * std::sin(phi1Rad) * std::sin(phi1Rad));
    double R1 = a * (1 - eccSquared) / std::pow(1 - eccSquared * std::sin(phi1Rad) * std::sin(phi1Rad), 1.5);

    double T[2] = {std::tan(phi1Rad) * std::tan(phi1Rad)};
    ComputePowers(T);

    double C[2] = {eccPrimeSquared * std::cos(phi1Rad) * std::cos(phi1Rad)};
    ComputePowers(C);

    const double FalseEast = 500000; // remove 500,000 meter offset for longitude
    double D[6] = {(easting - FalseEast) / (N1 * k0)};
    ComputePowers(D);

    double Lat = phi1Rad - (N1 * std::tan(phi1Rad) / R1) * (
                  D[1] / 2.0 -
                  ( 5 +  3 * T[0] +  10 * C[0] -  4 * C[1] -   9 * eccPrimeSquared)            * D[3] /  24 +
                  (61 + 90 * T[0] + 298 * C[0] + 45 * T[1] - 252 * eccPrimeSquared - 3 * C[1]) * D[5] / 720);
    double LonOrigin = (6 * utmZone - 3 - 180) * PI / 180;  // -3 puts origin in middle of zone
    double Lon = LonOrigin +
                 (D[0] -
                  (1 +  2 * T[0] +     C[0])                                              * D[2] /   6 +
                  (5 + 28 * T[0] - 2 * C[0] - 3 * C[1] + 8 * eccPrimeSquared + 24 * T[1]) * D[4] / 120
                 ) / std::cos(phi1Rad);

    lon = (Lon * 180) / PI;
    lat = (Lat * 180) / PI;
}

}
