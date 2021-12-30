#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cmath>


static void ui_draw_extras_limit_speed(UIState *s) {
    //const UIScene *scene = &s->scene;

    auto control_state = (*s->sm)["controlsState"].getControlsState();

    int activeNDA = control_state.getRoadLimitSpeedActive();
    int limit_speed = control_state.getRoadLimitSpeed();
    int left_dist = control_state.getRoadLimitSpeedLeftDist();

    if (activeNDA > 0) {
        int w = 120;
        int h = 54;
        int x = (s->fb_w + (bdr_s*2))/2 - w/2 - bdr_s;
        int y = 40 - bdr_s;

        const char* img = activeNDA == 1 ? "img_nda" : "img_hda";
        ui_draw_image(s, {x, y, w, h}, img, 1.f);
    }

    if (limit_speed > 10 && left_dist > 0) {
        int w = s->fb_w / 10;
        int h = s->fb_w / 10;
        int x = (bdr_s*2) + 200 + s->fb_w / 25;
        int y = 30;
        char str[32];

        nvgBeginPath(s->vg);
        nvgRoundedRect(s->vg, x, y, w, h, s->fb_w / 9);
        nvgStrokeColor(s->vg, COLOR_RED_ALPHA(200));
        nvgStrokeWidth(s->vg, s->fb_w / 72);
        nvgStroke(s->vg);

        NVGcolor fillColor = COLOR_BLACK_ALPHA(50);
        nvgFillColor(s->vg, fillColor);
        nvgFill(s->vg);
        nvgFillColor(s->vg, COLOR_WHITE_ALPHA(250));

        nvgFontSize(s->vg, s->fb_w / 15);
        nvgFontFace(s->vg, "sans-bold");
        nvgTextAlign(s->vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

        snprintf(str, sizeof(str), "%d", limit_speed);
        nvgText(s->vg, x+w/2, y+h/2, str, NULL);

        nvgFontSize(s->vg, s->fb_w / 18);

        if (left_dist >= 1000)
            snprintf(str, sizeof(str), "%.1fkm", left_dist / 1000.f);
        else
            snprintf(str, sizeof(str), "%dm", left_dist);

        nvgText(s->vg, x+w/2, y+h + 70, str, NULL);
    }

}

static void ui_draw_extras(UIState *s) {
    ui_draw_extras_limit_speed(s);
}
