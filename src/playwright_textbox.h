#ifndef PLAYWRIGHT_TEXTBOX_H
#define PLAYWRIGHT_TEXTBOX_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/rich_text_effect.hpp>

namespace godot {
  class PlaywrightTextbox : public CanvasLayer {
    GDCLASS(PlaywrightTextbox, CanvasLayer)
    
    private:
      Ref<RichTextEffect> text_reveal_effect;
      Ref<RichTextEffect> dlg_trigger_effect;
      Ref<RichTextEffect> dlg_end_effect;

    protected:
      static void _bind_methods();

    public:
      PlaywrightTextbox();
      ~PlaywrightTextbox();

    void _ready() override;
  };
}
#endif
