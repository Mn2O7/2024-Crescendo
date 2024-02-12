// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once
#include <frc/DigitalInput.h>

#include "Wombat.h"
#include "vision/Vision.h"
#include "utils/PID.h"
#include <units/angle.h>
#include <units/voltage.h>

struct AlphaArmConfig {
  wom::Gearbox alphaArmGearbox; //up+down
  wom::Gearbox alphaArmGearbox2;
  wom::PIDConfig<units::radians, units::volts> alphaArmPID;
  std::string path;
  // Vision *vision;
};

enum class AlphaArmState {
  kIdle,
  kIntakeAngle,
  kAmpAngle,
  kSpeakerAngle,
  kHoldAngle,
  kRaw
};

class AlphaArm : public ::behaviour::HasBehaviour {
 public:
  explicit AlphaArm(AlphaArmConfig config);

  void OnUpdate(units::second_t dt);
  void SetArmRaw(units::volt_t voltage);
  void SetState(AlphaArmState state);
  AlphaArmConfig GetConfig();

 private:
  units::radian_t CalcTargetAngle();

  AlphaArmConfig _config;
  AlphaArmState _state = AlphaArmState::kIdle;
  wom::utils::PIDController<units::radian, units::volt> _alphaArmPID;
  units::volt_t _setAlphaArmVoltage = 0_V;
  units::volt_t _rawArmVoltage = 0_V;
  units::volt_t _testRawVoltage = 3_V;
  units::radian_t _angle;
};
