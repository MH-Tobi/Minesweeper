#include "MainWindow.h"
#include <cstdint>
#include <array>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWindow>
#include <QAbstractScrollArea>
#include <QStyle>

#include <random>

#include <QHBoxLayout>
#include <QGroupBox>
#include <QList>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), _rows(10), _columns(20), _sum_mines(50), _Playfield(new QWidget(this))//, _Fields(0)
{
    QHBoxLayout *_Windowlayout = new QHBoxLayout;
    _Windowlayout->setContentsMargins(5, 5, 5, 5);
    setWindowTitle("Minesweeper");
    createMenu();
    _Windowlayout->setMenuBar(_MenuBar);
    _Windowlayout->addWidget(_Playfield);    

    NewGame();

    this->setLayout(_Windowlayout);
}

void MainWindow::createMenu()
{
    _MenuBar = new QMenuBar;

    _app_menu = new QMenu("App", this);
    _new_game_action = _app_menu->addAction("New");
    _settings_action = _app_menu->addAction("Settings");
    _quit_action = _app_menu->addAction("Quit");

    _MenuBar->addMenu(_app_menu);

    _info_menu = new QMenu("Info", this);

    _qt_info_action = _info_menu->addAction("About Qt");
    _other_info_action = _info_menu->addAction("About Other");

    _MenuBar->addMenu(_info_menu);

    connect(_new_game_action, &QAction::triggered, this, &MainWindow::NewGame);
    connect(_settings_action, &QAction::triggered, this, &MainWindow::Settings);
    connect(_quit_action, &QAction::triggered, this, &MainWindow::Quit);
    connect(_qt_info_action, &QAction::triggered, this, &MainWindow::AboutQt);
    connect(_other_info_action, &QAction::triggered, this, &MainWindow::AboutOther);
}

void MainWindow::Quit()
{
    QApplication::instance()->quit();
}

void MainWindow::AboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::NewGame()
{
    _Playfield->resize(FIELD_SIZE*_columns, FIELD_SIZE*_rows);
    
    _GameStarted=false;
    
    createFields();

    this->setFixedSize(_Playfield->width()+10, _Playfield->height()+45);
}

void MainWindow::createFields()
{
    for (QPushButton *field : _Fields)
    {
        field->close();
    }
    
    
    _Fields.clear();

    std::uint16_t k;
    std::uint16_t l;
    
    for (uint16_t i = 0; i < _rows*_columns; i++)
    {
        k = i/_columns;
        l = i % _columns;
        QPushButton *Button = new QPushButton(_Playfield);
        _Fields.append(Button);
        
        Button->setFixedSize(FIELD_SIZE, FIELD_SIZE);
        Button->move(l*FIELD_SIZE, k*FIELD_SIZE);
        Button->show();
        
        connect(Button, &QPushButton::clicked, this, [this, i]{ fieldClicked(i); });
    }
}

void MainWindow::fieldClicked(uint16_t field)
{
    if (_GameStarted)
    {
        if (_Fields[field]->accessibleName() == "9")
        {
            _Fields[field]->setStyleSheet("background-color: red;");
            _Fields[field]->setFlat(true);
            _Fields[field]->setEnabled(false);
        }else{
            _Fields[field]->setText(_Fields[field]->accessibleName());
            _Fields[field]->setFlat(true);
            _Fields[field]->setDisabled(true);
        }
        
    }else{
        startGame(field);
        _GameStarted = true;
        _Fields[field]->setFlat(true);
        _Fields[field]->setDisabled(true);
        _Fields[field]->setText("0");
    }
    
}

