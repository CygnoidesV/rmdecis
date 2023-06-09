//
// Created by catslashbin on 23-1-24.
//

#ifndef CYGNOIDES_DECISION_BASIC_AIMING_IMPL_H
#define CYGNOIDES_DECISION_BASIC_AIMING_IMPL_H

#include <map>
#include <Eigen/Dense>

#include "rmdecis/core.h"
#include "tracker/tracker.h"
#include "reconstructor/reconstructor.h"
#include "compensator/ballistic_compensator.h"
#include "utils/cv_utils.h"
#include "config.h"

#include "large_rune_aiming.h"
#include "reconstructor/rune_reconstructor.h"

class LargeRuneAiming::LargeRuneAimingImpl {
private:

    BallisticCompensator compensator;

    int n_updates = 0; // Nums update

    EulerAngles last_aiming_angle_{};

    Eigen::Vector3f normal_vec_world_;
    Eigen::Vector3f center_pt_world_;
    float vane_length_;


public:

    // Should be private. Set to public for debug use.
    Tracker tracker;
    RuneReconstructor rune_reconstructor;

    /**
     * Initialize BasicAimingImpl decision-maker.
     * @param cfg Config.
     */
    explicit LargeRuneAimingImpl(Config &cfg);

    /**
     * Update BasicAiming decision-maker with frame and get where to aim.
     * @param detection Result from the detection part.
     * @param debug_img Draw the debug info on this image. Pass in nullptr to disable debugging.
     * @return Euler angles, representing the aiming target.
     * @note The DetectArmorsFrame object is passed in by `move`. Do not reuse the detection.
     */
    EulerAngles update(RuneFrameInput detection, cv::Mat *debug_frame);

};


#endif //CYGNOIDES_DECISION_BASIC_AIMING_IMPL_H
