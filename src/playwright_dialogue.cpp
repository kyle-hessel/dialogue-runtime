#include "playwright_dialogue.h"

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>

using namespace godot;

void PlaywrightDialogue::_bind_methods() {
	BIND_ENUM_CONSTANT(DEFAULT);
    BIND_ENUM_CONSTANT(RESPONSE);
    BIND_ENUM_CONSTANT(CALL);
    BIND_ENUM_CONSTANT(MESSAGE);
    BIND_ENUM_CONSTANT(SHOUT);

    ClassDB::bind_method(D_METHOD("set_dialogue_type", "_dlg_type"), &PlaywrightDialogue::set_dialogue_type);
  	ClassDB::bind_method(D_METHOD("get_dialogue_type"), &PlaywrightDialogue::get_dialogue_type);
  	ClassDB::add_property("PlaywrightDialogue", PropertyInfo(Variant::INT, "dialogue_type", PROPERTY_HINT_ENUM, "DEFAULT:0,RESPONSE:1,CALL:2,MESSAGE:3,SHOUT:4"), "set_dialogue_type", "get_dialogue_type");
    ClassDB::bind_method(D_METHOD("set_dialogue_options", "_dlg_options"), &PlaywrightDialogue::set_dialogue_options);
    ClassDB::bind_method(D_METHOD("get_dialogue_options"), &PlaywrightDialogue::get_dialogue_options);
    ClassDB::add_property("PlaywrightDialogue", PropertyInfo(Variant::ARRAY, "dialogue_options"), "set_dialogue_options", "get_dialogue_options");
    ClassDB::bind_method(D_METHOD("set_speaker", "_spkr"), &PlaywrightDialogue::set_speaker);
    ClassDB::bind_method(D_METHOD("get_speaker"), &PlaywrightDialogue::get_speaker);
    ClassDB::add_property("PlaywrightDialogue", PropertyInfo(Variant::STRING, "speaker"), "set_speaker", "get_speaker");
    ClassDB::bind_method(D_METHOD("set_next_dialogue", "_next_dlg"), &PlaywrightDialogue::set_next_dialogue);
    ClassDB::bind_method(D_METHOD("get_next_dialogue"), &PlaywrightDialogue::get_next_dialogue);
    ClassDB::add_property("PlaywrightDialogue", PropertyInfo(Variant::OBJECT, "next_dialogue", PROPERTY_HINT_RESOURCE_TYPE, "PlaywrightDialogue"), "set_next_dialogue", "get_next_dialogue");
}

PlaywrightDialogue::PlaywrightDialogue() {
    dialogue_type = DIALOGUE_TYPE::DEFAULT;
    speaker = "";
}

PlaywrightDialogue::~PlaywrightDialogue() {

}

void PlaywrightDialogue::set_dialogue_type(DIALOGUE_TYPE _dlg_type) {
    dialogue_type = _dlg_type;
}


PlaywrightDialogue::DIALOGUE_TYPE PlaywrightDialogue::get_dialogue_type() const {
    return dialogue_type;
}

void PlaywrightDialogue::set_dialogue_options(TypedArray<Array> _dlg_options) {
    dialogue_options = _dlg_options;
}

TypedArray<Array> PlaywrightDialogue::get_dialogue_options() const {
    return dialogue_options;
}

void PlaywrightDialogue::set_speaker(const String &_spkr) {
    speaker = _spkr;
}

String PlaywrightDialogue::get_speaker() const {
    return speaker;
}

void PlaywrightDialogue::set_next_dialogue(Ref<PlaywrightDialogue> _next_dlg) {
    next_dialogue = _next_dlg;
}

Ref<PlaywrightDialogue> PlaywrightDialogue::get_next_dialogue() const {
    return next_dialogue;
}