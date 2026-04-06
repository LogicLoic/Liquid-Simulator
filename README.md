# Liquid Simulator

```mermaid
---
title: Liquid Simulator
---
classDiagram
    class Main{
        -map : Map
        -units : vector<Unit>

        +Main(width : unsigned int, height : unsigned int)
        ~Main()
        +Mouse(event : Event) void
        +LClick(event : Event) void
        +NextFrame(window : sf::RenderWindow) void
    }

    class Map{
        -width : int
        -height : int
        -pixels : vector< vector< Pixel>>
        
        +Map(width : int, height : int)
        ~Map()
        +Update() void
        +GetTotalAmount() double
        +GetPixels() vector< vector< Pixel>>
    }

    class Pixel{
        -amount : double
        -direction : double
        -color : sf::Color
        -Wall : bool

        +Pixel()
        ~Pixel()
        +GetAmount() double
        +SetAmount(amount : double) void
        +GetColor() sf::Color
        +SetColor(color : sf::Color) void
        +Expand() vector<double>
        +ExpandCalculate() void
        +IsWall() bool
    }

    class Unit{
        -x : int
        -y : int

        +Unit()
        ~Unit()
        +GetCoords() vector<int>
    }

    class Emitter{
        -amount : double
        -interval : double
        -additional : bool
        -color : sf::Color

        +Emitter()
        ~Emitter()
        +Emit() void
        +GetAdditional() bool
    }

    Main *-- Map
    Main *-- Unit
    Map *-- Pixel
    Emitter --|> Unit

```

## TODO List :
- [x] Init project
- [x] Code pixel
- [x] Can draw on window
- [x] Display map
- [x] Binding mouse
- [ ] Animation
- [ ] Expansion calculations
- [ ] Multiple liquids management
- [ ] Creating Units
- [ ] Save/Load