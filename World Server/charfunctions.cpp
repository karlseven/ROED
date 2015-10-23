/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007,2008,2009 OSRose Team http://www.dev-osrose.com

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    developed with Main erose/hrose source server + some change from the original eich source
*/
#include "character.h"
#include "worldserver.h"
#include <cmath>

// return true if this character is monster
bool CCharacter::IsMonster( )
{
    if(CharType==2 || CharType==3)
        return true;
    return false;
}

// return true if this character is player
bool CCharacter::IsPlayer( )
{
    if(CharType==1)
        return true;
    return false;
}

// return true if HP is lower to 1
bool CCharacter::IsDead( )
{
    if(Stats->HP<=0)
        return true;
    return false;
}

// return true if this character is summon
bool CCharacter::IsSummon( )
{
    if(CharType==3)
        return true;
    return false;
}

// Virtual function [return item drop]
CDrop* CCharacter::GetDrop( )
{
    return NULL;
}

// start action [attack]
void CCharacter::StartAction( CCharacter* Target, BYTE action, UINT skillid, bool restart, CCharacter* receiver )
{
    if(IsPlayer())
    {
        Log(MSG_INFO,"A Player does an action %i, skill %i",action,skillid);
    }
    else
    {
        Log(MSG_INFO,"A Monster does an action %i, skill %i",action,skillid);
    }

    BEGINPACKET( pak, 0 );
    if (restart)
    {
       Target=GetCharTarget( );
       action=Battle->atktype;
       skillid=Battle->skillid;
    }

    //Drakia: If the target is NULL, we should only do something that doesn't require a target.
    if (Target == NULL && (action != SKILL_AOE &&action != BUFF_SELF &&action != BUFF_AOE &&action != MONSTER_BUFF_SELF &&action != AOE_TARGET))
    {
        Log(MSG_WARNING,"We tried to start attack %i without a target",action);
        return;
    }

    //LMA: don't attack a dead or an offline player... It's stupid...
    if(Target!=NULL)
    {
        if(Target->IsPlayer())
        {
            CPlayer* thisplayer=reinterpret_cast<CPlayer*>(Target);
            if(!thisplayer->Session->inGame)
            {
                //Log(MSG_HACK,"We don't attack a player not in game yet..., %s",thisplayer->CharInfo->charname);
                return;
            }

        }

        if(Target->IsDead())
        {
            //but we can if it's a friendly (restore...).
            if(action!=SKILL_BUFF)
            {
                ClearBattle(Battle);
                return;
            }

        }

    }

    switch(action)
    {
        case NORMAL_ATTACK:
        {
            RESETPACKET( pak, 0x798 );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, Target->clientid );

            //ADDWORD    ( pak, Stats->Move_Speed );
            ADDWORD    ( pak, Stats->Base_Speed );
            //Log(MSG_INFO,"move speed %u, base speed %u",Stats->Move_Speed,Stats->Base_Speed);

            ADDFLOAT   ( pak, Target->Position->current.x*100 );
            ADDFLOAT   ( pak, Target->Position->current.y*100 );
            Battle->target = Target->clientid;
            Battle->atktarget = Target->clientid;
            Battle->atktype = action;
            Position->destiny  = Target->Position->current;
            Position->lastMoveTime = clock( );
        }
        break;
        case SKILL_ATTACK:
        case SKILL_BUFF:
        {
        	RESETPACKET( pak, 0x7b3 );
        	ADDWORD    ( pak, clientid );
        	ADDWORD    ( pak, Target->clientid );
        	ADDWORD    ( pak, skillid );
        	ADDWORD    ( pak, 50000 );
            ADDFLOAT   ( pak, Target->Position->current.x*100 );
            ADDFLOAT   ( pak, Target->Position->current.y*100 );
            ADDFLOAT   ( pak, Position->aoedestiny.x*100 );
            ADDFLOAT   ( pak, Position->aoedestiny.y*100 );
            Battle->target = Target->clientid;

            if(action==SKILL_ATTACK) Battle->skilltarget = Target->clientid;
            else Battle->bufftarget = Target->clientid;

            Battle->atktype = action;
            Position->destiny  = Target->Position->current;
            Battle->skillid = skillid;
            Position->lastMoveTime = clock( );
        }
        break;
        case MONSTER_SKILL_ATTACK:
        case MONSTER_SKILL_BUFF:
        {
        	RESETPACKET( pak, 0x7b3 );
        	ADDWORD    ( pak, clientid );
        	ADDWORD    ( pak, Target->clientid );
        	ADDWORD    ( pak, skillid );
            ADDBYTE (pak,0x2b);
            ADDBYTE (pak,0x01);
            ADDFLOAT   ( pak, Target->Position->current.x*100 );
            ADDFLOAT   ( pak, Target->Position->current.y*100 );
            ADDBYTE    ( pak, 0x06);
            Battle->target = Target->clientid;

            if(action==MONSTER_SKILL_ATTACK) Battle->skilltarget = Target->clientid;
            else Battle->bufftarget = Target->clientid;

            Battle->atktype = action;
            Position->destiny  = Target->Position->current;
            Battle->skillid = skillid;
            Position->lastMoveTime = clock( );
        }
        break;
        case SUMMON_BUFF:
        {
            //LMA: Special case for Support summons
        	RESETPACKET( pak, 0x7b3 );
        	ADDWORD    ( pak, clientid );
        	ADDWORD    ( pak, Target->clientid );
        	ADDWORD    ( pak, skillid );
            ADDBYTE (pak,0x2b);
            ADDBYTE (pak,0x01);
            ADDFLOAT   ( pak, Target->Position->current.x*100 );
            ADDFLOAT   ( pak, Target->Position->current.y*100 );
            /*
            ADDFLOAT   ( pak, Position->current.x*100 );
            ADDFLOAT   ( pak, Position->current.y*100 );
            */
            ADDBYTE    ( pak, 0x06);
            Battle->target = 0;
            //Battle->skilltarget = Target->clientid;
            Battle->bufftarget = Target->clientid;
            Battle->atktype = action;
            Position->destiny  = Target->Position->current;
            Battle->skillid = skillid;
            Position->lastMoveTime = clock( );
            GServer->SendToVisible( &pak, Target );
            return;

        }
        break;
        case SKILL_AOE:
        case BUFF_SELF:
        case BUFF_AOE:
        {
            RESETPACKET( pak, 0x7b2);
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, skillid );
            Battle->atktype = action;
            Battle->skillid = skillid;
        }
        break;
        case MONSTER_BUFF_SELF:
        {
            RESETPACKET( pak, 0x7b2);
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, skillid );
            Battle->atktype = action;
            Battle->skillid = skillid;
        }
        break;
        case AOE_TARGET:
        {
            //LMA 2008/09/02: new version, the target is a zone, not a monster... so we stick with aoedestiny ;)
            //PY mods
            //Target is NULL for this function when cast by a player
            //Target is NOT NULL when it comes from a monster
            if(Target != NULL) //monster attack
            {
                Position->aoedestiny.x = Target->Position->current.x;
                Position->aoedestiny.y = Target->Position->current.y;
            }
            RESETPACKET( pak, 0x7b4 );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, skillid );
            ADDFLOAT   ( pak, Position->aoedestiny.x*100 );
            ADDFLOAT   ( pak, Position->aoedestiny.y*100 );
            Battle->atktype = action;
            Battle->skillid = skillid;
            Battle->skilltarget = 0;
            Battle->target = Battle->atktarget;
            Position->destiny  = Position->aoedestiny;
            Position->lastMoveTime = clock( );
            Log(MSG_INFO,"StartAction, AOE_TARGET, target (%.2f,%.2f)",Position->aoedestiny.x,Position->aoedestiny.y);
        }
        break;
        case STAY_STILL_ATTACK:
        {
             //LMA: Very special case where the monster don't really attack (mc)
             Battle->atktype = action;
             Battle->skillid = skillid;
             Battle->skilltarget = Target->clientid;
             return;
         }
        default: return;
    }
    //if (getClient()==NULL)
       GServer->SendToVisible( &pak, this );
    /*else
        getClient();*/
}
bool CCharacter::IsOnBattle( )
{
    //Bonfire don't attack...
    if(Battle->atktype==0) return false;
    switch(Battle->atktype)
    {
        case NORMAL_ATTACK:
        {
            if(Battle->atktarget!=0) return true;
        }
        break;
        case SKILL_ATTACK:
        case AOE_TARGET:
        {
            if(Battle->skilltarget!=0 && Battle->skillid!=0) return true;
        }
        break;
        case SKILL_BUFF:
        {
            if(Battle->bufftarget!=0 && Battle->skillid!=0) return true;
        }
        break;
        case SUMMON_BUFF:
        {
             if(Battle->bufftarget!=0&&Battle->skillid!=0) return true;
        }
        break;
        case MONSTER_SKILL_BUFF:
        {
             if(Battle->bufftarget!=0 && Battle->skillid!=0) return true;
        }
        break;
        case MONSTER_SKILL_ATTACK:
        {
             if(Battle->skilltarget!=0 && Battle->skillid!=0) return true;
        }
        break;
        case MONSTER_BUFF_SELF:
        case SKILL_AOE:
        case SKILL_SELF:
        case BUFF_SELF:
        case BUFF_AOE:
        {
            if(Battle->skillid!=0) return true;
        }
        break;
        case STAY_STILL_ATTACK:
        {
              //LMA: Very special case where the monster don't really attack (mc)
              return true;
         }
        default: return false;
    }
}

