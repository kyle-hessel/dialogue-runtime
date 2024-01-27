#include "rich_text_effect_reveal.h"
#include "playwright_textbox.h"

#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/char_fx_transform.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/text_server_manager.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/signal.hpp>

using namespace godot;

RichTextEffectReveal::RichTextEffectReveal() {
	bbcode = "reveal";
}

RichTextEffectReveal::~RichTextEffectReveal() {
	
}

void RichTextEffectReveal::_bind_methods() {
	
}

bool RichTextEffectReveal::_process_custom_fx(const Ref<CharFXTransform> &char_fx) const {
	if (owning_textbox != nullptr) {
		UtilityFunctions::print(UtilityFunctions::var_to_str(char_fx->is_visible()));
		if (char_fx->get_relative_index() > owning_textbox->reveal_pos) {
			char_fx->set_visibility(false);
		}
		
		if (owning_textbox->advance_letter) {
			owning_textbox->reveal_pos++;
			owning_textbox->advance_letter = false;
		}
	}
	
	return true;
}

void RichTextEffectReveal::fetch_text_server() {
	text_server_manager = TextServerManager::get_singleton();
	text_server = text_server_manager->get_primary_interface();
}
