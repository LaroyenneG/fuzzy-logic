#include <sstream>
#include <iostream>

#include "CheckBoxController.h"
#include "SliderController.h"
#include "TimeWizardController.h"
#include "AutomaticPilotController.h"
#include "MenuController.h"
#include "View.h"


#define COLLISIONS_TITLE "Titanic sank"
#define COLLISIONS_MESSAGE "The titanic hit the iceberg :-("

namespace view {

    View::View()
            : parent(new QBoxLayout(QBoxLayout::TopToBottom)),
              titanicView(new QGraphicsView()),
              titanicScene(new QGraphicsScene()),
              dashboard(new QGridLayout()),
              menuBar(new QMenuBar()),
              commandPost(new QFormLayout()),
              statisticalBoard(new QFormLayout()),
              machineSlider(new QSlider(Qt::Horizontal)),
              rpmMachinesLabel(new QLabel()),
              speedLabel(new QLabel()),
              helmSlider(new QSlider(Qt::Horizontal)),
              courseLabel(new QLabel()),
              automaticPilotCheckBox(new QCheckBox()),
              progressBarLaser1(new QProgressBar()),
              progressBarLaser2(new QProgressBar()),
              progressBarLaser3(new QProgressBar()),
              distanceLabel(new QLabel()),
              refreshTimer(new QTimer(this)),
              automaticPilotTimer(new QTimer(this)),
              simulationMenu(nullptr),
              resetAction(nullptr),
              pauseAction(nullptr),
              playAction(nullptr),
              accelerationAction(nullptr),
              sceneMenu(nullptr),
              realIcebergSceneAction(nullptr),
              icebergSceneAction(nullptr) {


        titanicView->setScene(titanicScene);

        automaticPilotTimer->setInterval(DEFAULT_AUTOMATIC_PILOT_INTERVAL);
        refreshTimer->setInterval(DEFAULT_VIEW_TIMER_INTERVAL);

        machineSlider->setRange(SLIDER_MINIMUM_VALUE, SLIDER_MAXIMUM_VALUE);
        helmSlider->setRange(SLIDER_MINIMUM_VALUE, SLIDER_MAXIMUM_VALUE);

        setLayout(parent);

        parent->addWidget(titanicView);
        parent->addLayout(dashboard);

        createActions();
        createMenus();

        parent->setMenuBar(menuBar);


        dashboard->addLayout(commandPost, 0, 0);
        dashboard->addLayout(statisticalBoard, 0, 1);

        commandPost->addRow("Machine (%) : ", machineSlider);
        commandPost->addRow("Rotation (rpm) : ", rpmMachinesLabel);
        commandPost->addRow("Speed (nd) : ", speedLabel);
        commandPost->addRow("Helm (%) : ", helmSlider);
        commandPost->addRow("Course (degree) : ", courseLabel);
        commandPost->addRow("Distance (m) : ", distanceLabel);

        statisticalBoard->addRow("Automatic pilot : ", automaticPilotCheckBox);
        statisticalBoard->addRow("Laser 1 (%) : ", progressBarLaser1);
        statisticalBoard->addRow("Laser 2 (%) : ", progressBarLaser2);
        statisticalBoard->addRow("Laser 3 (%) : ", progressBarLaser3);


        QFile styleSheetFile(STYLE_SHEET_FILE_PATH);
        styleSheetFile.open(QFile::ReadOnly);
        setStyleSheet(QLatin1String(styleSheetFile.readAll()));
        styleSheetFile.close();

        setWindowTitle(WINDOWS_TITLE);
        setMinimumSize(WINDOWS_WIDTH_SIZE, WINDOWS_HEIGHT_SIZE);
    }

    View::~View() {

        delete simulationMenu;
        delete pauseAction;
        delete playAction;
        delete accelerationAction;
        delete resetAction;
        delete sceneMenu;
        delete realIcebergSceneAction;
        delete icebergSceneAction;
        delete refreshTimer;
        delete distanceLabel;
        delete progressBarLaser3;
        delete progressBarLaser2;
        delete progressBarLaser1;
        delete automaticPilotCheckBox;
        delete courseLabel;
        delete helmSlider;
        delete speedLabel;
        delete rpmMachinesLabel;
        delete machineSlider;
        delete statisticalBoard;
        delete commandPost;
        delete titanicView;
        delete titanicScene;
        delete dashboard;
        delete parent;
        delete menuBar;
    }

    QGraphicsScene *View::getGraphicsScene() {
        return titanicScene;
    }

    void View::setMachinesSpeed(double alt1, double turbine, double alt2) {

        std::string string =
                "Alternative left : " +
                std::to_string(static_cast<int>(std::round(alt1 * RDS_TO_TPM))) + " | " +
                "Turbine : " +
                std::to_string(static_cast<int>(std::round(turbine * RDS_TO_TPM))) + " | " +
                "Alternative right : " +
                std::to_string(static_cast<int>(std::round(alt2 * RDS_TO_TPM)));

        QString qString(string.data());

        rpmMachinesLabel->setText(qString);
    }

    void View::setShipSpeed(double value) {

        int nds = static_cast<int>(std::round(value * MS_TO_NDS));

        std::string string = std::to_string(nds);

        QString qString(string.data());

        speedLabel->setText(qString);
    }

    void View::setDistance(double value) {

        int m = static_cast<int>(std::round(value));

        std::string string = std::to_string(m);

        QString qString(string.data());

        distanceLabel->setText(qString);
    }

