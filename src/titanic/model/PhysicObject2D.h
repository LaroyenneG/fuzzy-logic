#ifndef LOGIQUEFLOUE_OBJECT2D_H
#define LOGIQUEFLOUE_OBJECT2D_H

#include <set>
#include <vector>
#include <array>
#include <cmath>
#include <list>
#include <iostream>
#include <map>
#include <fstream>

#include "BlackBox.h"

#define DEFAULT_POSITION_X 0.0
#define DEFAULT_POSITION_Y 0.0

#define DEFAULT_SPEED_X 0.0
#define DEFAULT_SPEED_Y 0.0

#define DEFAULT_ORIENTATION 0.0

#define DEFAULT_ACCELERATION_X 0.0
#define DEFAULT_ACCELERATION_Y 0.0

#define DEFAULT_ROTATION_SPEED 0.0
#define DEFAULT_ROTATION_ACCELERATION 0.0

#define MODEL_SPACE_DIMENSION 2
#define X_DIM_VALUE 0
#define Y_DIM_VALUE 1


#define MIN_VALUE(a, b) ((a<b) ? a : b)
#define MAX_VALUE(a, b) ((a>b) ? a : b)

#define POINT_QUEUE_SIZE 3

namespace view {
    class Draftsman;
}

namespace model {

    typedef std::array<double, MODEL_SPACE_DIMENSION> Vector;
    typedef std::array<double, MODEL_SPACE_DIMENSION> Point;
    typedef std::pair<Point, Point> Line;

    class PhysicObject2D {

#ifdef _ACTIVE_BLACK_BOX_
        protected:
            BlackBox blackBox;

        public:
            const BlackBox &getBlackBox() const;

#endif

    protected:
        const std::vector<Point> points;

        Point position;                  // m
        Vector speed;                     // m / s
        Vector acceleration;             // m / s²

        double orientation;                     // radian
        double rotationSpeed;                   // radian / s
        double rotationAcceleration;            // radian / s²

        double weight;                          // kg

        std::list<Point> positions;

    public:

        explicit PhysicObject2D(std::vector<Point> _points,
                                double _xPosition, double _yPosition,
                                double _xSpeed, double _ySpeed, double _xAcceleration, double _yAcceleration,
                                double _orientation, double rotationSpeed, double rotationAcceleration,
                                double _weight);


        explicit PhysicObject2D(const std::vector<Point> &_points,
                                double _xPosition,
                                double _yPosition, double _orientation, double _weight);


        virtual void resetToDefault();

        Vector computeCentrifugalStrength() const;

        bool touch(const PhysicObject2D &object) const;

        double distance(const PhysicObject2D &object) const;

        void writeAbsolutePoints(std::vector<Point> &wPoints) const;

        double getPositionX() const;

        double getPositionY() const;

        void setPositionX(double value);

        void setPositionY(double value);

        void setSpeedX(double value);

        void setSpeedY(double value);

        double getSpeed() const;

        double getSpeedX() const;

        double getSpeedY() const;

        double getAcceleration() const;

        double getAccelerationX() const;

        double getAccelerationY() const;

        void setAccelerationX(double value);

        void setAccelerationY(double value);

        void setOrientation(double value);

        double getOrientation() const;

        double getRotationSpeed() const;

        double getRotationAcceleration() const;

        void setRotationSpeed(double value);

        void setRotationAcceleration(double value);

        double getWeight() const;

        void setWeight(double value);

        virtual void nextTime(double time);

        void nextOrientation(double time);

        void nextPosition(double time);

        void nextRotationSpeed(double time);

        void nextSpeed(double time);

        Vector directionVector() const;

        const std::vector<Point> &getPoints() const;

        virtual void drawMe(view::Draftsman *draftsman);

        virtual ~PhysicObject2D() = default;

        /* static functions */

        static Line constructLine(const Point &point1, const Point &point2);

        static Vector inverseVector(const Vector &vector);

        static double angleBetweenVector(const Vector &vector1, const Vector &vector2);

        static double normVector(const Vector &vector);

        static Point pointRotation(const Point &point, double angle);

        static Point pointTranslation(const Point &point, const Vector &translation);

        static std::vector<Point> loadShapePoints(const std::string &filePath);

        static double distanceBetweenPoint(const Point &point1, const Point &point2);

        static Point circleCenterSolver(const Point &p1, const Point &p2, const Point &p3);

        static Vector vectorBetweenPoints(const Point &point1, const Point &point2);

        static double estimateOrdinateValue(double abscissa, const std::map<double, double> &points);

        static std::map<double, double> loadCoefficients(const std::string &filePath);

        static Point findLineIntersection(const Line &line1, const Line &line2, bool *status);

        static double lineLength(const Line &line);

        static double angleVectorDirection(const Vector &vector1, const Vector &vector2);
    };
}

#endif //LOGIQUEFLOUE_OBJECT2D_H