// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "AlphaArm.h"


AlphaArm::AlphaArm(AlphaArmConfig config) : _config(config) , _alphaArmPID(config.path + "/pid", config.alphaArmPID) 
{
  // _alphaArmPID = wom::utils::PIDController(config.alphaArmPID);
}

AlphaArmConfig AlphaArm::GetConfig() {
  return _config;
}

void AlphaArm::OnUpdate(units::second_t dt) {
  switch (_state) {
    case AlphaArmState::kIdle:
      _setAlphaArmVoltage = 0_V;
      break;
    // case AlphaArmState::kIntakeAngle:
    //   //Set Setpoint
    //   _setAlphaArmVoltage = _alphaArmPID.Calculate(_config.alphaArmGearbox.encoder->GetEncoderPosition(), dt, 0.2_V);
    //   break;
    // case AlphaArmState::kAmpAngle:
    //   //TODO 
    //   break;
    // case AlphaArmState::kSpeakerAngle:
    //   //TODO 
    //   break;
    // case AlphaArmState::kHoldAngle:
    //   _alphaArmPID.SetSetpoint(_angle);
    //   _setAlphaArmVoltage = _alphaArmPID.Calculate(_config.alphaArmGearbox.encoder->GetEncoderPosition(), dt, 0.2_V); //feedforward too high
    //   break;
    case AlphaArmState::kRaw:
       _setAlphaArmVoltage = _rawArmVoltage;
      //  _setAlphaArmVoltage = _testRawVoltage;
      // _config.alphaArmGearbox.motorController->SetVoltage(6_V);
      // _config.alphaArmGearbox.motorController->SetVoltage(_setAlphaArmVoltage);
      // _config.alphaArmGearbox2.motorController->SetVoltage(_setAlphaArmVoltage);
      break;
    default:
      std::cout << "Error: alphaArm in INVALID STATE" << std::endl;
      break;
  }
  _config.alphaArmGearbox.motorController->SetVoltage(_setAlphaArmVoltage);
  _config.alphaArmGearbox2.motorController->SetVoltage(_setAlphaArmVoltage);
  std::cout << "Encoder Value: " << _config.alphaArmGearbox.encoder->GetEncoderPosition().value() << std::endl;
  // std::cout << "Voltage: " << _setAlphaArmVoltage.value() << std::endl;
}

void AlphaArm::SetState(AlphaArmState state) {
  _state = state;
}

void AlphaArm::SetArmRaw(units::volt_t voltage) {
  _rawArmVoltage = voltage;
}

//  void AlphaArm::SetArmTestRaw(units::volt_t testvoltage) {
//    _testRawVoltage = testvoltage;
//  }

