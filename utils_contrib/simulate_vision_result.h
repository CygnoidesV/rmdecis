//
// Created by catslashbin on 23-1-4.
//

#ifndef CYGNOIDES_DECISION_SIMULATE_VISION_RESULT_H
#define CYGNOIDES_DECISION_SIMULATE_VISION_RESULT_H

#include <string>
#include <yaml-cpp/yaml.h>

#include "rmdecis/core.h"

class SimulateVisionOutput {
    int next_idx = 0;
    std::map<int, ArmorFrameInput> data;

public:

    explicit SimulateVisionOutput(const std::string &data_path);

    ArmorFrameInput getData(int index);

    ArmorFrameInput getNextData();
};

#endif //CYGNOIDES_DECISION_SIMULATE_VISION_RESULT_H
