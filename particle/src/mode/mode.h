#ifndef EMBEDDED_EXAM_MODE
#define EMBEDDED_EXAM_MODE

struct LayoutState
{
    int current_layout_index;
    int total_layout_count;
    Layout layouts[MAX_LAYOUT_COUNT];
};

//TODO functions currently in mode.cpp 
//TODO: move over layout code from screen cpp/h

#endif