bool CCharacter::CanAttack( ) // updated by Core
{
    clock_t etime = clock() - Battle->lastAtkTime;
    int weapontype = IsPlayer()?getWeaponType():0;
    //the fix: not much but it works ;)
    if (weapontype == 212)
    {
        return true;
    }

    if (Battle->lastcastspeed <= 0 || Battle->lastcastspeed == Stats->Attack_Speed)
    {
        if (etime < CLOCKS_PER_SEC * 1)
            return false;
    }
    else
    {
        if(etime < CLOCKS_PER_SEC * (Battle->lastcastspeed / 100))
            return false;
    }

    return true;
}

// return true if target is reached
bool CCharacter::IsTargetReached( CCharacter* Enemy, CSkills* skill )
{
    CMap* map = GServer->MapList.Index[Position->Map];
    float distance = GServer->distance( Position->current, Enemy->Position->current );

    if(skill==NULL)
   {
          if(distance<=Stats->Attack_Distance)
        {
            return true;
        }
        else
        {
            Position->destiny = Enemy->Position->current;
        }

    }
    else
    {
        if(distance<=skill->range)
        {
            return true;
        }
        else
        {
            Position->destiny = Enemy->Position->current;
        }

    }

    //LMA: log
    //LOTSOFLOGSHERE
    /*
    if(Enemy->IsMonster())
    {
        //Log(MSG_INFO,"E=M:: Player is at distance %.2f of the monster, and needs to be in range of %.2f",distance,Stats->Attack_Distance);
        Log(MSG_INFO,"E=M:: M CID %u, P CID %u, M(%.2f;%.2f)->(%.2f;%.2f), P(%.2f;%.2f)->(%.2f;%.2f), dist=%.2f",
        Enemy->clientid,clientid,
        Enemy->Position->current.x,Enemy->Position->current.y,
        Enemy->Position->destiny.x,Enemy->Position->destiny.y,
        Position->current.x,Position->current.y,
        Position->destiny.x,Position->destiny.y,
        distance);
    }

    if(Enemy->IsPlayer())
    {
        //Log(MSG_INFO,"E=P:: Player is at distance %.2f of the monster, and needs to be in range of %.2f",distance,Stats->Attack_Distance);
        Log(MSG_INFO,"E=P:: M CID %u, P CID %u, M(%.2f;%.2f)->(%.2f;%.2f), P(%.2f;%.2f)->(%.2f;%.2f), dist=%.2f",
        clientid,Enemy->clientid,
        Position->current.x,Position->current.y,
        Position->destiny.x,Position->destiny.y,
        Enemy->Position->current.x,Enemy->Position->current.y,
        Enemy->Position->destiny.x,Enemy->Position->destiny.y,
        distance);
    }
    */


    return false;
}

