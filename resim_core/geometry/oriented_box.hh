#pragma once

#include <Eigen/Dense>

#include "resim_core/transforms/liegroup_concepts.hh"

namespace resim::geometry {
//
// This class represents an oriented box. It consists of a transform describing
// the box's coordinate frame relative to a reference coordinate frame, and
// extents for the box. The box's coordinate frame is defined to be at the
// geometric center of the box. It is assumed that the Group template parameter
// represents a group of rigid transformations.
//
template <transforms::LieGroupType Group>
class OrientedBox {
 public:
  using ExtentsType = Eigen::Matrix<double, Group::DIMS, 1>;

  // Constructor
  OrientedBox(Group reference_from_box, ExtentsType extents);

  // Getters
  const Group &reference_from_box() const;
  const ExtentsType &extents() const;

  // Setters
  void set_reference_from_box(Group reference_from_box);
  void set_extents(ExtentsType extents);

 private:
  Group reference_from_box_;
  ExtentsType extents_{ExtentsType::Zero()};
};
}  // namespace resim::geometry
