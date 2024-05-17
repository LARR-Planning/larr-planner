

namespace larr_planner{
struct Position{
  double px;
  double py;
  double pz;
};
struct Quaternion{
  double qx;
  double qy;
  double qz;
  double qw;
};
struct RobotState {
  double t_sec{0.0};
  Position pos{0.0,0.0,0.0};
  Quaternion orientation{0.0,0.0,0.0,1.0};

};



}
