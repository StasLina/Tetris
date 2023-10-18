#include "Block.h"

const ModelIndex& BlockModel::GetModelIndex(const short& pos_x, const short& pos_y) {
    std::vector<ModelIndex>::iterator elm;
    auto pair=GetItemPosition(pos_x, pos_y);
    short test_x = pair.first;
    short test_y = pair.second;
    auto row = data_model.begin();
    int n;
    for (n = 0; n != test_y; ++n) {
        ++row;
    }
    elm = row->begin();
    for (n = 0; n != test_x; ++n) {
        ++elm;
    }
    return *elm;
}

void BlockModel::SetModelIndex(const ModelIndex& smth_data, const short& pos_x, const short& pos_y) {
    auto row = data_model.begin();
    int n;
    for (n = 0; n != pos_y; ++n) {
        ++row;
    }
    auto elm = row->begin();
    for (n = 0; n != pos_x; ++n) {
        ++elm;
    }
    *elm = smth_data;
    return;
}

void BlockModel::SetBlokShape(const std::string& smth_str) {
    int cur_row = 0, cur_col = 0;
    auto smth_char = smth_str.begin();
    auto smth_char_end = smth_str.end();

    //определяем размер
    while (smth_char != smth_char_end) {
        ++cur_col;
        if (*smth_char == '#') {
            if (max_col < cur_col) {
                max_col = cur_col;
            }
            if (min_col > cur_col) {
                min_col = cur_col;
            }
        }
        if (*smth_char == '\n') {
            //new line
            ++cur_row;
            if (max_row < cur_row) {
                max_row = cur_row;
            }
            if (min_row > cur_row) {
                min_row = cur_row;
            }
            cur_col = 0;
        }
        ++smth_char;
    }
    this->SetModelSize(max_col, max_row);

    smth_char = smth_str.begin();
    cur_col = 0;
    cur_row = 0;

    while (smth_char != smth_char_end) {
        switch (*smth_char) {
        case '#':
            SetModelIndex('#', cur_col, cur_row);
            break;
        case '\n':
            cur_col = -1;
            ++cur_row;
            break;
        default:
            break;
        }
        ++cur_col;
        ++smth_char;
    }
    //cout_matr();
}

inline std::pair<short, short> BlockModel::GetItemPosition(const short&x,const short &y) {
    switch (this->cur_rotation) {
    case AbstractBlockModel::types_rotation::rotate_0:
        return { x,y };
    case AbstractBlockModel::types_rotation::rotate_90:
        return { y,max_row-x-1 };
    case AbstractBlockModel::types_rotation::rotate_180:
        return { max_col - x - 1, max_row - y - 1 };
    case AbstractBlockModel::types_rotation::rotate_270:
        return { max_col - y - 1, x };
    }
    /*case AbstractBlockModel::types_rotation::rotate_0:
        return { x,y };
    case AbstractBlockModel::types_rotation::rotate_90:
        return { y,x };
    case AbstractBlockModel::types_rotation::rotate_180:
        return { max_col - x - 1, max_row - y - 1 };
    case AbstractBlockModel::types_rotation::rotate_270:
        return { max_col - y - 1, max_row - x - 1 };
    }*/
}

void BlockModel::SetModelSize(unsigned short col_count, unsigned short row_count) {
    data_model.resize(row_count);
    auto smth_row = data_model.begin();
    auto smth_row_end = data_model.end();
    while (smth_row != smth_row_end) {
        smth_row->resize(col_count);
        ++smth_row;
    }
}

void BlockModel::SetParent(AbstractModel* parent) {
    this->parent = parent;
}
