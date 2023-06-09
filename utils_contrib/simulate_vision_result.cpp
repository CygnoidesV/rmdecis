//
// Created by catslashbin on 23-1-4.
//

#include "simulate_vision_result.h"

using namespace cv;

RobotState robot_state(0, 0, 15000, false);

SimulateVisionOutput::SimulateVisionOutput(const std::string &data_path) {

    info("Start to get data from {} ...", data_path);

    std::vector<YAML::Node> ys = YAML::LoadAllFromFile(data_path);

    int seq_idx = 0;
    for (YAML::Node y: ys) {
        try {
            seq_idx = std::stoi(y["header"]["frame_id"].as<std::string>());

            YAML::Node stamp = y["header"]["stamp"];
            Time time = {stamp["secs"].as<int>(), stamp["nsecs"].as<int>() / (int) 1e3};
            robot_state = RobotState{y["header"]["gimbal_state"]["yaw"].as<float>(),
                                     y["header"]["gimbal_state"]["pitch"].as<float>(),
                                     15000, true};

            std::vector<DetectArmorInfo> armor_info;

            for (YAML::Node d: y["data"]) {
                FacilityID armor_type = (FacilityID) d["facility_id"].as<int>();
                float confidence = d["confidence"].as<float>();

                Point2f rt{d["rt_x"].as<float>(), d["rt_y"].as<float>()};
                Point2f lt{d["lt_x"].as<float>(), d["lt_y"].as<float>()};
                Point2f ld{d["ld_x"].as<float>(), d["ld_y"].as<float>()};
                Point2f rd{d["rd_x"].as<float>(), d["rd_y"].as<float>()};
                RectCorners2f corners{{rt, lt, ld, rd}};

                armor_info.emplace_back(armor_type, corners, confidence);
            }

            data.emplace(seq_idx, ArmorFrameInput(seq_idx, time, robot_state, armor_info));

            // debug("Loaded {}th data", seq_idx);
        }
        catch (YAML::BadConversion &e) {
            warn("Failed to get {}th data: {}", ++seq_idx, e.msg);
        }
    }

    info("Successfully loaded {} data.", ys.size());
}

ArmorFrameInput SimulateVisionOutput::getNextData() {
    auto d = getData(next_idx);
    next_idx++;
    return d;
}

ArmorFrameInput SimulateVisionOutput::getData(int seq_idx) {

    if (seq_idx < 0) {
        warn("Requesting invalid data.");
        return {seq_idx, Time(), robot_state, {}};
    }

    auto i = data.find(seq_idx);
    if (i == data.end()) {
        // Use last available data
        auto last_data = getData(seq_idx - 1);
        last_data.seq_idx = seq_idx;
        return last_data;
    }
    return data.at(seq_idx);
}
