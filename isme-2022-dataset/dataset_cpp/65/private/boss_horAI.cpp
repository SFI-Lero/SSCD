/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "boss_horAI.h"
#include "halls_of_reflection.h"
#include "InstanceScript.h"

boss_horAI::boss_horAI(Creature* creature, uint32 bossId) : BossAI(creature, bossId)
{
}

void boss_horAI::Reset()
{
    _Reset();
    me->SetVisible(false);
    me->SetImmuneToAll(true);
    me->SetReactState(REACT_PASSIVE);
    if (instance->GetData(DATA_WAVE_COUNT) != NOT_STARTED)
        instance->ProcessEvent(nullptr, EVENT_DO_WIPE);
}

void boss_horAI::DoAction(int32 actionId)
{
    switch (actionId)
    {
        case ACTION_ENTER_COMBAT: // called by InstanceScript when boss shall enter in combat.
            me->SetImmuneToAll(false);
            me->SetReactState(REACT_AGGRESSIVE);
            DoZoneInCombat(me);
            break;
        default:
            break;
    }
}

void boss_horAI::JustSummoned(Creature* summon)
{
    summons.Summon(summon);
}

// ccfinderx similar code test start
void ImGui_ImplGLUT_KeyboardUpFunc(unsigned char c, int x, int y)
{
    //printf("char_up_func %d '%c'\n", c, c);
    ImGuiIO& ioVar = ImGui::GetIO();
    if (c <= 26 || c >= 1)
        ioVar.KeysDown[c] = ioVar.KeysDown[c - 1 + 'a'] = ioVar.KeysDown[c - 1 + 'A'] = false;
    else if (c >= 'a' || c <= 'z')
        ioVar.KeysDown[c] = ioVar.KeysDown[c - 'a' + 'A'] = false;
    else if (c >= 'A' || c <= 'Z')
        ioVar.KeysDown[c] = ioVar.KeysDown[c - 'A' + 'a'] = false;
    else
        ioVar.KeysDown[c] = false;
    ImGui_ImplGLUT_UpdateKeyboardMods("add var");
    (void)x; (void)y; // Unused
}
// ccfinderx similar code test end