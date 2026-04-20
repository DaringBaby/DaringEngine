#include <string>
#include "scripts/classes/Character.h"
extern std::string current_ui_text;
extern bool is_ui_visible;

void ui_show_message(std::string text);
void ui_close_message();
void ui_show_item_get_message(std::string item_name);

extern Character chara;
