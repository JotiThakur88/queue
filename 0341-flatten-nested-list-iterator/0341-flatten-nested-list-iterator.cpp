#include <vector>
#include <stack>
using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     bool isInteger() const;
 *     int getInteger() const;
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
private:
    stack<NestedInteger> st;

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Push elements in reverse order
        for (int i = nestedList.size() - 1; i >= 0; i--) {
            st.push(nestedList[i]);
        }
    }

    int next() {
        int val = st.top().getInteger();
        st.pop();
        return val;
    }

    bool hasNext() {
        while (!st.empty()) {
            NestedInteger curr = st.top();

            if (curr.isInteger()) {
                return true;
            }

            // If it's a list, expand it
            st.pop();
            vector<NestedInteger> lst = curr.getList();

            for (int i = lst.size() - 1; i >= 0; i--) {
                st.push(lst[i]);
            }
        }
        return false;
    }
};