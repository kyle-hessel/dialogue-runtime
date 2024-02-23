#ifndef PLAYWRIGHT_DIALOGUE_H
#define PLAYWRIGHT_DIALOGUE_H

#include <godot_cpp/classes/resource.hpp>

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>

namespace godot {

    class PlaywrightDialogue : public Resource {
        GDCLASS(PlaywrightDialogue, Resource)

        protected:
			static void _bind_methods();

        public:
            enum DIALOGUE_TYPE {
                DEFAULT = 0,
                RESPONSE = 1,
                CALL = 2,
                MESSAGE = 3,
                SHOUT = 4
            };

			PlaywrightDialogue();
			~PlaywrightDialogue();

            void set_dialogue_type(DIALOGUE_TYPE _dlg_type);
            DIALOGUE_TYPE get_dialogue_type() const;
            void set_dialogue_options(TypedArray<Array> _dlg_options);
            TypedArray<Array> get_dialogue_options() const;
            void set_speaker(const String &_spkr);
            String get_speaker() const;
            void set_next_dialogue(Ref<PlaywrightDialogue> _next_dlg);
            Ref<PlaywrightDialogue> get_next_dialogue() const;
        
        private:
            DIALOGUE_TYPE dialogue_type;
            TypedArray<Array> dialogue_options;
            String speaker;
            Ref<PlaywrightDialogue> next_dialogue;

    };

}

VARIANT_ENUM_CAST(PlaywrightDialogue::DIALOGUE_TYPE);

#endif