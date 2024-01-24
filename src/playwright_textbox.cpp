#include "playwright_textbox.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void PlaywrightTextbox::_bind_methods() {
  
}

PlaywrightTextbox::PlaywrightTextbox() {
  
}

PlaywrightTextbox::~PlaywrightTextbox() {
  
}

void PlaywrightTextbox::_ready() {
  ResourceLoader* re_lo = ResourceLoader::get_singleton();
  text_reveal_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_reveal.tres");
  dlg_trigger_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_trigger.tres");
  dlg_end_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_end.tres");
  text_reveal_effect->set_name("testttt");
  UtilityFunctions::print(text_reveal_effect->get_name());
}
