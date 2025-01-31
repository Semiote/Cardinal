/*
 * DISTRHO Cardinal Plugin
 * Copyright (C) 2021-2022 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#pragma once

#include "rack.hpp"

#ifdef NDEBUG
# undef DEBUG
#endif

using namespace rack;

template<int hp>
struct ModuleWidgetWithSideScrews : ModuleWidget {
    static constexpr const float startX_In = 10.65f;
    static constexpr const float startX_Out = (hp - 3) * 15 + startX_In;
    static constexpr const float startY = 73.0f; // note: out bg box has 2px extra
    static constexpr const float padding = 29.0f;
    static constexpr const float middleX = startX_In + (startX_Out - startX_In) * 0.5f /*+ padding * 0.35f*/;

    void createAndAddInput(const uint paramId) {
        createAndAddInput(paramId, paramId);
    }

    void createAndAddInput(const uint posY, const uint paramId) {
        addInput(createInput<PJ301MPort>(Vec(startX_In, startY + padding * posY), module, paramId));
    }

    void createAndAddOutput(const uint paramId) {
        createAndAddOutput(paramId, paramId);
    }

    void createAndAddOutput(const uint posY, const uint paramId) {
        addOutput(createOutput<PJ301MPort>(Vec(startX_Out, startY + padding * posY), module, paramId));
    }

    void createAndAddScrews() {
        if (hp > 3) {
            addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
            addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
            addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
            addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        } else {
            addChild(createWidget<ScrewBlack>(Vec(0, 0)));
            addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, 0)));
            addChild(createWidget<ScrewBlack>(Vec(0, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
            addChild(createWidget<ScrewBlack>(Vec(box.size.x - RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        }
    }

    void drawBackground(NVGcontext* const vg) {
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, box.size.x, box.size.y);
        nvgFillPaint(vg, nvgLinearGradient(vg, 0, 0, 0, box.size.y,
                                           nvgRGB(0x18, 0x19, 0x19), nvgRGB(0x21, 0x22, 0x22)));
        nvgFill(vg);
    }

    void drawOutputJacksArea(NVGcontext* const vg, const int numOutputs) {
        nvgBeginPath(vg);
        nvgRoundedRect(vg, startX_Out - 2.5f, startY - 2.0f, padding, padding * numOutputs, 4);
        nvgFillColor(vg, nvgRGB(0xd0, 0xd0, 0xd0));
        nvgFill(vg);
    }

    void drawTextLine(NVGcontext* const vg, const uint posY, const char* const text) {
        const float y = startY + posY * padding;
        nvgBeginPath(vg);
        nvgFillColor(vg, color::WHITE);
        nvgText(vg, box.size.x * 0.5f, y + 16, text, nullptr);
    }

    void setupTextLines(NVGcontext* const vg) {
        nvgFontFaceId(vg, 0);
        nvgFontSize(vg, 11);
        nvgTextAlign(vg, NVG_ALIGN_CENTER);
    }
};

typedef ModuleWidgetWithSideScrews<3> ModuleWidgetWith3HP;
typedef ModuleWidgetWithSideScrews<8> ModuleWidgetWith8HP;
typedef ModuleWidgetWithSideScrews<9> ModuleWidgetWith9HP;
typedef ModuleWidgetWithSideScrews<11> ModuleWidgetWith11HP;
