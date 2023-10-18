#include "AbstractBlock.h"

AbstractBlockModel::AbstractBlockModel() {
    list_bloks.insert({ list_bloks.size(),this });
}

AbstractBlockModel::types_rotation AbstractBlockModel::GetRotateBlockLeft() {
    switch (cur_rotation)
    {
    case AbstractBlockModel::rotate_0:
        return types_rotation::rotate_90;
        break;
    case AbstractBlockModel::rotate_90:
        return types_rotation::rotate_180;
        break;
    case AbstractBlockModel::rotate_180:
        return types_rotation::rotate_270;
        break;
    case AbstractBlockModel::rotate_270:
        return types_rotation::rotate_0;
        break;
    default:
        break;
    }
}

AbstractBlockModel::types_rotation AbstractBlockModel::GetRotateBlockRight() {
    switch (cur_rotation)
    {
    case AbstractBlockModel::rotate_0:
        return types_rotation::rotate_270;
        break;
    case AbstractBlockModel::rotate_270:
        return types_rotation::rotate_180;
        break;
    case AbstractBlockModel::rotate_180:
        return types_rotation::rotate_90;
        break;
    case AbstractBlockModel::rotate_90:
        return types_rotation::rotate_0;
        break;
    default:
        break;
    }
}