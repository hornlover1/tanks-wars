#list of all the problems with the program.

# Bugs #

hint: This is not the optimistic page.

TO BE FIXED:
  * Jordan knows how to shoot through walls and poke the nose of the tank through

FIXED:
  * When two or more bullets or barricades are on the map at once, the program will seg-fault unless they are destroyed in the proper order.//iterator problem
  * Better tank image with proper sizing.
  * When bullets hit an object, they stop and sit there
  * When pixmap loaded, labels won't move
  * Only tell user things will be unlocked if they will be unlocked //Program doesn't say level is unlocked now
  * saveFile(), loadFile(), and saveHighScore() are not working
  * Player is able to defeat level 1 to eight times to open up the next 8 levels.
  * Make the label point in the direction the object is going.
  * The user is unable to play with the hard time.
  * Program won't run on windows
  * Take the file loading and saving into a separate singleton class
  * Make sure we are using issue tracker correctly
  * Fix the direction enumerator and add a direction of null.