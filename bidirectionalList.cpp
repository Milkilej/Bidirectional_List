#include <iostream>
#include <sstream>
#include <vector>

struct TestCase { std::string name{}; std::ostringstream failures{}; };
template <typename T> void operator | (TestCase& testCase, T&& testBody) {
    testBody(); auto failures = testCase.failures.str();
    if (failures.empty()) std::cout << testCase.name << ": SUCCESS\n";
    else std::cerr << testCase.name << ": FAILURE\n" << failures;
}
void addFailure(std::ostream& os, const char* file, unsigned line, const char* condition) {
    os << file << ":" << line << ": Failed: " << condition << "\n";
}
#define TEST(name) TestCase name{#name}; name | [&, &failures = name.failures]
#define EXPECT(cond) if (cond) {} else addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) if (cond) {} else return addFailure(failures, __FILE__, __LINE__, #cond)


struct ListElem {
    std::string val;
    ListElem* next;
};

class DoubleLinkedList  {
    public:
    DoubleLinkedList()
    {
        size_ = 0;
        head = nullptr;
    }

    int size()
    {
        return size_;
    }

    void insert(std::string elem)
    {
        ListElem* tmp = head;
        if (head == nullptr) {
            head = new ListElem;
            head -> val = elem; 
            head -> next = nullptr;
        }
        while(tmp != nullptr)
        {
            tmp = tmp->next;
        }
        
        tmp = new ListElem;
        tmp->val = elem;
        tmp->next = nullptr;
        size_++;
    }
    
    void remove()
    {
        if(head == nullptr)
            return;
        
        if(head -> next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            ListElem* tmp = head;
            while(tmp->next != nullptr)
            {
                tmp = tmp->next;
            }
            delete tmp;
            tmp = nullptr;
        }
        size_--;
        
    }

    std::string getFirst()
    {
        if(head == nullptr)
            return "";
        else
            return head->val;
    }

    void removeAllElements()
    {
        while(head != nullptr)
        {
            remove(); 
        }
    }

    private:
    int size_;
    ListElem* head;
};

int main() 
{   
    TEST(GivenDeleteAllElementReqestWhenReturnSize0)
    {
        DoubleLinkedList list;
        list.insert("222");
        list.insert("122");
        list.insert("123");
        list.removeAllElements();
        EXPECT(list.size() == 0);
    };

    TEST(GivenDeleteRequestWhenReturnHeadNextField)
    {
        DoubleLinkedList list;
        list.insert("222");
        list.insert("123");
        list.remove();
        list.remove();
        list.insert("333");
        EXPECT(list.getFirst() == "333");
    };
    
    TEST(GivenDeleteRequestWhenReturnSize1)
    {
        DoubleLinkedList list;
        list.insert("222");
        list.insert("123");
        list.remove();
        EXPECT(list.size() == 1);
    };

    TEST(GivenuDeleteRequestWhenReturnSizeMinus1)
    {
        DoubleLinkedList list;
        list.insert("222");
        list.remove();
        EXPECT(list.size() == 0);
    };

    TEST(GivenEmptyListWhenAskedForFirstValueReturnsInformationThatListIsEmpty)
    {
        DoubleLinkedList list;
        EXPECT(list.getFirst() == "");
    };

    TEST(GivenTwoElementsToListReturnsFirstElement)
    {
        DoubleLinkedList list;
        list.insert("123");
        list.insert("456");
        EXPECT(list.getFirst() == "123");
    };

    TEST(GivenDifferentElementToListReturnsFirstElement)
    {
        DoubleLinkedList list;
        list.insert("123");
        EXPECT(list.getFirst() == "123");
    };

    TEST(GivenElementToListReturnsFirstElement)
    {
        DoubleLinkedList list;
        list.insert("first second third");
        EXPECT(list.getFirst() == "first second third");
    };

    TEST(GivenElementToListReturnsSize1)
    {
        DoubleLinkedList list;
        list.insert("");
        EXPECT(list.size() == 1);
    };

    TEST(GivenEmptyListReturnsSize0)
    {
        DoubleLinkedList list;
        EXPECT(list.size() == 0);
    };

    TEST(GivenNoArgumentsReturnsEmptyList)
    {
        DoubleLinkedList* list = new DoubleLinkedList;
        EXPECT(list != nullptr);
        delete list;
    };
}
