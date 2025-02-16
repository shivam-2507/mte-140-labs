/************************************************************
 * You can use this file to test if your code is working
 * properly by designing your own test case and test code.
 *
 * We will only be providing test cases for Lab 1.1.
 *
 * To grade, we will compile your code and run it against
 * our own test suite. You should design your own tests in
 * this file to ensure that your code does what you expect.
 ************************************************************/

#include <iostream>
#include <string>

// Uncomment the .h files when you're ready to start testing
//#include "sequential-list.h"
#include "doubly-linked-list.h"

// Once uncommented, you will need to modify the CMakeLists.txt
// to add the .cpp file to be able to compile again.

// Note: This may require you to "rebuild" or "Reload CMake Project"

using namespace std;


#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;


string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

class DoublyLinkedListTest{
public:
    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
    bool test6();
    bool test7();
    bool test8();
    bool test9();
    bool test10();
};

int main() {

    int grade = 0;
    DoublyLinkedListTest linked_test;
    DoublyLinkedList list;

    string linked_test_descriptions[10] = {
            "Test1: New empty list is valid",
            "Test2: insert_front() and insert_back() on zero-element list",
            "Test3: select() and search() work properly",
            "Test4: remove_front() and remove_back() on one-element list",
            "Test5: replace() works properly",
            "Test6: insert_front() keeps moving elements forward",
            "Test7: inserting at different positions in the list",
            "Test8: try to remove too many elements, then add a few elements",
            "Test9: lots of inserts and deletes, all of them valid",
            "Test10: lots of inserts and deletes, some of them invalid",

    };

    bool linked_test_results[10];
    linked_test_results[0] = linked_test.test1();
    linked_test_results[1] = linked_test.test2();
    linked_test_results[2] = linked_test.test3();
    linked_test_results[3] = linked_test.test4();
    linked_test_results[4] = linked_test.test5();
    linked_test_results[5] = linked_test.test6();
    linked_test_results[6] = linked_test.test7();
    linked_test_results[7] = linked_test.test8();
    linked_test_results[8] = linked_test.test9();
    linked_test_results[9] = linked_test.test10();

    cout << "DOUBLY LINKED LIST TESTING RESULTS \n";
    cout << "********************************** \n";
    for (int i = 0; i < 10; ++i)
    {
        cout << linked_test_descriptions[i] << endl
             << get_status_str(linked_test_results[i]) << endl;
        if (linked_test_results[i])
            grade += 4;
    }
    grade += 10;
    cout << endl
         << "Total grade: " << grade << endl << endl;

    for (int i = 0; i < 500; i++) {
        list.insert_front(i);
    }
    list.print();
}

//############# DoublyLinkedListTest function definitions ###########

// New empty list is valid
bool DoublyLinkedListTest::test1()
{
    DoublyLinkedList list;
    ASSERT_TRUE(list.size() == 0)
    ASSERT_TRUE(list.empty() == true)
    ASSERT_TRUE(list.full() == false)
    ASSERT_TRUE(list.head_ == nullptr)
    ASSERT_TRUE(list.tail_ == nullptr)
    return true;
}

// insert_front() and insert_back() on zero-element list
bool DoublyLinkedListTest::test2()
{
    DoublyLinkedList list1, list2;
    list1.insert_front(100);
    list2.insert_back(100);

    ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
    ASSERT_TRUE(list1.head_ != nullptr && list1.head_ == list1.tail_)
    ASSERT_TRUE(list2.head_ != nullptr && list2.head_ == list2.tail_)
    ASSERT_TRUE(list1.head_->prev == nullptr && list1.tail_->next == nullptr)
    ASSERT_TRUE(list2.head_->prev == nullptr && list2.tail_->next == nullptr)
    ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)
    return true;
}


