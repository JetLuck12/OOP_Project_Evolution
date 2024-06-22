#pragma once
#include <assert.h>
#include "console.h"
#include "Creature_data.h"
#include <sstream>
#include <ostream>
#include <windows.h>

#include "Goat.h"
#include "Grass.h"
#include "Deer.h"
#include "Moss.h"
#include "Wolf.h"
#include "Lynx.h"

#define TITLE_X 0
#define TITLE_Y 47

#define LEGEND_X 184
#define LEGEND_Y 1

#define FIELD_PADDING 1

#define CHAR_BORDER '#'
#define CHAR_FIELD  ' '
#define CHAR_WOLF  'W'
#define CHAR_LYNX  'X'
#define CHAR_DEER  'Y'
#define CHAR_GOAT  'T'
#define CHAR_GRASS  '.'
#define CHAR_MOSS  '.'


#define COLOR_BORDER 1
#define COLOR_MEADOW  2
#define COLOR_MOUNTAINS  3
#define COLOR_WATER  4

static size_t field_x, field_y; // top-left corner
static size_t field_width, field_height;
static size_t point_x, point_y;

/* Output char using given color pair at given position. */
static void con_charAt(int ch, int color, size_t x, size_t y) {
    con_gotoXY(static_cast<int>(x), static_cast<int>(y));
    con_setColor(static_cast<short>(color));
    con_outTxt("%c", ch);
}

static void init_colors() {
    con_initPair(COLOR_BORDER, CON_COLOR_WHITE, CON_COLOR_BLACK);
    con_initPair(COLOR_MEADOW, CON_COLOR_WHITE, CON_COLOR_GREEN);
    con_initPair(COLOR_MOUNTAINS, CON_COLOR_BLACK, CON_COLOR_WHITE);
    con_initPair(COLOR_WATER, CON_COLOR_WHITE, CON_COLOR_BLUE);
}

static void initial_draw(Creature_data& data_) {

    con_clearScr();
    Creature_field& field = data_.get_field();
    for (size_t i = 0; i < field_height; ++i) {
        for (size_t j = 0; j < field_width; ++j) {
            size_t ch;
            size_t color;

            if (i == 0 || i == field_height - 1 || j == 0 || j == field_width - 1) {
                ch = CHAR_BORDER;
                color = COLOR_BORDER;
            }
            else {
                color = field.get_cell(Coord{ j - 1, i - 1, 0 }).get_landscape()->get_texture();
                if (field.get_cell(Coord{ j - 1, i - 1, 0 }).begin() == field.get_cell(Coord{ j - 1, i - 1, 0 }).end())
                {
                    ch = CHAR_FIELD;
                }
                else {
                    auto creature = --field.get_cell(Coord{ j - 1, i - 1, 0 }).end();
                    ch = (*creature)->get_texture().get_texture();
                }

            }
            con_charAt(static_cast<int>(ch), static_cast<int>(color), field_x + j, field_y + i);
        }
    }
    con_gotoXY(LEGEND_X, LEGEND_Y);
    con_setColor(COLOR_BORDER);
    con_outTxt("Moss: ");
    con_charAt(CHAR_MOSS, COLOR_MOUNTAINS, LEGEND_X + 7, LEGEND_Y);
    con_gotoXY(LEGEND_X, LEGEND_Y+1);
    con_setColor(COLOR_BORDER);
    con_outTxt("Grass: ");
    con_charAt(CHAR_GRASS, COLOR_MEADOW, LEGEND_X + 7, LEGEND_Y+1);
    con_gotoXY(LEGEND_X, LEGEND_Y+2);
    con_setColor(COLOR_BORDER);
    con_outTxt("Deer: ");
    con_charAt(CHAR_DEER, COLOR_MEADOW, LEGEND_X + 7, LEGEND_Y+2);
    con_gotoXY(LEGEND_X, LEGEND_Y+3);
    con_setColor(COLOR_BORDER);
    con_outTxt("Wolf: ");
    con_charAt(CHAR_WOLF, COLOR_MEADOW, LEGEND_X + 7, LEGEND_Y+3);
    con_gotoXY(LEGEND_X, LEGEND_Y+4);
    con_setColor(COLOR_BORDER);
    con_outTxt("Goat: ");
    con_charAt(CHAR_GOAT, COLOR_MOUNTAINS, LEGEND_X + 7, LEGEND_Y+4);
    con_gotoXY(LEGEND_X, LEGEND_Y + 5);
    con_setColor(COLOR_BORDER);
    con_outTxt("Lynx: ");
    con_charAt(CHAR_LYNX, COLOR_MOUNTAINS, LEGEND_X + 7, LEGEND_Y + 5);
}

