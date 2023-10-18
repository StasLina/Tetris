#include "map.h"

MapController::MapController() {
    this->x = GlobalVars::x_size;
    this->y = GlobalVars::y_size;
    map_model = 0;
}

void MapController::SetModel(MapModel* smth_model) {
    map_model = smth_model;
    smth_model->SetController(this);
}


void MapController::AddFirstSmthElm(AbstractModel* elm) {
    if (is_game_over)return;
    this->elm.smth_elm_model = elm;
    short wide = elm->GetXSize();
    short height = elm->GetYSize();
    if (proverka_size(wide, height)) {
        this->elm.cur.x = (x / 2) - (wide / 2);
        if (this->elm.cur.x < 0) {
            this->elm.cur.x = 0;
        }
        this->elm.cur.y = y+my_indent.top;
        this->elm.min.x = 0;
        this->elm.min.y = 0;
        this->elm.max.x = x - wide;
        this->elm.max.y = y - height;
    }
    else {
        //game over
    }
}
void MapController::AddSecondSmthElm(AbstractModel* elm) {

    if (is_game_over)return;
    if (this->elm.smth_elm_model != 0)
        delete this->elm.smth_elm_model;
    this->elm = elm2;
    this->elm2.smth_elm_model = elm;
    short wide = elm->GetXSize();
    short height = elm->GetYSize();
    if (proverka_size(wide, height)) {
        this->elm2.cur.x = (x / 2) - (wide / 2);
        if (this->elm2.cur.x < 0) {
            this->elm2.cur.x = 0;
        }
        this->elm2.cur.y = y + my_indent.top;
        this->elm2.min.x = 0;
        this->elm2.min.y = 0;
        this->elm2.max.x = x - wide;
        this->elm2.max.y = y - height;
    }
}
void MapController::Draw() {
    block_draw.lock();
    system("cls");
    if (is_game_over) {
        std::cout << "Game Oveeeerrrrr press r to restart"<<std::endl;
        block_draw.unlock();
        return;
    }
    std::string res_map_str;
    std::list<std::string> res_map;

    char fill_top=' ';

    std::string app_str_right = "\tScore: " + std::to_string(this->score) + "\n"
        + "\tNext block:\n";
    

//Next block
    auto elm_row_end = elm2.smth_elm_model->GetYSize();//elm.smth_elm_model->GetYSize();
    auto elm_col_end = elm2.smth_elm_model->GetXSize();
    int fix_row, fix_col;
    for (short cur_row = 0; cur_row != elm_row_end; ++cur_row) {
        app_str_right += "\t";
        for (short cur_col = 0; cur_col != elm_col_end; ++cur_col) {
            app_str_right += elm2.smth_elm_model->GetModelIndex(cur_col, cur_row).data;
        }
        app_str_right += "\n";
    }
    app_str_right += "\t level: " + std::to_string(lvl);

//�������
    std::list<std::string> app_str;
    std::string::iterator smthsymb, smthsymb_end;
    smthsymb = app_str_right.begin();
    smthsymb_end = app_str_right.end();
    std::string temp_str;
    temp_str = "";
    while (smthsymb != smthsymb_end) {
        if (*smthsymb == '\n') {
            app_str.push_back(temp_str);
            temp_str = "";
        }
        else {
            temp_str += *smthsymb;
        }
        ++smthsymb;
    }
    app_str.push_back(temp_str);

    std::list<std::string>::iterator app_str_it =app_str.begin(), app_str_end= app_str.end();
    

//top indent
    char fill_char = '$';
    for (int j = 0; j != my_indent.top-1; ++j) {
        res_map_str = "";
        for (int i = 0; i != my_indent.left-1; ++i) {
            res_map_str += fill_char;
        }
        res_map_str += '$';

        for (short cur_col = 0; cur_col != x; ++cur_col) {
            for (short i = 0; i != GlobalVars::wide_scale; ++i)
                res_map_str += fill_top;
        }
        res_map_str += '$';
        for (int i = 1; i != my_indent.right; ++i) {
            res_map_str += fill_char;
        }
        if (app_str_it != app_str_end) {
            res_map_str += *app_str_it++;
        }
        res_map.push_back(res_map_str);
        //res_map += '\n';
    }
//top indent last
    res_map_str = "";
    for (int i = 0; i != my_indent.left - 1; ++i) {
        res_map_str += '-';
    }
    res_map_str += '$';
    for (short cur_col = 0; cur_col != x; ++cur_col) {
        for (short i = 0; i != GlobalVars::wide_scale; ++i)
        res_map_str += fill_top;
    }
    res_map_str += '$';
    for (int i = 1; i != my_indent.right; ++i) {
        res_map_str += '-';
    }
    if (app_str_it != app_str_end) {
        res_map_str += *app_str_it++;
    }
    res_map.push_back(res_map_str);
    //res_map += '\n';

//�����
    for (short cur_row = y-1; cur_row != -1; --cur_row) {
        res_map_str = "";
        for (int i = 0; i != my_indent.left-1; ++i) {
            res_map_str += fill_char;
        }
        res_map_str += '$';
        for (short cur_col = 0; cur_col != x; ++cur_col) {
            for (short i = 0; i != GlobalVars::wide_scale; ++i)
            res_map_str += map_model->GetModelIndex(cur_col, cur_row).data;
        }
        res_map_str += '$';
        for (int i = 1; i != my_indent.right; i++) {
            res_map_str += fill_char;
        }
        if (app_str_it != app_str_end) {
            res_map_str += *app_str_it++;
        }
        //res_map += '\n';
        res_map.push_back(res_map_str);
    }
//indent bot
    for (int j = 0; j != my_indent.bot; j++) {
        res_map_str = "";
        for (int i = 0; i != my_indent.left-1; i++) {
            res_map_str += fill_char;
        }
        res_map_str += '$';
        for (short cur_col = 0; cur_col != x; ++cur_col) {
            for (short i = 0; i != GlobalVars::wide_scale; ++i)
            res_map_str += '$';
        }
        res_map_str += '$';
        for (int i = 1; i != my_indent.right; i++) {
            res_map_str += fill_char;
        }
        //res_map += '\n';
        res_map.push_back(res_map_str);
    }


    elm_row_end = get_size_y_into_visible();//elm.smth_elm_model->GetYSize();
    elm_col_end = elm.smth_elm_model->GetXSize();
    fix_row = 0;
    fix_col = 0;
    
    
    
    app_str_it = app_str.begin();
    int add_counter_app_str = 0;

    
    
    for (short cur_row = 0; cur_row != elm_row_end; ++cur_row) {
        fix_row = y - 1 - elm.cur.y - cur_row+ my_indent.top;

        auto smth_row = res_map.begin();
        for (short smth_i = 0; smth_i != fix_row; ++smth_i, ++smth_row);
        for (short cur_col = 0; cur_col != elm_col_end; ++cur_col) {
            fix_col = +cur_col + elm.cur.x;
            const char& symb = elm.smth_elm_model->GetModelIndex(cur_col, cur_row).data;
            if (symb != ' ') {
                for (int scale_i = 0; scale_i != GlobalVars::wide_scale;++scale_i) {
                    smth_row->at(
                        my_indent.left + GlobalVars::wide_scale * fix_col+ scale_i) = symb;
                }
            }
        }
    }


    auto smth_row = res_map.begin();
    auto smth_row_end = res_map.end();
    while (smth_row != smth_row_end) {
        std::cout << *smth_row << std::endl;
        ++smth_row;
    }
   
    if (GlobalVars::need_new_block) {
        auto n = rand() % AbstractModel::list_bloks.size();
        auto smth_elm = AbstractModel::list_bloks.begin();
        for (size_t i = 0; i != n; ++i) {
            ++smth_elm;
        }
        auto elm = smth_elm->second->GetCopy();
        elm->SetParent(map_model);
        AddSecondSmthElm(elm);
        GlobalVars::need_new_block = false;
    }
    block_draw.unlock();
}

