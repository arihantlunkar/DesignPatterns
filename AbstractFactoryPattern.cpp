#include <iostream>
#include <string>
#include <memory>

using namespace std;

class ITestCase
{
public:
    virtual ~ITestCase() = default;
    virtual void execute() const = 0;
};

class ComponentOne_TestCaseOne final : public ITestCase
{
public:
    ComponentOne_TestCaseOne()
    {
        cout << "Creating ComponentOne_TestCaseOne ..." << endl;
    }
    ~ComponentOne_TestCaseOne()
    {
        cout << "Destroying ComponentOne_TestCaseOne ..." << endl;
    }
    void execute() const
    {
        cout << "Executing ComponentOne_TestCaseOne ..." << endl;
    }
};

class ComponentOne_TestCaseTwo final : public ITestCase
{
public:
    ComponentOne_TestCaseTwo()
    {
        cout << "Creating ComponentOne_TestCaseTwo ..." << endl;
    }
    ~ComponentOne_TestCaseTwo()
    {
        cout << "Destroying ComponentOne_TestCaseTwo ..." << endl;
    }
    void execute() const
    {
        cout << "Executing ComponentOne_TestCaseTwo ..." << endl;
    }
};

class ComponentTwo_TestCaseOne final : public ITestCase
{
public:
    ComponentTwo_TestCaseOne()
    {
        cout << "Creating ComponentTwo_TestCaseOne ..." << endl;
    }
    ~ComponentTwo_TestCaseOne()
    {
        cout << "Destroying ComponentTwo_TestCaseOne ..." << endl;
    }
    void execute() const
    {
        cout << "Executing ComponentTwo_TestCaseOne ..." << endl;
    }
};

class ComponentTwo_TestCaseTwo final : public ITestCase
{
public:
    ComponentTwo_TestCaseTwo()
    {
        cout << "Creating ComponentTwo_TestCaseTwo ..." << endl;
    }
    ~ComponentTwo_TestCaseTwo()
    {
        cout << "Destroying ComponentTwo_TestCaseTwo ..." << endl;
    }
    void execute() const
    {
        cout << "Executing ComponentTwo_TestCaseTwo ..." << endl;
    }
};

class ITestCaseFactory
{
public:
    enum TestCaseType
    {
        One,
        Two
    };
    virtual unique_ptr<ITestCase> createTestCase(TestCaseType tTestCaseType) = 0;
    virtual ~ITestCaseFactory() = default;
};

class ComponentOne_TestCaseFactory final : public ITestCaseFactory
{
public:
    ComponentOne_TestCaseFactory()
    {
        cout << "Creating ComponentOne_TestCaseFactory ..." << endl;
    }
    ~ComponentOne_TestCaseFactory()
    {
        cout << "Destroying ComponentOne_TestCaseFactory ..." << endl;
    }
    unique_ptr<ITestCase> createTestCase(TestCaseType tTestCaseType)
    {
        unique_ptr<ITestCase> pTestCase = nullptr;
        switch(tTestCaseType)
        {
        case TestCaseType::One:
            pTestCase = unique_ptr<ITestCase>(new ComponentOne_TestCaseOne);
            break;
        case TestCaseType::Two:
            pTestCase = unique_ptr<ITestCase>(new ComponentOne_TestCaseTwo);
            break;
        default:
            break;
        }
        return pTestCase;
    }
};

class ComponentTwo_TestCaseFactory final : public ITestCaseFactory
{
public:
    ComponentTwo_TestCaseFactory()
    {
        cout << "Creating ComponentTwo_TestCaseFactory ..." << endl;
    }
    ~ComponentTwo_TestCaseFactory()
    {
        cout << "Destroying ComponentTwo_TestCaseFactory ..." << endl;
    }
    unique_ptr<ITestCase> createTestCase(TestCaseType tTestCaseType)
    {
        unique_ptr<ITestCase> pTestCase = nullptr;
        switch(tTestCaseType)
        {
        case TestCaseType::One:
            pTestCase = unique_ptr<ITestCase>(new ComponentTwo_TestCaseOne);
            break;
        case TestCaseType::Two:
            pTestCase = unique_ptr<ITestCase>(new ComponentTwo_TestCaseTwo);
            break;
        default:
            break;
        }
        return pTestCase;
    }
};

int main()
{
    unique_ptr<ITestCaseFactory> pITestCaseFactory = nullptr;
    unique_ptr<ITestCase> pITestCase = nullptr;


    pITestCaseFactory = unique_ptr<ITestCaseFactory>(new ComponentOne_TestCaseFactory);

    pITestCase =  pITestCaseFactory->createTestCase(ITestCaseFactory::One);
    pITestCase->execute();

    pITestCase = pITestCaseFactory->createTestCase(ITestCaseFactory::Two);
    pITestCase->execute();



    pITestCaseFactory = unique_ptr<ITestCaseFactory>(new ComponentTwo_TestCaseFactory);

    pITestCase = pITestCaseFactory->createTestCase(ITestCaseFactory::One);
    pITestCase->execute();

    pITestCase = pITestCaseFactory->createTestCase(ITestCaseFactory::Two);
    pITestCase->execute();

    return 0;
}
