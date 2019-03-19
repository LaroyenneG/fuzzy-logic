
#include "Titanic.h"
#include "AlternativeMachine.h"
#include "LowPressureTurbine.h"

namespace model {

    const std::set<std::pair<double, double >> Titanic::DEFAULT_POINTS{{0.0,   0.0},
                                                                       {-14.0, 30},
                                                                       {14.0,  30.0},
                                                                       {-14,   218.0},
                                                                       {14.0,  218.0},
                                                                       {0.0,   269.0}};

    Titanic::Titanic(const std::set<std::pair<double, double >> &points, double _course, double _rudder, double _weight)
            : Object2D(points, _weight),
              course(_course),
              rudder(), engines{{new AlternativeMachine(), new AlternativeMachine(), new LowPressureTurbine()}} {
    }

    Titanic::Titanic()
            : Titanic(DEFAULT_POINTS, DEFAULT_COURSE, DEFAULT_RUDDER, TITANIC_DEFAULT_WEIGHT) {

    }

    Titanic::~Titanic() {

        for (auto engine : engines) {
            delete engine;
        }
    }
}