/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef GZ_SIM_SYSTEMS_ACKERMANNSTEERING_HH_
#define GZ_SIM_SYSTEMS_ACKERMANNSTEERING_HH_

#include <memory>

#include <gz/sim/System.hh>

namespace gz
{
namespace sim
{
// Inline bracket to help doxygen filtering.
inline namespace GZ_SIM_VERSION_NAMESPACE {
namespace systems
{
  // Forward declaration
  class AckermannSteeringPrivate;

  /// \brief Ackermann steering controller which can be attached to a model
  /// with any number of left and right wheels.
  ///
  /// # System Parameters
  ///
  /// `<left_joint>`: Name of a joint that controls a left wheel. This
  /// element can appear multiple times, and must appear at least once.
  ///
  /// `<right_joint>`: Name of a joint that controls a right wheel. This
  /// element can appear multiple times, and must appear at least once.
  ///
  /// `<left_steering_joint>`: Name of a joint that controls steering for
  ///  left wheel. This element must appear once.  Vehicles that steer
  ///  rear wheels are not currently correctly supported.
  ///
  /// `<right_steering_joint>`: Name of a joint that controls steering for
  ///  right wheel. This element must appear once.
  ///
  /// `<wheel_separation>`: Distance between wheels, in meters. This element
  /// is optional, although it is recommended to be included with an
  /// appropriate value. The default value is 1.0m.
  ///
  /// `<kingpin_width>`: Distance between wheel kingpins, in meters. This
  /// element is optional, although it is recommended to be included with an
  /// appropriate value. The default value is 0.8m.  Generally a bit smaller
  /// than the wheel_separation.
  ///
  /// `<wheel_base>`: Distance between front and rear wheels, in meters. This
  /// element is optional, although it is recommended to be included with an
  /// appropriate value. The default value is 1.0m.
  ///
  /// `<steering_limit>`: Value to limit steering to.  Can be calculated by
  /// measuring the turning radius and wheel_base of the real vehicle.
  /// steering_limit = asin(wheel_base / turning_radius)
  /// The default value is 0.5 radians.
  ///
  /// `<wheel_radius>`: Wheel radius in meters. This element is optional,
  /// although it is recommended to be included with an appropriate value. The
  /// default value is 0.2m.
  ///
  /// `<odom_publish_frequency>`: Odometry publication frequency. This
  /// element is optional, and the default value is 50Hz.
  ///
  /// `<min_velocity>`: Minimum velocity [m/s], usually <= 0.
  /// `<max_velocity>`: Maximum velocity [m/s], usually >= 0.
  /// `<min_acceleration>`: Minimum acceleration [m/s^2], usually <= 0.
  /// `<max_acceleration>`: Maximum acceleration [m/s^2], usually >= 0.
  /// `<min_jerk Minimum>`: jerk [m/s^3], usually <= 0.
  /// `<max_jerk Maximum>`: jerk [m/s^3], usually >= 0.
  ///
  /// `<topic>`: Custom topic that this system will subscribe to in order to
  /// receive command velocity messages. This element if optional, and the
  /// default value is `/model/{name_of_model}/cmd_vel`.
  ///
  /// `<odom_topic>`: Custom topic on which this system will publish odometry
  /// messages. This element if optional, and the default value is
  /// `/model/{name_of_model}/odometry`.
  ///
  /// `<tf_topic>`: Custom topic on which this system will publish the
  /// transform from `frame_id` to `child_frame_id`. This element is optional,
  /// and the default value is `/model/{name_of_model}/tf`.
  ///
  /// `<frame_id>`: Custom `frame_id` field that this system will use as the
  /// origin of the odometry transform in both the `<tf_topic>`
  /// `gz.msgs.Pose_V` message and the `<odom_topic>`
  /// `gz.msgs.Odometry` message. This element if optional, and the
  /// default value is `{name_of_model}/odom`.
  ///
  /// `<child_frame_id>`: Custom `child_frame_id` that this system will use as
  /// the target of the odometry transform in both the `<tf_topic>`
  /// `gz.msgs.Pose_V` message and the `<odom_topic>`
  /// `gz.msgs.Odometry` message. This element if optional,
  /// and the default value is `{name_of_model}/{name_of_link}`.
  ///
  /// A robot with rear drive and front steering would have one each
  /// of left_joint, right_joint, left_steering_joint and
  /// right_steering_joint
  ///
  /// References:
  /// https://github.com/gazebosim/gz-sim/tree/main/src/systems/ackermann_steering
  /// https://www.auto.tuwien.ac.at/bib/pdf_TR/TR0183.pdf
  /// https://github.com/froohoo/ackermansteer/blob/master/ackermansteer/


  class AckermannSteering
      : public System,
        public ISystemConfigure,
        public ISystemPreUpdate,
        public ISystemPostUpdate
  {
    /// \brief Constructor
    public: AckermannSteering();

    /// \brief Destructor
    public: ~AckermannSteering() override = default;

    // Documentation inherited
    public: void Configure(const Entity &_entity,
                           const std::shared_ptr<const sdf::Element> &_sdf,
                           EntityComponentManager &_ecm,
                           EventManager &_eventMgr) override;

    // Documentation inherited
    public: void PreUpdate(
                const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm) override;

    // Documentation inherited
    public: void PostUpdate(
                const UpdateInfo &_info,
                const EntityComponentManager &_ecm) override;

    /// \brief Private data pointer
    private: std::unique_ptr<AckermannSteeringPrivate> dataPtr;
  };
  }
}
}
}

#endif
