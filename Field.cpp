#include "Field.h"
#include <QPushButton>
#include <QWidget>
#include "MainWindow.h"


Field::Field(uint16_t id, uint8_t size, QWidget *parent, MainWindow *game) : QPushButton(parent), _FieldID(id), _FieldSize(size), _FieldnearMines(-1)
{
    connect(this, &QPushButton::clicked, this, fieldClicked);
}

Field::~Field()
{}

uint16_t Field::getFieldID()        {return _FieldID;}
uint8_t  Field::getFieldSize()      {return _FieldSize;}
bool     Field::getFieldIsMine()    {return _FieldisMine;}
uint8_t  Field::getFieldNearMines() {return _FieldnearMines;}

void Field::setFieldID(uint16_t id)               {_FieldID = id;}
void Field::setFieldSize(uint8_t size)            {_FieldSize = size;}
void Field::setFieldIsMine(bool is_mine)          {_FieldisMine = is_mine;}
void Field::setFieldNearMines(int8_t near_mines)  {_FieldnearMines = near_mines;}

void Field::fieldClicked()
{
    if (_FieldnearMines == -1)
    {
        _FieldnearMines = 0;
        _FieldisMine = false;
    }

    if (_FieldisMine)
    {
        this->setStyleSheet("background-color: red;");
        this->setFlat(true);
        this->setEnabled(false);
    }else{
        this->setText(QString::number(this->getFieldNearMines()));
        this->setFlat(true);
        this->setDisabled(true);
    }
}