void MapController::MoveLeft() {
    if (is_game_over)return;
    was_user_input = true;
    if (VerifyUpdate()) {
        pos new_pos = elm.cur;
        --new_pos.x;
        if (proverka_cancel_moving_left(new_pos) == false) {
            elm.cur = new_pos;
        }
    }
    Draw();
}

void MapController::MoveRight() {
    if (is_game_over)return;
    was_user_input = true;
    if (VerifyUpdate()) {
        pos new_pos = elm.cur;
        ++new_pos.x;
        if (proverka_cancel_moving_right(new_pos) == false) {
            elm.cur = new_pos;
        }
    }
    Draw();
}

void MapController::MoveDown(bool user) {
    move_down.lock();
    if (is_game_over) {
        move_down.unlock();
        return;
    }
    if(user)was_user_input = true;
    if(VerifyUpdate()) {
        pos new_pos = elm.cur;
        --new_pos.y;
        if (proverka_cancel_moving_down(new_pos) == false) {
            elm.cur = new_pos;
        }
    }
    if(user)++score;
    Draw();
    move_down.unlock();
}

void MapController::MoveAbove() {
    if (is_game_over)return;
    if (VerifyUpdate()) {
        pos new_pos = elm.cur;
        ++new_pos.y;
        if (new_pos.y <= elm.max.y) {
            elm.cur = new_pos;
        }
    }
}

