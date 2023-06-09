//
// Created by catslashbin on 23-1-31.
//

#ifndef CYGNOIDES_DECISION_TRANSFORMER_H
#define CYGNOIDES_DECISION_TRANSFORMER_H

#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

#include "rmdecis/core.h"
#include "utils/cv_utils.h"

class Transform {

    //
    // Frame transform tool.
    //
    // Available frames
    // - Cam: Camera frame in REP standard.
    // - Gimbal: Stabilized gimbal frame, shooter center as origin, but x-axis point towards base's front, and z axis towards world up.
    // - World: The world frame.
    //
    // Internal frames
    // - GT (GimbalTmp): Un-stabilized gimbal frame, has the same direction with cam frame
    // - (CV_cam): Camera frame in OpenCV standard.
    //


private:

    Eigen::Affine3f transform_;

public:

    Transform();

    Transform(const Eigen::Matrix3f &rot, const Eigen::Vector3f &trans);

    Transform(const EulerAngles &rot, const Eigen::Vector3f &trans);

    Transform(Config &cfg, std::string field);

    Eigen::Vector3f applyTo(const Eigen::Vector3f &pt);

    Eigen::Vector3f applyInverseTo(const Eigen::Vector3f &pt);
};

class Transformer {
public:

    void update(const RobotState &robot_state);

    Eigen::Vector3f camToGimbal(const Eigen::Vector3f &pt);

    cv::Point3f camToGimbal(const cv::Point3f &pt);

    Eigen::Vector3f gimbalToWorld(const Eigen::Vector3f &pt);

    cv::Point3f gimbalToWorld(const cv::Point3f &pt);

    Eigen::Vector3f camToWorld(const Eigen::Vector3f &pt);

    cv::Point3f camToWorld(const cv::Point3f &pt);

    Eigen::Vector3f worldToGimbal(const Eigen::Vector3f &pt);

    cv::Point3f worldToGimbal(const cv::Point3f &pt);

    Eigen::Vector3f worldToCam(const Eigen::Vector3f &pt);

    cv::Point3f worldToCam(const cv::Point3f &pt);

    Eigen::Vector3f gimbalToCam(const Eigen::Vector3f &pt);

    cv::Point3f gimbalToCam(const cv::Point3f &pt);

    static Eigen::Vector3f modelToCam(const Eigen::Vector3f &pt, const CvTransform3f &trans_model2cam);

    static cv::Point3f modelToCam(const cv::Point3f &pt, const CvTransform3f &trans_model2cam);

    explicit Transformer(Config &cfg);

    Transform trans_cam2gt_;
    Transform trans_gt2gimbal_;
    Transform trans_gimbal2world_;
};


#endif //CYGNOIDES_DECISION_TRANSFORMER_H
