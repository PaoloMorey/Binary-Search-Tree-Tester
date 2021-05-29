#ifndef TESTER_BINARY_SEARCH_TREE_TESTER_H
#define TESTER_BINARY_SEARCH_TREE_TESTER_H

#include "BSTree.h"
#include "Mocker.h"

#define NUMBER_OF_TESTS 15

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

class Tester {
private:

public:

    template<typename T>
    static void testBSTree(Mocker, vector<T>);

    static void execute() {
        Mocker mocker;

        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            unsigned int size = mocker.generateRandomInt(10);
            int *elements = mocker.generateRandomArray<int>(size);
            testBSTree<int>(mocker, vector<int>(elements, elements + size));
            cout << "Test[" << i + 1 << "] sucessful" << endl;
        }

        // Test displayPreOrder(), displayInOrder(), displayPostOrder(), height() and isBalanced() functions
        auto test = new BSTree<int>;
        auto test1 = new BSTree<int>;
        vector<int> x = {9, 77, 41, 13, 15, 19, 69, 55, 95, 58};
        vector<int> y = {41, 24, 65, 12, 30, 51, 76, 8, 15, 27, 36};
        for (int i : x) test->insert(i);
        for (int i : y) test1->insert(i);

        ASSERT(test->displayInOrder() == "9 13 15 19 41 55 58 69 77 95 ", "There is a problem with the displayInOrder() function");
        ASSERT(test1->displayInOrder() == "8 12 15 24 27 30 36 41 51 65 76 ", "There is a problem with the displayInOrder() function");
        cout << "displayInOrder() function test sucessful" << endl;

        ASSERT(test->displayPreOrder() == "9 77 41 13 15 19 69 55 58 95 ", "There is a problem with the displayPreOrder() function");
        ASSERT(test1->displayPreOrder() == "41 24 12 8 15 30 27 36 65 51 76 ", "There is a problem with the displayPreOrder() function");
        cout << "displayPreOrder() function test sucessful" << endl;

        ASSERT(test->displayPostOrder() == "19 15 13 58 55 69 41 95 77 9 ", "There is a problem with the displayPostOrder() function");
        ASSERT(test1->displayPostOrder() == "8 15 12 27 36 30 24 51 76 65 41 ", "There is a problem with the displayPostOrder() function");
        cout << "displayPostOrder() function test sucessful" << endl;

        ASSERT(test->height() == 5, "There is a problem with the height() function");
        ASSERT(test1->height() == 3, "There is a problem with the height() function");
        cout << "height() function test sucessful" << endl;

        ASSERT(!test->isBalanced(), "There is a problem with the isBalanced() function");
        ASSERT(test1->isBalanced(), "There is a problem with the isBalanced() function");
        cout << "isBalanced() function test sucessful" << endl;
    };

    template<typename T>
    static void sortAndPrune(vector<T> &vec);
};

template<typename T>
void Tester::sortAndPrune(vector<T> &vec) {
    sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

template<typename T>
void Tester::testBSTree(Mocker mocker, vector<T> elements) {
    auto test = new BSTree<T>;
    for (int j = 0; j < elements.size(); ++j) {
        test->insert(elements[j]);
        ASSERT(test->find(elements[j]), "There is a problem with the insert() or find() function");
    }

    sortAndPrune(elements);

    ASSERT(elements.size() == test->size(), "There is a problem with the insert() or size() function");
    ASSERT(elements[elements.size() - 1] == test->maxValue(), "There is a problem with the maxValue() function");
    ASSERT(elements[0] == test->minValue(), "There is a problem with the maxValue() function");

    unsigned int toRemove = mocker.generateRandomInt(1, elements.size());
    for (int j = 0; j < toRemove; ++j) {
        unsigned int index = mocker.generateRandomInt(0, elements.size() - 1);
        T temp = elements.at(index);
        elements.erase(elements.begin() + index);
        test->remove(temp);
        ASSERT(!test->find(temp), "There is a problem with the remove() or find() function");
    }

    ASSERT(elements.size() == test->size(), "There is a problem with the remove() or size() function");
}


#endif //TESTER_BINARY_SEARCH_TREE_TESTER_H
