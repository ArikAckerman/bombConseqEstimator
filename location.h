#ifndef LOCATION_H
#define LOCATION_H

class Location {
public:
    Location(double latitude = 0.0, double longitude = 0.0);

    double latitude() const;
    void setLatitude(double latitude);

    double longitude() const;
    void setLongitude(double longitude);

private:
    double m_latitude;
    double m_longitude;
};

#endif // LOCATION_H
