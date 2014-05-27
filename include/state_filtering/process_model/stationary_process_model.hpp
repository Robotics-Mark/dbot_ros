/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014 Max-Planck-Institute for Intelligent Systems,
 *                     University of Southern California,
 *                     Karlsruhe Institute of Technology
 *    Jan Issac (jan.issac@gmail.com)
 *
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
 *   * Neither the name of Willow Garage, Inc. nor the names of its
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
 */

/**
 * @date 05/25/2014
 * @author Jan Issac (jan.issac@gmail.com)
 * Max-Planck-Institute for Intelligent Systems, University of Southern California (USC),
 *   Karlsruhe Institute of Technology (KIT)
 */

#ifndef STATE_FILTERING_PROCESS_MODEL_STATIONARY_PROCESS_MODEL_HPP
#define STATE_FILTERING_PROCESS_MODEL_STATIONARY_PROCESS_MODEL_HPP

// eigen
#include <Eigen/Dense>

// state_filtering
#include <state_filtering/distribution/distribution.hpp>
#include <state_filtering/distribution/gaussian/gaussian_mappable.hpp>
#include <state_filtering/distribution/gaussian/gaussian_sampleable.hpp>
#include <state_filtering/distribution/gaussian/gaussian_distribution.hpp>

namespace filter
{

template <typename ScalarType_ = double,
          int size = Eigen::Dynamic,
          int control_input_size = Eigen::Dynamic,
          int random_size = Eigen::Dynamic>
class StationaryProcessModel:
        public Distribution<ScalarType_, size >,
        public GaussianMappable<Distribution<ScalarType_, size>, random_size>,
        public GaussianSampleable<GaussianMappable<Distribution<ScalarType_, size>, random_size > >
{
public: /* distribution traits */
    typedef Distribution<ScalarType_, size> BaseType;
    typedef GaussianMappable< Distribution<ScalarType_, size>, random_size > BasenMappableType;

    enum
    {
        VariableSize = BaseType::VariableSize,
        ControlInputSize = control_input_size,
        RandomSize = random_size
    };
    typedef typename BaseType::ScalarType                           ScalarType;
    typedef typename BaseType::VariableType                         VariableType;
    typedef typename BasenMappableType::RandomType                  RandomType;
    typedef Eigen::Matrix<ScalarType, VariableSize, VariableSize>   CovarianceType;
    typedef Eigen::Matrix<ScalarType, ControlInputSize, 1>          ControlInputType;

    virtual ~StationaryProcessModel() { }

    virtual void conditionals(const double& delta_time,
                              const VariableType& state,
                              const ControlInputType& control) = 0;

    virtual void conditionals(const double& delta_time, const VariableType& state)
    {
        conditionals(delta_time, state, ControlInputType::Zero(ControlInputSize));
    }
};

}

#endif
