#include "rich_text_effect_reveal.h"

#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/char_fx_transform.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/text_server_manager.hpp>

using namespace godot;

RichTextEffectReveal::RichTextEffectReveal() {
	bbcode = "reveal";
}

RichTextEffectReveal::~RichTextEffectReveal() {
	
}

void RichTextEffectReveal::_bind_methods() {
	
}

bool RichTextEffectReveal::_process_custom_fx(const Ref<CharFXTransform> &char_fx) const {
	return true;
}

Ref<TextServer> RichTextEffectReveal::get_text_server() {
	text_server_manager = TextServerManager::get_singleton();
	return text_server_manager->get_primary_interface();
}