// return true if the character is moving
bool CCharacter::IsMoving( )
{
    if(Position->current.x == Position->destiny.x && Position->current.y == Position->destiny.y )
        return false;
    return true;
}

bool CCharacter::stopMoving()
{
     if( Position->current.x == Position->destiny.x && Position->current.y == Position->destiny.y )
        return false;
     Position->destiny =Position->current; //STOP MOVING
     printf(IsPlayer()?"Stopping char movement\n":"Stopping mob movement\n");
     printf("Stopped moving at: %i, %i\n", (int)Position->current.x, (int)Position->current.y);
     return true;
}

// VIRTUAL [add player damage]
void CCharacter::AddDamage( CCharacter* enemy, long long hitpower)
{
    Log(MSG_INFO,"In CCharacter::AddDamage");
}

// return character target
CCharacter* CCharacter::GetCharTarget( )
{
    CCharacter* thistarget = GServer->MapList.Index[Position->Map]->GetCharInMap( Battle->target );
    if (thistarget != NULL)
    {
        //Log(MSG_DEBUG, "getchartarget found target OK");
        return thistarget;
    }
    //Log(MSG_DEBUG, "getchartarget failed to find target");
    //if I don't currently have a target then return the character who just hit me
    thistarget = GServer->MapList.Index[Position->Map]->GetCharInMap( Battle->hitby );
    //if (thistarget == NULL)
    //{
    //    Log(MSG_DEBUG, "getcharinmap(battle->hitby) still failed to find a target");
    //    return thistarget;
    //}
    // still no target. Let's find teh closest player
    //CPlayer* thisplayer = NULL;
    //float distance = 0xffff;
    //for(UINT i=0;i<GServer->MapList.Index[Position->Map]->PlayerList.size();i++)
    //{
    //    CPlayer* thisclient = GServer->MapList.Index[Position->Map]->PlayerList.at(i);
    //    float tempdist = GServer->distance( Position->current, thisclient->Position->current );
    //    if(tempdist<distance)
    //    {
    //        thisplayer = thisclient;
    //        distance = tempdist;
    //    }
    //}
    //thistarget = (CCharacter*) thisplayer;
    //if (thistarget == NULL)
    //{
    //    Log(MSG_DEBUG, "still failed to find a target");
    //}
    //else
    //{
    //    Log(MSG_DEBUG, "OK Found a target.. finally id = ", thistarget->clientid);
    //}
    return thistarget;
}

