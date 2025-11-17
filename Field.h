#pragma once

#include <QPushButton>
#include "MainWindow.h"


class Field : public QPushButton
{
    Q_OBJECT

    public:
        Field(uint16_t id, uint8_t size, QWidget *parent, MainWindow *game);
        ~Field();

        uint16_t getFieldID();
        void setFieldID(uint16_t id);

        uint8_t getFieldSize();
        void setFieldSize(uint8_t size);

        bool getFieldIsMine();
        void setFieldIsMine(bool is_mine);

        int8_t getFieldNearMines();
        void setFieldNearMines(int8_t near_mines);

        uint16_t _FieldID;
        
    private:
        uint8_t _FieldSize;
        bool _FieldisMine;
        int8_t _FieldnearMines;
        
    public slots:
};