void MainWindow::startGame(uint16_t field)
{
    std::int16_t unallowed_Fields[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

    if (((field/_columns) > 0) && ((field/_columns) < _rows-1)) // if selected field is between the top and bottom row
    {
        if (((field % _columns) > 0) && ((field % _columns) < _columns))// if selected field is between the left and right column
        {
            unallowed_Fields[0] = field - _columns - 1;
            unallowed_Fields[1] = field - _columns;
            unallowed_Fields[2] = field - _columns + 1;
            unallowed_Fields[3] = field - 1;
            unallowed_Fields[4] = field;
            unallowed_Fields[5] = field + 1;
            unallowed_Fields[6] = field + _columns - 1;
            unallowed_Fields[7] = field + _columns;
            unallowed_Fields[8] = field + _columns + 1;
        }else if ((field % _columns) > 0)   // if selected field is in the right column
        {
            unallowed_Fields[0] = field - _columns - 1;
            unallowed_Fields[1] = field - _columns;
            unallowed_Fields[2] = field - 1;
            unallowed_Fields[3] = field;
            unallowed_Fields[4] = field + _columns - 1;
            unallowed_Fields[5] = field + _columns;
        }else{  // if selected field is in the left column
            unallowed_Fields[0] = field - _columns;
            unallowed_Fields[1] = field - _columns + 1;
            unallowed_Fields[2] = field;
            unallowed_Fields[3] = field + 1;
            unallowed_Fields[4] = field + _columns;
            unallowed_Fields[5] = field + _columns + 1;
        }
    }else if ((field/_columns) > 0) // if selected field is in the bottom row
    {
        if (((field % _columns) > 0) && ((field % _columns) < _columns))// if selected field is between the left and right column
        {
            unallowed_Fields[0] = field - _columns - 1;
            unallowed_Fields[1] = field - _columns;
            unallowed_Fields[2] = field - _columns + 1;
            unallowed_Fields[3] = field - 1;
            unallowed_Fields[4] = field;
            unallowed_Fields[5] = field + 1;
        }else if ((field % _columns) > 0)   // if selected field is in the right column
        {
            unallowed_Fields[0] = field - _columns - 1;
            unallowed_Fields[1] = field - _columns;
            unallowed_Fields[2] = field - 1;
            unallowed_Fields[3] = field;
        }else{  // if selected field is in the left column
            unallowed_Fields[0] = field - _columns;
            unallowed_Fields[1] = field - _columns + 1;
            unallowed_Fields[2] = field;
            unallowed_Fields[3] = field + 1;
        }
    }else{  // if selected field is in the top row
        if (((field % _columns) > 0) && ((field % _columns) < _columns))// if selected field is between the left and right column
        {
            unallowed_Fields[0] = field - 1;
            unallowed_Fields[1] = field;
            unallowed_Fields[2] = field + 1;
            unallowed_Fields[3] = field + _columns - 1;
            unallowed_Fields[4] = field + _columns;
            unallowed_Fields[5] = field + _columns + 1;
        }else if ((field % _columns) > 0)   // if selected field is in the right column
        {
            unallowed_Fields[0] = field - 1;
            unallowed_Fields[1] = field;
            unallowed_Fields[2] = field + _columns - 1;
            unallowed_Fields[3] = field + _columns;
        }else{  // if selected field is in the left column
            unallowed_Fields[0] = field + 1;
            unallowed_Fields[1] = field + _columns - 1;
            unallowed_Fields[2] = field + _columns;
            unallowed_Fields[3] = field + _columns + 1;
        }
    }

    std::uint16_t Mines[_sum_mines];
    
    std::uint16_t count_mines = 0;
    std::uint16_t column_range[2] = {0,0};
    std::uint16_t row_range[2] = {0,0};
   
    std::uint16_t Map[_rows][_columns];
    std::uint16_t f = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint16_t> distrib(0, ((_rows*_columns)-1));

    while (f < _sum_mines)
    {
        std::uint16_t Val = distrib(gen);
        std::uint16_t k = Val/_columns;
        std::uint16_t l = Val % _columns;
        bool skip = false;

        for (std::uint16_t i = 0; i < 9; i++)
        {
            if (Val == unallowed_Fields[i])
            {
                skip = true;
            }
        }

        if (!skip)
        {
            if (f>0)
            {
                Mines[f] = Val;
                f++;
                Map[k][l] = 9;
                for (std::uint16_t i = 0; i < f-1; i++)
                {
                    if (Val == Mines[i])
                    {
                        f--;
                    }
                }
            }else{
                Mines[f] = Val;
                f++;
                Map[k][l] = 9;
            }
        }
    }

    for (std::uint16_t i = 0; i < _rows; i++)
    {
        for (std::uint16_t j = 0; j < _columns; j++)
        {
            if (i > 0 && i < (_rows-1))
            {
                row_range[0] = i-1;
                row_range[1] = i+1;
            }else if (i > 0)
            {
                row_range[0] = i-1;
                row_range[1] = i;
            }else{
                row_range[0] = i;
                row_range[1] = i+1;
            }

            if (j > 0 && j < (_columns-1))
            {
                column_range[0] = j-1;
                column_range[1] = j+1;
            }else if (j > 0)
            {
                column_range[0] = j-1;
                column_range[1] = j;
            }else{
                column_range[0] = j;
                column_range[1] = j+1;
            }

            count_mines = 0;

            for (std::uint16_t m = row_range[0]; m <= row_range[1]; m++)
            {
                for (std::uint16_t n = column_range[0]; n <= column_range[1]; n++)
                {
                    if (Map[m][n] == 9)
                    {
                        count_mines++;
                    }
                }
            }
            if (Map[i][j] != 9)
            {
                _Fields[i*_columns+j]->setAccessibleName(QString::number(count_mines));
                //_Fields[i*_columns+j]->setText(QString::number(count_mines));
            }else{
                _Fields[i*_columns+j]->setAccessibleName("9");
                //_Fields[i*_columns+j]->setText("9");
            }
        }
    }
}