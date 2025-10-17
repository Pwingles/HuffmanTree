//
// Created by Kevin Rodriguez on 10/15/25.
//

#ifndef TREENODE_H
#define TREENODE_H

#pragma once
#include <string>


// Hold data for each node in the binary search tree

struct TreeNode {
    std::string key_word;
    int freq;
    TreeNode* left;
    TreeNode* right;


    // Constructor Each node is initialized with at least a word.
    explicit TreeNode(const std::string& w)
    : key_word(w), freq(1), left(nullptr), right(nullptr) {}
};







/**
 * Note to self (efficiency of initializer list):
 *
 * the differences between TreeNode(const std::string& w){
 *   word = w;
 *   count = 1;
 *   left = nullptr;
 *   right = nullptr;
 * }
 *
 *
 * and TreeNode(const std::string& w) : word(w), count(1), left(nullptr), right(nullptr) {}
 *
 *
 * : is an initializer list, in which word is created right away instead of
 * word being created into nothing then assigned w.
 */


#endif //TREENODE_H
