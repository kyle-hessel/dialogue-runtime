#include "playwright_textbox.h"
#include "rich_text_effect_reveal.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/timer.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void PlaywrightTextbox::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_textbox_margin_scene", "_margin_scene"), &PlaywrightTextbox::set_textbox_margin_scene);
  ClassDB::bind_method(D_METHOD("get_textbox_margin_scene"), &PlaywrightTextbox::get_textbox_margin_scene);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::OBJECT, "textbox_margin_scene"), "set_textbox_margin_scene", "get_textbox_margin_scene");
  ClassDB::bind_method(D_METHOD("set_letter_time", "_letter_time"), &PlaywrightTextbox::set_letter_time);
  ClassDB::bind_method(D_METHOD("get_letter_time"), &PlaywrightTextbox::get_letter_time);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::FLOAT, "letter_time"), "set_letter_time", "get_letter_time");
  ClassDB::bind_method(D_METHOD("set_space_time", "_space_time"), &PlaywrightTextbox::set_space_time);
  ClassDB::bind_method(D_METHOD("get_space_time"), &PlaywrightTextbox::get_space_time);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::FLOAT, "space_time"), "set_space_time", "get_space_time");
  ClassDB::bind_method(D_METHOD("set_punctuation_time", "_punc_time"), &PlaywrightTextbox::set_punctuation_time);
  ClassDB::bind_method(D_METHOD("get_punctuation_time"), &PlaywrightTextbox::get_punctuation_time);
  ClassDB::add_property("PlaywrightTextbox", PropertyInfo(Variant::FLOAT, "punctuation_time"), "set_punctuation_time", "get_punctuation_time");
  
  ClassDB::bind_method(D_METHOD("_on_letter_display_timeout"), &PlaywrightTextbox::_on_letter_display_timeout);
  ClassDB::bind_method(D_METHOD("_on_signal_show_entire_line"), &PlaywrightTextbox::_on_signal_show_entire_line);
  ClassDB::bind_method(D_METHOD("increment_letter"), &PlaywrightTextbox::increment_letter);

  ADD_SIGNAL(MethodInfo("finished_displaying"));
  
}

PlaywrightTextbox::PlaywrightTextbox() {
  letter_display_timer = memnew(Timer);

  letter_time = 0.03;
  space_time = 0.06;
  punctuation_time = 0.2;
  
  dialogue = "";
  letter_index = 0;
  
  reveal_pos = 0;
  advance_letter = false;
}

PlaywrightTextbox::~PlaywrightTextbox() {
  
}

void PlaywrightTextbox::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
	else {
		// Instantiate PackedScenes here.
		if (textbox_margin_scene != nullptr) {
			textbox_margin = Object::cast_to<MarginContainer>(textbox_margin_scene->instantiate());
			textbox_panel = Object::cast_to<PanelContainer>(textbox_margin->get_child(0));
			dialogue_label = Object::cast_to<RichTextLabel>(textbox_panel->get_child(0)->get_child(0));
			add_child(textbox_margin);
			
			// set up some properties on the Timer, as it isn't a part of the PackedScene.
			letter_display_timer->set_wait_time(0.05);
			letter_display_timer->set_one_shot(true);
			add_child(letter_display_timer);
		}

		// load all effect scenes so that they can be installed.
		ResourceLoader* re_lo = ResourceLoader::get_singleton();
		// This is created as a local variable to avoid a circular dependecy in the header of this class and PlaywrightTextbox. Wahoo!
		Ref<RichTextEffectReveal> text_reveal_effect = re_lo->load("res://addons/playwright_runtime/resources/rich_text_effect_reveal.tres");
		dlg_trigger_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_trigger.tres");
		dlg_end_effect = re_lo->load("res://assets/UI/dialogue/text/dialogue_label_end.tres");
		text_reveal_effect->fetch_text_server();
		text_reveal_effect->owning_textbox = this;
		text_reveal_effect->set_name("TextReveal");
		dlg_trigger_effect->set_name("DialogueTrigger");
		dlg_end_effect->set_name("DialogueEnd");
		
		// install the reveal, trigger, and end effects.
		dialogue_label->install_effect(text_reveal_effect);
		dialogue_label->install_effect(dlg_trigger_effect);
		dialogue_label->install_effect(dlg_end_effect);
		
		dialogue_label->parse_bbcode("[reveal]reeeee[/reveal]");

		TypedArray<RichTextEffect> rt_effects = dialogue_label->get_effects();
		for (int e = 0; e < rt_effects.size(); e++) {
			if (Ref<RichTextEffect> rte = Object::cast_to<RichTextEffect>(rt_effects[e]); rte != nullptr) {
				// if the RichTextEffect in question is a RichTextEffectReveal, wire up some signals.
				if (rte == text_reveal_effect) {
					UtilityFunctions::print(text_reveal_effect->get_name());
					
					// Signals for incrementing the text reveal effect.
					letter_display_timer->connect("timeout", Callable(this, "_on_letter_display_timeout"));
					letter_display_timer->connect("timeout", Callable(this, "increment_letter"));
					// Signal for displaying the entire line at once, skipping the above effect.
					connect("finished_displaying", Callable(this, "_on_signal_show_entire_line"));
				}
			}
		}
		
		// ### this was just a test to see if the reveal effect was working; delete!
		//advance_letter = true;
	}
}

void PlaywrightTextbox::begin_display_dialogue(String& text_to_display) {
	
}

void PlaywrightTextbox::increment_letter() {
	
}

void PlaywrightTextbox::display_line() {
	
}

void PlaywrightTextbox::_on_letter_display_timeout() {
	advance_letter = true;
}

void PlaywrightTextbox::_on_signal_show_entire_line() {
	reveal_pos = 500;
}

// getters and setters
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

void PlaywrightTextbox::set_letter_time(float _letter_time) {
	letter_time = _letter_time;
}

float PlaywrightTextbox::get_letter_time() const {
	return letter_time;
}

void PlaywrightTextbox::set_space_time(float _space_time) {
	space_time = _space_time;
}

float PlaywrightTextbox::get_space_time() const {
	return space_time;
}

void PlaywrightTextbox::set_punctuation_time(float _punc_time) {
	punctuation_time = _punc_time;
}

float PlaywrightTextbox::get_punctuation_time() const {
	return punctuation_time;
}
