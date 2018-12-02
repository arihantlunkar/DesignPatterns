#include <iostream>
#include <string>

using namespace std;

class Logger
{    
    private:    
        
    Logger() {}
    
    public:
    
    static Logger* getInstance()
    {
        if(m_pInstance == nullptr)
        {
            cout << "First instance created" << endl;
            m_pInstance = new Logger();
        }
        return m_pInstance;
    }
    
    static void releaseInstance()
    {        
        if(m_pInstance != nullptr)
        {
            cout << "Instance deleted" << endl;
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
    
    void log(const char* szMessage) const
    {
        cout << szMessage << endl; //Define your logic to log
    }
    
    private:
    
    static Logger* m_pInstance;
    
};

Logger* Logger::m_pInstance = nullptr;

int main()
{
    Logger::getInstance()->log("Bug 1");    
    Logger::getInstance()->log("Bug 2");   
    Logger::getInstance()->log("Bug 3");    
    Logger::getInstance()->log("Bug 4");      
    Logger::releaseInstance();
    
    return 0;
}
