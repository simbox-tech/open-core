#include "resim_core/experiences/proto/storyboard_to_proto.hh"

#include <gtest/gtest.h>

#include "resim_core/actor/state/proto/trajectory_to_proto.hh"
#include "resim_core/assert/assert.hh"
#include "resim_core/experiences/proto/experiences_test_helpers.hh"
#include "resim_core/experiences/proto/ilqr_drone_to_proto.hh"
#include "resim_core/experiences/proto/storyboard.pb.h"
#include "resim_core/experiences/storyboard.hh"
#include "resim_core/utils/match.hh"
#include "resim_core/utils/proto/uuid_to_proto.hh"

namespace resim::experiences {

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(StoryboardToProtoTest, TestPack) {
  // SETUP
  const Storyboard& test_storyboard = make_test_storyboard();
  proto::Storyboard storyboard_msg;

  // ACTION
  pack(test_storyboard, &storyboard_msg);
  // VERIFICATION
  ASSERT_EQ(
      test_storyboard.movement_models.size(),
      storyboard_msg.movement_models().size());
  for (int i = 0; i < storyboard_msg.movement_models().size(); i++) {
    MovementModel model = test_storyboard.movement_models.at(i);
    proto::MovementModel proto_model = storyboard_msg.movement_models().at(i);
    // Check the actor refeence
    ASSERT_EQ(
        model.actor_reference,
        unpack(proto_model.actor_reference().id()));
    match(
        model.model,
        [&](const actor::state::Trajectory& trajectory) {
          EXPECT_TRUE(proto_model.has_trajectory_model());
          EXPECT_TRUE(test_trajectory_equality(
              trajectory,
              unpack(proto_model.trajectory_model())));
        },
        [&](const ILQRDrone& ilqr_drone) {
          EXPECT_TRUE(proto_model.has_ilqr_drone());
          EXPECT_TRUE(test_ilqr_drone_equality(
              ilqr_drone,
              unpack(proto_model.ilqr_drone())));
        });
  }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(StoryboardToProtoTest, TestRoundTrip) {
  // SETUP
  Storyboard test_storyboard = make_test_storyboard();
  proto::Storyboard storyboard_msg;

  // ACTION
  pack(test_storyboard, &storyboard_msg);
  const Storyboard& retrieved_storyboard = unpack(storyboard_msg);
  EXPECT_TRUE(test_storyboard_equality(test_storyboard, retrieved_storyboard));
}

TEST(StoryboardToProtoDeathTest, TestPackInvalid) {
  // ACTION / VERIFICATION
  EXPECT_THROW(proto::pack(make_test_storyboard(), nullptr), AssertException);
}

TEST(StoryboardToProtoDeathTest, TestUnpackInvalid) {
  // SETUP
  proto::Storyboard storyboard_msg;
  storyboard_msg.add_movement_models();
  // ACTION / VERIFICATION
  EXPECT_THROW(unpack(storyboard_msg), AssertException);
}

}  // namespace resim::experiences
