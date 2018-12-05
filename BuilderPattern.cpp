#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <list>

using namespace std;

class Attribute final
{
    string m_strName;
    string m_strValue;

public:

    void print() const
    {
        if(!m_strName.empty())
        {
            cout << m_strName << "=\"" << m_strValue << "\"";
        }
    }

    class AttributeBuilder final
    {
        string m_strName;
        string m_strValue;

    public:

        AttributeBuilder addName(string strName) {
            this->m_strName = strName;
            return *this;
        }

        AttributeBuilder addValue(string strValue) {
            this->m_strValue = strValue;
            return *this;
        }

        Attribute build()
        {
            Attribute tAttribute;
            tAttribute.m_strName = this->m_strName;
            tAttribute.m_strValue = this->m_strValue;
            return tAttribute;
        }
    };
};

class Element final
{
    string m_strName;
    string m_strText;
    list<Attribute> m_lstAttribute;
    list<Element> m_lstElement;

public:

    void print() const
    {
        if(!m_strName.empty())
        {
            cout << "<" << m_strName;
            if(m_lstAttribute.size() != 0)
            {
                cout << " ";
                for (auto const& tAttribute : m_lstAttribute) {
                    tAttribute.print();
                    cout << " ";
                }
            }
            cout << ">";
            if(m_lstElement.size() != 0)
            {
                cout << endl;
                for (auto const& tElement : m_lstElement) {
                    tElement.print();
                    cout << endl;
                }
                cout << "</" << m_strName << ">";
            }
            else
            {
                cout << m_strText << "</" << m_strName << ">";
            }
        }
    }

    class ElementBuilder final
    {
        string m_strName;
        string m_strText;
        list<Attribute> m_lstAttribute;
        list<Element> m_lstElement;

    public:

        ElementBuilder addName(string strName) {
            this->m_strName = strName;
            return *this;
        }

        ElementBuilder addText(string strText) {
            this->m_strText = strText;
            return *this;
        }

        ElementBuilder addAttribute(const Attribute& tAttribute) {
            this->m_lstAttribute.push_back(tAttribute);
            return *this;
        }

        ElementBuilder addElement(const Element& tElement) {
            this->m_lstElement.push_back(tElement);
            return *this;
        }

        Element build()
        {
            Element tElement;
            tElement.m_strName = this->m_strName;
            tElement.m_strText = this->m_strText;
            tElement.m_lstAttribute = this->m_lstAttribute;
            tElement.m_lstElement = this->m_lstElement;
            return tElement;
        }
    };
};

class Xml final
{
    Element m_tRootElement;

public:

    void print() const
    {
        cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        m_tRootElement.print();
    }

    void setRoot(const Element& tElement)
    {
        m_tRootElement = tElement;
    }
};

int main()
{
    Element::ElementBuilder tElementBuilder = *(new Element::ElementBuilder());
    Element tRootElement = tElementBuilder
                           .addName("squares")
                           .build();

    for(int i = 1; i <= 5; i++)
    {
        Attribute tAttribute1 = (*(new Attribute::AttributeBuilder()))
                                .addName("x")
                                .addValue(to_string(i))
                                .build();

        Attribute tAttribute2 = (*(new Attribute::AttributeBuilder()))
                                .addName("y")
                                .addValue(to_string(i*i))
                                .build();

        Element tElement =  (*(new Element::ElementBuilder()))
                            .addName("data")
                            .addAttribute(tAttribute1)
                            .addAttribute(tAttribute2)
                            .build();

        tRootElement = tElementBuilder
                       .addElement(tElement)
                       .build();
    }

    Xml tXml;
    tXml.setRoot(tRootElement);
    tXml.print();

    return 0;
}
