
#include <stdexcept>
#include "Engine.h"

namespace model {

    Engine::Engine(double _rotationSpeed, double _power, double _friction,
                   double _propellerDiameter, double _propellerWeight, double _maxPower)
            : rotationSpeed(_rotationSpeed), power(_power), friction(_friction),
              propellerDiameter(_propellerDiameter), propellerWeight(_propellerWeight), maxPower(_maxPower) {

    }

    Engine::Engine(double _propellerDiameter, double _propellerWeight, double _maxPower)
            : Engine(ENGINE_DEFAULT_ROTATION, ENGINE_DEFAULT_POWER, ENGINE_DEFAULT_FRICTION, _propellerDiameter,
                     _propellerWeight,
                     _maxPower) {

    }

    double Engine::getRotationSpeed() const {
        return rotationSpeed;
    }

    double Engine::getPropulsionStrength() const {
        return 0;
    }

    double Engine::getPower() const {
        return power;
    }

    void Engine::setPower(double value) {

        if (value < -1.0 || value > 1.0) {
            throw std::out_of_range(ENGINE_VALUE_ERROR_MSG);
        }

        power = value;
    }
}
