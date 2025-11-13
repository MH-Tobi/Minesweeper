#pragma once

#include <QPushButton>
#include <QWidget>
#include "MainWindow.h"

//class QWidget;
//class QPushButton;
class Field : public QWidget , public QPushButton
{
    public:
        Field(uint16_t id, uint8_t size, QWidget *parent);
        ~Field();

        uint16_t getFieldID();
        void setFieldID(uint16_t id);

        uint8_t getFieldSize();
        void setFieldSize(uint8_t size);

        bool getFieldIsMine();
        void setFieldIsMine(bool is_mine);

        uint8_t getFieldNearMines();
        void setFieldNearMines(uint8_t near_mines);


    private:

        uint16_t _FieldID;
        uint8_t _FieldSize;
        bool _FieldisMine;
        uint8_t _FieldnearMines;
        QPushButton *_Button;


};