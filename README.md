# Tetris game in C++ with SDL2 lib

This project is a Tetris game wrote in C++ using SDL2 as a graphic and utilitary library.

## Installation

This projects is only made to be used on linux distributions. You will need the **g++**, **make**, **libsdl2-dev**, **libsdl2-image-dev**, **libSDL2-ttf-dev** and **libsdl2-mixer-dev** packages.
On Ubuntu, you can install them using :
```bash
 sudo apt install g++ make libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
 ```
To compile the code, open a terminal in the root and type :
```bash
make all
```

## Execution

To execute the game, open the **Tetris** file using : 
```bash
./Tetris
```

## How to play the game ?
The controls are the same as the [online Tetris game](https://tetris.com/play-tetris).
- To rotate the Tetromino, use the **ARROW_UP** key.
- To move right and left, use the **ARROW_RIGHT** and **ARROW_LEFT** keys.
- To go down faster, use the **ARROW_DOWN** key.
- To instantly drop the piece, use the **SPACE** key.
- To store a piece, use the **C** key.
- To pause the game, use the **ESCAPE** key.
- To navigate in the menu, use the **ARROW_UP** and **ARROW_DOWN** keys.
- To validate an entry in the menu, use the **RETURN** key.
- To modify a parameter value in the settings, use the **ARROW_RIGHT** and **ARROW_LEFT** keys.

## Documentation
The "make all" command will also create a documentation in the `html` format, that you can launch on your default browser by typing the following command or by opening [./doc/html/index.html](./doc/html/index.html) with a web browser.
```
make open_doc
```

## Acknowledgments

We are very grateful to [LazyFoo' Productions](http://lazyfoo.net/tutorials/SDL/index.php) for its tutorials on how to use the SDL2 library, particularely for its examples of FPS management, for example its **LTimer** class in _timer.hpp_. 

## Authors

This project has been wrote by [Luca Scimone]() and [Simon Willer](https://github.com/SimonWillerTPS), engineering students in [Telecom Physique Strasbourg](http://www.telecom-physique.fr/).
