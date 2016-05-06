/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Daichi Yoshikawa
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Daichi Yoshikawa nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Daichi Yoshikawa
 *
 *********************************************************************/

#ifndef __AHL_ROBOT_CONTROLLER_ORIENTATION_CONTROL_HPP
#define __AHL_ROBOT_CONTROLLER_ORIENTATION_CONTROL_HPP

#include <ahl_robot/ahl_robot.hpp>
#include "ahl_robot_controller/task/task.hpp"

namespace ahl_ctrl
{

  class OrientationControl : public Task
  {
  public:
    explicit OrientationControl(const ahl_robot::ManipulatorPtr& mnp, const std::string& target_link, double eigen_thresh = 0.001);
    virtual const std::string& getName() const override { return task::ORIENTATION_CONTROL; }
    virtual void setGoal(const Eigen::MatrixXd& Rd) override;
    virtual void updateModel() override;
    virtual void computeGeneralizedForce(Eigen::VectorXd& tau) override;
    virtual bool haveNullSpace() override { return true; }

  private:
    bool updated_;

    std::string target_link_;
    Eigen::Matrix3d Rd_;

    int idx_;
    Eigen::MatrixXd Jw_;
    Eigen::Matrix3d lambda_inv_;
    Eigen::Matrix3d lambda_;
    Eigen::MatrixXd J_dyn_inv_;
    Eigen::MatrixXd I_;

    Eigen::Vector3d M_unit_;
    double eigen_thresh_;
  };

} // namespace ahl_ctrl

#endif // __AHL_ROBOT_CONTROLLER_ORIENTATION_CONTROL_HPP
