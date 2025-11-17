# My little Minesweeper App

![Minesweeper](https://img.shields.io/badge/Status-in_development-orange)
![Language](https://img.shields.io/badge/C++-blue)
![Framework](https://img.shields.io/badge/Qt--6.10.0-green)

In this project I am creating a fairly simple version of the Minesweeper game.

The reason for this is that I was relatively dissatisfied with the resource utilization of today's applications.

In this context, I was also able to try my hand at using [Qt](https://www.qt.io/product/qt6).

## Current status

The application currently runs in a very rudimentary way.

The game can be started directly when the application is launched. Selecting a field only opens that selected field. The number of mines in the immediate vicinity is displayed. If a mine is hit, the field is highlighted in red.

Continuing the current game is still possible.

A new game can also be started if desired.

## To-Do's

- [ ] Implement Settings
  - [x] Changing the number of rows
  - [x] Changing the number of columns
  - [x] Changing the number of mines
  - [x] Changing the Size of the Fields
  - [ ] implement Setting-Validation
- [ ] Implement Info about other things
- [ ] Implement collective dissolution of contiguous fields without a mine in the immediate vicinity
- [ ] Implement a Reaction when you encounter a mine
- [ ] Implement a Reaction on success
- [ ] Implement the usage of the right Mouse-Click to mark fields
- [ ] Usage of Icons
- [ ] Create a Bomb detection mouse
- [ ] Clean up the Code :expressionless:
