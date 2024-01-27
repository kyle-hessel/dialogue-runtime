#ifndef RICH_TEXT_EFFECT_REVEAL_H
#define RICH_TEXT_EFFECT_REVEAL_H

#include "playwright_textbox.h"

#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/char_fx_transform.hpp>
#include <godot_cpp/classes/text_server_manager.hpp>
#include <godot_cpp/classes/text_server.hpp>

class CharFXTransform;

namespace godot {
	class RichTextEffectReveal: public RichTextEffect {
		GDCLASS(RichTextEffectReveal, RichTextEffect)
		
		private:
			TextServerManager* text_server_manager;
			Ref<TextServer> text_server;
		
		protected:
			static void _bind_methods();
		
		public:
			RichTextEffectReveal();
			~RichTextEffectReveal();
			
			PlaywrightTextbox* owning_textbox;
			
			virtual bool _process_custom_fx(const Ref<CharFXTransform> &char_fx) const override;
			
			void fetch_text_server();
	};
}

#endif
