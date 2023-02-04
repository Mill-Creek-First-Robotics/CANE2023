#include "LimeLight.hpp"

void LimeLight::Update() {
    // Whether the limelight has any valid targets (0 or 1)
    int tv = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("<tv>",0.0);
}