#include "playwright_textbox_response.h"
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/variant/array.hpp>

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
        dialogue_labels.append(dialogue_label);
    }
}

void PlaywrightTextboxResponse::_unhandled_input(const Ref<InputEvent> &event) {

}

void PlaywrightTextboxResponse::begin_display_response(TypedArray<String>) {

}

void PlaywrightTextboxResponse::select_response(const Ref<InputEvent> &event) {

}

void PlaywrightTextboxResponse::color_text_field_at_pos(int pos) {

}