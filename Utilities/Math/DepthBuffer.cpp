#include "DepthBuffer.h"
#include <cmath>

DepthList::DepthList()
{
    head = nullptr;
}

DepthList::~DepthList()
{
    //we need to delete node by node
    std::cout << "Deleting the depth buffer..." << std::endl;
    DepthListNode* oldNode = head;
    DepthListNode* currentNode = head;

    while(currentNode->next != nullptr)
    {
        oldNode = currentNode;
        currentNode = currentNode->next;
        delete oldNode;
    }

    std::cout << "Depth Buffer Successfully Deleted." << std::endl;
}

void DepthList::add(float value)
{
    DepthListNode* newNode = new DepthListNode();
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

DepthListNode* DepthList::first()
{
    return head;
}

std::ostream& operator<<(std::ostream &os, DepthListNode& node)
{
    os << node.value;
    return os;
}

DepthBuffer::DepthBuffer(int image_width, int image_height)
{
    for(int i = image_width*image_height; i >= 0; i--)
        depth_list.add(INFINITY);

    current_position = depth_list.first();
    currentNode = 0;
}

DepthBuffer::~DepthBuffer()
{

}

float DepthBuffer::getCurrentDepth()
{
    return current_position->value;
}

void DepthBuffer::shift()
{
    if(current_position != nullptr)
    {
        current_position = current_position->next;
        currentNode++;
    }
}

int DepthBuffer::size()
{
    return depth_list.size;
}

void DepthBuffer::reset()
{
    current_position = depth_list.first();
    currentNode = 0;
}

void DepthBuffer::setCurrentDepth(float value)
{
    current_position->value = value;
}

std::ostream& operator<<(std::ostream& os, DepthBuffer& depthBuffer)
{
    os << "Node: " << depthBuffer.currentNode << " Value: " << *depthBuffer.current_position;
    return os;
}