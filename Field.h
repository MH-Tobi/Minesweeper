#pragma once

#include <QPushButton>
#include "MainWindow.h"


class Field : public QPushButton
{
    Q_OBJECT

    public:
        Field(uint16_t id, uint8_t size, QWidget *parent);
        ~Field();

        uint16_t getFieldID();
        void setFieldID(uint16_t id);

        uint8_t getFieldSize();
        void setFieldSize(uint8_t size);

        bool getFieldIsMine();
        void setFieldIsMine(bool is_mine);

        int8_t getFieldNearMines();
        void setFieldNearMines(int8_t near_mines);

        bool getFieldIsQuestionable();
        bool getFieldIsMarked();

        uint16_t _FieldID;
        
    private:
        uint8_t _FieldSize;
        bool _FieldisMine;
        int8_t _FieldnearMines;

        bool _FieldIsQuestionable;
        bool _FieldIsMarked;
        
    public slots:
        void mousePressEvent(QMouseEvent *e);
        void setFieldIcon();

    signals:
        void rightClicked();
};