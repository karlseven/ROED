#include "worldserver.h"

// Add Player buffs
bool CWorldServer::AddBuffs( CSkills* thisskill, CCharacter* character, int intvalue )
{
    Log(MSG_INFO, "called addbuffs. %i",thisskill->id, thisskill->duration );
    bool bflag = false;
    for(unsigned int i=0;i<3;i++)
    {
        if(thisskill->status[i] != 0) // sets status flags in magicstatus array
        {
            bflag = CheckABuffs( thisskill, character, intvalue, i );
        }
        else // some skills are instant effects without status changes e.g. healing.
        {
            if(thisskill->buff[i] != 0)
            {
                bflag = InstantBuff( thisskill, character, intvalue, i );
            }
        }
    }
    return bflag;
}

// handle instant effect skills without status changes
bool CWorldServer::InstantBuff( CSkills* thisskill, CCharacter* character, int intvalue, int i )
{
    //Log( MSG_INFO, "Instant skill cast: Status (should be zero):%i buff: %i", thisskill->status[i], thisskill->buff[i] );

    switch( thisskill->buff[i])
    {
        case 16: // HP
        {
            if(thisskill->duration <= 0 )//is heal
            {
                if(character->Stats->HP <= 0) //character is dead
                    return true;



                Log(MSG_INFO,"Character %i HP is initially %I64i", character->clientid, character->Stats->HP);

                int heal = thisskill->value1[i];

				character->Stats->HP += heal;

                /*//character->Stats->HP += (long int)thisskill->value1[i]; //apparently there is no buff here. // + Evalue - 8;
                //Log(MSG_INFO,"Character %i healed by %i points",character->clientid, thisskill->value1[i]);
                if (thisskill->id>920 && thisskill->id<926)//Cure (id.921-925)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 1.5863));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Cure healed by %i points with %i int",character->clientid, healpoint, Evalue);
                }
                if (thisskill->id>980 && thisskill->id<986)//Recovery (id.981-985)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 3.6493));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Recovery healed by %i points with %i int",character->clientid, healpoint, Evalue);
                }
                if (thisskill->id>1030 && thisskill->id<1036)//Party Heal (id.1031-1035)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 1.7608));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Party Heal healed by %i points with %i int",character->clientid, healpoint, Evalue);
                }
                if (thisskill->id>1040 && thisskill->id<1046)//Intergrity (id.1041-1045)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 3.3663));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Integrity healed by %i points with %i int",character->clientid, healpoint, Evalue);
                }
                if (thisskill->id>1240 && thisskill->id<1246)//Heavently Grace (id.1241-1245)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 9.2050));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Heavently Grace healed by %i points with %i int",character->clientid, healpoint, Evalue);

                }
                if (thisskill->id>6099 && thisskill->id<6105)//Restoration (id.6100-6104)
                {
                    long int healpoint = (long int)(thisskill->value1[i] + ((Evalue - 15) * 4.1259));
                    character->Stats->HP += thisskill->value1[i] + healpoint;
                    Log(MSG_INFO,"Character %i Restoration healed by %i points with %i int",character->clientid, healpoint, Evalue);
                }*/
                if(character->Stats->HP > character->Stats->MaxHP )
                {
                    character->Stats->HP = character->Stats->MaxHP;
                }
                Log(MSG_INFO,"Character %i HP is now %I64i", character->clientid, character->Stats->HP);
                return true;
            }
        }
        break;
        case 17: // MP
        {
            if(thisskill->duration <= 0 )// recover MP
            {
                //Log(MSG_INFO,"Character %i MP was %I64i", character->clientid, character->Stats->MP);
                character->Stats->MP += (long int)thisskill->value1[i];
                if(character->Stats->MP > character->Stats->MaxMP)
                {
                    character->Stats->MP = character->Stats->MaxMP;
                }
                //Log(MSG_INFO,"Character %i MP is now %I64i", character->clientid, character->Stats->MP);
                return true;
            }
        }
        break;
        case 76: // Stamina
        {
            if(character->IsPlayer()) //monsters do not have stamina it would seem
            {
                if(thisskill->duration <= 0 )// recover Stamina
                {
                    CPlayer* thisclient = GServer->GetClientByID(character->clientid);
                    if(thisclient == NULL)return false;
                    thisclient->CharInfo->stamina += (long int)thisskill->value1[i];
                    if(thisclient->CharInfo->stamina > 5000)
                    {
                        thisclient->CharInfo->stamina = 5000;
                    }
                    //Log(MSG_INFO,"Character %i Stamina is now %i", character->clientid, thisclient->CharInfo->stamina);
                    return true;
                }
            }
            else
                return false;
        }
        break;
    }
    return false;
}

