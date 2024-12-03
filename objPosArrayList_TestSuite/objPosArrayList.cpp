#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize; 
}

void objPosArrayList::insertHead(objPos thisPos)
{
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1];
    }
    
    aList[0] = thisPos;  
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    // Shift all elements to the left
    for (int i = 0; i < listSize - 1; ++i) {
        aList[i] = aList[i + 1];
    }
    
    listSize--;
}

void objPosArrayList::removeTail()
{   
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}