#ifndef TRIP_PLANNER_H
#define TRIP_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

const double EARTH_RADIUS = 6371.0;

struct Destination {
    std::string name;
    double lat, lon;
};

struct Train {
    std::string from, to;
    std::string departure;
    std::string duration;
    double price;
};

inline double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_RADIUS * c;
}

struct Point { int x, y; };

inline Point geoToPixel(double lat, double lon, int imgW, int imgH) {

    const double latMax = 52.37, latMin = 44.38;
    const double lonMin = 22.13, lonMax = 40.22;

    int x = (int)((lon - lonMin) * (imgW / (lonMax - lonMin)));
    int y = (int)((latMax - lat) * (imgH / (latMax - latMin)));
    return {x, y};
}

#endif