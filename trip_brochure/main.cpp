#define cimg_display 0
#define cimg_use_png
#include "CImg.h"
#include "TripPlanner.h"
#include <algorithm>

using namespace cimg_library;

std::string trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t");
    if (std::string::npos == first) return s;
    size_t last = s.find_last_not_of(" \t");
    return s.substr(first, (last - first + 1));
}

int main() {
    std::vector<Destination> cities;
    std::vector<Train> trains;

    std::ifstream destFile("destinations.txt");
    std::string line;
    while (std::getline(destFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Destination d;
        std::string sLat, sLon, sep;
        std::getline(ss, d.name, '/');
        d.name = trim(d.name);
        std::getline(ss, sLat, '/');
        ss >> d.lon;
        d.lat = std::stod(sLat);
        cities.push_back(d);
    }

    std::ifstream trainFile("trains.txt");
    while (std::getline(trainFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Train t;
        std::getline(ss, t.from, '/'); t.from = trim(t.from);
        std::getline(ss, t.to, '/');   t.to = trim(t.to);
        std::getline(ss, t.departure, '/'); t.departure = trim(t.departure);
        std::getline(ss, t.duration, '/');  t.duration = trim(t.duration);
        ss >> t.price;
        trains.push_back(t);
    }

    std::string startCity, endCity;
    std::cout << "--- UKRZALIZNYTSIA TRIP PLANNER ---" << std::endl;
    std::cout << "Available: Kyiv, Lviv, Odesa, Kharkiv, Dnipro" << std::endl;
    std::cout << "From: "; std::cin >> startCity;
    std::cout << "To: ";   std::cin >> endCity;

    Destination *s = nullptr, *e = nullptr;
    for (auto &c : cities) {
        if (c.name == startCity) s = &c;
        if (c.name == endCity) e = &c;
    }

    if (!s || !e) {
        std::cout << "Error: City not found in database." << std::endl;
        return 1;
    }

    double dist = calculateDistance(s->lat, s->lon, e->lat, e->lon);
    
    CImg<unsigned char> img("map.png");
    unsigned char purple[] = { 147, 0, 211 }, black[] = { 0, 0, 0 }, white[] = { 255, 255, 255 };

    Point p1 = geoToPixel(s->lat, s->lon, img.width(), img.height());
    Point p2 = geoToPixel(e->lat, e->lon, img.width(), img.height());

    img.draw_line(p1.x, p1.y, p2.x, p2.y, purple, 1.0f, 0xFFFFFFFF);
    img.draw_circle(p1.x, p1.y, 7, purple);
    img.draw_circle(p2.x, p2.y, 7, purple);
    
    img.draw_text(p1.x + 10, p1.y - 20, s->name.c_str(), black, 0, 1, 24);
    img.draw_text(p2.x + 10, p2.y - 20, e->name.c_str(), black, 0, 1, 24);

    img.draw_rectangle(0, img.height() - 150, img.width(), img.height(), black, 0.8f);
    
    std::string header = "TRIP INFO: " + s->name + " -> " + e->name + " (" + std::to_string((int)dist) + " km)";
    img.draw_text(30, img.height() - 130, header.c_str(), white, 0, 1, 32);

    int yOffset = 80;
    bool foundTrain = false;
    for (auto &t : trains) {
        if (t.from == s->name && t.to == e->name) {
            std::string tInfo = "Train | Dep: " + t.departure + " | Dur: " + t.duration + " | Price: " + std::to_string((int)t.price) + " UAH";
            std::cout << tInfo << std::endl;
            img.draw_text(30, img.height() - yOffset, tInfo.c_str(), white, 0, 1, 20);
            yOffset -= 25;
            foundTrain = true;
        }
    }

    if (!foundTrain) {
        img.draw_text(30, img.height() - 70, "No direct trains found in database.", white, 0, 1, 20);
    }

    img.save_png("result.png");
    std::cout << "\nSUCCESS! Distance: " << dist << " km. Brochure saved to result.png" << std::endl;

    return 0;
}