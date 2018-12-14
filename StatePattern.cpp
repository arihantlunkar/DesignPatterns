#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

class GameController;

class GameState
{
    public:
    
    enum GameStateTypes
    {
        Running,
        Paused,
        Over
    };
    
    virtual void onRunning() = 0;
    
    virtual void onPaused() = 0;    
    
    virtual void onOver() = 0;
    
    GameState(GameController* pGameController) : m_pGameController(pGameController)
    {
    }
    
    protected:
    
    GameController* m_pGameController;
    
};

class Running : public GameState
{
    public:
    
    Running(GameController* pGameController) : GameState(pGameController)
    {
    }
    
    void onRunning()
    {
        cout << "Already game is running" << endl;
    }
    
    void onPaused()
    {        
        cout << "Player clicks pause. Game state changed. Running->Paused" << endl;               
        m_pGameController->setNewState(GameState::GameStateTypes::Paused);
    }
    
    void onOver()
    {        
        cout << "Player dies. Game state changed. Running->Over" << endl;               
        m_pGameController->setNewState(GameState::GameStateTypes::Over);
    }
};

class Paused : public GameState
{
    public:
    
    Paused(GameController* pGameController) : GameState(pGameController)
    {
    }
    
    void onRunning()
    {
        cout << "Player clicks resume. Game state changed. Paused->Running" << endl;        
        m_pGameController->setNewState(GameState::GameStateTypes::Running);
    }
    
    void onPaused()
    {   
        cout << "Already game is paused" << endl;     
    }
    
    void onOver()
    {        
        cout << "Game state cannot be changed. Paused->Over" << endl;
    }
};

class Over : public GameState
{
    public:
    
    Over(GameController* pGameController)  : GameState(pGameController)
    {
    } 
    
    void onRunning()
    {
        cout << "Player clicks start. Game state changed. Over->Running" << endl;
        m_pGameController->setNewState(GameState::GameStateTypes::Running);
    }
    
    void onPaused()
    {        
        cout << "Game state cannot be changed. Over->Paused" << endl;
    }
    
    void onOver()
    {        
        cout << "Already game is over" << endl;    
    }
};



class GameController
{
    private:
    
    map<GameState::GameStateTypes, GameState*> m_MapGameStates; 
    
    GameState::GameStateTypes m_tCurrentGameState;
    
    public:
    
    enum Transition
    {
        PlayerDies,
        PlayerClicksStart,
        PlayerClicksPause,
        PlayerClicksResume
    };
    
    GameController()
    {
        m_MapGameStates.insert ( pair<GameState::GameStateTypes, GameState*> (GameState::GameStateTypes::Running, new Running(this)) );
        m_MapGameStates.insert ( pair<GameState::GameStateTypes, GameState*> (GameState::GameStateTypes::Paused, new Paused(this)) );
        m_MapGameStates.insert ( pair<GameState::GameStateTypes, GameState*> (GameState::GameStateTypes::Over, new Over(this)) ) ;
        
        m_tCurrentGameState = GameState::GameStateTypes::Over;
    }
    
    void setNewState(GameState::GameStateTypes tGameState)
    {
        m_tCurrentGameState = tGameState;
    } 
    
    void doTask(Transition tTransition)
    { 
        auto search = m_MapGameStates.find(m_tCurrentGameState);
        if(search != m_MapGameStates.end())
        {
            GameState* pGameState = search->second;
            switch(tTransition)
            {
                case PlayerDies:
                pGameState->onOver();
                break;
                
                case PlayerClicksStart:
                pGameState->onRunning();
                break;
                
                case PlayerClicksPause:
                pGameState->onPaused();
                break;
                
                case PlayerClicksResume:
                pGameState->onRunning();
                break;
                
                default:
                break;
            }
        }
    }    
};

int main()
{    
    // Note: Write all classes(Running, Over, Paused, GameState, GameController) in different cpp and header file otherwise it will not compile.
    unique_ptr<GameController> pGameController = unique_ptr<GameController>(new GameController);
    
    for(int i = 0; i < 4; ++i)
    {
        pGameController->doTask((GameController::Transition)i);
    }
    
    return 0;
}
