#include <math.h>
#include <stdio.h>
#define PI 3.142857

//convert to radians
long double degreesToRadians(long double degrees) {
    return degrees * PI / 180;
}
//
double getDistance(long double lat1, long double  lon1, long double lat2, long double lon2) {
    int earthRadiusKm = 6371; //radius of the earth in km
    // convert all parameters
    lat1 = degreesToRadians(lat1);
    lat2 = degreesToRadians(lat2);
    lon2 = degreesToRadians(lon2);
    lon1 = degreesToRadians(lon1);
    long double lat = lat2 - lat1;
    long double lon = lon2 - lon1;
    // we will use Haversine formula :
     // a = sin²(Δφ / 2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ / 2)
     //c = 2 ⋅ atan2(√a, √(1−a))
     //d = R ⋅ c
    long double  a = sin(lat / 2) * sin(lat / 2) +
        pow(sin(lon / 2), 2) * cos(lat1) * cos(lat2);
    long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRadiusKm * c * 1000;    //convert here from km to m
}