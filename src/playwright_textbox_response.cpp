#include "playwright_textbox_response.h"
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

void PlaywrightTextboxResponse::_bind_methods() {
    
}

PlaywrightTextboxResponse::PlaywrightTextboxResponse() {
    player_selection = 0;
}

PlaywrightTextboxResponse::~PlaywrightTextboxResponse() {

}


void PlaywrightTextboxResponse::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	} 
    else {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
        ResourceLoader* re_lo = ResourceLoader::get_singleton();
        dlg_end_effect = re_lo->load("res://addons/playwright_runtime/resources/dialogue_label_end.tres");
        text_color_effect = re_lo->load("res://addons/playwright_runtime/resources/dialogue_label_color.tres");

        label_scene = re_lo->load("res://addons/playwright_runtime/scenes/dialogue_label.tscn");
        spacer_scene = re_lo->load("res://addons/playwright_runtime/scenes/dialogue_spacer.tscn");
    
        textbox_margin = Object::cast_to<MarginContainer>(textbox_margin_scene->instantiate());
        textbox_vbox = Object::cast_to<VBoxContainer>(textbox_margin->get_child(0)->get_child(0));
        dialogue_label = Object::cast_to<RichTextLabel>(textbox_vbox->get_child(0));

        dialogue_labels.append(dialogue_label); // dialogue_label is inherited from PlaywrightTextbox.
    }
}

void PlaywrightTextboxResponse::_unhandled_input(const Ref<InputEvent> &event) {
    if (event->is_action_pressed("ui_up") || event->is_action_pressed("ui_down")) {
        select_response(event);
    }
}

void PlaywrightTextboxResponse::begin_display_response(TypedArray<String> text_to_display) {
    dialogues = text_to_display;

    int l = 1; // start at one as one dialogue label already exists.
    while (l < dialogues.size()) {
        RichTextLabel* label_inst = Object::cast_to<RichTextLabel>(label_scene->instantiate());
        textbox_vbox->add_child(spacer_scene->instantiate());
        textbox_vbox->add_child(label_inst);
        dialogue_labels.append(label_inst);
        l++;
    }

    // ensure each RichTextLabel contains the proper effects and populate text for each of them w/ effects included.
    for (int d = 0; d < dialogue_labels.size(); d++) {
        RichTextLabel* dlg_label = Object::cast_to<RichTextLabel>(dialogue_labels[d]); // FIXME: crashes - is null.
        UtilityFunctions::print(dlg_label);
        dlg_label->install_effect(text_color_effect);
        dlg_label->install_effect(dlg_end_effect);
        color_text_field_at_pos(d);
    }
}

void PlaywrightTextboxResponse::select_response(const Ref<InputEvent> &event) {
    if (event->is_action_pressed("ui_up")) {
        if (player_selection > 0) {
            player_selection--;
            // refresh dialogue response fields
            for (int d = 0; d < dialogue_labels.size(); d++) {
                color_text_field_at_pos(d);
            }
        }
    }
    else if (event->is_action_pressed("ui_down")) {
        if (player_selection < dialogue_labels.size() - 1) {
            player_selection++;
            // refresh dialogue response fields
            for (int d = 0; d < dialogue_labels.size(); d++) {
                color_text_field_at_pos(d);
            }
        }
    }
}

void PlaywrightTextboxResponse::color_text_field_at_pos(int pos) {
    RichTextLabel* dlg_label = Object::cast_to<RichTextLabel>(dialogue_labels[pos]);
    //String dlg = Object::cast_to<String>(dialogues[pos]);
    if (pos == player_selection) {
        String dlg_with_bbcode = "[highlight_color color=#417fc2]" + String(dialogues[pos]) + "[/highlight_color]";
        dlg_label->parse_bbcode(dlg_with_bbcode);
    }
    else {
        String dlg_with_bbcode = "[highlight_color color=#ffffff]" + String(dialogues[pos]) + "[/highlight_color]";
        dlg_label->parse_bbcode(dlg_with_bbcode);
    }
}

void PlaywrightTextboxResponse::set_player_selection(int _selection) {
    player_selection = _selection;
}

int PlaywrightTextboxResponse::get_player_selection() const {
    return player_selection;
}