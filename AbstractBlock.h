#pragma once
#include "GlobalVars.h"

#include <map>
#include <string>

class AbstractBlockModel : public AbstractModel {
  virtual void after_rotation(){};

public:
  AbstractBlockModel();

  virtual void SetBlokShape(const std::string &smth_str) { return; };
  enum rotation_types {
    rotate_0 = 0,
    rotate_90 = 1,
    rotate_180 = 2,
    rotate_270 = 3
  };
  rotation_types GetRotateBlockLeft();
  rotation_types GetRotateBlockRight();
  virtual void RotateLeft() {
    cur_rotation = GetRotateBlockLeft();

    return;
  }
  virtual void RotateRight() {
    cur_rotation = GetRotateBlockRight();
    after_rotation();

    return;
  }
  virtual void MoveLeft() { return; }
  virtual void MoveRight() { return; }
  rotation_types cur_rotation = rotate_0;
};