// select() and search() work properly
bool DoublyLinkedListTest::test3()
{
    DoublyLinkedList list;
    const int num_elems = 5;
    for (int i = 0; i < num_elems; i++)
    {
        ASSERT_TRUE(list.insert_back(i * 100))
    }

    unsigned int idx = 3;
    ASSERT_TRUE(list.search(list.select(idx)) == idx)
    ASSERT_TRUE(list.select(num_elems + 1) == 400)
    ASSERT_TRUE(list.search(1000) == list.size())

    for (int i = 0; i < num_elems; i++)
    {
        ASSERT_TRUE(list.select(i) == i * 100)
    }

    ASSERT_TRUE(list.head_->prev == nullptr && list.tail_->next == nullptr)

    return true;
}

bool DoublyLinkedListTest::test4() {
    DoublyLinkedList list;

    ASSERT_TRUE(list.insert_front(100));
    ASSERT_TRUE(list.insert_back(100));

    ASSERT_TRUE(list.insert(200, 1));

    ASSERT_TRUE(list.remove_front());

    ASSERT_TRUE(list.insert_front(50));

    ASSERT_TRUE(list.remove_back());

    ASSERT_TRUE(list.insert_back(100));

    ASSERT_TRUE(list.remove(1));

    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(list.select(0) == 50);
    ASSERT_TRUE(list.select(1) == 100);

    return true;
}

bool DoublyLinkedListTest::test5() {
    DoublyLinkedList list;
    list.insert_front(100);
    list.insert_back(100);
    list.insert(200,2);
    list.insert(300,3);
    list.insert(400,4);

    ASSERT_TRUE(list.replace(2,11));
    ASSERT_TRUE(list.select(2) == 11);
    ASSERT_TRUE(list.size() == 5);
    ASSERT_FALSE(list.replace(10, 500));
    return true;
}
bool DoublyLinkedListTest::test6() {
    DoublyLinkedList list;
    list.insert_front(50);
    list.insert_back(100);
    list.insert(75, 1);
    ASSERT_TRUE(list.size() == 3);
    ASSERT_TRUE(list.select(1) == 75);
    return true;
}
bool DoublyLinkedListTest::test7() {
    DoublyLinkedList list;
    //"Test7: inserting at different positions in the list",
    list.insert_back(10);
    list.insert_front(5);
    list.insert(2,1);

    ASSERT_TRUE(list.select(0)==5);
    ASSERT_TRUE(list.select(1)==2);
    ASSERT_TRUE(list.select(2)==10);
    return true;
}
bool DoublyLinkedListTest::test8() {
    DoublyLinkedList list;
    //"Test8: try to remove too many elements, then add a few elements"
    ASSERT_FALSE(list.remove_back())
    ASSERT_FALSE(list.remove_front())
    list.insert_back(1);
    list.insert_back(2);
    ASSERT_TRUE(list.insert_front(3));
    ASSERT_TRUE(list.insert_back(4));
    ASSERT_TRUE(list.insert(5,1));

    ASSERT_TRUE(list.select(0)==3);
    ASSERT_TRUE(list.select(1)==5);
    ASSERT_TRUE(list.select(2)==1);
    ASSERT_TRUE(list.select(3)==2);
    ASSERT_TRUE(list.select(4)==4);


    return true;
}
bool DoublyLinkedListTest::test9() {
    //"Test9: lots of inserts and deletes, all of them valid",
    DoublyLinkedList list;
    for (int i = 0; i < 500; i++) {
        ASSERT_TRUE(list.insert_front(i));
    }
    for (int i = 0; i < 250; i++) {
        ASSERT_TRUE(list.remove_front());
        ASSERT_TRUE(list.remove_back());
    }
    return true;
}
bool DoublyLinkedListTest::test10() {
    //"Test10: lots of inserts and deletes, some of them invalid"
    DoublyLinkedList list;

    ASSERT_TRUE(list.insert_front(10));
    ASSERT_TRUE(list.insert_back(20));
    ASSERT_TRUE(list.insert(15, 1));

    ASSERT_FALSE(list.insert(25, 10));
    ASSERT_FALSE(list.insert(30, -1));

    ASSERT_TRUE(list.remove_front());
    ASSERT_TRUE(list.remove_back());

    ASSERT_FALSE(list.remove(5));
    ASSERT_FALSE(list.remove(100));

    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.select(0) == 15);

    return true;
}
