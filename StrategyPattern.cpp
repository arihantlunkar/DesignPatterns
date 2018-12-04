#include <iostream>
#include <string>
#include <memory>

using namespace std;

class WriteStrategy
{
    public:
    virtual void write() const = 0;   
    virtual ~WriteStrategy() = default;
};

class TextWriter final : public WriteStrategy
{
    public: 
    TextWriter()
    {        
        cout << "TextWriter Created" << endl;
    }
    ~TextWriter()
    {        
        cout << "TextWriter Deleted" << endl;
    }
    void write() const
    {
        cout << "TextWriter Used" << endl;
    }   
};

class ExcelSheetWriter final : public WriteStrategy
{
    public: 
    ExcelSheetWriter()
    {        
        cout << "ExcelSheetWriter Created" << endl;
    }
    ~ExcelSheetWriter()
    {        
        cout << "ExcelSheetWriter Deleted" << endl;
    }
    void write() const
    {
        cout << "ExcelSheetWriter Used" << endl;
    }   
};

class DBWriter final : public WriteStrategy
{
    public:
    DBWriter()
    {        
        cout << "DBWriter Created" << endl;
    }
    ~DBWriter()
    {        
        cout << "DBWriter Deleted" << endl;
    }
    void write() const
    {
        cout << "DBWriter Used" << endl;
    }   
};

class WriterController 
{
    
  public:
  
    enum WriteStrategyType
    {
        Text, ExcelSheet, DB
    };
    
    WriterController()
    {
        m_pTextWriter = std::unique_ptr<WriteStrategy>(new TextWriter);
        m_pExcelSheetWriter = std::unique_ptr<WriteStrategy>(new ExcelSheetWriter);
        m_pDBWriter = std::unique_ptr<WriteStrategy>(new DBWriter);
    }
    
    void setWriteStrategy(WriteStrategyType tWriteStrategyType)
    {
        switch(tWriteStrategyType)
        {
            case WriteStrategyType::Text:
            m_pWriteStrategy = m_pTextWriter.get();
            break;
            case WriteStrategyType::ExcelSheet:
            m_pWriteStrategy = m_pExcelSheetWriter.get();
            break;
            case WriteStrategyType::DB:
            m_pWriteStrategy = m_pDBWriter.get();
            break;
            default:
            break;
        }
    }
    
    void executeWriteTask() const
    {
        if(nullptr != m_pWriteStrategy)
        {
            m_pWriteStrategy->write();
        }
    }
    
  private:
  
    unique_ptr<WriteStrategy> m_pTextWriter = nullptr;
    unique_ptr<WriteStrategy> m_pExcelSheetWriter = nullptr;
    unique_ptr<WriteStrategy> m_pDBWriter = nullptr;
    
    WriteStrategy* m_pWriteStrategy = nullptr;
};

int main()
{
    unique_ptr< WriterController> pWriterController = std::unique_ptr<WriterController>(new WriterController);
    
    pWriterController->setWriteStrategy(WriterController::Text);
    pWriterController->executeWriteTask();
    pWriterController->setWriteStrategy(WriterController::ExcelSheet);
    pWriterController->executeWriteTask();
    pWriterController->setWriteStrategy(WriterController::DB);
    pWriterController->executeWriteTask();
    pWriterController->setWriteStrategy(WriterController::Text);
    pWriterController->executeWriteTask();
    
    return 0;
}
