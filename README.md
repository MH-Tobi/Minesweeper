# My little Minesweeper App

![Minesweeper](https://img.shields.io/badge/Status-in_development-orange)
![Language](https://img.shields.io/badge/C++-blue)
![Framework](https://img.shields.io/badge/Qt--6.10.0-green)

In this project I am creating a fairly simple version of the Minesweeper game.

The reason for this is that I was relatively dissatisfied with the resource utilization of today's applications.

In this context, I was also able to try my hand at using [Qt](https://www.qt.io/product/qt6).

## Current status

The application currently runs pretty good.

The game can be started immediately after launching the application. Selecting a field opens it.
The number of mines in the immediate vicinity is displayed.
If you select a field without mines nearby, all adjacent fields without mines are opened.
If a mine is hit, the field is marked with a mine symbol.
Continuing the current game is still possible.

A new game can also be started if desired.

You can also mark a field as questionable or as potentially mine (by right-clicking).

## Menu

<img src="/img/Menu.jpg" alt="Menu" width="400" height="100">

Two menu items are provided.

<img src="/img/App_Menu.jpg" alt="App Menu" width="150" height="150">

In the **App** menu, a new game can be started via the **New** menu item.
The **Settings** menu item opens a new window where certain game settings can be changed.
The **Quit** menu item closes the application.

<img src="/img/Info_Menu.jpg" alt="Info Menu" width="150" height="150">

The **Info** menu provides some information about the application.
The **About Qt** menu item displays information about the Qt version used.
The **About Other** menu item contains information about other elements of the application.

## Settings

<img src="/img/Settings.jpg" alt="Settings" width="200" height="200">

The **Settings** window allows you to configure the following:

- Number of rows
- Number of columns
- Number of mines in the playing field
- Field size in pixels
- Number of mine detector mouse

Changes can then be applied using the **Set** button.
The window will then close automatically.

If you decide you don't want to accept the changes, you can use the **Reset** button to return to the previous settings or use **Quit** to close the **Settings** window.

Changed settings will only take effect when a new game is started.

## How to Play

When you launch the application, you can start the game immediately by clicking on a field.

In the background, this first creates the minefield and starts the timer in the upper right corner. You always start in a field without any mines in your immediate vicinity.

<img src="/img/Game_Start.jpg" alt="Start Game" width="200" height="100">

The revealed fields then indicate the number of mines located in the immediate vicinity.

<img src="/img/Mines_near_Field.jpg" alt="Count Mines near the Field" width="100" height="100">

If you are certain that there is a mine in a particular field, you can mark the field with a flag by right-clicking. This will protect the field from being accidentally triggered.

<img src="/img/Flag_a_Field.jpg" alt="Mark a Field with Flag" width="100" height="100">

If you're unsure, you can mark the field as questionable by right-clicking again.

This will also protect the field from being accidentally activated.

<img src="/img/Field_is_questionable.jpg" alt="Mark a Field as Questionable" width="100" height="100">

To solve the game board, you must uncover all the fields without mines. The number of mines in the game board is shown in the third field above the game board.

<img src="/img/Status_Fields.jpg" alt="Game Status Fields" width="100" height="100">

In particularly difficult situations, it is not possible to find out where a mine might be located.

<img src="/img/Difficult_Field.jpg" alt="Where is a Mine?" width="100" height="100">

This is where the mine detector mouse comes in.

By activating the mine detector mouse, you can switch it from waiting mode (<img src="/icons/mouse_available.png" alt="Mouse waiting" width="20" height="20">) to working mode (<img src="/icons/mouse_working.png" alt="Mouse working" width="20" height="20">).

Now you can click on any field (not marked with a flag). If there is a mine in that field, the mine detector mouse will place a flag. If not, the field will be cleared. If you don't need the mine detector mouse after all, you can put it back into waiting mode.

However, you only have limited access to mine detector mouse( 3 by default). So choose wisely.

Once you have cleared all the empty fields, the game ends and the timer stops.

## To-Do's

- [x] Implement Settings
  - [x] Changing the number of rows
  - [x] Changing the number of columns
  - [x] Changing the number of mines
  - [x] Changing the Size of the Fields
  - [x] Changing the number of available Mouses
  - [x] implement Setting-Validation
- [x] Implement Timer
- [x] Implement Counts
  - [x] Counts for solved fields
  - [x] Counts for marked fields
- [ ] Implement Info about other things
- [x] Implement collective dissolution of contiguous fields without a mine in the immediate vicinity
- [x] Implement a Reaction when you encounter a mine
- [x] Implement a Reaction on success
- [x] Implement the usage of the right Mouse-Click to mark fields
- [x] Usage of Icons (Icons from <https://de.freepik.com/>)
- [x] Create a Bomb detection mouse
- [ ] Clean up the Code :expressionless:
