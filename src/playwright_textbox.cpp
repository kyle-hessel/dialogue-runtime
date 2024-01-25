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
  ClassDB::bind_method(D_METHOD("set_textbox_margin_scene", "_margin_scene"), &PlaywrightTextbox::set_textbox_margin_scene);
  ClassDB::bind_method(D_METHOD("get_textbox_margin_scene"), &PlaywrightTextbox::get_textbox_margin_scene);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "textbox_margin_scene"), "set_textbox_margin_scene", "get_textbox_margin_scene");
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
    if (textbox_margin_scene != nullptr)
      textbox_margin = Object::cast_to<MarginContainer>(textbox_margin_scene->instantiate());
      textbox_panel = Object::cast_to<PanelContainer>(textbox_margin->get_child(0));
      dialogue_label = Object::cast_to<RichTextLabel>(textbox_panel->get_child(0)->get_child(0));
      dialogue_label->set_text("reeeee");
      add_child(textbox_margin);

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

void PlaywrightTextbox::set_textbox_margin_scene(Ref<PackedScene> _margin_scene) {
  textbox_margin_scene = _margin_scene;
}

MarginContainer* PlaywrightTextbox::get_textbox_margin() const {
  return textbox_margin;
}

Ref<PackedScene> PlaywrightTextbox::get_textbox_margin_scene() const {
  return textbox_margin_scene;
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
