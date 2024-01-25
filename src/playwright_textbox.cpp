#include "playwright_textbox.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/timer.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void PlaywrightTextbox::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_textbox_margin", "_margin_container"), &PlaywrightTextbox::set_textbox_margin);
  ClassDB::bind_method(D_METHOD("get_textbox_margin"), &PlaywrightTextbox::get_textbox_margin);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "textbox_margin", PROPERTY_HINT_NONE), "set_textbox_margin", "get_textbox_margin");
  ClassDB::bind_method(D_METHOD("set_textbox_panel", "_panel_container"), &PlaywrightTextbox::set_textbox_panel);
  ClassDB::bind_method(D_METHOD("get_textbox_panel"), &PlaywrightTextbox::get_textbox_panel);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "textbox_panel", PROPERTY_HINT_NONE), "set_textbox_panel", "get_textbox_panel");
  ClassDB::bind_method(D_METHOD("set_dialogue_label", "_rich_text_label"), &PlaywrightTextbox::set_dialogue_label);
  ClassDB::bind_method(D_METHOD("get_dialogue_label"), &PlaywrightTextbox::get_dialogue_label);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "dialogue_label", PROPERTY_HINT_NONE), "set_dialogue_label", "get_dialogue_label");
  ClassDB::bind_method(D_METHOD("set_letter_display_timer", "_timer"), &PlaywrightTextbox::set_letter_display_timer);
  ClassDB::bind_method(D_METHOD("get_letter_display_timer"), &PlaywrightTextbox::get_letter_display_timer);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "letter_display_timer", PROPERTY_HINT_NONE), "set_letter_display_timer", "get_letter_display_timer");
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
