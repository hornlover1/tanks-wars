class GameState {
	private:
		//level number must exist from gamestate to gamestate. How? gamestate is reinitialized. The value must be saved somewhere outside this code.
		static int levelNumber = 1;
		static GameState *gameState = nullptr;
		vector<Object> objectVector = new vector<Object>();		

//only creates a new gameState
        void newGameState() {
            if(gameState != nullptr) {
//This abruptly destroyes the previous gameState. Does the level number, or anything else need to be preserved?
				delete gameState;
				gameState = new GameState();
            } else {
				gameState = new GameState();
			}
		}

	public: 
		void GameState() //this the same as loading?
		{
			//download map - pass level number, 
			loadMap(levelNumber);	
		}
	
		void updateGameState()//I assume this code will be called continuously
		{//probably need access to timer class
		
			//make every object move
			for(object : objectVector)
			{
				object->Movement();
			}
			
			//decrease levelTimer
		}

		//returns the one instance of the GameState
		static GameState* getGameState()
		{
			return gameState;
		}
		
		//append objects to the vector
		void addObejectVector(Object object)
		{
			objectVector.add(object);
		}

		//return the vector, most likely for iteration.
		vector<Object>* getVector()
		{
			return objectVector;
		}

//how is this different from creating a new gameState?
		void loadGameState()
		{

		}

		void saveGameState()
		{
			
		}
};


