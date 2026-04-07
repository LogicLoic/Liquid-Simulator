# Liquid Simulator

```mermaid
---
title: Liquid Simulator
---
classDiagram
    class Main{
        -map : Map
        -brush : Brush

        +Main(width : unsigned int, height : unsigned int)
        ~Main()
        +NextFrame(window : sf::RenderWindow) void
        +Event(window : sf::RenderWindow, isDragging : bool)
        +Loop(window : sf::RenderWindow, width : unsigned int, height : unsigned int)
    }

    class Map{
        -width : int
        -height : int
        -pixels : vector< vector< Pixel>>
        -units : vector< Unit>
        
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
        +SetColor(color : sf::Color, transparency : double) void
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

    class Brush{
        -amount : double
        -color : sf::Color
        -type : BrushType

        +Brush()
        ~Brush()
        +RefreshInfos(amount : double, color : sf::Color, type : BrushType) void
        +GetAmount() double
        +GetColor() sf::Color
        +GetType() BrushType
    } 

    class BrushType{
        <<enumeration>>
        Liquid,
        Wall,
        Erase,
        Emitter
    }

    Main *-- Map
    Map *-- Unit
    Main *-- Brush
    Map *-- Pixel
    Brush --> BrushType
    Emitter --|> Unit

```

## TODO List :
- [x] Init project
- [x] Code pixel
- [x] Can draw on window
- [x] Display map
- [x] Binding mouse
- [x] Animation
- [x] Expansion calculations
- [ ] Brush & Global Panels
- [ ] Multiple liquids management
- [ ] Creating Units
- [ ] Save/Load