#include "playwright_textbox.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/timer.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void PlaywrightTextbox::_bind_methods() {

}

PlaywrightTextbox::PlaywrightTextbox() {
  
}

PlaywrightTextbox::~PlaywrightTextbox() {
  
}

void PlaywrightTextbox::_ready() {
  if (Engine::get_singleton()->is_editor_hint()) {
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
  }
  else {
    // Instantiate packed scenes here.

    ResourceLoader* re_lo = ResourceLoader::get_singleton();
    text_reveal_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_reveal.tres");
    dlg_trigger_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_trigger.tres");
    dlg_end_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_end.tres");
    text_reveal_effect->set_name("testttt");
    UtilityFunctions::print(text_reveal_effect->get_name());
  }
}

void PlaywrightTextbox::set_textbox_margin(MarginContainer* _margin_container) {
  textbox_margin = _margin_container;
}

MarginContainer* PlaywrightTextbox::get_textbox_margin() const {
  return textbox_margin;
}

void PlaywrightTextbox::set_textbox_panel(PanelContainer* _panel_container) {
  textbox_panel = _panel_container;
}

PanelContainer* PlaywrightTextbox::get_textbox_panel() const {
  return textbox_panel;
}

void PlaywrightTextbox::set_dialogue_label(RichTextLabel* _rich_text_label) {
  dialogue_label = _rich_text_label;
}

RichTextLabel* PlaywrightTextbox::get_dialogue_label() const {
  return dialogue_label;
}

void PlaywrightTextbox::set_letter_display_timer(Timer* _timer) {
  letter_display_timer = _timer;
}

Timer* PlaywrightTextbox::get_letter_display_timer() const {
  return letter_display_timer;
}