inline int init_draw(Creature_data& data) {
    int max_x, max_y;

    con_init();

    init_colors();
    HWND hWindowConsole = GetConsoleWindow();
    RECT r;
    GetWindowRect(hWindowConsole, &r); //stores the console's current dimensions
    MoveWindow(hWindowConsole, r.left, r.top, 4000, 1000, TRUE);

    // calculate size of field
    con_getMaxXY(&max_x, &max_y);
    field_x = 1;
    field_y = FIELD_PADDING;
    field_width = data.get_field().get_x() + 2;
    field_height = data.get_field().get_y() + 2;
    assert(field_width > 2);
    assert(field_height > 2);

    initial_draw(data);
    return 0;
}

inline void processing_draw(Creature_data& data, size_t tick)
{
    Creature_field& field = data.get_field();



    for (size_t i = 0; i < field_height; ++i) {
        for (size_t j = 0; j < field_width; ++j) {
            size_t ch;

            if (i == 0 || i == field_height - 1 || j == 0 || j == field_width - 1) {
                continue;
            }
                Cell& cell = field.get_cell(Coord{ j - 1, i - 1, 0 });
                if (!cell.is_changed())
                {
                    continue;
                }
                size_t color = cell.get_landscape()->get_texture();
                if (field.get_cell(Coord{ j - 1, i - 1, 0 }).begin() == field.get_cell(Coord{ j - 1, i - 1, 0 }).end())
                {
                    ch = CHAR_FIELD;
                }
                else {
                    auto creature = --field.get_cell(Coord{ j - 1, i - 1, 0 }).end();
                    ch = (*creature)->get_texture().get_texture();
                }
                cell.reset_change();
            con_charAt(static_cast<int>(ch), static_cast<int>(color), field_x + j, field_y + i);
        }
    }
    size_t plants = 0, herbs = 0, preds = 0, grass = 0, moss = 0, deers = 0, goats = 0, wolfs = 0, lynx = 0;
    for (auto creature = data.get_list().begin(); creature != data.get_list().end(); ++creature)
    {
        if (!!std::dynamic_pointer_cast <Grass>(*creature))
        {
            plants++;
            grass++;
        }
    	else if(!!std::dynamic_pointer_cast <Moss>(*creature))
        {
            plants++;
            moss++;
        }
        else if (!!std::dynamic_pointer_cast <Deer>(*creature))
        {
            herbs++;
            deers++;
        }
        else if (!!std::dynamic_pointer_cast <Goat>(*creature))
        {
            herbs++;
            goats++;
        }
        else if (!!std::dynamic_pointer_cast <Wolf>(*creature))
        {
            wolfs++;
            preds++;
        }
        else if (!!std::dynamic_pointer_cast <Lynx>(*creature))
        {
            lynx++;
            preds++;
        }
    }

    con_setColor(COLOR_BORDER);
    con_gotoXY(LEGEND_X, LEGEND_Y + 9);
    con_outTxt("Herbivirous: %d", herbs);

    con_gotoXY(LEGEND_X, LEGEND_Y + 10);
    con_outTxt("Plants: %d", plants);

    con_gotoXY(LEGEND_X, LEGEND_Y + 11);
    con_outTxt("Preds: %d", preds);

    con_gotoXY(LEGEND_X, LEGEND_Y + 13);
    con_outTxt("Grass: %d", grass);

    con_gotoXY(LEGEND_X, LEGEND_Y + 14);
    con_outTxt("Moss: %d", moss);

    con_gotoXY(LEGEND_X, LEGEND_Y + 15);
    con_outTxt("Deer: %d", deers);

    con_gotoXY(LEGEND_X, LEGEND_Y + 16);
    con_outTxt("Goat: %d", goats);

    con_gotoXY(LEGEND_X, LEGEND_Y + 17);
    con_outTxt("Wolf: %d", wolfs);

    con_gotoXY(LEGEND_X, LEGEND_Y + 18);
    con_outTxt("Lynx: %d", lynx);

    con_gotoXY(LEGEND_X, LEGEND_Y + 20);
    con_outTxt("Tick: %d", tick);

}

inline void erase_creatures(Creature_data& data)
{
    Creature_field& field = data.get_field();

    for (size_t y = 0; y < field.get_y(); ++y)
    {
	    for (size_t x = 0; x < field.get_x(); ++x)
	    {
		    if(!field.get_cell(Coord{x,y,0}).is_changed())
		    {
			    continue;
		    }
            size_t ch = CHAR_FIELD;
            size_t color = field.get_cell(Coord{x, y, 0}).get_landscape()->get_texture();
            con_charAt(static_cast<int>(ch), static_cast<int>(color), field_x + x + 1, field_y + y + 1);
	    }
    }
    con_gotoXY(LEGEND_X + 13, LEGEND_Y + 9);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 8, LEGEND_Y + 10);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 7, LEGEND_Y + 11);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 7, LEGEND_Y + 13);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 6, LEGEND_Y + 14);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 6, LEGEND_Y + 15);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 6, LEGEND_Y + 16);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 6, LEGEND_Y + 17);
    con_outTxt("    ");
    con_gotoXY(LEGEND_X + 6, LEGEND_Y + 18);
    con_outTxt("    ");

}