// return character Buff target
CCharacter* CCharacter::GetCharBuffTarget( )
{
    return GServer->MapList.Index[Position->Map]->GetCharInMap( Battle->bufftarget );
}

// VIRTUAL [reduce ammon/bullets/cannons]
void CCharacter::ReduceABC( int amount, bool do_packet )
{

}

// VIRTUAL //LMA: Searching for replacement arrows, bullets...
int CCharacter::SearchABC ( int slot )
{

}

// VIRTUAL [get extra buff value]
int CCharacter::GetEVBuff( )
{
    return 0;
}

unsigned int CCharacter::GetStr( )
{
    return 15;
}
unsigned int CCharacter::GetDex( )
{
    return 15;
}
// VIRTUAL [return intelligence]
unsigned int CCharacter::GetInt( )
{
    return 15;
}

// VIRTUAL [return charm]
unsigned int CCharacter::GetCha( )
{
    return 10;
}


// VIRTUAL [return Sensibility]
unsigned int CCharacter::GetSen( )
{
    return 10;
}

// VIRTUAL [return Concentration]
unsigned int CCharacter::GetCon( )
{
    return 15;
}

unsigned int CCharacter::GetClassRequiredStatus()
{
    return 0;
}

void CCharacter::RefreshBuff( )
{
    bool bflag = false;
    for( UINT i=0;i<32;i++)
    {
        if(MagicStatus[i].Buff == 0) continue;
        clock_t etime = clock() - MagicStatus[i].BuffTime;
        if( etime >= MagicStatus[i].Duration * CLOCKS_PER_SEC )
        {

            Log(MSG_INFO,"Magic Status %i, vanish after: %i", MagicStatus[i].Status, MagicStatus[i].Duration);

            switch(MagicStatus[i].Status)
            {
                case STATUS_HP_8: case STATUS_HP_18: case STATUS_HP_30: case STATUS_HP_43: case STATUS_HP_58: case STATUS_HP_75: case STATUS_SUMMON_HP:
                case STATUS_HP_92: case STATUS_HP_111: case STATUS_HP_131: case STATUS_HP_152: case STATUS_HP_174: case STATUS_HP_197: case STATUS_HP_221:
                case STATUS_HP_246: case STATUS_HP_272: case STATUS_HP_299: case STATUS_HP_326: case STATUS_HP_354: case STATUS_HP_383: case STATUS_HP_413:
                case STATUS_HP_443: case STATUS_HP_475: case STATUS_HP_539: case STATUS_HP_572: case STATUS_HP_5_PC: case 115:
                {
                    Status->HPHeal = 0xff;
                }
                break;

                case STATUS_MP_6: case STATUS_MP_10: case STATUS_MP_14: case STATUS_MP_18: case STATUS_MP_21: case STATUS_MP_25: case STATUS_MP_29:
                case STATUS_MP_33: case STATUS_MP_36: case STATUS_MP_40: case STATUS_MP_44: case STATUS_MP_48: case STATUS_MP_51: case STATUS_MP_55:
                case STATUS_MP_59: case STATUS_MP_63: case STATUS_MP_66: case STATUS_MP_70: case STATUS_MP_74: case STATUS_MP_78: case STATUS_MP_81:
                case STATUS_MP_85: case STATUS_MP_89: case STATUS_MP_93: case STATUS_MP_96: case 116:
                {
                    Status->MPHeal = 0xff;
                }
                break;

                case 18: // attack power up
                case 19: // attack power down
                case 48: // attack power up
                {
                    if(i == BUFF_ATTACK_UP_POS)
                    {
                        Status->Attack_up = 0xff;
                    }
                    else
                    {
                        Status->Attack_down = 0xff;
                    }
                    Stats->Attack_Power = GetAttackPower( );
                }
                break;
                case 20: // def up
                case 21: // def down
                case 49: // def up
                {
                    if(i==BUFF_DEFENSE_UP_POS)
                    {
                        Status->Defense_up= 0xff;
                    }
                    else
                    {
                        Status->Defense_down = 0xff;
                    }
                    Stats->Defense = GetDefense( );
                }
                break;
                case 24: //Accuracy up
                case 25: //Accuracy down
                case 51: //attack Accuracy up.
                {
                    if(i==BUFF_HITRATE_UP_POS)
                    {
                        Status->Accuracy_up= 0xff;
                    }
                    else
                    {
                        Status->Accuracy_down = 0xff;
                    }
                    Stats->Accuracy = GetAccuracy( );
                }
                break;
                case 22: // macic resistance up
                case 23: // magic resistance down
                case 50: // magic resistance up
                {
                    if(i==BUFF_MDEFENSE_UP_POS)
                    {
                        Status->Magic_Defense_up = 0xff;
                    }
                    else
                    {
                        Status->Magic_Defense_down = 0xff;
                    }
                    Stats->Magic_Defense = GetMagicDefense( );
                }
                break;
                case 28: //dodge up
                case 29: //dodge down
                case 53: //dodge rate up
                {
                    if(i==BUFF_DODGE_UP_POS)
                    {
                        Status->Dodge_up = 0xff;
                    }
                    else
                    {
                        Status->Dodge_down = 0xff;
                    }
                    Stats->Dodge = GetDodge( );
                }
                break;
                case 14: //dash
                case 15: //slow
                case 46: //movement speed increased
                {
                    if(i==BUFF_DASH_UP_POS)
                    {
                        Status->Dash_up = 0xff;
                    }
                    else
                    {
                        Status->Dash_down = 0xff;
                    }
                    Stats->Move_Speed = GetMoveSpeed( );
                }
                break;
                case 16: // haste attack
                case 17: // slow attack
                case 47: // attack speed up
                {
                    if(i==BUFF_HASTE_UP_POS)
                    {
                        Status->Haste_up = 0xff;
                    }
                    else
                    {
                        Status->Haste_down = 0xff;
                    }
                    //Stats->Attack_Speed_Percent = GetAttackSpeedPercent( );
                }
                break;
                case 26: // crit up
                case 27: // crit down
                case 52: // crit up
                {
                    if(i==BUFF_CRITICAL_UP_POS)
                    {
                        Status->Critical_up = 0xff;
                    }
                    else
                    {
                        Status->Critical_down = 0xff;
                    }
                    Stats->Critical = GetCritical( );
                }
                break;
                case 12: // max HP up
                case 44: // max HP up
                {
                    if(i==BUFF_MAX_HP_POS)
                    {
                        Status->HP_up = 0xff;
                    }
                    else
                    {
                        Status->HP_down = 0xff;
                    }
                    Stats->MaxHP = GetMaxHP( );

                    if(Stats->HP > Stats->MaxHP)
                    {
                        Stats->HP = Stats->MaxHP;
                    }
                }
                break;
                case 13: // max MP up
                case 45: // max MP up
                {
                    if(i==BUFF_MAX_MP_POS)
                    {
                        Status->MP_up = 0xff;
                    }
                    else
                    {
                        Status->MP_down = 0xff;
                    }
                    Stats->MaxMP = GetMaxMP( );

                    if(Stats->MP > Stats->MaxMP)
                    {
                        Stats->MP = Stats->MaxMP;
                    }
                }
                break;
                case 32: // faint
                {
                    Status->Faint = 0xff;
                    Status->CanMove = true;
                    Status->CanCastSkill = true;
                    Status->CanAttack = true;
                    //printf("removing stun\n");
                }
                break;
                case 7: case 8: case 9: case 10: case 11: case 89: //poisoned
                {
                    Status->Poisoned = 0xff;
                    //printf("removing poison\n");
                }
                break;
                case 30: // muted
                {
                    Status->Muted = 0xff;
                    Status->CanCastSkill = true;
                }
                break;
                case 31: // sleep May need to be fixed later to accomodate multiple status effects.
                {
                    Status->Sleep = 0xff;
                    Status->CanMove = true;
                    Status->CanCastSkill = true;
                    Status->CanAttack = true;
                }
                break;
                case 36: //A_Extra_Damage:
                case 54: //A_GMExtra_Damage:
                case 83: //Valkyrie Charm:
                {
                    if(i==BUFF_DUMMY_DAMAGE_POS)
                    {
                        Status->ExtraDamage_up = 0xff;
                        Stats->ExtraDamage_add = 0;//We put extardamage add value to 0 if we lost the adddmg buff
                    }
                    else
                    {
                        Status->ExtraDamage_down = 0xff;
                        Stats->ExtraDamage_add = 0;//We put extardamage add value to 0 if we lost the adddmg buff
                    }
                }
                break;
                case 56: //Taunt
                {
                    Status->Taunt = 0xff;
                    //printf("removing Taunt\n");
                }
                break;
                case 58: case 61: case 74: case 77:  case 78: case 79: case 80: //flame
                {
                    Status->Flamed = 0xff;
                }
                break;
                case 33://Stealth,Camoflauge
                {
                    if(IsAttacking( ))
                    {
                        MagicStatus[i].Duration = 0;
                    }
                    Status->Stealth = 0xff;
                    //printf("removing Stealth\n");
                }
                break;
                case 86://Stealth,Weary
                {
                    Status->Weary = 0xff;
                    Status->CanCastSkill = true;
                    //printf("removing Weary\n");
                }
                break;
                case 34://Cloaking
                {
                    Status->Cloaking = 0xff;
                    //printf("removing Cloaking\n");
                }
                break;
                case 35: //ShieldDamage:
                {
                    if(i==BUFF_SHIELD_DAMAGE_POS)
                    {
                        Status->ShieldDamage_up = 0xff;
                        //Stats->ShieldDamage = 0xff;
                    }
                    else
                    {
                        Status->ShieldDamage_down = 0xff;
                        //Stats->ShieldDamage = 0xff;
                    }
                }
                break;
                case 55://Detect
                {
                    Status->Detect = 0xff;
                    Status->Cloaking = 0xff;
                    Status->Stealth = 0xff;
                    //printf("Detect Done\n");
                }
                break;
                case 38://Purify
                {
                    //Buff_Down
                    Status->Attack_down = 0xff;
                    Status->Defense_down = 0xff;
                    Status->Accuracy_down = 0xff;
                    Status->Magic_Defense_down = 0xff;
                    Status->Dodge_down = 0xff;
                    Status->Dash_down = 0xff;
                    Status->Haste_down = 0xff;
                    Status->Critical_down = 0xff;
                    Status->HP_down = 0xff;
                    Status->MP_down = 0xff;
                    Status->ExtraDamage_down = 0xff;
                    Status->ShieldDamage_down = 0xff;
                    Status->ALL_down = 0xff;

                    //Bad Status
                    //Status->Stun = 0xff;
                    Status->Poisoned = 0xff;
                    Status->Muted = 0xff;
                    Status->Sleep = 0xff;
                    Status->Flamed = 0xff;
                    Status->Faint = 0xff;

                    //Stats
                    Stats->Attack_Power = GetAttackPower( );
                    Stats->Defense = GetDefense( );
                    Stats->Accuracy = GetAccuracy( );
                    Stats->Magic_Defense = GetMagicDefense( );
                    Stats->Dodge = GetDodge( );
                    Stats->Move_Speed = GetMoveSpeed( );
                    Stats->Attack_Speed = GetAttackSpeed( );
                    //Stats->Attack_Speed_Percent = GetAttackSpeedPercent();
                    Stats->Critical = GetCritical( );
                    Stats->MaxHP = GetMaxHP( );
                    Stats->MaxMP = GetMaxMP( );
                    //printf("Purify Done\n");
                }
                break;
				case 39:// Dispell
                {
                    //Buff_Down
                    Status->Attack_down = 0xff;
                    Status->Defense_down = 0xff;
                    Status->Accuracy_down = 0xff;
                    Status->Magic_Defense_down = 0xff;
                    Status->Dodge_down = 0xff;
                    Status->Dash_down = 0xff;
                    Status->Haste_down = 0xff;
                    Status->Critical_down = 0xff;
                    Status->HP_down = 0xff;
                    Status->MP_down = 0xff;
                    Status->ExtraDamage_down = 0xff;
                    Status->ShieldDamage_down = 0xff;
                    Status->ALL_down = 0xff;

                    //Buff_Up
                    Status->Attack_up = 0xff;
                    Status->Defense_up = 0xff;
                    Status->Accuracy_up = 0xff;
                    Status->Magic_Defense_up = 0xff;
                    Status->Dodge_up = 0xff;
                    Status->Dash_up = 0xff;
                    Status->Haste_up = 0xff;
                    Status->Critical_up = 0xff;
                    Status->HP_up = 0xff;
                    Status->MP_up = 0xff;
                    Status->ExtraDamage_up = 0xff;
                    Status->ShieldDamage_up = 0xff;
                    Status->ALL_up = 0xff;

                    //Bad Status
                    //Status->Stun = 0xff;
                    Status->Poisoned = 0xff;
                    Status->Muted = 0xff;
                    Status->Sleep = 0xff;
                    Status->Flamed = 0xff;
                    Status->Faint = 0xff;

                    //Stats
                    Stats->Attack_Power = GetAttackPower( );
                    Stats->Defense = GetDefense( );
                    Stats->Accuracy = GetAccuracy( );
                    Stats->Magic_Defense = GetMagicDefense( );
                    Stats->Dodge = GetDodge( );
                    Stats->Move_Speed = GetMoveSpeed( );
                    Stats->Attack_Speed = GetAttackSpeed( );
                    Stats->Critical = GetCritical( );
                    Stats->MaxHP = GetMaxHP( );
                    Stats->MaxMP = GetMaxMP( );
                    //printf("Dispell Done\n");
                }
                break;
                default:
                {
                    Log(MSG_WARNING,"Unknow skill status in charfunctions %u.",MagicStatus[i].Status);
                }
            }
            BEGINPACKET( pak,0x7b7 );
            ADDWORD    ( pak, clientid );
            ADDDWORD   ( pak, GServer->BuildBuffs( this ) );
            GServer->SendToVisible( &pak, this );
            MagicStatus[i].Status = 0;
            MagicStatus[i].Buff = 0;
            MagicStatus[i].BuffTime = 0;
            MagicStatus[i].Duration = 0;
            MagicStatus[i].Value = 0;
            bflag = true;
        }
        else if ( ((MagicStatus[i].Status >= 7 && MagicStatus[i].Status <= 11) || MagicStatus[i].Status == 89) && etime > 1*CLOCKS_PER_SEC) //Do poison dmg every 1.5 seconds
        {
             Stats->HP -= MagicStatus[i].Status; //Actually take 7, 8, 9, 10 or 11 from the health. Based on the Status itself, LMA: can be 89 noc too.
             MagicStatus[i].BuffTime += 1*CLOCKS_PER_SEC;
             MagicStatus[i].Duration -= 1;
             //printf("did %i poison dmg to the player, still %i seconds and %i HP remain \n", MagicStatus[i].Status, MagicStatus[i].Duration, Stats->HP);
             //Log(MSG_WARNING,"did %i poison dmg to the player / monster, still %i seconds and %I64i HP remain", MagicStatus[i].Status, MagicStatus[i].Duration, Stats->HP);

            //LMA: If dead, let's the client resynch
            if(IsDead())
            {
                BEGINPACKET( pak, 0x79f );
                ADDWORD    ( pak, clientid );
                ADDDWORD   ( pak, 1);
                GServer->SendToVisible( &pak, this );
                Log(MSG_INFO,"death poison for %i, amount: %i",clientid,MagicStatus[i].Status);
            }

             //A bunch of messy code to send dmg packet
             BEGINPACKET( pak, 0x7b6 );
             ADDWORD    ( pak, clientid );
             ADDWORD    ( pak, 0 );
             ADDDWORD   ( pak, 0x000007f8 );
             ADDBYTE    ( pak, 0x00 );
             ADDDWORD   ( pak, MagicStatus[i].Status );

             //If Enemy is killed
             if( IsDead())
             {
                 //printf("char died\n");
                 CDrop* thisdrop = NULL;
                 ADDDWORD   ( pak, 16 );
                 if( !IsSummon( ) && !IsPlayer( ))
                 {
                    //LMA: No drop if already dead and drop done.
                    if(drop_dead)
                    {
                        Log(MSG_WARNING,"Trying to make a monster (CID %u, type %u) drop again but already did.",clientid,char_montype);
                    }
                    else
                    {
                         thisdrop = GetDrop( );
                         if( thisdrop!=NULL)
                         {
                             CMap* map = GServer->MapList.Index[thisdrop->posMap];
                             map->AddDrop( thisdrop );
                         }

                    }

                 }

                 //GServer->SendToVisible( &pak, this, thisdrop );
                 GServer->SendToVisible( &pak, this);
             }
             else
             {
                 //If enemy is still alive
                 ADDDWORD   ( pak, 4 );
                 GServer->SendToVisible( &pak, this );
             }
         }
        else if ( MagicStatus[i].Status == 58 || MagicStatus[i].Status == 61 || MagicStatus[i].Status == 71 || MagicStatus[i].Status >= 77 && MagicStatus[i].Status <= 80 || MagicStatus[i].Status == 88 && etime > 1*CLOCKS_PER_SEC) //Do flame dmg every 1.5 seconds
        {
             Stats->HP -= MagicStatus[i].Status;
             MagicStatus[i].BuffTime += 1*CLOCKS_PER_SEC;
             MagicStatus[i].Duration -= 1;
             printf("did %i flame dmg to the player, still %i seconds and %i HP remain \n", MagicStatus[i].Status, MagicStatus[i].Duration, Stats->HP);

            //LMA: If dead, let's the client resynch
            if(IsDead())
            {
                BEGINPACKET( pak, 0x79f );
                ADDWORD    ( pak, clientid );
                ADDDWORD   ( pak, 1);
                GServer->SendToVisible( &pak, this );
                Log(MSG_INFO,"death flame for %i, amount: %i",clientid,MagicStatus[i].Status);
            }

             //A bunch of messy code to send dmg packet
             BEGINPACKET( pak, 0x7b6 );
             ADDWORD    ( pak, clientid );
             ADDWORD    ( pak, 0 );
             ADDDWORD   ( pak, 0x000007f8 );
             ADDBYTE    ( pak, 0x00 );
             ADDDWORD   ( pak, MagicStatus[i].Status );

             //If Enemy is killed
             if( IsDead())
             {
                 //printf("char died\n");
                 CDrop* thisdrop = NULL;
                 ADDDWORD   ( pak, 16 );
                 if( !IsSummon( ) && !IsPlayer( ))
                 {
                    //LMA: No drop if already dead and drop done.
                    if(drop_dead)
                    {
                        Log(MSG_WARNING,"Trying to make a monster (CID %u, type %u) drop again but already did.",clientid,char_montype);
                    }
                    else
                    {
                         thisdrop = GetDrop( );
                         if( thisdrop!=NULL)
                         {
                             CMap* map = GServer->MapList.Index[thisdrop->posMap];
                             map->AddDrop( thisdrop );
                         }

                    }

                 }
                 //GServer->SendToVisible( &pak, this, thisdrop );
                 GServer->SendToVisible( &pak, this);
             }
             else
             {
                 //If enemy is still alive
                 ADDDWORD   ( pak, 4 );
                 GServer->SendToVisible( &pak, this );
             }
         }

    }
    for( UINT i=0;i<32;i++)
    {
        if(MagicStatus2[i].Buff == 0) continue;
        clock_t etime = clock() - MagicStatus2[i].BuffTime;
        if( etime >= MagicStatus2[i].Duration * CLOCKS_PER_SEC )
        {
        CPlayer* thisplayer = GServer->GetClientByID(clientid);
            Log(MSG_INFO,"Magic Status %i, vanish after: %i", MagicStatus2[i].Status, MagicStatus2[i].Duration);

            switch(MagicStatus2[i].Status)
            {
                case 126: // ALLbuff up
                {
                    if(i == BUFF_ATTACK_UP_POS)
                    {
                        Status->Attack_up = 0xff;
                        thisplayer->Attr->ALLbuff = 0;
                    }
                    else
                    {
                        Status->Attack_down = 0xff;
                        thisplayer->Attr->ALLbuff = 0;
                    }
                }
                default:
                {
                    Log(MSG_WARNING,"Unknow skill status in charfunctions %u.",MagicStatus[i].Status);
                }
            }
            BEGINPACKET( pak,0x7b7 );
            ADDWORD    ( pak, clientid );
            ADDDWORD   ( pak, GServer->BuildBuffs( this ) );
            GServer->SendToVisible( &pak, this );
            MagicStatus2[i].Status = 0;
            MagicStatus2[i].Buff = 0;
            MagicStatus2[i].BuffTime = 0;
            MagicStatus2[i].Duration = 0;
            MagicStatus2[i].Value = 0;
        }
    }
//    if(bflag)
//    {
//        BEGINPACKET( pak,0x7b7 );
//        ADDWORD    ( pak, clientid );
//        ADDDWORD   ( pak, GServer->BuildBuffs( this ) );
//        GServer->SendToVisible( &pak, this );
//    }
}

// VIRTUAL [return party pointer]
CParty* CCharacter::GetParty( )
{
    return NULL;
}

// VIRTUAL [return party pointer]
GAGroup* CCharacter::GetGroup( )
{
    return NULL;
}

// VIRTUAL [return clan pointer]
CLAN* CCharacter::GetClan( )
{
    return NULL;
}

bool CCharacter::IsAttacking( )
{
    if(IsOnBattle( ))
    {
        switch(Battle->atktype)
        {
            case SKILL_BUFF:
            case BUFF_SELF:
            case BUFF_AOE:
                return false;
        }
    }
    else return false;
    return true;
}

// [VIRTUAL]
void CCharacter::reduceItemsLifeSpan(bool atacked)
{
}

// [VIRTUAL]
unsigned CCharacter::getWeaponType()
{
}

/*
// [VIRTUAL]
bool CCharacter::AddClanPoints(unsigned int count)
{
}
*/

// [VIRTUAL]
CClientSocket* CCharacter::getClient()
{
   return NULL;
}
