#include "Field.h"
#include <QPushButton>
#include <QWidget>
#include <QMouseEvent>
#include "MainWindow.h"


Field::Field(uint16_t id, uint8_t size, QWidget *parent) :
    QPushButton(parent),
    _FieldID(id),
    _FieldSize(size),
    _FieldisMine(false),
    _FieldnearMines(-1),
    _FieldIsQuestionable(false),
    _FieldIsMarked(false)    
{
    connect(this, &Field::rightClicked, this, &Field::setFieldIcon);
}

Field::~Field(){}

uint16_t Field::getFieldID()            {return _FieldID;}
void     Field::setFieldID(uint16_t id) {_FieldID = id;}

uint8_t Field::getFieldSize()             {return _FieldSize;}
void    Field::setFieldSize(uint8_t size) {_FieldSize = size;}

bool Field::getFieldIsMine()             {return _FieldisMine;}
void Field::setFieldIsMine(bool is_mine) {_FieldisMine = is_mine;}

int8_t Field::getFieldNearMines()                  {return _FieldnearMines;}
void   Field::setFieldNearMines(int8_t near_mines) {_FieldnearMines = near_mines;}

bool Field::getFieldIsQuestionable() {return _FieldIsQuestionable;};
bool Field::getFieldIsMarked()       {return _FieldIsMarked;};

void Field::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        emit rightClicked();
    }else{
        emit clicked();
    }
}

void Field::setFieldIcon()
{
    if(_FieldIsMarked)
    {
        _FieldIsQuestionable = true;
        _FieldIsMarked = false;
        
        setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\questionmark.png"));
        setIconSize(QSize(_FieldSize*3/4,_FieldSize*3/4));

    }else if (_FieldIsQuestionable)
    {
        _FieldIsQuestionable = false;

        setIcon(QIcon());
        
    }else{
        _FieldIsMarked = true;
        
        setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\flag.png"));
        setIconSize(QSize(_FieldSize*3/4,_FieldSize*3/4));
    }
}