
//----------------------------------------------------------------------
// Author: Michael Calmette
// File:   bst_collection.h
// Implements a basic binary search tree
//----------------------------------------------------------------------


#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include <algorithm>           
#include "collection.h"


template<typename K, typename V>
class BSTCollection : public Collection<K,V>
{
public:

  // create an empty tree
  BSTCollection();
  
  // bst copy constructor
  BSTCollection(const BSTCollection <K,V>& rhs);

  // bst assignment operator
  BSTCollection<K,V>& operator=(const BSTCollection <K ,V >& rhs);

  // delete the bst
  ~BSTCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

  // return the height of the tree
  int height() const;
  
private:

  // tree node structure
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to calc tree height (can use std::max)
  int height(const Node* subtree_root) const;

  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of keys
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);
	
  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);
  
  // number of k-v pairs in the collection
  int collection_size; 

  // tree root
  Node* root;
   
};


// TODO: implement the above functions here ...

// Note that for the remove helper, since it returns a Node pointer,
// it must be defined as: 
//
    template<typename K, typename V>
    BSTCollection<K,V>::BSTCollection()
    {  
      collection_size = 0;
      root = nullptr;
    }
    

    template<typename K, typename V>
    BSTCollection<K,V>::BSTCollection(const BSTCollection <K,V>& rhs)
    { 
      collection_size = 0;
      root = nullptr;
      *this = rhs;
    }

    template<typename K, typename V>
    BSTCollection<K,V>& BSTCollection<K,V>::operator=(const BSTCollection <K ,V >& rhs)
    {
        if(this != &rhs)
        {
          make_empty(root);
          preorder_copy(rhs.root,root);
        }
        return *this;   
    }


    template<typename K, typename V>
    BSTCollection<K,V>::~BSTCollection()
    {
      make_empty(root);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::add(const K& a_key, const V& a_val)
    {
      Node* tmp = new Node;
      tmp->key = a_key;
      tmp->value = a_val;
      tmp->left = nullptr;
      tmp->right = nullptr;
      
      if(collection_size == 0)
      {
        root = tmp;
        collection_size++;
        return;
      }
       //iterate left and right
    
      Node* cur = root;
      while(cur != nullptr)
      {
          //if less than, go to left
          if(tmp -> key < cur -> key) //go left
          {
            if(cur -> left == nullptr)
            {
              cur -> left = tmp;
              cur = nullptr;
            }
            else
              cur = cur -> left;
          }
          else // go to the right
          {
            if(cur -> right == nullptr)
            {
              cur -> right = tmp;
              cur = nullptr;
            }
            else    
              cur = cur -> right;  
          } 
      }
      collection_size++;
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::remove(const K& a_key)
    {
      if(collection_size == 0)
        return;
      //helper function
      root = remove(a_key, root);
    }

    template<typename K, typename V>
    bool BSTCollection<K,V>::find(const K& search_key, V& the_val) const
    {
      //use looping
      if(collection_size == 0)
        return false;

      Node* tmp = new Node;
      tmp -> key = search_key;
      tmp -> value = the_val;
      tmp -> left = nullptr;
      tmp-> right = nullptr;
      
      Node* cur = root;
      //iterate left and right
      while(cur != nullptr)
      {
        if(cur->key == tmp->key) //match
        {
          the_val = cur -> value;
          return true;
        }
        else 
        {
          if(cur -> left == nullptr && cur->right == nullptr)
           cur = nullptr;
          else
          {
           if(cur-> key > tmp->key)
             cur = cur -> left;
           else
             cur = cur -> right;
          }
        }
      } 
      return false;
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
    {
      range_search(root, k1, k2, vals);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::keys(std::vector<K>& all_keys) const
    {
       inorder(root, all_keys);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
    {
      inorder(root, all_keys_sorted);
    }

    template<typename K, typename V>
    int BSTCollection<K,V>::size() const
    {
      return collection_size;
    }

    template<typename K, typename V>
    int BSTCollection<K,V>::height() const
    {
      return height(root);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::make_empty(Node* subtree_root)
    {
        if(subtree_root == nullptr)
          return;
        
        make_empty(subtree_root -> left);
        make_empty(subtree_root -> right);

        delete subtree_root;
        subtree_root = nullptr;
    }
    
    template<typename K, typename V>
    int BSTCollection<K,V>::height(const Node* subtree_root) const
    {
        if(subtree_root == nullptr)
          return 0;

        int leftHeight = height(subtree_root -> left);
        int rightHeight = height(subtree_root -> right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::inorder(const Node* subtree_root, std::vector<K>& keys) const
    {
       if(subtree_root == nullptr)
         return;
       inorder(subtree_root->left,keys);
       keys.push_back(subtree_root->key);
       inorder(subtree_root->right,keys);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::range_search(const Node* subtree_root, const K& k1, const K& k2,
                          std::vector<V>& vals) const
    {
        if(subtree_root == nullptr)
          return;
        
        range_search(subtree_root->left,k1,k2,vals);
        range_search(subtree_root->right,k1,k2,vals);

        if(subtree_root-> key >= k1 && subtree_root->key <= k2)
          vals.push_back(subtree_root->value);
    }

    template<typename K, typename V>
    void BSTCollection<K,V>::preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst)
    {
      if(subtree_root_src == nullptr)
        return;
      //visit node, then go left, and then go right
      preorder_copy(subtree_root_src->left,subtree_root_dst);
      add(subtree_root_src->key,subtree_root_src->value);
      preorder_copy(subtree_root_src->right,subtree_root_dst);
    }

    template<typename K, typename V>
    typename BSTCollection<K,V>::Node*
    BSTCollection<K,V>::remove(const K& key, Node* subtree_root)
    {
       if(subtree_root == nullptr)
         return subtree_root;
       
       if(subtree_root && key < subtree_root->key)//else check if need to go left 
          subtree_root->left = remove(key, subtree_root->left);
       else if(subtree_root && key > subtree_root->key)//else check if need to go right
          subtree_root->right = remove(key, subtree_root->right);
       else if(subtree_root && key == subtree_root->key)//if a match
       {
          Node* tmp = subtree_root;
          //no children
          if(subtree_root->left == nullptr && subtree_root->right == nullptr)
          {
           delete tmp;
           subtree_root = nullptr;
          }
          //subtree root has one child
          else if(subtree_root -> right == nullptr && subtree_root->left != nullptr)
          {
           subtree_root = subtree_root->left;
           delete tmp;
           tmp = nullptr;
          }
          else if(subtree_root->right != nullptr && subtree_root->left == nullptr)
          {
            subtree_root = subtree_root->right;
            delete tmp;
            tmp = nullptr;
          }
          else //subtree root has two children
          {
            Node* copy = subtree_root;
            tmp = subtree_root -> right;
            while(tmp->left != nullptr)
            {
             copy = tmp;
             tmp = tmp->left;
            }
            //redirect copy node
            if(copy != subtree_root)
            {
              copy->left = tmp->right;
            }
            tmp -> left = subtree_root->left;
            subtree_root->left= nullptr;

            if(subtree_root->right != tmp)
            {
              tmp->right = subtree_root->right;
            }
            delete subtree_root;
            subtree_root = tmp;
            copy = nullptr;
            tmp = nullptr;
          }
          collection_size--;
       }
       return subtree_root;
    }


#endif
