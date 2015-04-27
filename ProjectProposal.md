The user(s) will play the game by controlling a personal tank. The tank is maneuvered through a series of obstacles in a war-torn country.  Some of the obstacles are merely stationary, others are outright dangerous.  The goal of the game is too complete missions, which may be to seek out another tank controlled by another user or the AI.  The mission must be completed within a time limit.  A high score of fastest times will be accumulated.

The user(s) will move the body of the tank through the use of the arrow keys.  The gun turret will have greater freedom of movement and will point in the same direction as the user(s)’s cursor.  The maps will be pre-created and in separate files.  Each map will have multiple times, a separate time for each difficulty level.  The easier the level, the more time the user(s) will have. The user(s) must complete that map within that time.  If the user(s) runs out of ammo then the time will run down and the user(s) will lose.  Failed levels must be repeated.  Special boxes will be randomly placed in the map to give the user(s) more time and ammo.  A Cheat mode will download a special map with each object type placed on it so that they may be thoroughly tested. Unlimited time and ammo will be given for continuos testing.

C version (goal: make something playable, if a little boring)
  * Map file loading
  * Stationary objects (including destroyable objects/barricades)
  * Countdown timer/ability to win or lose a level
  * Shooting projectiles/hitting [stationary](stationary.md) targets
  * Cheat mode (for, um, debugging)

B version (goal: make the game interesting)
  * Movable non-player objects & AI (e.g., opposing tanks; this is going to take time to get right)
  * Game save/reload (tip: consider leveraging your map file loading logic to handle ongoing game saving/loading, too)
  * High scores/low times file

A version (goal: to make the game complete)
  * Networked multiplayer support (major feature)
  * Sound (minor feature)

Extras (all the little polishes that make a game awesome)
  * Modified driving surfaces (mud, ice, etc.)
  * Random goodies/power ups
  * Extra animations/effects (e.g., exploding objects)
  * Level designer