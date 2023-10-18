#ifndef BLOCK_H
#define BLOCK_H
#include "AbstractBlock.h"
#include <list>
#include <vector>
class BlockModel :public AbstractBlockModel {
   
public:
    BlockModel(std::string data) 
     : AbstractBlockModel() {
        SetBlokShape(data);
    };
    void after_rotation() override {
        parent->data_changed();
    };
    virtual AbstractModel* GetCopy() override { return new BlockModel(*this); } ;
    const ModelIndex& GetModelIndex(const short &pos_x, const short &pos_y) override;
    void SetModelIndex(const ModelIndex & smth_data, const short &pos_x, const short &pos_y) override;;
    unsigned short GetXSize() {
        switch (cur_rotation)
        {
        case AbstractBlockModel::rotate_0:
        case AbstractBlockModel::rotate_180:
            return max_col;
        case AbstractBlockModel::rotate_90:
        case AbstractBlockModel::rotate_270:
            return max_row;
        }
    }
    unsigned short GetYSize() {
        switch (cur_rotation)
        {
        case AbstractBlockModel::rotate_0:
        case AbstractBlockModel::rotate_180:
            return max_row;
        case AbstractBlockModel::rotate_90:
        case AbstractBlockModel::rotate_270:
            return max_col;
        }
    }
    void SetBlokShape(const std::string& smth_str);

    //void cout_matr();
    inline std::pair<short, short> GetItemPosition(const short &x,const short&y);
    void SetModelSize(unsigned short col_count, unsigned short row_count) override;
    void SetParent(AbstractModel* parent)override;

    void Rotate() override {
        this->RotateRight();
    }
    void CancelRotate() override {
        this->RotateLeft();
    }

private:
    short min_col = 1000, max_col = 0;
    short  min_row = 1000, max_row = 0;
    //int chape;
    std::list <std::vector<ModelIndex>> data_model;
    //0 row - bot n row - top
    AbstractModel* parent=0;
    
};
#endif