void MapController::data_changed() {
    if (is_game_over)return;
    elm.swap();
    auto old_pos_cur = elm.cur;

    if (elm.cur.x < elm.min.x) {
        elm.cur.x = elm.min.x;
    }
    if (elm.cur.y < elm.min.y) {
        elm.cur.y = elm.min.y;
    }
    if (elm.cur.x > elm.max.x) {
        elm.cur.x = elm.max.x;
    }
    if (new_shape_exsist()) {
        VerifyUpdate();
        Draw();
    }
    else {
        elm.swap();
        elm.smth_elm_model->CancelRotate();
        elm.cur = old_pos_cur;
    }
    
}

bool MapController::VerifyUpdate() {
    if (proverka_cancel_moving()) {
        if (first_zero == false) {
            first_zero = true;
            return true;
        }
        else {
            first_zero = false;
            save_block_to_map();
            proverka_rows();
            if (map_model->isMax()) {
                //gamve over
                is_game_over = true;
            }
            else {
                GlobalVars::need_new_block = true;
            }
            ++count_placed_bloks;
            if ((count_placed_bloks % 5)==0) {
                ++lvl;
            }
            return false;
        }
    }
    return true;
}

bool MapController::proverka_cancel_moving() {
    if (elm.cur.y == 0) {
        return true;
    }
    auto size_x = elm.smth_elm_model->GetXSize();
    auto size_y = get_size_y_into_map();//get_size_y_into_visible();//elm.smth_elm_model->GetYSize();
    for (short c = 0; c != size_x; ++c) {
        for (short r = 0; r != size_y; ++r) {
            const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
            if (char_block != ' ') {
                const char char_map = map_model->GetModelIndex(elm.cur.x + c, elm.cur.y + r - 1).data;
                if (char_map != ' ')
                    return true;
                break;
            }
        }
    }
    return false;
}

bool MapController::save_block_to_map() {
    auto size_x = elm.smth_elm_model->GetXSize();
    auto size_y = get_size_y_into_map();//->GetYSize();
    for (short c = 0; c != size_x; ++c) {
        for (short r = 0; r != size_y; ++r) {
            const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
            if(char_block!=' ')
            map_model->SetModelIndex(char_block, elm.cur.x + c, elm.cur.y + r);
        }
    }
    return map_model->SetMax(elm.cur.y + size_y - 1);

}

void MapController::proverka_rows() {
    auto size_x = map_model->GetXSize();
    auto size_y = get_size_y_into_map(); //elm.smth_elm_model->GetYSize(); //get_size_y_into_map();
    bool perverka = true;
    int count_del_row = 0;
    for (short r = 0; r != size_y; ++r) {
        perverka = true;
        for (short c = 0; c != size_x; ++c) {
            const char& char_map = map_model->GetModelIndex(c, elm.cur.y + r-count_del_row).data;
            if (char_map == ' ') {
                perverka = false;
            }
        }
        if (perverka) {
            map_model->DeleteRow(elm.cur.y + r - count_del_row);
            ++count_del_row;
            score+=10;
        }
    }
}

