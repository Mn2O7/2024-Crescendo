// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "AlphaArmBehaviour.h"

#include <frc/XboxController.h>

AlphaArmManualControl::AlphaArmManualControl(AlphaArm* alphaArm, frc::XboxController* codriver)
    : _alphaArm(alphaArm), _codriver(codriver) {
  Controls(alphaArm);
  _alphaArm->SetState(AlphaArmState::kRaw);
}

void AlphaArmManualControl::OnTick(units::second_t dt) {
  if (_rawControl) {
    if (std::abs(_codriver->GetLeftY()) > 0.3) {
      _alphaArm->SetArmRaw(3_V);
    } else {
      _alphaArm->SetArmRaw(0_V);
    }
  }

  std::cout << std::to_string(_codriver->GetLeftY()) << std::endl;
}
