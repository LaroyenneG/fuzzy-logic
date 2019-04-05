
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

            model::Line line = model::PhysicObject2D::constructLine(points[i], points[i + 1]);

            scene->addLine(scaleConverter(line), QPen(Qt::black));
        }
    }

    void Draftsman::drawVectors() {
    }

    void Draftsman::drawTitanic(const model::Titanic *titanic) {

        const static QImage TITANIC_IMAGE(TITANIC_PICTURE_FILE_NAME);
        const static QPoint DIMENSION = scaleConverter(TITANIC_SIZE, TITANIC_WIDTH);


        QGraphicsPixmapItem *titanicItem = new QGraphicsPixmapItem(
                QPixmap::fromImage(TITANIC_IMAGE).scaled(DIMENSION.x(), DIMENSION.y()));

        QTransform rotation;
        rotation.rotateRadians(titanic->getOrientation());

        QPoint position = scaleConverter(titanic->getPositionX() + TITANIC_WIDTH / 2.0,
                                         titanic->getPositionY() - TITANIC_SIZE / 2.0);

        QTransform translation;
        translation.translate(position.x(), position.y());

        QTransform transform = rotation * translation;

        titanicItem->setTransform(transform);

        scene->addItem(titanicItem);
    }

    void Draftsman::drawIceberg(const model::Iceberg *iceberg) {


        const static QImage ICEBERG_IMAGE(ICEBERG_IMAGE_FILE);
        const static QPoint DIMENSION = scaleConverter(ICEBERG_DEFAULT_RAYON * 2.0, ICEBERG_DEFAULT_RAYON * 2.0);

        QGraphicsPixmapItem *icebergItem = new QGraphicsPixmapItem(
                QPixmap::fromImage(ICEBERG_IMAGE).scaled(DIMENSION.x(), DIMENSION.y()));

        QPoint position = scaleConverter(iceberg->getPositionX() - ICEBERG_DEFAULT_RAYON,
                                         iceberg->getPositionY() - ICEBERG_DEFAULT_RAYON);

        QTransform translation;
        translation.translate(position.x(), position.y());

        icebergItem->setTransform(translation);

        scene->addItem(icebergItem);
    }

    void Draftsman::drawLaserSensor(const model::LasersSensors<3> *laserSensor) {

        auto lines = laserSensor->getLaserLines(model->getElements());

        for (auto line : lines) {

            scene->addLine(scaleConverter(line), QPen(Qt::red));
        }
    }


    /* static functions */

    QPoint Draftsman::scaleConverter(const model::Point &point) {
        return scaleConverter(point[X_DIM_VALUE], point[Y_DIM_VALUE]);
    }

    QLine Draftsman::scaleConverter(const model::Line &line) {

        return QLine(scaleConverter(line.first), scaleConverter(line.second));
    }

    QPoint Draftsman::scaleConverter(double x, double y) {

        QPoint point(static_cast<int>(x * DRAFTSMAN_SCALE), static_cast<int>(y * DRAFTSMAN_SCALE));

        return point;
    }
}