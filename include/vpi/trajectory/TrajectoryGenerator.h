// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include <stdio.h>

#include "vpi/spline/SplineParameterizer.h"
#include "vpi/trajectory/Trajectory.h"
#include "vpi/trajectory/TrajectoryConfig.h"
#include "vpi/trajectory/DifferentialDriveKinematicsConstraint.h"
#include "vpi/trajectory/TrajectoryConstraint.h"

namespace vpi {
/**
 * Helper class used to generate trajectories with various constraints.
 */
class TrajectoryGenerator {
 public:

  /**
   * Generates a trajectory from the given control vectors and config. This
   * method uses clamped cubic splines -- a method in which the exterior control
   * vectors and interior waypoints are provided. The headings are automatically
   * determined at the interior points to ensure continuous curvature.
   *
   * @param initial           The initial control vector.
   * @param interiorWaypoints The interior waypoints.
   * @param end               The ending control vector.
   * @param config            The configuration for the trajectory.
   * @return The generated trajectory.
   */
  static Trajectory GenerateTrajectory(
      Spline<3>::ControlVector initial,
      const std::vector<Translation2d>& interiorWaypoints,
      Spline<3>::ControlVector end, const TrajectoryConfig& config);

  /**
   * Generates a trajectory from the given waypoints and config. This method
   * uses clamped cubic splines -- a method in which the initial pose, final
   * pose, and interior waypoints are provided.  The headings are automatically
   * determined at the interior points to ensure continuous curvature.
   *
   * @param start             The starting pose.
   * @param interiorWaypoints The interior waypoints.
   * @param end               The ending pose.
   * @param config            The configuration for the trajectory.
   * @return The generated trajectory.
   */
  static Trajectory GenerateTrajectory(
      const VexGpsPose2d& start, const std::vector<Translation2d>& interiorWaypoints,
      const VexGpsPose2d& end, const TrajectoryConfig& config);

  /**
   * Generates a trajectory from the given quintic control vectors and config.
   * This method uses quintic hermite splines -- therefore, all points must be
   * represented by control vectors. Continuous curvature is guaranteed in this
   * method.
   *
   * @param controlVectors List of quintic control vectors.
   * @param config         The configuration for the trajectory.
   * @return The generated trajectory.
   */
  static Trajectory GenerateTrajectory(
      std::vector<Spline<5>::ControlVector> controlVectors,
      const TrajectoryConfig& config);

  /**
   * Generates a trajectory from the given waypoints and config. This method
   * uses quintic hermite splines -- therefore, all points must be represented
   * by Pose2d objects. Continuous curvature is guaranteed in this method.
   *
   * Generally one should specify a Trajectory by using the method that
   * utilizes the `VexGpsPose2d start` and `VexGpsPose2d end` parameters.
   *
   * @param waypoints List of waypoints.
   * @param config    The configuration for the trajectory.
   * @return The generated trajectory.
   */
  static Trajectory GenerateTrajectory(const std::vector<Pose2d>& waypoints,
                                       const TrajectoryConfig& config);

  /**
   * Generate spline points from a vector of splines by parameterizing the
   * splines.
   *
   * @param splines The splines to parameterize.
   *
   * @return The spline points for use in time parameterization of a trajectory.
   */
  template <typename Spline>
  static std::vector<Pose2dWithCurvature> SplinePointsFromSplines(
      const std::vector<Spline>& splines) {
    // Create the vector of spline points.
    std::vector<Pose2dWithCurvature> splinePoints;

    // Add the first point to the vector.
    splinePoints.push_back(splines.front().GetPoint(0.0));

    // Iterate through the vector and parameterize each spline, adding the
    // parameterized points to the final vector.
    for (auto&& spline : splines) {
      auto points = SplineParameterizer::Parameterize(spline);
      // Append the array of poses to the vector. We are removing the first
      // point because it's a duplicate of the last point from the previous
      // spline.
      splinePoints.insert(std::end(splinePoints), std::begin(points) + 1,
                          std::end(points));
    }
    return splinePoints;
  }

  /**
   * Set error reporting function. By default, it is output to stderr.
   *
   * @param func Error reporting function.
   */
  static void SetErrorHandler(std::function<void(const char*)> func) {
    s_errorFunc = std::move(func);
  }

 private:
  static void ReportError(const char* error);

  static const Trajectory kDoNothingTrajectory;
  static std::function<void(const char*)> s_errorFunc;
};
}  // namespace vpi