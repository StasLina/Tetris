#include "AbstractBlock.h"

AbstractBlockModel::AbstractBlockModel() {
  list_bloks.insert({list_bloks.size(), this});
}

AbstractBlockModel::rotation_types
AbstractBlockModel::GetRotateBlockLeft() {
  switch (cur_rotation) {
  case AbstractBlockModel::rotate_0:
    return rotation_types::rotate_90;
    break;
  case AbstractBlockModel::rotate_90:
    return rotation_types::rotate_180;
    break;
  case AbstractBlockModel::rotate_180:
    return rotation_types::rotate_270;
    break;
  case AbstractBlockModel::rotate_270:
    return rotation_types::rotate_0;
    break;
  default:
    break;
  }
}

AbstractBlockModel::rotation_types
AbstractBlockModel::GetRotateBlockRight() {
  switch (cur_rotation) {
  case AbstractBlockModel::rotate_0:
    return rotation_types::rotate_270;
    break;
  case AbstractBlockModel::rotate_270:
    return rotation_types::rotate_180;
    break;
  case AbstractBlockModel::rotate_180:
    return rotation_types::rotate_90;
    break;
  case AbstractBlockModel::rotate_90:
    return rotation_types::rotate_0;
    break;
  default:
    break;
  }
}
