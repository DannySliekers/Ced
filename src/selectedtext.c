#include <stdbool.h>
#include "selectedtext.h"

bool is_selected_text_set(SelectedText selected_text) {
    return selected_text.begin_col != -1 
        || selected_text.begin_line != -1
        || selected_text.end_col != -1
        || selected_text.end_line != -1;

}

void reset_selected_text(SelectedText* selected_text) {
    selected_text->begin_col = -1;
    selected_text->end_col = -1;
    selected_text->begin_line = -1;
    selected_text->end_line = -1;
}