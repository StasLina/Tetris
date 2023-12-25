#pragma once
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <vector>
struct pos {
  int x, y;
};

class GlobalVars {
public:
  static int x_size;
  static int y_size;
  static bool need_new_block;
  static short wide_scale;
  friend bool operator<=(GlobalVars &index1,
                         const GlobalVars &index2) {

    if (index1.x_size <= index2.x_size &&
        index1.y_size <= index2.y_size) {

      return true;
    } else {

      return false;
    }
  }
  friend bool operator>=(GlobalVars &index1,
                         const GlobalVars &index2) {

    if (index1.x_size >= index2.x_size &&
        index1.y_size >= index2.y_size) {

      return true;
    } else {

      return false;
    }
  }
};
class ModelIndex {
public:
  ModelIndex(){};
  ModelIndex(const char ch) { data = ch; };
  char data = ' ';
  // pos position;
  friend std::ostream &operator<<(std::ostream &os,
                                  const ModelIndex &index) {
    os << index.data << index.data;

    return os;
  }
};
class AbstractModel {
public:
  virtual const ModelIndex &GetModelIndex(short const &pox_x,
                                          const short &pos_y) {

    return ModelIndex();
  };
  virtual void SetModelIndex(const ModelIndex &smth_index,
                             const short &pox_x,
                             const short &pos_y){};
  virtual unsigned short GetXSize() { return 0; }
  virtual unsigned short GetYSize() { return 0; }
  virtual void SetModelSize(unsigned short x, unsigned short y) {

    return;
  };
  virtual void data_changed(){};
  virtual void SetParent(AbstractModel *parent){};
  // virtual void SetParent(AbstractModel*) {};
  virtual void Rotate(){};
  virtual void CancelRotate(){};
  virtual AbstractModel *GetCopy() { return 0; };
  static std::map<int, AbstractModel *> list_bloks;
};
class AbstractView {
public:
  virtual void SetModel(AbstractModel *input_model) {
    this->model = input_model;
  }
  virtual void DrawModel() {
    auto x_size = model->GetXSize();
    auto y_size = model->GetYSize();

    for (unsigned short y = 0; y != y_size; y++) {

      for (unsigned short x = 0; x != x_size; x++) {
        std::cout << model->GetModelIndex(x, y);
      }
      std::cout << std::endl;
    }
  }

private:
  AbstractModel *model;
};
class StandartModel : public AbstractModel {
public:
  const ModelIndex &GetModelIndex(short const &pos_x,
                                  const short &pos_y) override {
    auto row = data.begin();
    short n = 0;

    while (n != pos_y) {
      ++row;
      ++n;
    }
    n = 0;
    auto col = row->begin();

    while (n != pos_x) {
      ++col;
      ++n;
    }

    return *col;
  };
  void SetModelIndex(const ModelIndex &smth_index, const short &pos_x,
                     const short &pos_y) override {
    auto row = data.begin();
    short n = 0;

    while (n != pos_y) {
      ++row;
      ++n;
    }
    n = 0;
    auto col = row->begin();

    while (n != pos_x) {
      ++col;
      ++n;
    }
    *col = smth_index;
  };
  unsigned short GetXSize() override { return data.begin()->size(); }
  unsigned short GetYSize() override { return data.size(); }
  void SetModelSize(unsigned short x, unsigned short y) override {
    data.resize(y);
    auto row = data.begin();
    short n = 0;

    while (n != y) {
      row->resize(x);
      ++row;
      ++n;
    }
  };
  std::list<std::vector<ModelIndex>> data;

private:
};

class AbstractMapController {
public:
  virtual void data_changed(){};
};
class MapModel : public StandartModel {
  AbstractMapController *controller;
  void data_changed() override { controller->data_changed(); };
  unsigned short cur_max = 0;

public:
  void SetController(AbstractMapController *controller) {
    this->controller = controller;
  }
  void DeleteRow(int smth_index_row) {
    std::list<std::vector<ModelIndex>>::iterator it =
     this->data.begin();

    for (int cur_offset_row = 0; cur_offset_row != smth_index_row; ++cur_offset_row, ++it)
      ;
    this->data.erase(it);
    this->data.push_back(std::vector<ModelIndex>());
    this->data.back().resize(this->GetXSize());
    --cur_max;
  }
  bool SetMax(const unsigned short &cur_max) {

    if (this->cur_max < cur_max) {

      if (cur_max == this->data.size()) {

        return true;
      } else {
        this->cur_max = cur_max;

        return false;
      }
    }

    return false;
  }
  bool isMax() {

    if (this->cur_max >= this->GetYSize() - 1) {

      return true;
    }

    return false;
  }
};
#endif // !GLOBAL_VARS_H
