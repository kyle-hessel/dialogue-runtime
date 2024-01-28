#ifndef PLAYWRIGHT_TEXTBOX_RESPONSE_H
#define PLAYWRIGHT_TEXTBOX_RESPONSE_H

#include "playwright_textbox.h"

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include <godot_cpp/variant/array.hpp>

namespace godot {
    class PlaywrightTextboxResponse: public PlaywrightTextbox {
        GDCLASS(PlaywrightTextboxResponse, PlaywrightTextbox)

        private:
            Ref<PackedScene> label_scene;
            Ref<PackedScene> spacer_scene;

            Ref<RichTextEffect> text_color_effect;

            VBoxContainer* textbox_vbox;

            TypedArray<RichTextLabel> dialogue_labels;
            TypedArray<String> dialogues;

            int player_selection;
        
        protected:
            static void _bind_methods();
        
        public:
            PlaywrightTextboxResponse();
            ~PlaywrightTextboxResponse();



            void _ready() override;
    };
}

#endif