#ifndef PLAYWRIGHT_TEXTBOX_H
#define PLAYWRIGHT_TEXTBOX_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/timer.hpp>

#include <godot_cpp/variant/string.hpp>

namespace godot {
	class PlaywrightTextbox : public CanvasLayer {
		GDCLASS(PlaywrightTextbox, CanvasLayer)
			
		private:
			PanelContainer* textbox_panel;
			Timer* letter_display_timer;
			
			Ref<RichTextEffect> dlg_trigger_effect;

			const int MAX_WIDTH = 256;

			String dialogue;
			int letter_index;

			float letter_time;
			float space_time;
			float punctuation_time;

			void begin_display_dialogue(const String &text_to_display);
			void increment_letter();

		protected:
			static void _bind_methods();

			MarginContainer* textbox_margin;

			Ref<PackedScene> textbox_margin_scene;

			RichTextLabel* dialogue_label;
			Ref<RichTextEffect> dlg_end_effect;

		public:
			PlaywrightTextbox();
			~PlaywrightTextbox();

			void display_line();
			
			int reveal_pos;
			bool advance_letter;
			
			void _on_letter_display_timeout();
			void _on_signal_show_entire_line();

			void set_textbox_margin(MarginContainer* _margin_container);
			void set_textbox_margin_scene(Ref<PackedScene> _margin_scene);
			MarginContainer* get_textbox_margin() const;
			Ref<PackedScene> get_textbox_margin_scene() const;

			void set_textbox_panel(PanelContainer* _panel_container);
			PanelContainer* get_textbox_panel() const;

			void set_dialogue_label(RichTextLabel* _rich_text_label);
			RichTextLabel* get_dialogue_label() const;

			void set_letter_display_timer(Timer* _timer);
			Timer* get_letter_display_timer() const;

			void set_letter_time(float _letter_time);
			float get_letter_time() const;

			void set_space_time(float _space_time);
			float get_space_time() const;

			void set_punctuation_time(float _punc_time);
			float get_punctuation_time() const;
				  
			void _ready() override;
	};
}
#endif
