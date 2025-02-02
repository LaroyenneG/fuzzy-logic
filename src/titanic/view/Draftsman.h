
#ifndef LOGIQUEFLOUE_DRAFTSMAN_H
#define LOGIQUEFLOUE_DRAFTSMAN_H

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Model.h"

#define DRAFTSMAN_SCALE 1.0

#define TITANIC_PICTURE_FILE_NAME "../assets/titanic.png"


namespace view {

    class Draftsman {

    private:
        static const QColor SEA_COLOR;

        const model::Model *model;
        QGraphicsScene *scene;

        static QPoint scaleConverter(double x, double y);

        static QLine scaleConverter(const model::Line &line);

        static QPoint scaleConverter(const model::Point &point);

    public:
        explicit Draftsman(const model::Model *_model, QGraphicsScene *_scene);

        void draw();

        void drawVectors();

        void drawElement(const model::PhysicObject2D *object);

        void drawTitanic(const model::Titanic *titanic);

        void drawIceberg(const model::Iceberg *iceberg);

        void drawLaserSensor(const model::LasersSensors<TITANIC_LASERS_COUNTER> *laserSensor);

        ~Draftsman() = default;
    };
}


#endif //LOGIQUEFLOUE_DRAFTSMAN_H