    void View::setCheckBoxController(controller::CheckBoxController *checkBoxController) const {

        QObject::connect(automaticPilotCheckBox, SIGNAL(clicked(bool)), checkBoxController,
                         SLOT(automaticPilotStateChange(bool)));
    }

    void View::setSliderController(controller::SliderController *sliderController) const {

        QObject::connect(machineSlider, SIGNAL(valueChanged(int)), sliderController,
                         SLOT(machinePowerSliderValueChanged(int)));

        QObject::connect(helmSlider, SIGNAL(valueChanged(int)), sliderController, SLOT(helmSliderValueChanged(int)));
    }

    void View::setTimeWizardController(controller::TimeWizardController *timeWizardController) const {

        QObject::connect(refreshTimer, SIGNAL(timeout()), timeWizardController, SLOT(nextTime()));
    }

    void View::setAutomaticPilotController(controller::AutomaticPilotController *automaticPilotController) const {

        QObject::connect(automaticPilotTimer, SIGNAL(timeout()), automaticPilotController, SLOT(compute()));
    }

    void View::setMenuController(controller::MenuController *menuController) const {

        QObject::connect(icebergSceneAction, &QAction::triggered, menuController,
                         &controller::MenuController::icebergScene);
        QObject::connect(realIcebergSceneAction, &QAction::triggered, menuController,
                         &controller::MenuController::realIcebergScene);

        QObject::connect(resetAction, &QAction::triggered, menuController, &controller::MenuController::reset);
        QObject::connect(pauseAction, &QAction::triggered, menuController, &controller::MenuController::pause);
        QObject::connect(playAction, &QAction::triggered, menuController, &controller::MenuController::play);
        QObject::connect(accelerationAction, &QAction::triggered, menuController,
                         &controller::MenuController::acceleration);
    }

    int View::getTimeInterval() const {
        return refreshTimer->interval();
    }

    void View::setTimeInterval(int time) {
        refreshTimer->setInterval(time);
    }

    void View::display() {
        startTime();
        show();
    }

    void View::stopTime() {

        if (refreshTimer->isActive()) {
            refreshTimer->stop();
        }
    }

    void View::startTime() {

        if (!refreshTimer->isActive()) {
            refreshTimer->start();
        }
    }

    void View::touching() {

        QMessageBox::information(this, QString(COLLISIONS_TITLE), QString(COLLISIONS_MESSAGE));

        setLasersValue(0.0, 0.0, 0.0);
    }

    void View::enableAutomaticPilot() {

        if (automaticPilotTimer->isActive()) {
            automaticPilotTimer->stop();
        }

        automaticPilotTimer->start();

        automaticPilotCheckBox->setChecked(true);
    }

    void View::disableAutomaticPilot() {

        automaticPilotTimer->stop();

        automaticPilotCheckBox->setChecked(false);

        setLasersValue(0.0, 0.0, 0.0);
    }

    void View::setHelmValue(double value) {

        helmSlider->setValue(static_cast<int>(std::round(value)));
    }

    void View::setMachinePower(double value) {

        machineSlider->setValue(static_cast<int>(value * (SLIDER_MAXIMUM_VALUE - SLIDER_MINIMUM_VALUE)));
    }

    void View::setCourse(double value) {

        static const unsigned int DEGREE = 360;

        int course = static_cast<int>(value * COURSE_RDS_TO_DEGREE) % DEGREE;
        if (course < 0) { course += DEGREE; }

        std::string string = std::to_string(course);

        QString qString(string.data());

        courseLabel->setText(qString);
    }

    QGraphicsView *View::getGraphicsView() {

        return titanicView;
    }

    void View::setLasersValue(double laser1, double laser2, double laser3) {

        static const double MUTIPLY = 100.0;

        progressBarLaser1->setValue(static_cast<int>(std::round(laser1 * MUTIPLY)));
        progressBarLaser2->setValue(static_cast<int>(std::round(laser2 * MUTIPLY)));
        progressBarLaser3->setValue(static_cast<int>(std::round(laser3 * MUTIPLY)));
    }

    bool View::automaticPilotIsEnable() {

        return automaticPilotCheckBox->isChecked();
    }

    void View::createMenus() {

        simulationMenu = menuBar->addMenu(tr("&Simulation"));
        simulationMenu->addAction(pauseAction);
        simulationMenu->addAction(playAction);
        simulationMenu->addAction(accelerationAction);
        simulationMenu->addAction(resetAction);

        sceneMenu = menuBar->addMenu(tr("&Scene"));
        sceneMenu->addAction(realIcebergSceneAction);
        sceneMenu->addAction(icebergSceneAction);
    }

    void View::createActions() {

        pauseAction = new QAction(tr("&Pause"));
        playAction = new QAction(tr("&Play"));
        accelerationAction = new QAction(tr("&Acceleration"));
        resetAction = new QAction(tr("&Reset to default"));

        realIcebergSceneAction = new QAction(tr("&Real iceberg scene"));
        icebergSceneAction = new QAction(tr("&Iceberg scene"));
    }

    void View::lockDashboard() {

        helmSlider->setDisabled(true);
        machineSlider->setDisabled(true);
        automaticPilotCheckBox->setDisabled(true);
    }

    void View::unlockDashboard() {

        helmSlider->setDisabled(false);
        machineSlider->setDisabled(false);
        automaticPilotCheckBox->setDisabled(false);
    }
}