bool MapController::proverka_cancel_moving_down(const pos& smth_pos) {
    if (smth_pos.y < elm.min.y) {
        return true;
    }
    if (smth_pos.y >= elm.min.y) {
        auto size_x = elm.smth_elm_model->GetXSize();
        auto size_y = get_size_y_into_map();//elm.smth_elm_model->GetYSize();
        for (short c = 0; c != size_x; ++c) {
            for (short r = 0; r != size_y; ++r) {
                const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
                if (char_block != ' ') {
                    const char char_map = map_model->GetModelIndex(elm.cur.x + c, elm.cur.y + r - 1).data;
                    if (char_map != ' ')return true;
                    break;
                }
            }
        }
    }
    return false;
}

bool MapController::proverka_cancel_moving_left(const pos& smth_pos) {
    if (smth_pos.x < elm.min.x) {
        return true;
    }
    if (smth_pos.x == elm.min.x) {
        return false;
    }
    if (smth_pos.x > elm.min.x) {
        auto size_x = this->elm.smth_elm_model->GetXSize();
        auto size_y = get_size_y_into_map();//elm.smth_elm_model->GetYSize(); //get_size_y_into_map();
        for (short r = 0; r != size_y; ++r) {
            for (short c = 0; c != size_x; ++c) {
                const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
                if (char_block != ' ') {
                    const char char_map = map_model->GetModelIndex(elm.cur.x + c - 1, elm.cur.y + r).data;
                    if (char_map != ' ')return true;
                    break;
                }
            }
        }
    }
    return false;
}

bool MapController::proverka_cancel_moving_right(const pos& smth_pos) {
    if (smth_pos.x > elm.max.x) {
        return true;
    }
    if (smth_pos.x == elm.max.x) {
        return false;
    }
    if (smth_pos.x < elm.max.x) {
        auto size_x = this->elm.smth_elm_model->GetXSize();
        auto size_y = get_size_y_into_map();//elm.smth_elm_model->GetYSize(); //
        for (short r = 0; r != size_y; ++r) {
            for (short c = size_x - 1; c != -1; --c) {
                const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
                if (char_block != ' ') {
                    const char char_map = map_model->GetModelIndex(elm.cur.x + c + 1, elm.cur.y + r).data;
                    if (char_map != ' ')return true;
                    break;
                }
            }
        }
    }
    return false;
}

unsigned short MapController::get_size_y_into_map() {
    auto size_y = elm.smth_elm_model->GetYSize();
    short correction_z = 0;//���� ����
    int max = map_model->GetYSize() - 1;//elm.max.y + my_indent.top;
    if (elm.cur.y > max) {
        return 0;
    }
    else {
        auto diff = max - elm.cur.y + 1;
        if (diff < size_y) {
            size_y = diff;
        }
    }
    return size_y;

}

unsigned short MapController::get_size_y_into_visible() {
    auto size_y = elm.smth_elm_model->GetYSize();
    short correction_z = 0;//���� ����
    int max = map_model->GetYSize() + my_indent.top - 1;//elm.max.y + my_indent.top;
    if (elm.cur.y > max) {
        return 0;
    }
    else {
        auto diff = max - elm.cur.y + 1;
        if (diff < size_y) {
            size_y = diff;
        }
    }
    return size_y;
}

bool MapController::new_shape_exsist() {

    auto size_x = elm.smth_elm_model->GetXSize();
    auto size_y = get_size_y_into_map();

    bool proverka = true;
    for (short c = 0; c != size_x; ++c) {
        for (short r = 0; r != size_y; ++r) {
            const char& char_block = elm.smth_elm_model->GetModelIndex(c, r).data;
            if (char_block != ' ') {
                const char char_map = map_model->GetModelIndex(elm.cur.x + c, elm.cur.y + r).data;
                if (char_map != ' ') {
                    proverka = false;
                    c = size_x - 1;
                    break;
                }

            }
        }
    }
    return proverka;
}
