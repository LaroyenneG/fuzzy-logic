#include <utility>

#include "PhysicObject2D.h"
#include "Draftsman.h"

namespace model {

    PhysicObject2D::PhysicObject2D(std::vector<Point> _points,
                                   double _xPosition, double _yPosition, double _xSpeed, double _ySpeed,
                                   double _xAcceleration, double _yAcceleration,
                                   double _orientation, double _rotationSpeed, double _rotationAcceleration,
                                   double _weight)
            : points(std::move(_points)), position{{_xPosition, _yPosition}}, speed{{_xSpeed, _ySpeed}},
              acceleration{{_xAcceleration, _yAcceleration}}, orientation(_orientation), rotationSpeed(_rotationSpeed),
              rotationAcceleration(_rotationAcceleration), weight(_weight) {
    }

    PhysicObject2D::PhysicObject2D(const std::vector<Point> &_points,
                                   double _xPosition,
                                   double _yPosition, double _orientation, double _weight) :
            PhysicObject2D(_points, _xPosition, _yPosition, DEFAULT_SPEED_X, DEFAULT_SPEED_Y, DEFAULT_ACCELERATION_X,
                           DEFAULT_ACCELERATION_Y, _orientation, DEFAULT_ROTATION_SPEED, DEFAULT_ROTATION_ACCELERATION,
                           _weight) {
    }


    double PhysicObject2D::getPositionX() const {
        return position[X_DIM_VALUE];
    }

    double PhysicObject2D::getPositionY() const {
        return position[Y_DIM_VALUE];
    }

