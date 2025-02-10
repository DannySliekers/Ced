#include <stdbool.h>

#ifndef SELECTEDTEXT_H
#define SELECTEDTEXT_H

typedef struct {
    int begin_line;
    int end_line;
    int begin_col;
    int end_col;
} SelectedText;

bool is_selected_text_set(SelectedText selected_text);
void reset_selected_text(SelectedText* selected_text);

#endif