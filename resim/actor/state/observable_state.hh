#pragma once

#include "resim/actor/actor_id.hh"
#include "resim/actor/state/rigid_body_state.hh"
#include "resim/time/timestamp.hh"

namespace resim::actor::state {

// This struct represents the observable state of an actor along with that
// actor's id and the state's time of validity.
struct ObservableState {
  ActorId id;
  bool is_spawned = false;
  time::Timestamp time_of_validity;
  RigidBodyState<transforms::SE3> state;
};

}  // namespace resim::actor::state