    void PhysicObject2D::setPositionX(double value) {
        position[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setPositionY(double value) {
        position[Y_DIM_VALUE] = value;
    }

    void PhysicObject2D::setSpeedX(double value) {
        speed[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setSpeedY(double value) {
        speed[Y_DIM_VALUE] = value;
    }

    double PhysicObject2D::getSpeedX() const {
        return speed[X_DIM_VALUE];
    }

    double PhysicObject2D::getSpeedY() const {
        return speed[Y_DIM_VALUE];
    }

    double PhysicObject2D::getAccelerationX() const {
        return acceleration[X_DIM_VALUE];
    }

    double PhysicObject2D::getAccelerationY() const {
        return acceleration[Y_DIM_VALUE];
    }

    void PhysicObject2D::setAccelerationX(double value) {
        acceleration[X_DIM_VALUE] = value;
    }

    void PhysicObject2D::setAccelerationY(double value) {
        acceleration[Y_DIM_VALUE] = value;
    }

    void PhysicObject2D::drawMe(view::Draftsman *draftsman) {
        draftsman->drawElement(this);
    }

    double PhysicObject2D::distance(const PhysicObject2D &object) const {

        std::vector<Point> myPoints;
        writeAbsolutePoints(myPoints);

        std::vector<Point> objectPoints;
        object.writeAbsolutePoints(objectPoints);

        bool init = false;
        double best = 0.0;

        for (auto myPoint : myPoints) {

            for (auto objectPoint : objectPoints) {

                double distance = distanceBetweenPoint(myPoint, objectPoint);

                if (!init || best > distance) {
                    best = distance;
                    init = true;
                }
            }
        }

        return best;
    }

    bool PhysicObject2D::touch(const PhysicObject2D &object) const {

        std::vector<Point> shape1;
        writeAbsolutePoints(shape1);

        std::vector<Point> shape2;
        object.writeAbsolutePoints(shape2);


        for (unsigned int i = 0; !shape1.empty() && i < shape1.size() - 1; ++i) {

            Line line1 = constructLine(shape1[i], shape1[i + 1]);

            for (unsigned int j = 0; !shape2.empty() && j < shape2.size() - 1; ++j) {

                Line line2 = constructLine(shape2[j], shape2[j + 1]);

                bool status = false; // if true then intersection in segments

                findLineIntersection(line1, line2, &status);

                if (status) {
                    return true;
                }
            }
        }

        return false;
    }

    Vector PhysicObject2D::computeCentrifugalForce() const {

        static const double NEGLIGIBLE = pow(10, -4);

        Vector strength{{0.0, 0.0}};

        if (positions.size() == POINT_QUEUE_SIZE) {

            Point nPosition[POINT_QUEUE_SIZE];

            int index = 0;
            for (auto it = positions.begin(); it != positions.end(); it++, index++) {
                nPosition[index] = *it;
            }

            Vector dv1{{nPosition[1][X_DIM_VALUE] - nPosition[0][X_DIM_VALUE],
                               nPosition[1][Y_DIM_VALUE] - nPosition[0][Y_DIM_VALUE]}};
            Vector dv2{{nPosition[2][X_DIM_VALUE] - nPosition[0][X_DIM_VALUE],
                               nPosition[2][Y_DIM_VALUE] - nPosition[0][Y_DIM_VALUE]}};

            double angleAlign = angleBetweenVector(dv1, dv2);

            if (angleAlign >= NEGLIGIBLE) {

                Point circleCenter = circleSolver(nPosition[0], nPosition[1], nPosition[2]);

                double rayon = distanceBetweenPoint(circleCenter, nPosition[0]);

                Vector direction = vectorBetweenPoints(circleCenter, nPosition[0]);

                double directionNorm = normVector(direction);

                direction[X_DIM_VALUE] /= directionNorm;
                direction[Y_DIM_VALUE] /= directionNorm;

                double value = weight * getSpeed() / rayon;

                strength = {value * direction[X_DIM_VALUE], value * direction[Y_DIM_VALUE]};
            }
        }

        return strength;
    }

    void PhysicObject2D::writeAbsolutePoints(std::vector<Point> &wPoints) const {

        for (auto &point : getPoints()) {

            wPoints.push_back(pointTranslation(pointRotation(point, orientation), position));
        }
    }

    const std::vector<Point> &PhysicObject2D::getPoints() const {

        return points;
    }

    void PhysicObject2D::setOrientation(double value) {

        orientation = value;
    }

    double PhysicObject2D::getOrientation() const {

        return orientation;
    }

    double PhysicObject2D::getSpeed() const {

        return normVector(speed);
    }


    double PhysicObject2D::getRotationSpeed() const {

        return rotationSpeed;
    }

    double PhysicObject2D::getRotationAcceleration() const {

        return rotationAcceleration;
    }

    void PhysicObject2D::setRotationSpeed(double value) {

        rotationSpeed = value;
    }

    void PhysicObject2D::setRotationAcceleration(double value) {

        rotationAcceleration = value;
    }

    double PhysicObject2D::getWeight() const {

        return weight;
    }

    void PhysicObject2D::setWeight(double value) {

        weight = value;
    }

    void PhysicObject2D::nextTime(double time) {

        nextRotationSpeed(time);
        nextOrientation(time);

        nextSpeed(time);
        nextPosition(time);
    }

    void PhysicObject2D::nextSpeed(double time) {

        speed[X_DIM_VALUE] += acceleration[X_DIM_VALUE] * time;
        speed[Y_DIM_VALUE] += acceleration[Y_DIM_VALUE] * time;
    }

    void PhysicObject2D::nextRotationSpeed(double time) {

        rotationSpeed += rotationAcceleration * time;
    }

    void PhysicObject2D::nextOrientation(double time) {

        static const unsigned int ROUND_NUMBER = 1000;

        orientation += rotationSpeed * time;

        orientation = (static_cast<int>(std::round(orientation * ROUND_NUMBER)) %
                       static_cast<int>(std::round(M_PI * 2.0) * ROUND_NUMBER)) * 1.0 / ROUND_NUMBER;
    }

    void PhysicObject2D::nextPosition(double time) {

        position[X_DIM_VALUE] += speed[X_DIM_VALUE] * time;
        position[Y_DIM_VALUE] += speed[Y_DIM_VALUE] * time;

        if (positions.size() >= POINT_QUEUE_SIZE) {
            positions.pop_front();
        }

        positions.push_back(position);
    }

    double PhysicObject2D::angleBetweenVector(const Vector &vector1, const Vector &vector2) {

        const double denominator = normVector(vector1) * normVector(vector2);

        const double numerator =
                vector1[X_DIM_VALUE] * vector2[X_DIM_VALUE] + vector1[Y_DIM_VALUE] * vector2[Y_DIM_VALUE];

        double relation = (denominator != 0.0) ? numerator / denominator : M_PI / 2.0;

        if (relation >= 1.0) {
            relation = 1.0;
        }
        if (relation <= -1.0) {
            relation = -1.0;
        }

        return acos(relation);
    }

    double PhysicObject2D::normVector(const Vector &vector) {

        return sqrt(vector[X_DIM_VALUE] * vector[X_DIM_VALUE] + vector[Y_DIM_VALUE] * vector[Y_DIM_VALUE]);
    }

    Point PhysicObject2D::pointRotation(const Point &point, double angle) {

        Point nPoint;

        nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] * cos(angle) - point[Y_DIM_VALUE] * sin(angle);
        nPoint[Y_DIM_VALUE] = point[X_DIM_VALUE] * sin(angle) + point[Y_DIM_VALUE] * cos(angle);

        return nPoint;
    }

    Point PhysicObject2D::pointTranslation(const Point &point, const Vector &translation) {

        Point nPoint;

        nPoint[X_DIM_VALUE] = point[X_DIM_VALUE] + translation[X_DIM_VALUE];
        nPoint[Y_DIM_VALUE] = point[Y_DIM_VALUE] + translation[Y_DIM_VALUE];

        return nPoint;
    }

    Vector PhysicObject2D::directionVector() const {

        return Vector{{cos(orientation), sin(orientation)}};
    }

    Vector PhysicObject2D::inverseVector(const Vector &vector) {

        return Vector{{-vector[X_DIM_VALUE], -vector[Y_DIM_VALUE]}};
    }

    std::vector<Point> PhysicObject2D::loadShapePoints(const std::string &filePath) {

        static const double POINT_MAX_VALUE = INFINITY;

        std::vector<Point> points;

        std::ifstream ifstream(filePath);

        while (ifstream) {

            double x = INFINITY;
            double y = INFINITY;

            ifstream >> x;
            ifstream >> y;

            if (x != POINT_MAX_VALUE && y != POINT_MAX_VALUE) {
                points.push_back(Point{{x, y}});
            }
        }

        ifstream.close();

        return points;
    }

    double PhysicObject2D::distanceBetweenPoint(const Point &point1, const Point &point2) {

        double somme = 0.0;

        for (unsigned int i = 0; i < MODEL_SPACE_DIMENSION; ++i) {
            somme += (point1[i] - point2[i]) * (point1[i] - point2[i]);
        }

        return std::sqrt(somme);
    }

    Point PhysicObject2D::circleSolver(const Point &p1, const Point &p2, const Point &p3) {

        const double meaning = (p3[Y_DIM_VALUE] - p2[Y_DIM_VALUE] < 0) ? -1.0 : 1.0;

        const double rotationAngle =
                angleBetweenVector(vectorBetweenPoints(p1, p2), vectorBetweenPoints(p2, p3)) * meaning;

        const Vector referenceVector = vectorBetweenPoints(p2, p3);

        Point lastCursor = p2;
        Point newCursor = p3;

        do {
            Vector transform = pointRotation(vectorBetweenPoints(lastCursor, newCursor), rotationAngle);

            lastCursor = newCursor;

            newCursor[X_DIM_VALUE] += transform[X_DIM_VALUE];
            newCursor[Y_DIM_VALUE] += transform[Y_DIM_VALUE];

        } while (angleBetweenVector(referenceVector, vectorBetweenPoints(p3, newCursor)) < M_PI / 2.0);


        return Point{{(p3[X_DIM_VALUE] - newCursor[X_DIM_VALUE]) / 2.0 + newCursor[X_DIM_VALUE],
                             (p3[Y_DIM_VALUE] - newCursor[Y_DIM_VALUE]) / 2.0 + newCursor[Y_DIM_VALUE]}};
    }

    Vector PhysicObject2D::vectorBetweenPoints(const Point &point1, const Point &point2) {

        return Vector{{point2[X_DIM_VALUE] - point1[X_DIM_VALUE], point2[Y_DIM_VALUE] - point1[Y_DIM_VALUE]}};
    }


    double PhysicObject2D::estimateOrdinateValue(double abscissa, const std::map<double, double> &points) {

        std::list<std::pair<double, double>> sortedPoints;

        for (auto &point : points) {
            sortedPoints.push_front(point);
        }

        sortedPoints.sort([](const std::pair<double, double> &p1, const std::pair<double, double> &p2) {
            return p1.first < p2.first;
        });

        double value = 0.0;

        if (sortedPoints.size() >= 2) {

            std::pair<double, double> leftPoint(0.0, 0.0);

            bool initLeft = false;

            for (auto it = sortedPoints.begin(); it != sortedPoints.end(); it++) {

                std::pair<double, double> point = *it;

                if (!initLeft) {
                    leftPoint = point;
                    initLeft = true;
                }

                if (leftPoint.first < point.first && point.first <= abscissa) {
                    leftPoint = point;
                }
            }


            std::pair<double, double> rightPoint(0.0, 0.0);

            bool initRight = false;

            for (auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); it++) {

                std::pair<double, double> point = *it;

                if (!initRight) {
                    rightPoint = point;
                    initRight = true;
                }

                if (rightPoint.first > point.first && point.first >= abscissa) {
                    rightPoint = point;
                }
            }


            if (initRight && initLeft && leftPoint.first != rightPoint.first) {

                double a = (rightPoint.second - leftPoint.second) / (rightPoint.first - leftPoint.first);

                double b = leftPoint.second - a * leftPoint.first;

                value = a * abscissa + b;
            }
        }

        return value;
    }

    std::map<double, double> PhysicObject2D::loadCoefficients(const std::string &filePath) {

        static const double MAX_INCIDENCE_VALUE = 3.5;

        std::map<double, double> coefficients;

        std::ifstream ifstream(filePath);

        while (ifstream) {

            double x = MAX_INCIDENCE_VALUE;
            double y = MAX_INCIDENCE_VALUE;

            ifstream >> x;
            ifstream >> y;

            if (x != MAX_INCIDENCE_VALUE && y != MAX_INCIDENCE_VALUE) {
                coefficients[x] = y;
            }
        }

        ifstream.close();

        return coefficients;
    }

    Point PhysicObject2D::findLineIntersection(const Line &line1, const Line &line2, bool *status) {

        *status = false;

        Point solution;

        const Point &firstPointLine1 = line1.first;
        const Point &secondPointLine1 = line1.second;

        Vector vectorLine1 = vectorBetweenPoints(firstPointLine1, secondPointLine1);

        const Point &firstPointLine2 = line2.first;
        const Point &secondPointLine2 = line2.second;

        Vector vectorLine2 = vectorBetweenPoints(firstPointLine2, secondPointLine2);

        if (vectorLine1[X_DIM_VALUE] * vectorLine2[Y_DIM_VALUE] !=
            vectorLine1[Y_DIM_VALUE] * vectorLine2[X_DIM_VALUE]) {

            // equation : y = ax + b

            const double a1 = vectorLine1[Y_DIM_VALUE] / vectorLine1[X_DIM_VALUE];

            const double b1 = firstPointLine1[Y_DIM_VALUE] - a1 * firstPointLine1[X_DIM_VALUE];


            const double a2 = vectorLine2[Y_DIM_VALUE] / vectorLine2[X_DIM_VALUE];

            const double b2 = firstPointLine2[Y_DIM_VALUE] - a2 * firstPointLine2[X_DIM_VALUE];


            const double x = (b2 - b1) / (a1 - a2);

            if (MIN_VALUE(firstPointLine1[X_DIM_VALUE], secondPointLine1[X_DIM_VALUE]) < x &&
                MAX_VALUE(firstPointLine1[X_DIM_VALUE], secondPointLine1[X_DIM_VALUE]) > x &&
                MIN_VALUE(firstPointLine2[X_DIM_VALUE], secondPointLine2[X_DIM_VALUE]) < x &&
                MAX_VALUE(firstPointLine2[X_DIM_VALUE], secondPointLine2[X_DIM_VALUE]) > x) {

                *status = true;

                solution = {x, a1 * x + b1};
            }
        }

        return solution;
    }

    Line PhysicObject2D::constructLine(const Point &point1, const Point &point2) {

        Line line;

        line.first = point1;
        line.second = point2;

        return line;
    }

    double PhysicObject2D::lineLength(const Line &line) {
        return distanceBetweenPoint(line.first, line.second);
    }
}