#include "scripts/engine/ui.h"

std::string current_ui_text = "";
bool is_ui_visible = false;

void ui_show_message(std::string text) {
    current_ui_text = text;
    is_ui_visible = true;
}

void ui_close_message() {
    current_ui_text = "";
    is_ui_visible = false;
}

void ui_show_item_get_message(std::string item_name) {
    // def name for now
    current_ui_text = chara.get_name() + " obtained: item name.";
    is_ui_visible = true;
}
