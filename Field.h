#pragma once

#include <QPushButton>


class Field : public QPushButton
{
    Q_OBJECT

    public:
        Field(uint16_t id, uint8_t size, QWidget *parent);
        ~Field();

        uint16_t getFieldID();
        void     setFieldID(uint16_t id);

        uint8_t getFieldSize();
        void    setFieldSize(uint8_t size);

        bool getFieldIsMine();
        void setFieldIsMine(bool isMine);

        int8_t getFieldNearMines();
        void   setFieldNearMines(int8_t nearMines);

        bool getFieldIsQuestionable();
        bool getFieldIsMarked();

    private:
        uint16_t _field_id;
        uint8_t  _field_size;
        bool     _field_is_mine;
        int8_t   _field_near_mines;
        bool     _field_is_questionable;
        bool     _field_is_marked;
        
    public slots:
        void mousePressEvent(QMouseEvent *e);
        void setFieldIcon();

    signals:
        void rightClicked();
};