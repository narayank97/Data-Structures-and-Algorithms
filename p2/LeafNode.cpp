#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
//    int last;
    if(count < leafSize){ //makes sure leaf node is not full
        sort(value);
        return NULL;
    }

//    addValue(value, last);

    else if(leftSibling && leftSibling->getCount() < leafSize) { //check left
        //need method add value to left, dont know if you want function or just code here
        if(value < values[0]) {
            leftSibling->insert(value);
        }
        else {
            leftSibling->insert(values[0]);
            for(int i = 1; i < leafSize; i++) { // move everything up one
                values[i - 1] = values[i];
            }
            count --;
            return insert(value);
        }
    }

    else if(rightSibling && rightSibling->getCount() < leafSize) { //check right
        //need method to add value to right, dont know if you want function or just code here
        if(value > values[leafSize - 1]) { //give max to right
            rightSibling->insert(value); // if value is greater hand it off
        }
        else { // if last value stored is greater, hand it off and replace it with the new one
            rightSibling->insert(values[leafSize - 1]);
            count --;
            return insert(value);
        }
    }

    else { //split
        split(value);
    }
  // students must write this
  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

void LeafNode::sort(int value) {

    values[count]=value;
	count ++;
    int temp;
	for(int i = count - 1; i > 0; i--){
        if(values[i - 1] > values[i]) {
            temp = values[i];
            values[i] = values[i - 1];
            values[i -1] = temp;
        }
		else {
			break;
        }

	}

}

LeafNode* LeafNode::split(int value) {

    LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);

    /*
    (leafSize + 1) / 2 gives index of last value guaranteed to move to newRight
    ((leafSIze + 1) / 2) - 1 gives the value that could go depending on if the
    new value or the old value stored at that position in values[] is larger
    */

    if(rightSibling) { //if there is a right sibling
        rightSibling->setLeftSibling(ptr);
    }

    rightSibling = ptr;

    for(int i = leafSize - 1; i >= (leafSize + 1) / 2; i--) {
        ptr->insert(values[i]);
    }
    if (value > values[((leafSize + 1) / 2) - 1]) { //given value is greater than middle positon
        ptr->insert(value);
    }
    else {
        ptr->insert(values[((leafSize + 1) / 2) - 1]);
        values[((leafSize + 1) / 2) - 1] = value;
    }

    count = (leafSize + 1) / 2;

    return ptr;

}
