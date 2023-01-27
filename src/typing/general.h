//
// Created by catslashbin on 23-1-19.
//

#ifndef CYGNOIDES_DECISION_GENERAL_H
#define CYGNOIDES_DECISION_GENERAL_H

#include "armor.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <utility>
#include <iostream>

/**
 * Type of time.
 * @param sec POSIX time, second.
 * @param usec POSIX time, microsecond.
 */
struct Time {
    int sec;
    int usec;

    bool isDefined = false;

    Time(int sec, int usec) : sec(sec), usec(usec), isDefined(true) {}

    Time() : sec(0), usec(0), isDefined(false) {}

    /**
     * Calculate the diff of two time.
     * @param rhs
     * @return Time difference, in second. If not time is not defined, return 0.
     */
    float inline operator-(const Time &rhs) const {
        if (isDefined && rhs.isDefined)
            return (sec - rhs.sec) + (usec - rhs.usec) * 1e-6f;
        return 0.f;
    }

    /**
     * Add sec to the time instance.
     * @param rhs Time addition in second.
     * @return
     */
    Time operator+(const float rhs) const {
        return Time{sec + int(rhs), usec + int((rhs - int(rhs)) * 1e6)};
    }
};

struct EulerAngles {
    float yaw, pitch, roll;

    explicit EulerAngles() = default;

    explicit EulerAngles(const float angles[]) {
        yaw = angles[0];
        pitch = angles[1];
        roll = angles[2];
    }

    explicit EulerAngles(float yaw, float pitch) {
        this->yaw = yaw;
        this->pitch = pitch;
        roll = 0.f;
    }
};

struct Transform3d {
    cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64F);
    cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64F);

    Transform3d() = default;

    Transform3d(cv::Mat rvec, cv::Mat tvec) {
        this->rvec = std::move(rvec);
        this->tvec = std::move(tvec);
    }

    std::vector<cv::Point3f> applyTo(const std::vector<cv::Point3f> &pts) const {
        cv::Mat rot_mat;
        std::vector<cv::Point3f> ret;
        Rodrigues(rvec, rot_mat);

        cv::transform(pts, ret, rot_mat);

        for (auto &pt: pts) {
            ret.push_back((cv::Point3f) tvec + pt);
        }

        return ret;
    }

    cv::Point3f applyTo(const cv::Point3f &pt) const {
        return applyTo(std::vector<cv::Point3f>{pt}).at(0);
    }
};

#endif //CYGNOIDES_DECISION_GENERAL_H
