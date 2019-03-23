
#include <iostream>
#include "Draftsman.h"


namespace view {

    const QColor Draftsman::SEA_COLOR(0, 138, 230);

    Draftsman::Draftsman(const model::Model *_model, QGraphicsScene *_scene)
            : model(_model), scene(_scene) {

        scene->setBackgroundBrush(SEA_COLOR);
    }

    void Draftsman::draw() {

        scene->clear();

        for (auto element : model->getElements()) {
            element->drawMe(this);
        }
    }

    void Draftsman::drawElement(const model::PhysicObject2D *object) {

        std::vector<model::Point> points;

        object->writeAbsolutePoints(points);

        for (unsigned int i = 0; !points.empty() && i < points.size() - 1; ++i) {

            auto &p1 = points[i];
            auto &p2 = points[i + 1];

            QPoint qp1 = scaleConverter(p1[X_DIM_VALUE], p1[Y_DIM_VALUE]);
            QPoint qp2 = scaleConverter(p2[X_DIM_VALUE], p2[Y_DIM_VALUE]);

            QLine line(qp1, qp2);

            scene->addLine(line);
        }
    }

    QPoint Draftsman::scaleConverter(double x, double y) {

        QPoint point(static_cast<int>(x * DRAFTSMAN_SCALE), static_cast<int>(y * DRAFTSMAN_SCALE));

        return point;
    }

    void Draftsman::drawVectors() {

        auto titanic = model->getTitanic();

        QLine accelerationLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                               scaleConverter(titanic->getAccelerationX() * 100.0 + titanic->getPositionX(),
                                              titanic->getAccelerationY() * 100.0 + titanic->getPositionY()));

        scene->addLine(accelerationLine, QPen(Qt::green));


        QLine speedLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                        scaleConverter(titanic->getSpeedX() * 10.0 + titanic->getPositionX(),
                                       titanic->getSpeedY() * 10.0 + titanic->getPositionY()));


        scene->addLine(speedLine, QPen(Qt::black));

        model::Vector lift = titanic->computeLift(0.0);

        QLine liftLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                       scaleConverter(lift[0] * 0.001 + titanic->getPositionX(),
                                      lift[1] * 0.001 + titanic->getPositionY()));

        scene->addLine(liftLine, QPen(Qt::red));

        model::Vector engine = titanic->computePropulsion(0.000001);

        QLine engineLine(scaleConverter(titanic->getPositionX(), titanic->getPositionY()),
                         scaleConverter(engine[0] + titanic->getPositionX(),
                                        engine[1] + titanic->getPositionY()));

        scene->addLine(engineLine, QPen(Qt::yellow));
    }
}