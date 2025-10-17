#include "PriorityQueue.h"
#include "TreeNode.h"
#include <vector>
#include <iostream>
#include <algorithm> // for std::sort, std::ranges

// Constructor: takes an initial vector of nodes
PriorityQueue::PriorityQueue(std::vector<TreeNode*> nodes) {
    items_ = nodes; // Copies everything into items_ 1:1

    //from beginning to end of items_, go through and sorty by higherPriority
    std::ranges::sort(items_, higherPriority);
}





// Return the number of elements in the queue
std::size_t PriorityQueue::size() const noexcept {
    return items_.size(); // Simple size function
}







// Return true if the queue is empty
bool PriorityQueue::empty() const noexcept {
    return items_.empty(); // true if empty, false if not
}







// Return the minimum element (items_.back()) or nullptr if empty
TreeNode* PriorityQueue::findMin() const noexcept {
    // If empty return nullptr
    if (items_.empty()) {
        return nullptr;
    }
    return items_.back();
}







// Remove and return the minimum element
TreeNode* PriorityQueue::extractMin() noexcept {
    // If empty return nullptr
    if (items_.empty()) {
        return nullptr;
    }
    // Return the last element
    TreeNode* min = items_.back();
    // Remove the last element
    items_.pop_back();
    return min;
}







// Remove the minimum element if it exists (similar to extract, but no return)
void PriorityQueue::deleteMin() noexcept {
    if (items_.empty()) {
        return;
    }
    items_.pop_back(); 
}







// Insert a node while keeping the vector sorted
void PriorityQueue::insert(TreeNode* node) {
    items_.push_back(node);

    // Sort the items_ vector by higherPriority, ranges is just (.begin(), .end(), higherPriority);
    std::ranges::sort(items_, higherPriority);
}







// Print the contents of the queue for debugging
void PriorityQueue::print(std::ostream& os) const {
    os << "PriorityQueue contents (front = lowest priority):\n";
    for (const auto& node : items_) {
        os << "{" << node->key_word << ": " << node->freq << "}\n";
    }
}






// Static comparator: determines ordering (freq desc, key_word asc)
bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept {
    if (a->freq != b->freq) {
        return a->freq > b->freq; // Higher Frequency First
    }
    return a->key_word < b->key_word; // Tie: smaller key_word first
}







// Optional check to verify the vector is sorted (for debugging)
bool PriorityQueue::isSorted() const {

    // Itereate through the items_ vector and make sure each element is greater than the next element using higherPriority
    for (size_t i = 0; i < items_.size() - 1; ++i) {
        if (!higherPriority(items_[i], items_[i + 1])) {
            return false;
        }
    }
    return true;
}
