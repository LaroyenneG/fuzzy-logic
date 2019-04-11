#include "LeaveATip.h"

LeaveATip::LeaveATip(fuzzylogic::type _service, fuzzylogic::type _food, fuzzylogic::type _minTip,
                     fuzzylogic::type _maxTip)
        : service(_service), food(_food), minTip(_minTip), maxTip(_maxTip) {

    std::ifstream file(LEAVE_A_TIP_INTERPRETER_FILE_PATH);

    fuzzyInterpreter.executeFile(file);

    file.close();
}

LeaveATip::LeaveATip()
        : LeaveATip(LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE, LEAVE_A_TIP_DEFAULT_VALUE,
                    LEAVE_A_TIP_DEFAULT_VALUE) {

}

void LeaveATip::setService(fuzzylogic::type _service) {
    service = _service;
}

void LeaveATip::setFood(fuzzylogic::type _food) {
    food = _food;
}

void LeaveATip::setMinTip(fuzzylogic::type _minTip) {
    minTip = _minTip;
}

void LeaveATip::setMaxTip(fuzzylogic::type _maxTip) {
    maxTip = _maxTip;
}

fuzzylogic::type LeaveATip::evaluateTip() {
    return 0;
}