// Add DeBuffs
bool CWorldServer::CheckABuffs( CSkills* thisskill, CCharacter* character, int intvalue,int i)
{
    Log( MSG_INFO, "checkabuffs status: %i buff: %i SkillID: %i", thisskill->status[i], thisskill->buff[i], thisskill->id);
    bool bflag = false;

	// Terr0risT - Certain skills have success rates lower than 100%. We will implement that.
    int randv = GServer->RandNumber(0, 100);

    if(thisskill->status[i] != 0)
    {
        switch( thisskill->status[i])
        {
            case STATUS_POISON_25:
            case STATUS_POISON_50:
            case STATUS_POISON_75:
            case STATUS_POISON_100:
            case STATUS_POISON_150:
            case STATUS_POISON_300:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Poisoned Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Poisoned, character->Status->Poisoned,true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_POISONED_POS)
                    {
                        character->Status->Poisoned = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Poisoned Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_SILENCE:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Mute Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Muted, character->Status->Muted, true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_DUMB_POS)
                    {
                        character->Status->Muted = j;
                        character->Status->CanCastSkill = false;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Muted Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_SLEEP:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Sleep Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Sleep, character->Status->Sleep, true, true );
                Log( MSG_INFO, "Sleep Status attempted. position = %i", BuffValue.Position);
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_SLEEP_POS)
                    {
                        character->Status->Sleep = j;
                        character->Status->CanAttack = false;
                        character->Status->CanMove = false;
                        character->Status->CanCastSkill = false;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Sleep Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_STUN:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Fainted Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Faint, character->Status->Faint, true, true );
                //Log( MSG_INFO, "Stun Status attempted. position = %i", BuffValue.Position);
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_FAINT_POS)
                    {
                        character->Status->Faint = j;
                        character->Status->CanAttack = false;
                        character->Status->CanMove = false;
                        character->Status->CanCastSkill = false;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Fainted Status applied");
                        bflag = true;
                    }
                }
            }
            break;
			case STATUS_CANCEL_BUFF1:
            case STATUS_CANCEL_ALL: // Dispell. removes all buff and debuff effects
            {
                //Log( MSG_INFO, "checkabuffs: Dispell Status detected %i", thisskill->status[i] );
                // some dispell skills have duration of 2 seconds. Others have zero.
                // for now we will treat them all as instants so we don't need a buff slot
                if(randv <= thisskill->success)
                {
                    for(int i = 0; i < 30; i++)
                    {
                        character->MagicStatus[i].Duration = 0;
                        character->MagicStatus[i].BuffTime = 0;
                    }
                    Log( MSG_INFO, "Dispell Status applied successfully");
                    // the rest will be taken care of in RefreshBuffs()
					bflag = false;
                }
                bflag = false;
            }
            break;
            case STATUS_ENCHANT_DAMAGE1: //A_Extra_Damage:
            case STATUS_IM_ENCHANT_DAMAGE: //A_GMExtra_Damage:
            case STATUS_ENCHANT_DAMAGE2: //Valkyrie Charm:
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, character->Status->ExtraDamage_up,character->Status->ExtraDamage_down, character->Stats->Attack_Power,true );

                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->ExtraDamage_add;
                    //LMA: fix by sickb0y
                    character->Stats->ExtraDamage_add = thisskill->value2[1];

                    if(j==BUFF_DUMMY_DAMAGE_POS)
                        character->Status->ExtraDamage_up = j;
                    else
                        character->Status->ExtraDamage_down = j;
                    Log( MSG_INFO, "Add DMG buff position %i. AddDMG(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    //character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].Buff = thisskill->status[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    //character->MagicStatus[j].Value = BuffValue.Value;  // wrongO . Additional damage uses skill power not buff value. Fix later
                    character->MagicStatus[j].Value = thisskill->atkpower;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
                else{ Log( MSG_INFO, "value is NULL");}

            }
            break;
            case STATUS_REFLECT:
            {
                 CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->ShieldDamage_up,
                                                character->Status->ShieldDamage_down,true);
//                                                character->Stats->ShieldDamage, true );
                 if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
