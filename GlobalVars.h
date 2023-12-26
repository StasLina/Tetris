#pragma once
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <vector>

struct pos {
  int pos_x, pos_y;
};

class GlobalVars {
public:
  static int x_size;
  static int y_size;
  static bool is_need_new_block;
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
    os <<  index.data << index.data;

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
  virtual void SetModelSize(unsigned short pos_x, unsigned short pos_y) {
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

    for (unsigned short pos_y = 0; pos_y != y_size; pos_y++) {

      for (unsigned short pos_x = 0; pos_x != x_size; pos_x++) {
        std::cout << model->GetModelIndex(pos_x, pos_y);
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
    short smth_offset = 0;

    while (smth_offset != pos_y) {
      ++row;
      ++smth_offset;
    }
    smth_offset = 0;
    auto col = row->begin();

    while (smth_offset != pos_x) {
      ++col;
      ++smth_offset;
    }
    return *col;
  };
  void SetModelIndex(const ModelIndex &smth_index, const short &pos_x,
                     const short &pos_y) override {
    auto row = data.begin();
    short smth_offset = 0;

    while (smth_offset != pos_y) {
      ++row;
      ++smth_offset;
    }
    smth_offset = 0;
    auto col = row->begin();

    while (smth_offset != pos_x) {
      ++col;
      ++smth_offset;
    }
    *col = smth_index;
  };
  unsigned short GetXSize() override { return data.begin()->size(); }
  unsigned short GetYSize() override { return data.size(); }
  void SetModelSize(unsigned short pos_x, unsigned short pos_y) override {
    data.resize(pos_y);
    auto row = data.begin();
    short smth_offset = 0;

    while (smth_offset != pos_y) {
      row->resize(pos_x);
      ++row;
      ++smth_offset;
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

    for (int cur_offset_row = 0; cur_offset_row != smth_index_row;
         ++cur_offset_row, ++it)
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
