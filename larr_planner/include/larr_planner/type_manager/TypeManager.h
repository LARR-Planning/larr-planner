
namespace larr_planner {
struct Position {
  double px;
  double py;
  double pz;
};
struct Quaternion {
  double qx;
  double qy;
  double qz;
  double qw;
};
struct RobotState {
  double t_sec{0.0};
  Position pos{0.0, 0.0, 0.0};
  Quaternion orientation{0.0, 0.0, 0.0, 1.0};
};
struct LinearSystemControlInput {
  double t_sec{0.0};
  unsigned int seq{0};
  double vx{0.0f};
  double vy{0.0f};
  double vz{0.0f};
  double wx{0.0f};
  double wy{0.0f};
  double wz{0.0f};
};

} // namespace larr_planner
