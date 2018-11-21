#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

void InternalNode::addLeft() {

    BTreeNode* ptr = children[0];
    InternalNode* left = (InternalNode*)getLeftSibling();

    for(int i = 0; i < internalSize; i++) { //move everything to the left onces
        children[i] = children[i + 1];
    }

    count--;

    left->children[left->count] = ptr;
    left->count++;

    for(int j = 0; j < count; j++) {
        keys[j] = children[j]->getMinimum();
    }

    for(int k = 0; k < left->count; k++) {
        left->keys[k] = left->children[k]->getMinimum();
    }
}

void InternalNode::addRight() {

    BTreeNode* ptr = children[0];
    InternalNode* right = (InternalNode*)getRightSibling();

    for(int i = 0; i < internalSize; i++) { //move everything to the right onces
        children[i] = children[i - 1];
    }

    right->count++;
    right->children[0] = ptr;

    count--;

    for(int j = 0; j < count; j++) {
        keys[j] = children[j]->getMinimum();
    }

    for(int k = 0; k < right->count; k++) {
        right->keys[k] = right->children[k]->getMinimum();
    }
}


InternalNode* InternalNode::insert(int value)
{
    int pos;
    for(pos = 0; pos <  (count - 1); pos++) { //stop at position of internal node to insert
        if(value < keys[pos + 1]) {
            break;
        }
    }

    if(pos == (count - 1)) { //add at furthest right
        BTreeNode* ptr = (children[pos]->insert(value));
        if(ptr) { //if there is a split
            children[count]=ptr;
            count++;
        }
    }

    else { //then there is a split in middle of children and need to adjust the pointers
        BTreeNode* ptr = (children[pos]->insert(value));
        int n;
        if(ptr) { //if split
            if (!children[pos + 1]) {
			children[pos + 1] = ptr;
        }

		    else {//move pointers to children
              	for (n = count; n > (pos + 1); n--) {
				    children[n] = children[n -1];
                }
			    children[n] = ptr;
		    }
                count ++;
        }
    }

    for(int index = 0; index < count; index++) { //adjust keys
        keys[index] = children[index]->getMinimum();
    }

    if(leftSibling) { //adjust keys
        InternalNode* left = (InternalNode*)getLeftSibling();
        for(int j = 0; j < leftSibling->getCount(); j++){
            left->keys[j] = left->children[j]->getMinimum();
        }
    }

    if(rightSibling) { //adjust keys
        InternalNode* right = (InternalNode*)getRightSibling();
        for(int i = 0; i < rightSibling->getCount(); i++) {
            right->keys[i] = right->children[i]->getMinimum();
        }
    }

    if(count > internalSize) {
        if(leftSibling && leftSibling->getCount() < internalSize) { //check left
            addLeft();
        }
        else if(rightSibling && rightSibling->getCount() < internalSize) { //check right
            addRight();
        }
        else { //split
            return split(value);
        }
    }


  // students must write this
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
    children[0] = oldRoot;
    children[1] = node2;
    keys[0] = oldRoot->getMinimum();
    keys[1] = node2->getMinimum();
    count = 2;
  // students must write this
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  // students may write this
} // InternalNode::insert()

InternalNode* InternalNode::split(int value) {

    InternalNode* new_node = new InternalNode(internalSize, leafSize, parent, this, rightSibling);

    if(rightSibling) { //if there is a right sibling
        // BTreeNode* new_tree_node = rightSibling;
        rightSibling->setLeftSibling(new_node);
    }

    rightSibling = new_node;
    InternalNode* right = (InternalNode*)getRightSibling();

    for(int i = internalSize - 1; i >= (internalSize + 1) / 2; i--) {
        //new_node->insert(children[i]);
        right-> children[i-1] = children[count-1];
        right-> keys[i-1] = keys[count-1];
        right-> count++;

    }

    return right;
}

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()
