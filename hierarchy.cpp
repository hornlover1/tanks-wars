class Object : QLabel {
	QString objectName; //to identify the type of object

	//make label impermeable
	virtual Movement() { /*code to move object */} //timer code needed
    
    //predifined basic sizes for these objects.  Change here, change everywhere.
        //PROBLEM:What if we don't want the standard size for a copy of one of  
        //these objects?  If we made these Const that existed for every object than 
        //we could change if for any one object.
    static int bulletS, tankBS, specialObs, exploTrapS, turrentS;
    
    //each subclass will redefine this object.
    virtual bool isDestroyable = false
    
    int x,y,height,width;
    
    //constructor
    Object(QImage image) { }
    
    //set image to size of label
    setImage();
    
    //we need away to detect if this object was contacted by another object. 
        //method should return true if touched, false otherwise
    contact();
    
    virtual explosion {}
};

class WallBlock : public Object {
    
};

class Bullet : public Object {
    override isDestroyable = true;
    
    overrride Movement() {/*Increment x and y by 1 to move bullet in straight line (?)*/} 
   
    //bullet must have uneque ability to detect another objects isDestroyable and possibly destroy that object.
    override explosion(Object that) {/*Is called by this object on contact(). 
        switches the labels image with an explosion.png before destroying
        the objects intance.
       If (other that -> isDestroyable == true) {
            //do the same for that object
        }
       */}
};

class TankBody : public Object {
    override isDestroyable = true;
    override Movement() {
        /*move based on input.  But his code won't enable upright combination
        if(up arrow) { y++; }
        if(down arrow) { y--; }
        
        if(left arrow) { x++; }
        if(right arrow) { x--; }   
        
        Direct front of tank (x/2) to face the direction the tank is going*/
    }
};

//special object that may need to be built from the ground up.  May need to consist of two labels instread of one.
class Turret : public Object {
    override Movement() {//must be on tankbody, move with tank body}
        
    /*must direct front end toward cursor position.*/
}

//other possibilities
class PushableObtacle : public WallBlock {
    //obstacles the tank must push past and destroy
};

class ExplosiveTraps : public Bullet {
    //a big bullet that doesn't move and explodes when touched by tank or bullet.
};
