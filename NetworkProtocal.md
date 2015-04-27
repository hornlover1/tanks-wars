# Network Protocol #

## Connection ##

Two users will pull up the game at the same time. One user will enter the IP address of the other user. The game will then call that IP address on port 7537 (That port does not appear to be used by any other known application, plus it's prime). The opponent's server will respond by confirming connection and creating a connection to the first player's server. If any step along this path fails, the user will receive an error message. If we have extra time, we might implement automatic discovery of other players on the network by sending a UDP multicast packet to all devices on the network. Any devices with a running instance of the game will respond with a TCP unicast packet.

## Play over the Network ##

The network communication will take place over two channels. Each instance of the game will have a server and a client. When the user of game 1 moves his tank or fires a bullet, client 1 will send a message to server 2 which will then show the movement on game 2's screen. Messages will only be sent when motion occurs. The messages will take the following formats.
  * "startTank x y d" - indicates that the user's tank's coordinates (x,y) as well as the direction d that it is moving
  * "stopTank x y" - indicates that the tank has stopped at position (x, y)
  * "bullet x y angle" - indicates that the user's tank shot from coordinate (x,y) at and angle of _angle_
  * "level n ipAddr" - when connecting to each other, the instances will tell each other which level their playing and their IP Address so that they can connect to each other