//                    character->Stats->ShieldDamage = thisskill->atkpower;
                    if(j==BUFF_SHIELD_DAMAGE_POS)
                        character->Status->ShieldDamage_up = j;
                    else
                        character->Status->ShieldDamage_down = j;
                    //character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].Buff = thisskill->status[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    //character->MagicStatus[j].Value = BuffValue.Value;  // wrongO . shield damage uses skill power not buff value. Fix later
                    character->MagicStatus[j].Value = thisskill->atkpower;
                    character->MagicStatus[j].Status = thisskill->status[i];

					character->shield_reflect=thisskill->atkpower;
                    bflag = true;
                }
            }
            break;
            case STATUS_ATTACK_UP:
            case STATUS_ATTACK_DOWN:
            case STATUS_IM_ATTACK_UP:
            {
                //Log( MSG_INFO, "checkabuffs: Attack buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Attack_up,
                                                character->Status->Attack_down,
                                                character->Stats->Attack_Power, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Attack_Power;

                    character->Stats->Attack_Power = BuffValue.NewValue;
                    if(j==BUFF_ATTACK_UP_POS)
                        character->Status->Attack_up = j;
                    else
                        character->Status->Attack_down = j;
                    Log( MSG_INFO, "Attack Power buff position %i. Atk(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_DEFENSE_UP:
            case STATUS_DEFENSE_DOWN1:
            case STATUS_IM_DEFENSE_UP:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Defense buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Defense_up,
                                                character->Status->Defense_down,
                                                character->Stats->Defense, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Defense;

                    character->Stats->Defense = BuffValue.NewValue;
                    if(j==BUFF_DEFENSE_UP_POS)
                        character->Status->Defense_up = j;
                    else
                        character->Status->Defense_down = j;
                    Log( MSG_INFO, "Deffence buff position %i. Deff(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_HIT_UP:
            case STATUS_HIT_DOWN:
            case STATUS_IM_HIT_UP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Accuracy_up,
                                                character->Status->Accuracy_down,
                                                character->Stats->Accuracy, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Accuracy;

                    character->Stats->Accuracy = BuffValue.NewValue;
                    if(j==BUFF_HITRATE_UP)
                        character->Status->Accuracy_up = j;
                    else
                        character->Status->Accuracy_down = j;
                    Log( MSG_INFO, "Accuracy buff position %i. Acc(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_MDEFENSE_UP:
            case STATUS_MDEFENSE_DOWN:
            case STATUS_IM_MDEFENSE_UP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Magic_Defense_up,
                                                character->Status->Magic_Defense_down,
                                                character->Stats->Magic_Defense, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Magic_Defense;

                    character->Stats->Magic_Defense = BuffValue.NewValue;
                    if(j==BUFF_MDEFENSE_UP_POS)
                        character->Status->Magic_Defense_up = j;
                    else
                        character->Status->Magic_Defense_down = j;
                    Log( MSG_INFO, "Magic Resistance buff position %i. MDef(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_AVOID_UP:
            case STATUS_AVOID_DOWN:
            case STATUS_IM_AVOID_UP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Dodge_up,
                                                character->Status->Dodge_down,
                                                character->Stats->Dodge, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Dodge;

                    character->Stats->Dodge = BuffValue.NewValue;
                    if(j==BUFF_DODGE_UP_POS)
                        character->Status->Dodge_up = j;
                    else
                        character->Status->Dodge_down = j;
                    Log( MSG_INFO, "Dodge buff position %i. Dr(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_DASH_UP:
            case STATUS_DASH_DOWN:
            case STATUS_IM_DASH_UP:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: move speed buff detected %i", thisskill->buff[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Dash_up,
                                                character->Status->Dash_down,
                                                character->Stats->Move_Speed, true );

                //LMA: >=0 because some skills are really efficient...
                if(BuffValue.NewValue>=0)
                {
                    UINT j = BuffValue.Position;

                    //LMA: for debug
                    UINT prev_value=character->Stats->Move_Speed;

                    character->Stats->Move_Speed = BuffValue.NewValue;
                    if(j==BUFF_DASH_UP_POS)
                        character->Status->Dash_up = j;
                    else
                        character->Status->Dash_down = j;
                    Log( MSG_INFO, "Move speed buff position %i. move speed(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_HASTE_UP:
            case STATUS_HASTE_DOWN:
            case STATUS_IM_HASTE_UP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Haste_up,
                                                character->Status->Haste_down,
                                                character->Stats->Attack_Speed, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    double prev_value=character->Stats->Attack_Speed;

                    character->Stats->Attack_Speed = BuffValue.NewValue;
                    if(j==BUFF_HASTE_UP_POS)
                        character->Status->Haste_up = j;
                    else
                        character->Status->Haste_down = j;
                    Log( MSG_INFO, "Attack Speed buff position %i. ASpeed(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_CRITICAL_UP:
            case STATUS_CRITICAL_DOWN:
            case STATUS_IM_CRITICAL_UP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->Critical_up,
                                                character->Status->Critical_down,
                                                character->Stats->Critical, true );
                if(BuffValue.NewValue != 0)
                {
                    UINT j = BuffValue.Position;

                    //Tomiz : Debug
                    UINT prev_value=character->Stats->Critical;

                    character->Stats->Critical = BuffValue.NewValue;
                    if(j==BUFF_CRITICAL_UP_POS)
                        character->Status->Critical_up = j;
                    else
                        character->Status->Critical_down = j;
                    Log( MSG_INFO, "Critical buff position %i. Crit(%i->%i). buff value %i", j,prev_value,BuffValue.NewValue,BuffValue.Value );
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_MAX_HP: // max HP up
            case STATUS_IM_MAX_HP: // max HP up
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->HP_up,
                                                character->Status->HP_down,
                                                character->Stats->MaxHP, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->MaxHP = BuffValue.NewValue;
                    if(j==BUFF_MAX_HP_POS)
                        character->Status->HP_up = j;
                    else
                        character->Status->HP_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_MAX_MP:
            case STATUS_IM_MAX_MP:
            if(randv <= thisskill->success)
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->MP_up,
                                                character->Status->MP_down,
                                                character->Stats->MaxMP, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    character->Stats->MaxMP = BuffValue.NewValue;
                    if(j==BUFF_MAX_MP_POS)
                        character->Status->MP_up = j;
                    else
                        character->Status->MP_down = j;
                    character->MagicStatus[j].Buff = thisskill->buff[i];
                    character->MagicStatus[j].BuffTime = clock();
                    character->MagicStatus[j].Duration = thisskill->duration;
                    character->MagicStatus[j].Value = BuffValue.Value;
                    character->MagicStatus[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_BURN_30:
            case STATUS_BURN_60:
            case STATUS_BURN_100:
            case STATUS_BURN_150:
            case STATUS_BURN_200:
            case STATUS_BURN_300:
            case STATUS_BURN_400:
            if(randv <= thisskill->success)
            {
                Log( MSG_INFO, "checkabuffs: Flamed Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Flamed, character->Status->Flamed,true, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_BURN_POS)
                    {
                        character->Status->Flamed = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        Log( MSG_INFO, "Flamed Status applied");
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_STEALTH1:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Stealth Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Stealth, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_STEALTH_POS)
                    {
                        character->Status->Stealth = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Stealth Status %i applied for %is", character->MagicStatus[j].Buff, thisskill->duration);
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_STEALTH_WEAKEN:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Weary Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Weary, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                        character->Status->Weary = j;
                        character->Status->CanCastSkill = false;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Weary Status %i applied for %is", character->MagicStatus[j].Buff, thisskill->duration);
                        bflag = true;
                }
            }
            break;
            case STATUS_CLOAKING: //Cloak
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Cloak Status detected %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Cloaking, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_CLOAKING_POS)
                    {
                        character->Status->Cloaking = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Cloak Status %i applied for %is",character->MagicStatus[j].Buff, thisskill->duration);
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_DETECT: //Detect
            if(randv <= thisskill->success)
            {
                Log( MSG_INFO, "checkabuffs: Detect Status detected : %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Detect, true );
                if(BuffValue.Position != 0xff)
                {
                        UINT j = BuffValue.Position;
                        character->Status->Detect = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Detect Status %i applied for to %i",character->MagicStatus[j].Status, character->clientid);
                        bflag = true;
                }
            }
            break;
            case STATUS_TAUNT:
            if(randv <= thisskill->success)
            {
                //Log( MSG_INFO, "checkabuffs: Taunt Status detected : %i", thisskill->status[i] );
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Taunt, true );
                if(BuffValue.Position != 0xff)
                {
                    UINT j = BuffValue.Position;
                    if(j==BUFF_TAUNT_POS)
                    {
                        character->Status->Taunt = j;
                        //character->MagicStatus[j].Buff = 1; // needs some value or else it will not be counted in GetBuffValue. trying it with 1
                        character->MagicStatus[j].Buff = thisskill->status[i];
                        character->MagicStatus[j].BuffTime = clock();
                        character->MagicStatus[j].Duration = thisskill->duration;
                        character->MagicStatus[j].Value = 0; // this might cause headaches later
                        character->MagicStatus[j].Status = thisskill->status[i];
                        //Log( MSG_INFO, "Taunt Status %i applied for to %i",character->MagicStatus[j].Status, character->clientid);
                        bflag = true;
                    }
                }
            }
            break;
            case STATUS_CANCEL_DEBUFF1:
            if(randv <= thisskill->success)
            {
				CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i, 0xff, character->Status->Recover, true );
                if(BuffValue.Position != 0xff)
                {
                   UINT j = BuffValue.Position;
                        character->MagicStatus[j].Duration = 0;
                        character->MagicStatus[j].BuffTime = 0;
                        bflag = true;
                }
            }
            break;
            case STATUS_STR_UP: case STATUS_STR_DOWN:
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->STR_up,
                                                character->Status->STR_down,
                                                0, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    CPlayer* thisclient = GServer->GetClientByID(character->clientid);
                    thisclient->Attr->STRbuff = BuffValue.NewValue;
                    if(thisclient->Attr->STRbuff > 0)
                        character->Status->STR_up = j;
                    else
                        character->Status->STR_down = j;

                    character->MagicStatus2[j].Buff = thisskill->buff[i];
                    character->MagicStatus2[j].BuffTime = clock();
                    character->MagicStatus2[j].Duration = thisskill->duration;
                    character->MagicStatus2[j].Value = BuffValue.Value;
                    character->MagicStatus2[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_DEX_UP:
            case STATUS_INT_UP:
            case STATUS_CON_UP:
            case STATUS_CHA_UP:
            case STATUS_SEN_UP:
            break;
            case STATUS_ALL_UP: case STATUS_ALL_DOWN:
            {
                CBValue BuffValue = GetBuffValue( thisskill, character, intvalue, i,
                                                character->Status->ALL_up,
                                                character->Status->ALL_down,
                                                0, true );
                if(BuffValue.NewValue!=0)
                {
                    UINT j = BuffValue.Position;
                    CPlayer* thisclient = GServer->GetClientByID(character->clientid);
                    thisclient->Attr->ALLbuff = BuffValue.NewValue;
                    if(thisclient->Attr->ALLbuff > 0)
                        character->Status->ALL_up = j;
                    else
                        character->Status->ALL_down = j;

                    character->MagicStatus2[j].Buff = thisskill->buff[i];
                    character->MagicStatus2[j].BuffTime = clock();
                    character->MagicStatus2[j].Duration = thisskill->duration;
                    character->MagicStatus2[j].Value = BuffValue.Value;
                    character->MagicStatus2[j].Status = thisskill->status[i];
                    bflag = true;
                }
            }
            break;
            case STATUS_DEX_DOWN:
            case STATUS_INT_DOWN:
            case STATUS_CON_DOWN:
            case STATUS_CHA_DOWN:
            case STATUS_SEN_DOWN:
            break;
            default:
            {
                Log(MSG_WARNING,"Unknown skill status: %i offset %i in skill %u.",thisskill->status[i],i,thisskill->id);
            }
            break;

        }
    }

    character->RefreshBuff( );

    return bflag;
}

CBValue CWorldServer::GetBuffValue( CSkills* thisskill, CCharacter* character, int intvalue, UINT i, UINT up, UINT down, UINT CurrentValue, bool Buff, bool Status )
{
    CBValue NewValue;
    NewValue.Position = 0xff;
    NewValue.NewValue = 0;
    NewValue.Value = 0;
    UINT Value = 0;
    UINT NormalValue = 0;
    UINT UpValue = 0;
    UINT DownValue = 0;
    // not currently detecting debuffs properly so let's bring in some new code :)
    //PY buff mod based on thiskill->status[i]

    //LMA: removing 13 (max mp) from debuff to buff
    switch(thisskill->status[i])
    {
        case 12: case 13: case 14: case 16: case 18:
        case 20: case 22: case 24: case 26: case 28:
        case 35: case 36:
        case 40: case 41: case 42: case 44: case 45: case 46: case 47: case 48: case 49:
        case 50: case 51: case 52: case 53: case 54: case 57:
        case 83: case 126:
            Buff = true;
        break;

        case 7: case 8: case 9:
        case 10: case 11: case 15: case 17: case 19:
        case 21: case 23: case 25: case 27: case 29:
        case 30: case 31: case 32: case 33: case 34: case 37: case 38: case 39:
        case 43:
        case 55: case 56: case 58: case 59:
        case 60: case 61: case 62: case 63: case 64: case 65: case 66:  case 67: case 68: case 69:
        case 70: case 71: case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79:
        case 80: case 86: case 88: case 89:
            Buff = false;
        break;
        default:
        {
            Log(MSG_WARNING,"Unknown status can't tell if a buff or not %u offset %u for skill %u",thisskill->status[i],i,thisskill->id);
            Buff = true;
        }
        break;

    }
    switch(thisskill->status[i])
    {
        case STATUS_HP_8: case STATUS_HP_18: case STATUS_HP_30: case STATUS_HP_43: case STATUS_HP_58: case STATUS_HP_75: case STATUS_SUMMON_HP:
        case STATUS_HP_92: case STATUS_HP_111: case STATUS_HP_131: case STATUS_HP_152: case STATUS_HP_174: case STATUS_HP_197: case STATUS_HP_221:
        case STATUS_HP_246: case STATUS_HP_272: case STATUS_HP_299: case STATUS_HP_326: case STATUS_HP_354: case STATUS_HP_383: case STATUS_HP_413:
        case STATUS_HP_443: case STATUS_HP_475: case STATUS_HP_539: case STATUS_HP_572: case 115:
            NewValue.Position = BUFF_HP_POS;
            break;

        case STATUS_MP_6: case STATUS_MP_10: case STATUS_MP_14: case STATUS_MP_18: case STATUS_MP_21: case STATUS_MP_25: case STATUS_MP_29:
        case STATUS_MP_33: case STATUS_MP_36: case STATUS_MP_40: case STATUS_MP_44: case STATUS_MP_48: case STATUS_MP_51: case STATUS_MP_55:
        case STATUS_MP_59: case STATUS_MP_63: case STATUS_MP_66: case STATUS_MP_70: case STATUS_MP_74: case STATUS_MP_78: case STATUS_MP_81:
        case STATUS_MP_85: case STATUS_MP_89: case STATUS_MP_93: case STATUS_MP_96: case 116:
            NewValue.Position = BUFF_MP_POS;
            break;

        case STATUS_POISON_25: case STATUS_POISON_50: case STATUS_POISON_75: case STATUS_POISON_100: case STATUS_POISON_150: case STATUS_POISON_300:
            NewValue.Position = BUFF_POISONED_POS;
            break;

        case STATUS_MAX_HP: case STATUS_IM_MAX_HP: case STATUS_HALLOWEEN_MAX_HP:
            NewValue.Position = BUFF_MAX_HP_POS;
            break;

        case STATUS_MAX_MP: case STATUS_IM_MAX_MP: case STATUS_HALLOWEEN_MAX_MP:
            NewValue.Position = BUFF_MAX_MP_POS;
            break;

        case STATUS_DASH_UP: case STATUS_IM_DASH_UP: case STATUS_HALLOWEEN_DASH_UP:
            NewValue.Position = BUFF_DASH_UP_POS;
            break;

        case STATUS_DASH_DOWN: case STATUS_DASH_DOWN2:
            NewValue.Position = BUFF_DASH_DOWN_POS;
            break;

        case STATUS_HASTE_UP: case STATUS_IM_HASTE_UP: case STATUS_HALLOWEEN_HASTE_UP:
            NewValue.Position = BUFF_HASTE_UP_POS;
            break;

        case STATUS_HASTE_DOWN:
            NewValue.Position = BUFF_HASTE_DOWN_POS;
            break;

        case STATUS_ATTACK_UP: case STATUS_IM_ATTACK_UP: case STATUS_EVT_ATTACK_UP: case STATUS_HALLOWEEN_ATTACK_HP:
            NewValue.Position = BUFF_ATTACK_UP_POS;
            break;

        case STATUS_ATTACK_DOWN:
            NewValue.Position = BUFF_ATTACK_DOWN_POS;
            break;

        case STATUS_DEFENSE_UP: case STATUS_IM_DEFENSE_UP: case STATUS_HALLOWEEN_DEFENSE_UP:
            NewValue.Position = BUFF_DEFENSE_UP_POS;
            break;

        case STATUS_DEFENSE_DOWN1: case STATUS_DEFENSE_DOWN2:
            NewValue.Position = BUFF_DEFENSE_DOWN_POS;
            break;

        case STATUS_MDEFENSE_UP: case STATUS_IM_MDEFENSE_UP: case STATUS_HALLOWEEN_MDEFENSE_UP:
            NewValue.Position = BUFF_MDEFENSE_UP_POS;
            break;

        case STATUS_MDEFENSE_DOWN:
            NewValue.Position = BUFF_MDEFENSE_DOWN_POS;
            break;

        case STATUS_IM_HIT_UP: case STATUS_HALLOWEEN_HIT_UP: case STATUS_HIT_UP:
            NewValue.Position = BUFF_HITRATE_UP_POS;
            break;

         case STATUS_HIT_DOWN:
            NewValue.Position = BUFF_HITRATE_DOWN_POS;
            break;

        case STATUS_IM_CRITICAL_UP: case STATUS_CRITICAL_UP:
            NewValue.Position = BUFF_CRITICAL_UP_POS;
            break;

        case STATUS_CRITICAL_DOWN:
            NewValue.Position = BUFF_CRITICAL_DOWN_POS;
            break;

        case STATUS_AVOID_UP: case STATUS_IM_AVOID_UP: case STATUS_EVT_DODGE: case STATUS_HALLOWEEN_AVOID_UP:
            NewValue.Position = BUFF_DODGE_UP_POS;
            break;

        case STATUS_AVOID_DOWN:
            NewValue.Position = BUFF_DODGE_DOWN_POS;
            break;

        case STATUS_SILENCE:
            NewValue.Position = BUFF_DUMB_POS;
            break;

        case STATUS_SLEEP:
            NewValue.Position = BUFF_SLEEP_POS;
            break;

        case STATUS_STUN:
            NewValue.Position = BUFF_FAINT_POS;
            break;

        case STATUS_STEALTH1: case STATUS_STEALTH2:
            NewValue.Position = BUFF_STEALTH_POS;
            break;

        case STATUS_CLOAKING:
            NewValue.Position = BUFF_CLOAKING_POS;
            break;

        case STATUS_REFLECT: case STATUS_SHIELD: case STATUS_MSHIELD_ABSORB:
            NewValue.Position = BUFF_SHIELD_DAMAGE_POS;
            break;

        case STATUS_ENCHANT_DAMAGE1: case STATUS_IM_ENCHANT_DAMAGE: case STATUS_ENCHANT_DAMAGE2: case STATUS_HALLOWEEN_ENCHANT_DAMAGE1:
        case STATUS_HALLOWEEN_ENCHANT_DAMAGE2: case  STATUS_HALLOWEEN_ENCHANT_DAMAGE3: case STATUS_HALLOWEEN_ENCHANT_DAMAGE4: case STATUS_HALLOWEEN_ENCHANT_DAMAGE5:
            NewValue.Position = BUFF_DUMMY_DAMAGE_POS;
            break;

        case STATUS_TAUNT:
            NewValue.Position = BUFF_TAUNT_POS;
            break;

        case STATUS_BURN_30: case STATUS_BURN_60: case STATUS_BURN_100: case STATUS_BURN_150: case STATUS_BURN_200: case STATUS_BURN_300: case STATUS_BURN_400:
            NewValue.Position = BUFF_TAUNT_POS;
            break;

        case STATUS_STR_UP:
            NewValue.Position = BUFF_STATUS_STR_UP_POS;
            break;

        case STATUS_INT_UP:
            NewValue.Position = BUFF_STATUS_INT_UP_POS;
            break;

        case 126:
            NewValue.Position = BUFF_STATUS_ALL_UP_POS;
            break;
    }
    if(NewValue.Position == 0xff)
    {
        Log(MSG_DEBUG,"No poisiton for %i",thisskill->status[i]);
        return NewValue;
    }
    if(character->MagicStatus[NewValue.Position].Status == 0)
    {
        NormalValue = CurrentValue;
    }
    else
    {
        NormalValue = CurrentValue - character->MagicStatus[NewValue.Position].Value;
        UpValue = character->MagicStatus[NewValue.Position].Value;
    }

    if( thisskill->value2[i] > 0 )
    {
        if(thisskill->buff[i]==24)
        {
            Value = NormalValue * thisskill->value2[i] / 1000;
        }
        else
            Value = NormalValue * thisskill->value2[i] / 100;

    }
    if( thisskill->value1[i] > 0 )
    {
        int difference = floor(thisskill->value1[i] * 1.539);
        float divider = 485.0 / difference;
        int statbonus = thisskill->value1[i] + round((intvalue - 15) / divider);
        Value += statbonus;
        Log(MSG_INFO, "Buff = %i , Buff Value = %i give %i bonus", thisskill->buff[i],thisskill->value1[i], Value);// 5-0,3164556962025316=
        Log(MSG_INFO, "Stat bonus: %i", statbonus);
    }
    if( thisskill->status[i] == 83 && (thisskill->id > 900 && thisskill->id < 910) )//Tomiz: Temp Fix For Spirit Boost who use atkpower for value (when skill is self skill)
    {
        Value += thisskill->atkpower;
        Log(MSG_INFO, "Add DMG Skill: thisskill->value1 = %i",thisskill->atkpower);
    }

    if(Buff)
    {
        if( Value + CurrentValue - DownValue >= CurrentValue )
        {
            CurrentValue = NormalValue - DownValue + Value;
        }
        else
        {
            CurrentValue = 0;
        }
    }
    else
    {
        CurrentValue = NormalValue + UpValue - Value;
    }
    Log(MSG_INFO, "Value %i CurrentValue %i DownValue %i",Value,CurrentValue,DownValue);
    NewValue.NewValue = CurrentValue;
    NewValue.Value = Value;
    return NewValue;
}

// Build Buffs to Show
unsigned int CWorldServer::BuildBuffs( CCharacter* character )
{
    return (BuildUpBuffs(character) + BuildDeBuffs(character));
}
unsigned int CWorldServer::BuildBuffs2( CCharacter* character )
{
    return (BuildUpBuffs2(character) + BuildDeBuffs2(character));
}
// Build Buffs to Show
unsigned int CWorldServer::BuildUpBuffs( CCharacter* character )
{
    DWORD buff = 0;

    if(character->Status->HPHeal != 0xff)//A_DASH:
        buff += BUFF_HP;
    if(character->Status->MPHeal != 0xff)//A_DASH:
        buff += BUFF_MP;
    if(character->Status->Dash_up != 0xff)//A_DASH:
        buff += BUFF_DASH_UP;
    if(character->Status->HP_up != 0xff)//A_HP:
        buff += BUFF_MAX_HP; //10000000
    if(character->Status->MP_up != 0xff)//A_MP:
        buff += BUFF_MAX_MP; //20000000
    if(character->Status->Attack_up != 0xff)//A_ATTACK: !!!!!
        buff += BUFF_ATTACK_UP; // 00040000 !!!!!
    if(character->Status->Haste_up != 0xff)//A_HASTE:
        buff += BUFF_HASTE_UP;
    if(character->Status->Defense_up != 0xff)//A_DEFENSE: !!!!
        buff += BUFF_DEFENSE_UP;
    if(character->Status->Magic_Defense_up != 0xff)//A_MDEFENSE_UP
        buff += BUFF_MDEFENSE_UP;
    if(character->Status->Accuracy_up != 0xff)//A_ACCUR:
        buff += BUFF_HITRATE_UP; //000001000
    if(character->Status->Critical_up != 0xff)//A_CRITICAL:
        buff += BUFF_CRITICAL_UP;
    if(character->Status->Dodge_up != 0xff)//A_DODGE:
        buff += BUFF_DODGE_UP;
    if(character->Status->ExtraDamage_up != 0xff)
        buff += BUFF_DUMMY_DAMAGE;
    if(character->Status->ShieldDamage_up != 0xff)//A_Shield_Damage:
        buff += BUFF_SHIELD_DAMAGE;

    return buff;
}
// Build Buffs to Show
unsigned int CWorldServer::BuildDeBuffs( CCharacter* character )
{
    DWORD buff = 0;

    if(character->Status->Dash_down != 0xff)//A_DASH: s
        buff += BUFF_DASH_DOWN;
    if(character->Status->HP_down != 0xff)//A_HP:
        buff += 0;
    if(character->Status->MP_down != 0xff)//A_MP:
        buff += 0;
    if(character->Status->Poisoned != 0xff)//A_POISON
        buff += BUFF_POISONED;
    if(character->Status->Flamed != 0xff)//A_FLAME
        buff += BUFF_BURN;
    if(character->Status->Attack_down != 0xff) // A_ATTACK:
        buff += BUFF_ATTACK_DOWN;
    if(character->Status->Haste_down != 0xff)//A_HASTE:
        buff += BUFF_HASTE_DOWN;
    if(character->Status->Defense_down != 0xff)//A_DEFENSE:
        buff += BUFF_DEFENSE_DOWN;
    if(character->Status->Magic_Defense_down != 0xff)
        buff += BUFF_MDEFENSE_DOWN;
    if(character->Status->Dodge_down  != 0xff)
        buff += BUFF_DODGE_UP;
    if(character->Status->Accuracy_down != 0xff)//A_ACCUR:
        buff += BUFF_HITRATE_DOWN;
    if(character->Status->Critical_down != 0xff)//A_CRITICAL:
        buff += BUFF_CRITICAL_DOWN;
    if(character->Status->Muted != 0xff)//A_MUTE
        buff += BUFF_DUMB;
    if(character->Status->Weary != 0xff)//A_STEALTH
        buff += BUFF_DUMB;
    if(character->Status->ExtraDamage_down != 0xff)//A_Extra_Damage:
        buff += BUFF_DUMMY_DAMAGE;
    if(character->IsSummon( ))
        buff += BUFF_LIFE_TIME;
    if(character->Status->Stuned != 0xff)//A_STUN
        buff += BUFF_FAINT;
    if(character->Status->Stealth != 0xff)//A_STEALTH
        buff += BUFF_STEALTH;
    if(character->Status->Cloaking != 0xff)//A_CLOAKING
        buff += BUFF_CLOAKING;

    return buff;
}
unsigned int CWorldServer::BuildUpBuffs2( CCharacter* character )
{
    DWORD buff = 0;

    if(character->Status->STR_up != 0xff)//A_DASH:
        buff += BUFF_STATUS_STR_UP;
    if(character->Status->INT_up != 0xff)//A_HP:
        buff += BUFF_STATUS_INT_UP; //10000000
    if(character->Status->CON_up != 0xff)//A_MP:
        buff += BUFF_STATUS_CON_UP; //20000000
    if(character->Status->DEX_up != 0xff)//A_ATTACK: !!!!!
        buff += BUFF_STATUS_DEX_UP; // 00040000 !!!!!

    return buff;
}
// Build Buffs to Show
unsigned int CWorldServer::BuildDeBuffs2( CCharacter* character )
{
    DWORD buff = 0;

    if(character->Status->STR_down != 0xff)//A_DASH:
        buff += 0;
    if(character->Status->INT_down != 0xff)//A_HP:
        buff += 0; //10000000
    if(character->Status->CON_down != 0xff)//A_MP:
        buff += 0; //20000000
    if(character->Status->DEX_down != 0xff)//A_ATTACK: !!!!!
        buff += 0; // 00040000 !!!!!

    return buff;
}
unsigned int CWorldServer::GetBUFFPosition( int status )
{
    DWORD buff = 0;
    switch(status)
            {
                case 0:
                break;
                case 18: // attack power up
                case 19: // attack power down
                case 48: // attack power up
                {
                    buff = BUFF_ATTACK_UP;
                }
                break;
                case 20: // def up
                case 21: // def down
                case 49: // def up
                {
                    buff = BUFF_DEFENSE_UP;
                }
                break;
                case 24: //Accuracy up
                case 25: //Accuracy down
                case 51: //attack Accuracy up.
                {
                    buff = BUFF_HITRATE_UP;
                }
                break;
                case 22: // macic resistance up
                case 23: // magic resistance down
                case 50: // magic resistance up
                {
                    buff = BUFF_MDEFENSE_UP;
                }
                break;
                case 28: //dodge up
                case 29: //dodge down
                case 53: //dodge rate up
                {
                    buff = BUFF_DODGE_UP;
                }
                break;
                case 14: //dash
                case 15: //slow
                case 46: //movement speed increased
                {
                    buff = BUFF_DASH_UP;
                }
                break;
                case 16: // haste attack
                case 17: // slow attack
                case 47: // attack speed up
                {
                   buff = BUFF_HASTE_UP;
                }
                break;
                case 26: // crit up
                case 27: // crit down
                case 52: // crit up
                {
                    buff = BUFF_CRITICAL_UP;
                }
                break;
                case 12: // max HP up
                case 44: // max HP up
                {
                    buff = BUFF_MAX_HP;
                }
                break;
                case 13: // max MP up
                case 45: // max MP up
                {
                    buff = BUFF_MAX_MP;
                }
                break;
                case 32: // stun
                {
                    buff = BUFF_FAINT;
                }
                break;
                case 7: case 8: case 9: case 10: case 11: case 89: //poisoned
                {
                    buff = BUFF_POISONED;
                }
                break;
                case 30: // muted
                {
                    buff = BUFF_DUMB;
                }
                break;
                case 31: // sleep May need to be fixed later to accomodate multiple status effects.
                {
                    buff = BUFF_DUMB;
                }
                break;
                case 36: //A_Extra_Damage:
                case 54: //A_GMExtra_Damage:
                case 83: //Valkyrie Charm:
                {
                    buff = BUFF_DUMMY_DAMAGE;
                }
                break;
                case 56: //Taunt
                {
                    buff = BUFF_DUMB;
                }
                break;
                case 58: case 61: case 74: case 77:  case 78: case 79: case 80: //flame
                {
                    buff = BUFF_BURN;
                }
                break;
                case 33://Stealth,Camoflauge
                {
                    buff = BUFF_STEALTH;
                }
                break;
                case 86://Stealth,Weary
                {
                    buff = BUFF_STEALTH;
                }
                break;
                case 34://Cloaking
                {
                    buff = BUFF_CLOAKING;
                }
                break;
                case 35: //ShieldDamage:
                {
                    buff = BUFF_SHIELD_DAMAGE;
                }

                break;
                case STATUS_HP_8: case STATUS_HP_18: case STATUS_HP_30: case STATUS_HP_43: case STATUS_HP_58: case STATUS_HP_75: case STATUS_SUMMON_HP:
                case STATUS_HP_92: case STATUS_HP_111: case STATUS_HP_131: case STATUS_HP_152: case STATUS_HP_174: case STATUS_HP_197: case STATUS_HP_221:
                case STATUS_HP_246: case STATUS_HP_272: case STATUS_HP_299: case STATUS_HP_326: case STATUS_HP_354: case STATUS_HP_383: case STATUS_HP_413:
                case STATUS_HP_443: case STATUS_HP_475: case STATUS_HP_539: case STATUS_HP_572: case 115:
                {
                    buff = BUFF_HP;
                }
                break;

                case STATUS_MP_6: case STATUS_MP_10: case STATUS_MP_14: case STATUS_MP_18: case STATUS_MP_21: case STATUS_MP_25: case STATUS_MP_29:
                case STATUS_MP_33: case STATUS_MP_36: case STATUS_MP_40: case STATUS_MP_44: case STATUS_MP_48: case STATUS_MP_51: case STATUS_MP_55:
                case STATUS_MP_59: case STATUS_MP_63: case STATUS_MP_66: case STATUS_MP_70: case STATUS_MP_74: case STATUS_MP_78: case STATUS_MP_81:
                case STATUS_MP_85: case STATUS_MP_89: case STATUS_MP_93: case STATUS_MP_96: case 116:
                {
                    buff = BUFF_MP;
                }
                break;
                default:
                {
                    Log(MSG_WARNING,"Unknow skill status in charfunctions %i.",status);
                }
            }

    return buff;
}
unsigned int CWorldServer::GetBUFFPosition2( int status )
{
    DWORD buff = 0;
    switch(status)
            {
                case 0:
                break;
                case 126: // attack power up
                {
                    buff = BUFF_STATUS_ALL_UP;
                }
                break;
                default:
                {
                    Log(MSG_WARNING,"Unknow skill status in charfunctions %i.",status);
                }
            }

    return buff;
}
bool CWorldServer::AddUseItemStatus( CUseInfo* thisuse, CPlayer* thisclient )
{
//    CCharacter* character = GServer->GetClientByID(thisclient->clientid);
//    if(character == NULL) return true;
//    switch(thisuse->statuschange)
//    {
//        case STATUS_HP_8: case STATUS_HP_18: case STATUS_HP_30: case STATUS_HP_43: case STATUS_HP_58: case STATUS_HP_75: case STATUS_SUMMON_HP:
//        case STATUS_HP_92: case STATUS_HP_111: case STATUS_HP_131: case STATUS_HP_152: case STATUS_HP_174: case STATUS_HP_197: case STATUS_HP_221:
//        case STATUS_HP_246: case STATUS_HP_272: case STATUS_HP_299: case STATUS_HP_326: case STATUS_HP_354: case STATUS_HP_383: case STATUS_HP_413:
//        case STATUS_HP_443: case STATUS_HP_475: case STATUS_HP_539: case STATUS_HP_572: case 115:
//        {
//            int j = BUFF_HP_POS;
//            character->Status->HPHeal = j;
//            character->MagicStatus[j].Buff = thisuse->statuschange;
//            character->MagicStatus[j].BuffTime = clock();
//            character->MagicStatus[j].Duration = 10;
//            character->MagicStatus[j].Value = 0; // this might cause headaches later
//            character->MagicStatus[j].Status = thisuse->statuschange;
//            Log(MSG_WARNING,"Added HPHeal");
//        }
//        break;
//
//        case STATUS_MP_6: case STATUS_MP_10: case STATUS_MP_14: case STATUS_MP_18: case STATUS_MP_21: case STATUS_MP_25: case STATUS_MP_29:
//        case STATUS_MP_33: case STATUS_MP_36: case STATUS_MP_40: case STATUS_MP_44: case STATUS_MP_48: case STATUS_MP_51: case STATUS_MP_55:
//        case STATUS_MP_59: case STATUS_MP_63: case STATUS_MP_66: case STATUS_MP_70: case STATUS_MP_74: case STATUS_MP_78: case STATUS_MP_81:
//        case STATUS_MP_85: case STATUS_MP_89: case STATUS_MP_93: case STATUS_MP_96: case 116:
//        {
//            int j = BUFF_MP_POS;
//            character->Status->MPHeal = j;
//            character->MagicStatus[j].Buff = thisuse->statuschange;
//            character->MagicStatus[j].BuffTime = clock();
//            character->MagicStatus[j].Duration = 10;
//            character->MagicStatus[j].Value = 0; // this might cause headaches later
//            character->MagicStatus[j].Status = thisuse->statuschange;
//            Log(MSG_WARNING,"Added MPHeal");
//        }
//        break;
//    }
    return true;
}
