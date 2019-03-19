

#include "Rudder.h"

namespace model {

    Rudder::Rudder()
            : Rudder(RUDDER_DEFAULT_VALUE, RUDDER_DEFAULT_W_SPEED_X, RUDDER_DEFAULT_W_SPEED_Y, RUDDER_DEFAULT_SIZE) {

    }

    Rudder::Rudder(double _value, double _xWaterSpeed, double _yWaterSpeed, double _size)
            : value(_value), waterSpeed{_xWaterSpeed, _yWaterSpeed}, size(_size) {

    }

    void Rudder::setValue(double _value) {
        value = _value;
    }

    double Rudder::getValue() const {
        return value;
    }

    void Rudder::setWaterSpeedX(double xValue) {
        waterSpeed[0] = xValue;
    }

    void Rudder::setWaterSpeedY(double yValue) {
        waterSpeed[1] = yValue;
    }

    std::array<double, SPACE_DIMENSION> Rudder::getVectorStrength() const {
        return std::array<double, SPACE_DIMENSION>();
    }
}