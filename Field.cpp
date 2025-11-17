#include "Field.h"
#include <QPushButton>
#include <QWidget>
#include "MainWindow.h"


Field::Field(uint16_t id, uint8_t size, QWidget *parent) : QPushButton(parent), _FieldID(id), _FieldSize(size), _FieldnearMines(-1)
{}

Field::~Field()
{}

uint16_t Field::getFieldID()        {return _FieldID;}
uint8_t  Field::getFieldSize()      {return _FieldSize;}
bool     Field::getFieldIsMine()    {return _FieldisMine;}
int8_t  Field::getFieldNearMines() {return _FieldnearMines;}

void Field::setFieldID(uint16_t id)               {_FieldID = id;}
void Field::setFieldSize(uint8_t size)            {_FieldSize = size;}
void Field::setFieldIsMine(bool is_mine)          {_FieldisMine = is_mine;}
void Field::setFieldNearMines(int8_t near_mines)  {_FieldnearMines = near_mines;}

