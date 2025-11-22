#include "Field.h"

#include <QMouseEvent>


Field::Field(uint16_t id, uint8_t size, QWidget *parent) :
    QPushButton(parent),
    _field_id(id),
    _field_size(size),
    _field_is_mine(false),
    _field_near_mines(-1),
    _field_is_questionable(false),
    _field_is_marked(false)    
{
    connect(this, &Field::rightClicked, this, &Field::setFieldIcon);
}

Field::~Field(){}

uint16_t Field::getFieldID()            {return _field_id;}
void     Field::setFieldID(uint16_t id) {_field_id = id;}

uint8_t Field::getFieldSize()             {return _field_size;}
void    Field::setFieldSize(uint8_t size) {_field_size = size;}

bool Field::getFieldIsMine()             {return _field_is_mine;}
void Field::setFieldIsMine(bool isMine) {_field_is_mine = isMine;}

int8_t Field::getFieldNearMines()                  {return _field_near_mines;}
void   Field::setFieldNearMines(int8_t nearMines) {_field_near_mines = nearMines;}

bool Field::getFieldIsQuestionable()           {return _field_is_questionable;}
void Field::setFieldIsQuestionable(bool value) {_field_is_questionable = value;}

bool Field::getFieldIsMarked()           {return _field_is_marked;}
void Field::setFieldIsMarked(bool value) {_field_is_marked = value;}

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
    if(_field_is_marked)
    {
        _field_is_questionable = true;
        _field_is_marked = false;
        
        setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\questionmark.png"));
        setIconSize(QSize(_field_size*3/4,_field_size*3/4));

    }else if (_field_is_questionable)
    {
        _field_is_questionable = false;

        setIcon(QIcon());
        
    }else{
        _field_is_marked = true;
        
        setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\flag.png"));
        setIconSize(QSize(_field_size*3/4,_field_size*3/4));
    }
}