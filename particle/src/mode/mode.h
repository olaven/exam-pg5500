#ifndef EMBEDDED_EXAM_MODE
#define EMBEDDED_EXAM_MODE

#include "../screen/layout.h" //TODO: can remove this once types are moved 
struct LayoutState
{
    int current_layout_index;
    int total_layout_count;
    Layout * layouts;
};

//TODO functions currently in mode.cpp 
//TODO: move over layout code from screen cpp/h

#endif
