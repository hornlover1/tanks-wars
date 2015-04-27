# Details #

First is the user's name.
Second is the maximum level the user can play.

## Example ##

```
user.name "Nathan"
maxLevel 3
```

# Level Format #

The first line is the times for easy, medium, and hard. The other lines describe objects in the level.

## Format ##

```
time easy medium hard
tank x y
tank2 x y
wall x y width height
barricade x y
```

## Example ##

```
time 45 40 30
wall -25 -25 805 25
tank 100 300
tank2 500 300
barricade 240 270
```