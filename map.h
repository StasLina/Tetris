#pragma once
#include "GlobalVars.h"

#include <ios>
#include <mutex>
#include <string>
#include <thread>
class MapController : public AbstractMapController {
public:
  MapController();
  ~MapController() {
    is_game_over = true;

    while (this->timer_end == false) {
      std::this_thread::yield();
    }

    if (this->elm.smth_elm_model != 0) {
      delete this->elm.smth_elm_model;
    }

    if (this->elm2.smth_elm_model != 0) {
      delete this->elm2.smth_elm_model;
    }
  }
  void StartGame() {
    std::thread timer(&MapController::mytymer, this);
    timer.detach();
  }
  bool timer_end = false;
  void mytymer() {

    while (is_game_over == false) {

      if (was_user_input == false) {
        MoveDown(false);
      } else {
        was_user_input = false;
        MoveDown(false);
      }
      double time_sleep = 2.5 - std::pow(1.055, lvl);
      std::this_thread::sleep_for(
       std::chrono::milliseconds(long(time_sleep * 1000)));
    }
    timer_end = true;
  }
  void SetModel(MapModel *smth_model);
  void AddFirstSmthElm(AbstractModel *elm);
  void AddSecondSmthElm(AbstractModel *elm);
  void Draw();
  void MoveLeft();
  void MoveRight();
  void MoveDown(bool user = true);
  void MoveAbove();
  void ElmRotate() { elm.smth_elm_model->Rotate(); };
  void data_changed() override;

private:
  short x, y;
  MapModel *map_model;
  struct smth_elm {
    pos cur, min, max;
    smth_elm() { smth_elm_model = 0; }
    void swap() {
      auto temp = min.y;
      min.y = min.x;
      min.x = temp;
      temp = max.y;
      max.y = max.x;
      max.x = temp;
    }
    AbstractModel *smth_elm_model;
  };
  smth_elm elm, elm2;
  bool proverka_size(const short &x, const short &y) { return true; };
  void map_model_delete_row(int row) {
    this->map_model->DeleteRow(row);
  }
  //
  bool VerifyUpdate();

  bool proverka_cancel_moving();
  bool save_block_to_map();
  void proverka_rows();
  bool first_zero = true;
  bool proverka_cancel_moving_down(const pos &smth_pos);
  bool proverka_cancel_moving_left(const pos &smth_pos);
  bool proverka_cancel_moving_right(const pos &smth_pos);

  unsigned short get_size_y_into_map();
  unsigned short get_size_y_into_visible();
  bool new_shape_exsist();
  struct indent {
    short left = 7, right = 7, bot = 1, top = 5;
  };
  indent my_indent;
  bool is_game_over = false;
  int score = 0;
  int lvl = 0;
  unsigned long count_placed_bloks = 0;
  bool was_user_input = true;
  std::mutex block_draw, move_down;
};
