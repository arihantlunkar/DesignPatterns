#include <iostream>
#include <string>

using namespace std;

class WriteStrategy
{
public:
    virtual void write() = 0;
    virtual ~WriteStrategy() {}
};

class TextWriter : public WriteStrategy
{
public:
    ~TextWriter()
    {
        cout << "TextWriter Deleted" << endl;
    }
    void write()
    {
        cout << "TextWriter Used" << endl;
    }
};

class ExcelSheetWriter : public WriteStrategy
{
public:
    ~ExcelSheetWriter()
    {
        cout << "ExcelSheetWriter Deleted" << endl;
    }
    void write()
    {
        cout << "ExcelSheetWriter Used" << endl;
    }
};

class DBWriter : public WriteStrategy
{
public:
    ~DBWriter()
    {
        cout << "DBWriter Deleted" << endl;
    }
    void write()
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

    ~WriterController()
    {
        deletePreviousWriteStrategyIfAny();
    }

    void setWriteStrategy(WriteStrategyType tWriteStrategyType)
    {
        deletePreviousWriteStrategyIfAny();
        switch(tWriteStrategyType)
        {
        case WriteStrategyType::Text:
            m_pWriteStrategy = new TextWriter();
            break;
        case WriteStrategyType::ExcelSheet:
            m_pWriteStrategy = new ExcelSheetWriter();
            break;
        case WriteStrategyType::DB:
            m_pWriteStrategy = new DBWriter();
            break;
        default:
            break;
        }
    }

    void executeWriteTask()
    {
        if(nullptr != m_pWriteStrategy)
        {
            m_pWriteStrategy->write();
        }
    }

private:

    void deletePreviousWriteStrategyIfAny()
    {
        if(nullptr != m_pWriteStrategy)
        {
            delete m_pWriteStrategy;
            m_pWriteStrategy = nullptr;
        }
    }

    WriteStrategy *m_pWriteStrategy = nullptr;
};

int main()
{
    WriterController *pWriterController = new WriterController();

    pWriterController->setWriteStrategy(WriterController::Text);
    pWriterController->executeWriteTask();
    pWriterController->setWriteStrategy(WriterController::ExcelSheet);
    pWriterController->executeWriteTask();
    pWriterController->setWriteStrategy(WriterController::DB);
    pWriterController->executeWriteTask();

    delete pWriterController;
    pWriterController = nullptr;
    
    return 0;
}
