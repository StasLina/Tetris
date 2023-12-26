// clang-format.exe -i -style=file -files=files_for_format

#include "Block.h"
#include "map.h"

#include <conio.h>
#include <iostream>
#include <map>

int GlobalVars::x_size = 10;
int GlobalVars::y_size = 10;
bool GlobalVars::is_need_new_block = true;
std::map<int, AbstractModel *> AbstractModel::list_bloks;
short GlobalVars::wide_scale = 2;

int loadBloks() {
  BlockModel *block;
  block = new BlockModel("#\n"
                         "#\n"
                         "#\n"
                         "#\n");
  block = new BlockModel("#\n"
                         "#\n"
                         "##\n");
  block = new BlockModel(" #\n"
                         " #\n"
                         "##\n");
  block = new BlockModel("##\n"
                         "##\n");
  block = new BlockModel(" ##\n"
                         "##\n");
  block = new BlockModel("##\n"
                         " ##\n");
  block = new BlockModel("###\n"
                         " #\n");
  /*
   block = new BlockModel(
       "#\n"
       "#\n"
       "#\n"
       "#\n"
       "#\n"
       "#\n"
       "#\n"
       "#\n"
       "#\n"
   );
   block = new BlockModel(
       "##\n"
       "# \n"
   );
   block= new BlockModel(
" #  #\n"
"######\n"
   );
   block = new BlockModel(
       "#\n"
   );
   block = new BlockModel(
       "#####\n"
   );
   block = new BlockModel(
       " #\n"
       "#\n"
   );
   block = new BlockModel(
       "#\n"
       "#\n"
       "#\n"
       "#\n"
   );
   block = new BlockModel(
       "##\n"
       "#\n"
       "#\n"
       "#\n"
   );*/

  return 0;
}

BlockModel *GetRandomBlock() {
  auto offset_n = rand() % AbstractModel::list_bloks.size();
  auto smth_elm = AbstractModel::list_bloks.begin();

  for (size_t cur_offset = 0; cur_offset != offset_n; ++cur_offset) {
    ++smth_elm;
  }

  return (BlockModel *) smth_elm->second;
}
BlockModel *GetBlock(int n_elm) {
  auto smth_elm = AbstractBlockModel::list_bloks.begin();

  for (size_t cur_offset = 0; cur_offset != n_elm; ++cur_offset) {
    ++smth_elm;
  }

  return (BlockModel *) smth_elm->second;
}
int main() {
  loadBloks();
  srand(time(0));
  AbstractView smth_view;
  MapController *map = new MapController();

  MapModel *map_model = new MapModel();
  map_model->SetModelSize(GlobalVars::x_size, GlobalVars::y_size);
  map->SetModel(map_model);

  char ch;
  bool isCicle = true;

  BlockModel *elm = 0;
  elm = new BlockModel(*GetRandomBlock());
  elm->SetParent(map_model);
  map->AddSecondSmthElm(elm);

  elm = new BlockModel(*GetRandomBlock());
  elm->SetParent(map_model);
  map->AddSecondSmthElm(elm);
  GlobalVars::is_need_new_block = false;
  map->StartGame();

  while (true) {
    ch = _getch();
    switch (ch) {
    case 'q':
      isCicle = false;
      break;
    // case 'w': map->MoveAbove(); break;
    case 'a':
      map->MoveLeft();
      break;
    case 's':
      map->MoveDown();
      break;
    case 'd':
      map->MoveRight();
      break;
    case 'w':
      map->ElmRotate();
      break;
    case 'r': {
      delete map_model;
      delete map;
      map = new MapController();
      map_model = new MapModel();
      map_model->SetModelSize(GlobalVars::x_size, GlobalVars::y_size);
      map->SetModel(map_model);
      elm = new BlockModel(*((BlockModel *) GetBlock(0)));
      elm->SetParent(map_model);
      map->AddSecondSmthElm(elm);

      elm = new BlockModel(*GetRandomBlock());
      elm->SetParent(map_model);
      map->AddSecondSmthElm(elm);
      GlobalVars::is_need_new_block = false;
      map->StartGame();
      break;
    }
    }
  }

  delete elm;

  system("pause");
}
