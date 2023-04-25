#include "Location.h"

Location::Location(double latitude, double longitude)
    : m_latitude(latitude), m_longitude(longitude)
{
}

double Location::latitude() const
{
    return m_latitude;
}

void Location::setLatitude(double latitude)
{
    m_latitude = latitude;
}

double Location::longitude() const
{
    return m_longitude;
}

void Location::setLongitude(double longitude)
{
    m_longitude = longitude;
}
