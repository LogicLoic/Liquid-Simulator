# Liquid Simulator

```mermaid
---
title: Liquid Simulator
---
classDiagram
    class Main{
        -map : Map
        -units : vector<Unit>

        +Main(width : int, height : int)
        ~Main()
        +Mouse(event : Event) void
        +LClick(event : Event) void
        +NextFrame() void
    }

    class Map{
        -width : int
        -height : int
        -pixels : vector<vector<Pixel>>
        
        +Map(width : int, height : int)
        ~Map()
        +Update() void
        +GetTotalAmount() double
    }

    class Pixel{
        -amount : double
        -direction : double
        -color : string
        -Wall : bool

        +Pixel()
        ~Pixel()
        +GetAmount() double
        +SetAmount(amount : double) void
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
        -color : string

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
