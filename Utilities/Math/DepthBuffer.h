#ifndef COMP_371_PROJECT_DEPTHBUFFER_H
#define COMP_371_PROJECT_DEPTHBUFFER_H

#include "Ray.h"
#include <vector>

struct DepthListNode
{
    public:
        float value;
        DepthListNode* next;
        friend std::ostream& operator<<(std::ostream& os, DepthListNode& node);
};

class DepthList
{
    //linked list for storing depths
    private:
        DepthListNode* head;

    public:
        DepthList();
        ~DepthList();
        int size;
        void add(float value);
        DepthListNode* first();
};

class DepthBuffer
{
    private:
        DepthList depth_list;
        DepthListNode* current_position;
        int currentNode;

    public:
        DepthBuffer(int image_width, int image_height);
        ~DepthBuffer();
        float getCurrentDepth(); //return the depth in the current node
        void shift(); //shifts the depth list to the next depth
        int size();
        void reset(); //moves the current position pointer back to the head
        void setCurrentDepth(float value);
        friend std::ostream& operator<<(std::ostream& os, DepthBuffer& depthBuffer);
};

#endif
