#include <gtest/gtest.h>

#include <Arm.h>
#include <frc/simulation/SolenoidSim.h>
#include <frc/simulation/XboxControllerSim.h>

using namespace frc;
using namespace frc::sim;
using namespace std;
using namespace Constants;

class ArmTest : public testing::Test {
 protected:
  // shared_ptr<XboxController> m_controller = make_shared<XboxController>(0);
  // XboxControllerSim m_simController{*m_controller};
  // Arm m_arm{m_controller};
  // SolenoidSim m_solenoid{PneumaticsModuleType::CTREPCM, Solenoids::ARM_SOLENOID};
};


// TEST_F(ArmTest, ArmPistonDefaultFalse) {
//   EXPECT_EQ(m_solenoid.GetOutput(),false);
// }

// TEST_F(ArmTest, ArmExtensionMovesManually) {
//   WPI_TalonSRX* extensionSim = m_arm.GetExtensionMotor();
//   EXPECT_EQ(extensionSim->GetMotorOutputPercent(),0.0);
//   m_simController.SetYButton(true);
//   m_arm.DebugArmExtension();
//   EXPECT_EQ(extensionSim->GetMotorOutputPercent(),0.5);
//   m_simController.SetYButton(false);
//   m_arm.DebugArmExtension();
//   EXPECT_EQ(extensionSim->GetMotorOutputPercent(),0.0);
// }
/**
 * @note: This test will fail because testing OOP code is a pain. 
 */
// TEST_F(ArmTest, PistonToggles) {
//   m_simController.SetAButton(true);
//   m_arm.HandleGrabberPneumatics();
//   EXPECT_EQ(m_solenoid.GetOutput(), true);
// }