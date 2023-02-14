//
// Created by catslashbin on 23-2-4.
//

#include <rmdecis/basic_aiming.h>
#include <iostream>

using namespace cv;

FrameInput getDetectionResult() {
    // Construct DetectArmorInfo
    auto corners = ArmorCorners2d({100, 200}, {100, 300}, {200, 200}, {200, 300});
    auto armor = DetectArmorInfo(STANDARD_3, corners, 1.0);

    // Construct DetectArmorsFrame
    int seq_idx = 0;
    Time time = {34567654, 122};
    std::vector<DetectArmorInfo> armor_info = {armor};

    return FrameInput(seq_idx, time, armor_info, RobotState{0, 0, 15});
}

int main() {
    // Load config
    Config cfg("../config/config.yml");
    BasicAiming basic_aiming(cfg);

    // Predict
    EulerAngles angles = basic_aiming.update(getDetectionResult());

    // Print result (should be "0 0")
    std::cout << angles.pitch << " " << angles.yaw << std::endl;
}