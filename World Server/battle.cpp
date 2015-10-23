/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007 OSRose Team http://www.dev-osrose.com

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

    depeloped with Main erose/hrose source server + some change from the original eich source
*/
#include "character.h"
#include "worldserver.h"

void CCharacter::DoAttack( )
{
     /*
     if(IsSummon())
       Log(MSG_INFO,"Someone attacks type=%i,skillid=%i",Battle->atktype,Battle->skillid);
     */

    //osptest begin
    if(IsSummon())
    {
        CCharacter* Enemy = GetCharTarget( );
        if(Enemy == NULL && Battle->atktype != SKILL_AOE && Battle->atktype != BUFF_AOE)
        {
            //LogDebug("No Enemy found");
            ClearBattle( Battle );
            return;
        }
        //LogDebug("Client id: %i Enemy client id: %i",clientid, Enemy->clientid);
        if(this == Enemy) //summoned monster is attacking itself. It has been observed to happen
        {
            //Log(MSG_INFO,"Clearing Battle for this summon");
            ClearBattle( Battle );
            return;
        }
    }
    //osptest end

    //LMA: If we're dead, why are we still fighting?
    if(IsDead())
    {
        ClearBattle(Battle);
        return;
    }

    CMap* map = GServer->MapList.Index[Position->Map];
    switch(Battle->atktype)
    {
        case NORMAL_ATTACK://normal attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }

            //osptest
            if(Enemy == this)
            {
                //Log(MSG_INFO,"WTF?? I AM trying to attack myself");
                ClearBattle( Battle );
            }
            //osptest end

            //LMA: Some logs.
            /*
            if(map->id==8)
            {
                bool is_ok=false;
                bool is_reached=false;
                bool can_attack=false;

                float distance = GServer->distance( Position->current, Enemy->Position->current );
                is_reached=IsTargetReached( Enemy );
                can_attack=CanAttack( );

                if(is_reached&&can_attack)
                    is_ok=true;

                if(IsMonster())
                {
                    Log(MSG_INFO,"monster has reached? %i (%.2f/%.2f), canattack? %i, will attack? %i",is_reached,distance,Stats->Attack_Distance,can_attack,is_ok);

                    if (is_ok)
                        Log(MSG_INFO,"NORMAL_ATTACK, monster %i has reached %i (%.2f<=%.2f)",clientid,Enemy->clientid,distance,Stats->Attack_Distance);
                    else
                        Log(MSG_INFO,"NORMAL_ATTACK, monster %i hasn't reached? %i (%.2f>%.2f)",clientid,Enemy->clientid,distance,Stats->Attack_Distance);
                }
                else
                {
                    Log(MSG_INFO,"player has reached? %i (%.2f/%.2f), canattack? %i, will attack? %i",is_reached,distance,Stats->Attack_Distance,can_attack,is_ok);

                    if (is_ok)
                        Log(MSG_INFO,"NORMAL_ATTACK, player %i has reached %i (%.2f<=%.2f)",clientid,Enemy->clientid,distance,Stats->Attack_Distance);
                    else
                        Log(MSG_INFO,"NORMAL_ATTACK, player %i hasn't reached? %i (%.2f>%.2f)",clientid,Enemy->clientid,distance,Stats->Attack_Distance);
                }

            }
            */
            //End of logs.


            if(IsTargetReached( Enemy ) && CanAttack( ))
            {
                if(GServer->ServerDebug)
                {
                    if(IsMonster())
                    {
                        Log(MSG_INFO,"monster Doing a normal attack");
                    }
                    else
                    {
                        Log(MSG_INFO,"player Doing a normal attack");
                    }
                }

                NormalAttack( Enemy );

                if (Enemy->IsMonster()) // do monster AI script when monster is attacked.
                {
                    CMonster* monster = GServer->GetMonsterByID(Enemy->clientid, Enemy->Position->Map);

                    if(monster!=NULL)
                    {
                        if(!monster->IsDead())
                        {
                            /*Log(MSG_INFO,"Monster %i is attacked, doing his AI 3, HP: %I64i",monster->clientid,monster->Stats->HP);
                            monster->DoAi(monster->thisnpc->AI, 3);*/

                            //LMA: Doing is_attacked from time to time, not at each attack...
                            if(0<=GServer->round((clock( ) - monster->nextAi_attacked)))
                            {
                                monster->nextAi_attacked=clock();
                                clock_t temp=monster->nextAi_attacked;
                                if(GServer->ServerDebug)
                                    Log(MSG_INFO,"Monster %i is attacked, doing his AI 3, HP: %I64i",monster->clientid,monster->Stats->HP);
                                monster->DoAi(monster->thisnpc->AI, 3);

                                if (temp==monster->nextAi_attacked)
                                {
                                    //LMA: AI Timer by default, some AIP can change this.
                                    monster->nextAi_attacked+=monster->thisnpc->AiTimer;
                                }

                                //Log(MSG_INFO,"Clock is %u, next is_attacked at %u, so in %u",clock(),monster->thisnpc->AiTimer,monster->thisnpc->AiTimer-clock());
                                if(GServer->ServerDebug)
                                    Log(MSG_INFO,"Clock is %u, next is_attacked at %u, so in %u",clock(),monster->nextAi_attacked,monster->nextAi_attacked-clock());

                            }

                        }

                    }

                }

            }
            else
            {

                /*if(IsPlayer())
                {
                    if(!IsTargetReached( Enemy ))
                        Log(MSG_INFO,"Player %i hasn't reached his enemy (%i) yet (%.2f,%.2f) (%.2f,%.2f)",this->clientid,this->Battle->atktarget,this->Position->current.x,this->Position->current.y,this->Position->destiny.x,this->Position->destiny.y);
                }
                else
                {
                    if(!IsTargetReached( Enemy ))
                        Log(MSG_INFO,"Monster %i hasn't reached his enemy (%i) yet (%.2f,%.2f) (%.2f,%.2f)",this->clientid,this->Battle->atktarget,this->Position->current.x,this->Position->current.y,this->Position->destiny.x,this->Position->destiny.y);
                }*/

            }

        }
        break;
        case SKILL_ATTACK://skill attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
            {
                SkillAttack( Enemy, skill );

				//Some skill attacks has aoe effects
				if(skill->aoerange>0)
                {
                    Position->aoedestiny=Enemy->Position->current;
					if(GServer->ServerDebug)
                        Log(MSG_INFO,"[DoAttack] In AOE_TARGET time for AoeSkill");
                    Battle->atktype=AOE_TARGET;
                    AoeSkill( skill, NULL );    //LMA: no specific Enemy in Zone.
                }

                if (Enemy->IsMonster())
                {
                    CMonster* monster = GServer->GetMonsterByID(Enemy->clientid, Enemy->Position->Map);

                    if(monster!=NULL)
                        monster->DoAi(monster->thisnpc->AI, 3);
                }

            }

        }
        break;
        case MONSTER_SKILL_ATTACK://LMA: monster skill attack
        {
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
                SkillAttack( Enemy, skill );
        }
        break;
        case SUMMON_BUFF://Summon buffs (support)
        {
            //LMA: For summon that buff player :)
            if (Battle->bufftarget==0)
               break;
            CCharacter* master = GetCharBuffTarget( );
            if(master==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(IsTargetReached( master, skill ) && CanAttack( ))
                SummonBuffSkill( master, skill );
        }
        break;
        case MONSTER_SKILL_BUFF://LMA: monster buffs
        {
            CCharacter* Enemy= GetCharTarget( );
            if(Enemy==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }

            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
            {
                BuffSkill( Enemy, skill );
            }

        }
        break;
       case SKILL_BUFF://buffs
        {
            //osptest
            CCharacter* Enemy = GetCharTarget( );
            if(Enemy == NULL)
            {
                //LogDebug("this target is NULL");
                ClearBattle( Battle );
                return;
            }

            CSkills* skill = GServer->GetSkillByID( Battle->skillid );

            if(skill == NULL)
            {
                //LogDebug("this skill is NULL");
                //ClearBattle( Battle );
                return;
            }

            //LogDebug("Called skill buff code for skill %i",skill->id);
            if(IsTargetReached( Enemy, skill ) && CanAttack( ))
            {
                //LogDebug("Skill successfully cast");
                //BuffSkill( Enemy, skill );

                if(IsPlayer())
                {
                    CPlayer* plkiller=(CPlayer*) this;
                    //Log(MSG_WARNING,"Before Buff skill Player %i (%s) targets cid %i",clientid,plkiller->CharInfo->charname,plkiller->Battle->target);
                }

                BuffSkill( Enemy, skill );

                if(IsPlayer())
                {
                    CPlayer* plkiller=(CPlayer*) this;
                    //Log(MSG_WARNING,"After Buff skill Player %i (%s) targets cid %i",clientid,plkiller->CharInfo->charname,plkiller->Battle->target);
                }

            }
            //osptest end
        }
        break;  //LMA: break was missing?
        case SKILL_AOE:
        case SKILL_SELF:
        case AOE_TARGET:
        {
            CCharacter* Enemy = NULL;
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            if(Battle->atktype==AOE_TARGET)
            {
                //LMA 2008/09/02: new version, the target is a zone, not a monster... so we stick with aoedestiny ;)
                float distance=GServer->distance( Position->current, Position->aoedestiny );
                //Log(MSG_INFO,"distance %f / range: %i, current: %.2f,%.2f, aoe: %.2f,%.2f",distance,skill->range,Position->current.x,Position->current.y,Position->aoedestiny.x,Position->aoedestiny.y);
                //osprose: canattacl
                if(distance<=skill->range&&CanAttack( ))
                {
                    if(GServer->ServerDebug)
                        Log(MSG_INFO,"[DoAttack] In AOE_TARGET time for AoeSkill");
                    AoeSkill( skill, NULL );    //LMA: no specific Enemy in Zone.
                }
                else
                {
                    //LMA: Too verbose...
                    //Log(MSG_INFO,"[DoAttack] In AOE_TARGET not reached or can't attack");
                }

            }
            else
            {
                if(Enemy==NULL)
                {
                    if(GServer->ServerDebug)
                        Log(MSG_INFO,"player %i: default AOE attack (%i/%i) %i for enemy NULL ", clientid,Battle->atktype,AOE_TARGET,skill->id);
                    if (skill->atkpower == 0)//Like Howl Skill soldier (AOE Def down) or Detect skill have 0 atkpower
                    {
                        if(GServer->ServerDebug)
                            Log(MSG_INFO,"[DoAttack] AoeDebuff");
                        AoeDebuff( skill, NULL );
                    }
                    else
                    {
                        AoeSkill( skill, Enemy );
                    }
                }
                else
                {
                    if(GServer->ServerDebug)
                        Log(MSG_INFO,"player %i: default AOE attack (%i/%i) %i for enemy %i ", clientid,Battle->atktype,AOE_TARGET,skill->id,Enemy->clientid);
                    AoeSkill( skill, Enemy );
                }

                //AoeSkill( skill, Enemy );
            }
        }
        break;
        case BUFF_SELF:
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                //osprose
                //ClearBattle( Battle );
                return;
            }
            BuffSkill( this, skill );
        }
        break;
        case MONSTER_BUFF_SELF:    //LMA: monster selfs buffs.
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }
            BuffSkill( this, skill );
        }
        break;
       case BUFF_AOE:
        {
            CSkills* skill = GServer->GetSkillByID( Battle->skillid );
            if(skill==NULL)
            {
                ClearBattle( Battle );
                return;
            }

             //osprose
             AoeBuff( skill );
             //osprose end
        }
        break;
        default:
        {
            return;
        }
        break;
    }

}

// do normal attack
void CCharacter::NormalAttack( CCharacter* Enemy )
{
    bool is_already_dead=Enemy->IsDead();

    Position->destiny = Position->current;

    reduceItemsLifeSpan( false );
    Enemy->OnBeAttacked( this );

    //Stat modifier based on level. int statcap will give 75% chance to apply modifier at the level set
    int statcap = 700;
    float statmodifier = ((statcap/75)/(3.79+1.0095 - (Stats->Level*0.017272))); //divide stat by this value to make it have a max of 75% chance at level 220 which is also level dependant

    long int hitpower = 0;
    int block = 0;
    bool critical = false;
    bool dodge = false;

    //Dodge - If we successfully dodge damage = 0 and should skip rest of calculations to free up CPU time
    float hitchance;
    if(!IsMonster( )) hitchance = Stats->Accuracy / statmodifier; else hitchance = (Stats->Accuracy/10) / statmodifier; //can have a hitchance of 75% at level 220 when same level
    float dodgechance = Enemy->Stats->Dodge / statmodifier; //enemys dodge chance up to 75% at level 220 when same level
    if(hitchance > 75) hitchance = 75;

    int serverrandom = GServer->RandNumber( 0, 100 );

    if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
    {
        if(serverrandom < (19-hitchance)) //19 was chosen as at level 1 with default accuracy its 5% chance to dodge
            dodge=true; // dodged
    }
    else
    {
        if(dodgechance > 75) dodgechance = 75;

        if(serverrandom < (dodgechance - hitchance)) //enemys dodge chance - your hit chance
            dodge=true; // dodged
    }
    //if(IsMonster( ))Log(MSG_INFO,"Monster - %f enemy dodge, %f my hit, %f difference, %i random", dodgechance, hitchance, (dodgechance - hitchance), serverrandom);
    //if(IsPlayer( ))Log(MSG_INFO,"Player - %f enemy dodge, %f my hit, %f difference, %i random", dodgechance, hitchance, (dodgechance - hitchance), serverrandom);
    if(dodge==false)
    {
        //Block - Enemy has a shield. Get potential block value. Shields come with a flat % chance to block regardless of level
        if(GServer->RandNumber(1, 100) < Enemy->Stats->Block_Rate){
            if(Stats->MagicAttack != 1) //can only block physical attacks
                block = Enemy->Stats->Blocked_dmg;
        }

        //The difference in levels used in some of the calculations
        float leveldifference = Enemy->Stats->Level - Stats->Level;
        if(leveldifference > 15) leveldifference = 15;

        //Do we use magic defense or physical defense
        float defense = 0;
        if(Stats->MagicAttack == 1) defense = Enemy->Stats->Magic_Defense; else defense = Enemy->Stats->Defense;

        //Damage reduction due to armour
        float reduction = 0;
        if(defense < 0) reduction = 0; //make sure opponent doesnt have negative armour
        else reduction = (defense*3.5)/(85*(Enemy->Stats->Level/2.93)+(defense*3.5)+5500);

        //Get ratio of potential damage divide by 15. This is to ensure that if the enemy is 15 levels higher their damage reduction will be 100%
        float dmgmultiplierperlevel = (1-reduction) / 15;

        //Work out the new reduction with level taken into effect
        reduction = reduction + leveldifference * dmgmultiplierperlevel;
        if(reduction < 0) reduction = 0;
        if(reduction > 1) reduction = 1;

        //Players maximum armour cap is 75%, while monsters dont have a armour cap
        if(reduction > 0.75 && Enemy->IsPlayer( )) reduction = 0.75;

        //Percentage damage done after reduction
        float dmgmultiplier;
        dmgmultiplier = 1 - reduction;

        //Attack dmg after defense taken into consideration
        long int attack = (long int) (Stats->Attack_Power * dmgmultiplier);

        //We want a minimum attack amount which we can set below
        if(attack < 5) attack = 5;

        float d_attack = attack / 100;
        float mod = GServer->RandNumber( 0, 10 ) * d_attack;

        hitpower = (long int)floor(attack);
        if(IsPlayer( )) //temp fix to find balance btw monster and player
        {
            hitpower = (long int)floor(attack * (GServer->Config.PlayerDmg/1000.00));
        }
        else
        if(Enemy->IsMonster( )) //temp fix to find balance btw monster and player
        {
            hitpower = (long int)floor(attack * (GServer->Config.MonsterDmg/1000.00));
        }
        if(IsPlayer())//Add Dmg
        {
            if( Stats->ExtraDamage_add !=0 )
            {
                long int hitsave=hitpower;
                hitpower += ((hitpower * Stats->ExtraDamage_add) / 100);
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"ExtraDmg Normal atk: before %i, after %i (ED: %i)",hitsave,hitpower,Stats->ExtraDamage_add);
            }
        }

        int serverrandom = GServer->RandNumber( 0, 100 );
        long int temp = hitpower; //used for logging
        if(hitpower<=0)
        {
            hitpower = 0;
        }
        else
        {
            if(IsPlayer() && serverrandom < (Stats->Critical/statmodifier)) //Check players crit rating
            {
                if(Stats->MagicAttack != 1)
                {
                    hitpower = (long int)floor(hitpower*2);
                } else
                {
                    hitpower = (long int)floor(hitpower*1.5);
                }
                critical = true;
            }
            if(IsMonster() && serverrandom < 5) //monsters have a flat rate of 5% crit through all levels
            {
                if(Stats->MagicAttack != 1)
                {
                    hitpower = (long int)floor(hitpower*2);
                } else
                {
                    hitpower = (long int)floor(hitpower*1.5);
                }
                critical = true;
            }
        }
        //if(critical && IsMonster()) Log(MSG_INFO,"Monster crits me - original: %i, new: %i, random: %i", (int)floor(temp), (int)floor(hitpower), serverrandom);
        //if(critical && IsPlayer()) Log(MSG_INFO,"I crit Monster - original: %i, new: %i, random: %i, crit chance: %f", (int)floor(temp), (int)floor(hitpower), serverrandom, (Stats->Critical/statmodifier));
    }

    //if we blocked subtract it from final dmg value
    hitpower = hitpower - block;

    //apply the damage to the monster
    if(!Enemy->IsSummon( ) && Enemy->IsMonster( ))
    {
        Enemy->AddDamage( this, (long long) hitpower );
        Enemy->damagecounter += (long long) hitpower;// is for AI
    }


	//Damage reflect
    if(Enemy->Status->ShieldDamage_up != 0xff && ((Stats->HP) > ((long long) (hitpower*(Enemy->shield_reflect) / 100))))
    {
        Stats->HP -= (long long) (hitpower*(Enemy->shield_reflect) / 100);
        if(GServer->ServerDebug)
            Log(MSG_INFO,"%i percent Damage Reflected", Enemy->shield_reflect);
		if(Stats->HP < 0)
		{
			Stats->HP = 0;
		}

        //Log(MSG_HACK,"Value = %i",Enemy->shield_reflect);
    }

    Enemy->Stats->HP -=  (long long) hitpower;

    if(GServer->ServerDebug)
    {
        if (Enemy->IsMonster())
        {
            Log(MSG_INFO,"Normal Attack, monster HP %I64i, hitpower %li",Enemy->Stats->HP,hitpower);
        }
        else
        {
            Log(MSG_INFO,"Normal Attack, Player HP %I64i, hitpower %li",Enemy->Stats->HP,hitpower);
        }
    }
    // actually the target was hit, if it was sleeping, set duration of
    // sleep to 0. map process will remove sleep then at next player-update
    if (Enemy->Status->Sleep != 0xff) {
        Enemy->MagicStatus[Enemy->Status->Sleep].Duration = 0;
    }

    //if (IsPlayer())
    //printf("Target suffered %i physical damage, %i HP still remain \n", hitpower, Enemy->Stats->HP);
    //else printf("Mob did %i physical damage, %i HP still remain \n", hitpower, Enemy->Stats->HP);
    Enemy->reduceItemsLifeSpan(true);
    if(Enemy->IsMonster()&&Enemy->IsDead())
    {
        BEGINPACKET( pak, 0x79f );
        ADDWORD    ( pak, Enemy->clientid );
        ADDDWORD   ( pak, 1);
        GServer->SendToVisible( &pak, Enemy );
        if(GServer->ServerDebug)
            Log(MSG_INFO,"death atk for %i, amount: %i",Enemy->clientid,hitpower);
    }

    BEGINPACKET( pak, 0x799 );
    ADDWORD    ( pak, clientid );
    //ADDWORD    ( pak, Battle->atktarget );
    ADDWORD    ( pak, Enemy->clientid );

    if(Enemy->IsDead())
    {
        CDrop* thisdrop = NULL;
        ADDDWORD   ( pak, hitpower );
        ADDDWORD   ( pak, 16 );
        if(!Enemy->IsSummon( ) && !Enemy->IsPlayer( ))
        {
            thisdrop = Enemy->GetDrop( );
            if(thisdrop != NULL)
            {
                //ADDFLOAT   ( pak, thisdrop->pos.x*100 );
                //ADDFLOAT   ( pak, thisdrop->pos.y*100 );
                //if(thisdrop->type == 1)
                //{
                //    ADDWORD( pak, 0xccdf );
                //    ADDDWORD( pak, thisdrop->amount );
                //}
                //else
                //{
                //    ADDWORD   ( pak, GServer->BuildItemHead( thisdrop->item ) );
                //    ADDDWORD   ( pak, GServer->BuildItemData( thisdrop->item ) );
                //}
                //ADDWORD    ( pak, thisdrop->clientid );
                //ADDWORD    ( pak, thisdrop->owner );
                CMap* map = GServer->MapList.Index[thisdrop->posMap];
                map->AddDrop( thisdrop );
            }
        }
        GServer->SendToVisible( &pak, Enemy ); //, thisdrop );
        OnEnemyDie( Enemy );
        if(Enemy->IsPlayer())
        {
            CPlayer* plkilled=(CPlayer*) Enemy;
            if(plkilled!=NULL)
            {
                BEGINPACKET( pak, 0x829 );
                ADDDWORD   ( pak, 4 );
                ADDBYTE    ( pak, 0 );
                ADDWORD    ( pak, Enemy->Stats->HP );
                ADDWORD    ( pak, Enemy->Stats->MP );
                plkilled->client->SendPacket(&pak);

                BEGINPACKET( pak2, 0x7ec );
                ADDBYTE(pak2, 0xd0 );
                ADDBYTE(pak2, 0x8a );
                ADDWORD(pak2, 0xffff);
                ADDBYTE(pak2, 0x4b);
                plkilled->client->SendPacket( &pak2 );

				for(int i = 0; i < 30; i++)
				for(int i = 0; i < 30; i++)
				{
					plkilled->MagicStatus[i].Duration = 0;
					plkilled->MagicStatus[i].BuffTime = 0;
				}
				plkilled->RefreshBuff();
            }

        }
    }
    else
    {
        ADDDWORD   ( pak, hitpower );
        ADDDWORD   ( pak, (hitpower>0?(critical?12:0):0) );
        GServer->SendToVisible( &pak, Enemy );
    }
    ReduceABC( );
    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = Stats->Attack_Speed;
        if(IsPlayer()&&Status->Stance==DRIVING)
    {
        CPlayer* plkiller=(CPlayer*) this;

        if(plkiller->items[136].itemnum==0||plkiller->items[139].itemnum==0)
        {
            if(GServer->ServerDebug)
                Log(MSG_WARNING,"%s should be riding but doesn't have a motor %i or weapon %i (normal_attack)?",plkiller->CharInfo->charname,plkiller->items[136].itemnum,plkiller->items[139].itemnum);
            return;
        }

        //We take the fuel amount.
        //Log(MSG_INFO,"lifespan before %i, sp_value %i",plkiller->items[136].lifespan,plkiller->items[136].sp_value);
        plkiller->items[136].sp_value-=(int)plkiller->attack_fuel;
        if(plkiller->items[136].sp_value<0)
        {
            plkiller->items[136].sp_value=0;
        }

        plkiller->items[136].lifespan=(int)(plkiller->items[136].sp_value/10);

        if(plkiller->items[136].lifespan<0)
        {
            plkiller->items[136].sp_value=0;
        }

        //Log(MSG_INFO,"lifespan after %i, sp_value %i, attack fuel %.2f",plkiller->items[136].lifespan,plkiller->items[136].sp_value,plkiller->attack_fuel);

        BEGINPACKET( pak,0x7ce );
        ADDWORD    ( pak, 0x88 ); //Slot
        ADDWORD    ( pak, plkiller->items[136].sp_value );
        plkiller->client->SendPacket( &pak );

        //We stop attack if needed
        if(plkiller->items[136].lifespan==0)
        {
            BEGINPACKET( pak, 0x796 );
            ADDWORD    ( pak, plkiller->clientid );
            ADDFLOAT   ( pak, plkiller->Position->current.x*100 );
            ADDFLOAT   ( pak, plkiller->Position->current.y*100 );
            ADDWORD    ( pak, 0x0000 );
            GServer->SendToVisible( &pak, plkiller );

            //clear battle.
            ClearBattle(Battle);
            //Log(MSG_INFO,"No more fuel to attack");
        }
        Battle->lastatktype = NOTHING;
    }
}

// do skill attack
bool CCharacter::SkillAttack( CCharacter* Enemy, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;
    UseAtkSkill( Enemy, skill );
	if(skill->costtype[0] == 17)
        Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    //Some skills uses zulie
    if(skill->costtype[0] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[0];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );
    }
    if(skill->costtype[1] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[1];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );

    }else if(skill->costtype[1] == 17)
    {
        Stats->MP -= (skill->costamount[1] - (skill->mp * Stats->MPReduction / 100));
    }
    if(Stats->MP<0) Stats->MP=0;
    if(!Battle->contatk)
    {
        //osprose
        //ClearBattle( Battle );
        if(GServer->ServerDebug)
            Log(MSG_INFO,"after skill, nothing special, not in contact / range?...");

        //he was already fighting the monster in normal_attack mode and did a skill, now he has to resume normal_attack.
        if(Battle->skilltarget!=0&&(Battle->atktarget!=Battle->skilltarget))
        {
            //Stop...
            if(GServer->ServerDebug)
                Log(MSG_INFO,"after skill, player is doing nothing (first attack).");
            ClearBattle(Battle);
        }

    }

    GServer->DoSkillScript( this, skill );       //So far only used for summons
    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    return true;
}

// do buff skill
bool CCharacter::BuffSkill( CCharacter* Target, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        //Log(MSG_INFO,"7bb battle casttime==0");
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
        {
            //Log(MSG_INFO,"etime<SKILL_DELAY: %i<%i",etime,SKILL_DELAY);
            return true;
        }

    }

    //Log(MSG_INFO,"new stat MP %i",Stats->MP);
    //Log(MSG_INFO,"%i Really doing skill %i to %i",clientid,skill->id,Target->clientid);

    if(GServer->ServerDebug)
        Log(MSG_INFO,"Doing a simple buff BuffSkill");
    Battle->castTime = 0;
    UseBuffSkill( Target, skill );
	if(skill->costtype[0] == 17)
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    //Some skills uses zulie
    if(skill->costtype[0] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[0];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );
    }
    if(skill->costtype[1] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[1];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );

    }else if(skill->costtype[1] == 17)
    {
        Stats->MP -= (skill->costamount[1] - (skill->mp * Stats->MPReduction / 100));
    }
    if(Stats->MP<0) Stats->MP=0;

    /*
    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    */

    //osprose
    GServer->DoSkillScript( this, skill );
    if(IsMonster()) //Monsters need to be reset to normal attack and clear skill attacks.
    {
        Battle->bufftarget = 0;
        Battle->skilltarget = 0;
        Battle->skillid = 0;
        Battle->atktype = NORMAL_ATTACK;
    }
    //osprose end

    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    return true;
}

// do Debuff skill [netwolf]
bool CCharacter::DebuffSkill( CCharacter* Enemy, CSkills* skill )
{
    Position->destiny = Position->current;
    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;
    UseDebuffSkill( Enemy, skill );
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;
    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    return true;
}

//LMA: A summon does a buff skill
//2do: check if master is debuffed.
bool CCharacter::SummonBuffSkill( CCharacter* Target, CSkills* skill )
{
    Position->destiny = Position->current;

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        //Log(MSG_INFO,"0x7bb");
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }

    //LMA: For now, it seems the summon buff only one time :(
    //Log(MSG_INFO,"Real buff skill");
    Battle->castTime = 0;
    UseBuffSkill( Target, skill );
    ClearBattle( Battle );
    GServer->DoSkillScript( this, skill );
    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    return true;
}

// do AoE skill
bool CCharacter::AoeSkill( CSkills* skill, CCharacter* Enemy )
{

    //LMA: not here since AOE can have NULL Enemy, will be catched later by the call to the skill.
    //bool is_already_dead=Enemy->IsDead();
    if(GServer->ServerDebug)
        Log(MSG_INFO,"In AOE Skill");
    Position->destiny = Position->current;
    //Log(MSG_INFO,"Position in AOE: %.2f,%.2f",Position->current.x,Position->current.y);

    //LMA: handling case of AOE_SKILLS and AOE_TARGET (the target point is not the same).
    fPoint goodtarget;
    goodtarget=Position->current;
    if (Battle->atktype==AOE_TARGET)
    {
       goodtarget=Position->aoedestiny;
    }

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        //LMA: No delay for AOE_TARGET skill (zone)
        if (Battle->atktype!=AOE_TARGET)
        {
            clock_t etime = clock() - Battle->castTime;
            if(etime<SKILL_DELAY)
                return true;
        }

    }

    Battle->castTime = 0;
    CMap* map = GServer->MapList.Index[Position->Map];

    //osprose
    //LMA: pvp ?
    UINT save_atktype=Battle->atktype;

    if(IsPlayer() || IsSummon())
    {
        //monsters.
        for(UINT i=0;i<map->MonsterList.size();i++)
        {
            CMonster* monster = map->MonsterList.at(i);
            if(monster->clientid == clientid) continue;
            if(monster->IsSummon( ) && (map->allowpvp == 0 || monster->owner == clientid)) continue;
            if(GServer->IsMonInCircle( goodtarget,monster->Position->current,(float)skill->aoeradius+1))
            {
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"AOE Attack (1) player attacks monster %i (clientID %u) radius %.2f",monster->montype,monster->clientid,(float)skill->aoeradius+1);

                //LMA: we have to since AOE doesn't have a specific target and atkskil resets some values.
                Battle->skilltarget=monster->clientid;
                Battle->skillid=skill->id;
                Battle->atktype = save_atktype;
                UseAtkSkill( (CCharacter*) monster, skill, false, true );

                //LMA: TEST is there a "buff/debuff" skill with it too?
                /*
                if (skill->status[0]!=0&&skill->buff[0]!=0&&monster->Stats->HP>0)
                {
                    UseBuffSkill( (CCharacter*)monster, skill );
                    Log(MSG_INFO,"AOE Attack (1) player buffs monster %i",monster->montype);
                }
                */

                //LMA: AIP time.
                monster->DoAi(monster->thisnpc->AI, 3);
                //END OF TEST.

            }

        }

        //Pvp, group Vs group, here all.
        if(map->allowpvp!=0&&IsPlayer())
        {
            CPlayer* plattacker=(CPlayer*) this;
            for (UINT i=0;i<map->PlayerList.size();i++)
            {
                CPlayer* thisplayer=map->PlayerList.at(i);
                if(thisplayer==NULL)
                {
                    continue;
                }

                //not attacking allies.
                if(thisplayer->pvp_id==plattacker->pvp_id)
                {
                    continue;
                }

                if(GServer->IsMonInCircle( goodtarget,thisplayer->Position->current,(float)skill->aoeradius+1))
                {
                    //LMA: we have to since AOE doesn't have a specific target and atkskil resets some values.
                    Battle->skilltarget=thisplayer->clientid;
                    Battle->skillid=skill->id;
                    Battle->atktype = save_atktype;
                    UseAtkSkill( (CCharacter*) thisplayer, skill, false, true );
                    if(GServer->ServerDebug)
                        Log(MSG_WARNING,"AOE Skill pvp player %s",thisplayer->CharInfo->charname);
                }

            }

        }

    }

    if(IsMonster() && !IsSummon())
    {
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            if(player->clientid == clientid) continue;
            if(GServer->IsMonInCircle( goodtarget,player->Position->current,(float)skill->aoeradius+1))
            {
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"AOE Attack (2) monster attacks player %s radius %.2f",player->CharInfo->charname,(float)skill->aoeradius+1);
                UseAtkSkill( (CCharacter*) player, skill, false, true );
            }

        }
    }
    //osprose end

    if(Enemy!=NULL)
    {
        if(!Enemy->IsDead( ))
        {
            Battle->atktarget = Battle->target;
            Battle->atktype = NORMAL_ATTACK;
            Battle->skilltarget = 0;
            Battle->skillid = 0;
        }
        else
        {
            ClearBattle( Battle );
        }

    }

    if(skill->costtype[0] == 17)
    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    //Some skills uses zulie
    if(skill->costtype[0] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[0];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );
    }
    if(skill->costtype[1] == 40)
    {
        CPlayer* thisclient = GServer->GetClientByID(clientid,Position->Map);
        thisclient->CharInfo->Zulies -= skill->costamount[1];
        if(thisclient->CharInfo->Zulies < 0) thisclient->CharInfo->Zulies = 0;
        BEGINPACKET( pak, 0x71d );
        ADDQWORD( pak, thisclient->CharInfo->Zulies );
        thisclient->client->SendPacket( &pak );

    }else if(skill->costtype[1] == 17)
    {
        Stats->MP -= (skill->costamount[1] - (skill->mp * Stats->MPReduction / 100));
    }
    if(Stats->MP<0) Stats->MP=0;
    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    return true;
}

bool CCharacter::AoeBuff( CSkills* skill )
{
    Position->destiny = Position->current;

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }

    Battle->castTime = 0;
    CMap* map = GServer->MapList.Index[Position->Map];

    //checking if buffing party and no party so himself :)
//    if(skill->target==1 && GetParty( )==NULL)
//    {
//        Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
//        if(Stats->MP<0) Stats->MP=0;
//
//        if(GServer->ServerDebug)
//            Log(MSG_INFO,"AOEBuffs, buffing only myself");
//        UseBuffSkill( this, skill );
//
//        //LMA: do we have to resume a Normal Attack?
//        //ClearBattle( Battle );
//        //Battle->lastAtkTime = clock( );
//
//        return true;
//    }

    //LMA: Summon don't go there...
    //if(IsMonster())
    if(IsMonster()&&!IsSummon())
    {
        if(GServer->ServerDebug)
            Log(MSG_INFO,"Monster in AOE Buff");
        for(UINT i=0;i<map->MonsterList.size();i++)
        {
            CMonster* monster = map->MonsterList.at(i);
            switch(skill->target)
            {
                case tPartyMember: // party
                break;
                case 2: //tClanMember
                break;
                case 3: //tAlly
                case 7: //tAllCharacters
                case 8: //tAllMembers. all characters
                case 11: //Bonfire skill now uses a target value of 11 for some reason. PY
                {
                     //Log(MSG_INFO,"Applying AOE buff as long as I can find a close enough monster");
                     if(GServer->IsMonInCircle( Position->current,monster->Position->current,(float)skill->aoeradius + 1))
                     {
                         UseBuffSkill( (CCharacter*)monster, skill );
                     }
                }
                break;
                case 5: //hostile.
                break;
            }
        }

    }
    else
    {
        //players / summons
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            switch(skill->target)
            {
                case 1: // party
                {
                    if(player->Party->party==GetParty( ))
                    {
                        if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius+1))
                        {
                            UseBuffSkill( (CCharacter*)player, skill );
                        }

                    }
                }
                break;
                case 2: //clan member
                {
                    if (player->Clan == GetClan( ))
                    {
                        //Log(MSG_INFO,"Applying AOE buff as long as I can find a close enough clan member");
                        if(GServer->IsMonInCircle( Position->current, player->Position->current, (float)skill->aoeradius + 1 ) )
                        {
                            UseBuffSkill( (CCharacter*)player, skill );
                        }

                    }
                }
                break;
                case 3:  //ally
                case 7: //everyone
                case 8: //all characters
                {
                    if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius + 1))
                    {
                        UseBuffSkill( (CCharacter*)player, skill );
                    }

                }
                break;
                case 5: //hostile
                break;
            }
        }

    }


    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
    if(Stats->MP<0) Stats->MP=0;

    //ClearBattle( Battle );
    //osprose
    Battle->bufftarget = 0;
    Battle->skilltarget = 0;
    Battle->skillid = 0;

    //LMA: no because in weird cases (party+first target buff+aoe buff)
    //a party buffer could attack a buffed one.
    //Battle->atktype = NORMAL_ATTACK;
    Battle->atktype = 0;
    //ClearBattle( Battle );
    //osprose end

    Battle->lastAtkTime = clock( );
    Battle->lastcastspeed = skill->castingspeed;
    //LMA: do we have to resume a Normal Attack?


    return true;
}

// Aoe Debuff [netwolf]
bool CCharacter::AoeDebuff( CSkills* skill, CCharacter* Enemy )
{
    Position->destiny = Position->current;

    if(Battle->castTime==0)
    {
        BEGINPACKET( pak, 0x7bb );
        ADDWORD    ( pak, clientid );
        GServer->SendToVisible( &pak, (CCharacter*)this );
        Battle->castTime = clock();
        return true;
    }
    else
    {
        clock_t etime = clock() - Battle->castTime;
        if(etime<SKILL_DELAY)
            return true;
    }
    Battle->castTime = 0;

    CMap* map = GServer->MapList.Index[Position->Map];
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* monster = map->MonsterList.at(i);
        if(monster->clientid==clientid) continue;
        if(IsSummon( ) || IsPlayer( ))
        {
            if(monster->IsSummon( ) && (map->allowpvp==0 || monster->owner==clientid)) continue;
        }
        else
        {
            if(!monster->IsSummon( )) continue;
        }
        if(GServer->IsMonInCircle( Position->current,monster->Position->current,(float)skill->aoeradius+1))
        {
            if(GServer->ServerDebug)
                Log(MSG_INFO,"AOE Debuff (1) monster %i",monster->montype);
            UseDebuffSkill( (CCharacter*) monster, skill );
        }

    }

    if(map->allowpvp!=0 || (IsMonster( ) && !IsSummon( )))
    {
        for(UINT i=0;i<map->PlayerList.size();i++)
        {
            CPlayer* player = map->PlayerList.at(i);
            if(player->clientid==clientid) continue;
            if(GServer->IsMonInCircle( Position->current,player->Position->current,(float)skill->aoeradius+1))
            {
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"AOE Debuff (2) player %s",player->CharInfo->charname);
                //UseDebuffSkillTest( (CCharacter*) player, skill );
                UseDebuffSkill( (CCharacter*) player, skill );
            }

        }
    }

    Stats->MP -= (skill->mp - (skill->mp * Stats->MPReduction / 100));
     if(Stats->MP<0) Stats->MP=0;
    //ClearBattle( Battle );
     Battle->lastAtkTime = clock( );
     Battle->lastcastspeed = skill->castingspeed;
    //LMA: do we have to resume a Normal Attack?


     return true;
 }
// use skill attack
void CCharacter::UseAtkSkill( CCharacter* Enemy, CSkills* skill, bool deBuff, bool aoe )
{
    //LMA: Sometimes it's fired several times, no need to kill several times ;)
    bool is_already_dead=Enemy->IsDead();

    //We Check if The Skill need a Bow, Gun, Launcher or Crossbow and reduce the number of Arrow, Bullet or Canon the player have by 1 (Client is Buged)
    bool need_arrows=false;
    if(skill->weapon[0]==BOW || skill->weapon[0] == GUN || skill->weapon[0] == LAUNCHER || skill->weapon[0] == CROSSBOW)
    {
        need_arrows=true;
    }
    if(skill->weapon[1]==BOW || skill->weapon[1] == GUN || skill->weapon[1] == LAUNCHER || skill->weapon[1] == CROSSBOW)
    {
        need_arrows=true;
    }
    if (need_arrows)
    {
        ReduceABC(1,false); //We Reduce by 1 because Client is Buged, and we set the flag do_packet to false
    }

    reduceItemsLifeSpan( false );
    Enemy->reduceItemsLifeSpan(true);

    //Stat modifier based on level. int statcap will give 75% chance to apply modifier at the level set
    int statcap = 700;
    float statmodifier = ((statcap/75)/(3.79+1.0095 - (Stats->Level*0.017272))); //divide stat by this value to make it have a max of 75% chance at level 220 which is also level dependant

    long int hitpower = 0;
    int block = 0;
    bool critical = false;
    bool dodge = false;

    //Dodge - If we successfully dodge damage = 0 and should skip rest of calculations to free up CPU time
    float hitchance;
    if(!IsMonster( )) hitchance = Stats->Accuracy / statmodifier; else hitchance = (Stats->Accuracy/10) / statmodifier; //can have a hitchance of 75% at level 220 when same level
    float dodgechance = Enemy->Stats->Dodge / statmodifier; //enemys dodge chance up to 75% at level 220 when same level
    if(hitchance > 75) hitchance = 75;

    int serverrandom = GServer->RandNumber( 0, 100 );

    if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
    {
        if(serverrandom < (19-hitchance)) //19 was chosen as at level 1 with default accuracy its 5% chance to dodge
            dodge=true; // dodged
    }
    else
    {
        if(dodgechance > 75) dodgechance = 75;

        if(serverrandom < (dodgechance - hitchance)) //enemys dodge chance - your hit chance
            dodge=true; // dodged
    }
    if(dodge==false || aoe==true)
    {
        //Block - Enemy has a shield. Get potential block value. Shields come with a flat % chance to block regardless of level
        if(GServer->RandNumber(1, 100) < Enemy->Stats->Block_Rate){
            if(Stats->MagicAttack != 1) //can only block physical attacks
                block = Enemy->Stats->Blocked_dmg;
        }
        //if we blocked, and its aoe ignore it
        if(aoe) block = 0;

        //The difference in levels used in some of the calculations
        float leveldifference = Enemy->Stats->Level - Stats->Level;
        if(leveldifference > 15) leveldifference = 15;

        //Do we use magic defense or physical defense
        float defense = 0;
        if(Stats->MagicAttack == 1) defense = Enemy->Stats->Magic_Defense; else defense = Enemy->Stats->Defense;

        //Damage reduction due to armour
        float reduction = 0;
        if(defense < 0) reduction = 0; //make sure opponent doesnt have negative armour
        else reduction = (defense*3.5)/(85*(Enemy->Stats->Level/2.93)+(defense*3.5)+5500);

        //Get ratio of potential damage divide by 15. This is to ensure that if the enemy is 15 levels higher their damage reduction will be 100%
        float dmgmultiplierperlevel = (1-reduction) / 15;

        //Work out the new reduction with level taken into effect
        reduction = reduction + leveldifference * dmgmultiplierperlevel;
        if(reduction < 0) reduction = 0;
        if(reduction > 1) reduction = 1;

        //Players maximum armour cap is 75%, while monsters dont have a armour cap
        if(reduction > 0.75 && Enemy->IsPlayer( )) reduction = 0.75;

        //Percentage damage done after reduction
        float dmgmultiplier;
        dmgmultiplier = 1 - reduction;

        //Attack dmg after defense taken into consideration
        long int attack = (long int) ((Stats->Attack_Power + skill->atkpower) * dmgmultiplier)-block;

        //We want a minimum attack amount which we can set below
        if(attack < 5) attack = 5;

        float d_attack = attack / 100;
        float mod = GServer->RandNumber( 0, 10 ) * d_attack;

        hitpower = (long int)floor(attack);
        if(IsPlayer( )) //temp fix to find balance btw monster and player
        {
            hitpower = (long int)floor(attack * (GServer->Config.PlayerDmg/1000.00));
        }
        else
        if(Enemy->IsMonster( )) //temp fix to find balance btw monster and player
        {
            hitpower = (long int)floor(attack * (GServer->Config.MonsterDmg/1000.00));
        }
        if(IsPlayer())//Add Dmg
        {
            if( Stats->ExtraDamage_add !=0 )
            {
                long int hitsave=hitpower;
                hitpower += ((hitpower * Stats->ExtraDamage_add) / 100);
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"ExtraDmg Normal atk: before %i, after %i (ED: %i)",hitsave,hitpower,Stats->ExtraDamage_add);
            }
        }

        int serverrandom = GServer->RandNumber( 0, 100 );
        long int temp = hitpower; //used for logging
        if(hitpower<=0)
        {
            hitpower = 0;
        }
        else
        {
            if(IsPlayer() && serverrandom < (Stats->Critical/statmodifier)) //Check players crit rating
            {
                if(Stats->MagicAttack != 1)
                {
                    hitpower = (long int)floor(hitpower*2);
                } else
                {
                    hitpower = (long int)floor(hitpower*1.5);
                }
                critical = true;
            }
            if(IsMonster() && serverrandom < 5) //monsters have a flat rate of 5% crit through all levels
            {
                if(Stats->MagicAttack != 1)
                {
                    hitpower = (long int)floor(hitpower*2);
                } else
                {
                    hitpower = (long int)floor(hitpower*1.5);
                }
                critical = true;
            }
        }
    }

    //Skill power calculations LMA/Tomiz : New Way
    long int skillpower = hitpower;
    float skill_hitvalue = hitchance;

    serverrandom = GServer->RandNumber( 0, 100 );

    switch(skill->formula)//Magical Or Weapon Type Skill?
    {
		case 0://Skill Mental Storm
        {
            skillpower = 0;
        }
		break;
        case 1://Weapon type dmg
        {
            skillpower += GetSen();
            if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
            {
                if(serverrandom < (19-hitchance))
                    skillpower /= 2;
            }
            else
            {
                if(dodgechance > 75) dodgechance = 75;

                if(serverrandom < (dodgechance - hitchance) && !aoe) //enemys dodge chance - your hit chance
                    skillpower /= 2;
            }
        }
        break;
        case 2://Magical type dmg
        {
            skillpower += GetInt();
            if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
            {
                if(serverrandom < (19-hitchance))
                    skillpower /= 2;
            }
            else
            {
                if(dodgechance > 75) dodgechance = 75;

                if(serverrandom < (dodgechance - hitchance) && !aoe) //enemys dodge chance - your hit chance
                    skillpower /= 2;
            }
        }
        break;
        case 3://Weapon type dmg
        {
            skillpower += GetSen();
            if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
            {
                if(serverrandom < (19-hitchance))
                    skillpower = 0;
            }
            else
            {
                if(dodgechance > 75) dodgechance = 75;

                if(serverrandom < (dodgechance - hitchance) && !aoe) //enemys dodge chance - your hit chance
                    skillpower = 0;
            }
        }
        break;
        case 4://Magical type dmg
        {
            skillpower += GetInt();
            if(IsMonster( ) && !IsSummon()) //monsters have a static 19% dodge level when at the same level
            {
                if(serverrandom < (19-hitchance))
                    skillpower = 0;
            }
        else
        {
        if(dodgechance > 75) dodgechance = 75;

        if(serverrandom < (dodgechance - hitchance) && !aoe) //enemys dodge chance - your hit chance
            skillpower = 0;
        }
    }
    break;
        case 6://Dual Scratch
        {
            skillpower = skillpower * ((250-Stats->Level)*0.0045) + skillpower;
        }
        break;
        default:
        {
            skillpower = skillpower * 2.5;
        }
        break;
    }
    //END Skill power calculations LMA/Tomiz : New Way
   long int attack = (long int) (skillpower);

    if(GServer->ServerDebug)
        Log( MSG_INFO, "Attack before random mod = %f",attack );
    if(attack < 0) attack = 0;
    float d_attack = attack / 100;
    float mod = GServer->RandNumber( 0, 10 ) * d_attack;
    attack += mod;
    if(GServer->ServerDebug)
        Log( MSG_INFO, "Attack after random mod = %f",attack );

    skillpower = (int)attack;
    if(GServer->ServerDebug)
        Log( MSG_INFO, "skillpower = %i",skillpower );
    bool bflag = false;
    Enemy->OnBeAttacked( this );
    if(skillpower<=0) skillpower = 0;
    if(IsPlayer())//Add Dmg
    {
        if( Stats->ExtraDamage_add != 0)
        {
            //LMA: ED, Devilking / Arnold
            long int hitsave=skillpower;
            skillpower += ((skillpower * Stats->ExtraDamage_add) / 100);
            if(GServer->ServerDebug)
                Log(MSG_INFO,"ExtraDmg Skill atk: before %i, after %i (ED: %i)",hitsave,skillpower,Stats->ExtraDamage_add);
        }
    }

    if(!Enemy->IsSummon( ) && Enemy->IsMonster( ))
    {
        Enemy->AddDamage( this, (long long) skillpower );
        Enemy->damagecounter+= (long long) skillpower;// is for AI
    }

	//Damage reflect
    if(Enemy->Status->ShieldDamage_up != 0xff && ((Stats->HP) > ((long long) (skillpower*(Enemy->shield_reflect) / 100))))
    {
        Stats->HP -= (long long) (skillpower*(Enemy->shield_reflect) / 100);
        if(GServer->ServerDebug)
            Log(MSG_INFO,"%i percent Damage Reflected", Enemy->shield_reflect);

		if(Stats->HP < 0)
		{
			Stats->HP = 0;
		}
    }

    Enemy->Stats->HP -=  (long long) skillpower;
    if(GServer->ServerDebug)
        Log(MSG_INFO,"Atk Skill damage %li, Enemy HP after %li",skillpower,Enemy->Stats->HP);

    // actually the target was hit, if it was sleeping, set duration of
    // sleep to 0. map process will remove sleep then at next player-update
    if (Enemy->Status->Sleep != 0xff) {
        Enemy->MagicStatus[Enemy->Status->Sleep].Duration = 0;
    }

    //LMA: forcing the HP amount value, only when it's supposed to be dead side.
    if(Enemy->IsMonster()&&Enemy->IsDead())
    {
        BEGINPACKET( pak, 0x79f );
        ADDWORD    ( pak, Enemy->clientid );
        ADDDWORD   ( pak, 1);
        GServer->SendToVisible( &pak, Enemy );
        if(GServer->ServerDebug)
            Log(MSG_INFO,"death skill atk for %i, amount: %i",Enemy->clientid,skillpower);
    }

    unsigned short command = (skill->skilltype == 6 || skill->skilltype == 9) ? 0x799 : 0x7b6;
    BEGINPACKET( pak, command );

    if(command == 0x799)
    {
        ADDWORD    ( pak, clientid );
        ADDWORD    ( pak, Enemy->clientid );
        //LMA: Skillpower elsewhere.
        //ADDDWORD   ( pak, skillpower );
    }
    else
    {
        ADDWORD    ( pak, Enemy->clientid );
        ADDWORD    ( pak, clientid );
        ADDDWORD   ( pak, 0x000007f8 );
        ADDBYTE    ( pak, 0x00 );
        //LMA: Skillpower elsewhere.
        //ADDDWORD   ( pak, skillpower );
    }

    //If Enemy is killed
    if(Enemy->IsDead())
    {
        //LMA: Skillpower elsewhere.
        //ADDDWORD   ( pak, Enemy->Stats->MaxHP);
        ADDDWORD   ( pak, skillpower);

        //LMA: UW handling, adding support for other quests.
        if (!is_already_dead&&((GServer->MapList.Index[Position->Map]->QSDkilling>0&&IsPlayer()&&Enemy->IsPlayer())||(GServer->MapList.Index[Position->Map]->QSDDeath&&Enemy->IsPlayer())))
        {
            if(GServer->ServerDebug)
                Log(MSG_INFO,"UWKILL begin skill atk");
            UWKill(Enemy);
        }

        //LMA: test for quest hack (stackable).
        #ifdef QHACK
        if(!is_already_dead&&Enemy->die_quest!=0&&Enemy->IsMonster()&&(IsPlayer()||IsSummon()))
        {
            QuestKill(Enemy->die_quest);
        }
        #endif
        //LMA END

        if(GServer->ServerDebug)
            Log(MSG_INFO,"Enemy is dead");
        CDrop* thisdrop = NULL;
        ADDDWORD   ( pak, 16 );

        if(!Enemy->IsSummon( ) && !Enemy->IsPlayer( ))
        {
            //LMA: looping the drops (double drop medal for example).
            int nb_drops = GServer->Config.ItemDropRate;
            if (IsPlayer())
            {
                CPlayer* plkiller=(CPlayer*) this;
                nb_drops += plkiller->bonusddrop + Stats->itemdroprate;
                if(GServer->ServerDebug)
                    Log(MSG_INFO,"Drop time, there should be %i drops",nb_drops);  // default = 1 with no medal
            }

            //No drop if already dead and drop done.
            if(Enemy->drop_dead)
            {
                if(GServer->ServerDebug)
                    Log(MSG_WARNING,"Trying to make a monster (CID %u, type %u) drop again but already did.",Enemy->clientid,Enemy->char_montype);
                nb_drops=0;
            }

            for (int k=0;k<nb_drops;k++)
            {
                thisdrop = Enemy->GetDrop( );
                if(thisdrop!=NULL)
                {
                    if(GServer->ServerDebug)
                        Log(MSG_INFO,"Dropping Nb %i",k);
                    CMap* map = GServer->MapList.Index[thisdrop->posMap];
                    map->AddDrop( thisdrop );
                }

            }

        }

        GServer->SendToVisible( &pak, Enemy );
        //LMA: end of test.

        //LMA: test
        //OnEnemyDie( Enemy );
        ClearBattle(Battle);
        if(!is_already_dead)
        {
            TakeExp(Enemy);
        }
        //end of test.

        //LMA: Special Packet to tell if the player is dead?
        if(Enemy->IsPlayer())
        {
            CPlayer* plkilled=(CPlayer*) Enemy;
            if(plkilled!=NULL)
            {
                BEGINPACKET( pak, 0x829 );
                ADDDWORD   ( pak, 4 );
                ADDBYTE    ( pak, 0 );
                ADDWORD    ( pak, Enemy->Stats->HP );
                ADDWORD    ( pak, Enemy->Stats->MP );
                plkilled->client->SendPacket(&pak);

				for(int i = 0; i < 30; i++)
				{
					plkilled->MagicStatus[i].Duration = 0;
					plkilled->MagicStatus[i].BuffTime = 0;
				}
				plkilled->RefreshBuff();
            }

        }
    }
    else
    {
        //LMA: Skillpower elsewhere.
        ADDDWORD   ( pak, skillpower );

        //If enemy is still alive
        if(GServer->ServerDebug)
            Log(MSG_INFO,"The enemy is still alive");
        //ADDDWORD   ( pak, 4 );
        ADDDWORD   ( pak, (skillpower>0?(critical?12:0):0) )
        GServer->SendToVisible( &pak, Enemy );
        bflag = GServer->AddBuffs( skill, Enemy, GetInt( ) ); // send to AddBuffs instead.
        //Send (de)buff information to the whole world
        if(skill->nbuffs>0 && bflag)
        {
            if(GServer->ServerDebug)
                Log(MSG_INFO,"The enemy cliendID %u is being buffed with %u",Battle->skilltarget,Battle->skillid);
            BEGINPACKET( pak, 0x7b5 );
            ADDWORD    ( pak, Battle->skilltarget );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, Battle->skillid );
            ADDWORD    ( pak, GetInt( ) );
            ADDBYTE    ( pak, skill->nbuffs );
            GServer->SendToVisible( &pak, Enemy );
        }
    }
    if (deBuff) return;
    //Send skill animation to the world
    RESETPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);

    //LMA: Is it really used?
    if(command != 0x799)
    {
        ADDWORD    ( pak, 1);
    }

    GServer->SendToVisible( &pak, this );

    return;
}

// use buff skill
void CCharacter::UseBuffSkill( CCharacter* Target, CSkills* skill )
{
    bool bflag = false;
    bflag = GServer->AddBuffs( skill, Target, GetInt( ) );
    if(GServer->ServerDebug)
        Log(MSG_INFO,"In UseBuffSkills, skill %i, nbuffs %i, bflag %i to %u",skill->id,skill->nbuffs,bflag,Target->clientid);
    if(skill->nbuffs>0 && bflag == true)
    {
        BEGINPACKET( pak, 0x7b5 );
        ADDWORD    ( pak, Target->clientid );
        ADDWORD    ( pak, clientid );
        ADDWORD    ( pak, Battle->skillid );
        ADDWORD    ( pak, GetInt( ) );
        ADDBYTE    ( pak, skill->nbuffs );
        GServer->SendToVisible( &pak, Target );
    }
    BEGINPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);
    ADDWORD    ( pak, 1);
	GServer->SendToVisible( &pak, (CCharacter*)this );

	//LMA: Patch for Revive stuff...
	if(skill->skilltype==20&&Target->IsPlayer())
	{
	    CPlayer* thisclient = GServer->GetClientByID(Target->clientid,Position->Map);
	    if (thisclient==NULL)
	    {
	        CPlayer* thisclient = GServer->GetClientByID(Target->clientid,Target->Position->Map);
	    }

	    if (thisclient==NULL)
	    {
	        if(GServer->ServerDebug)
                Log(MSG_WARNING,"Can't find clientID %i for revive...",Target->clientid);
	        return;
	    }

        //not exact but should be fair enough...
        if(GServer->ServerDebug)
            Log(MSG_INFO,"before Revive, HP %I64i, Xp %I64i, skill %i",thisclient->Stats->HP,thisclient->CharInfo->Exp,skill->atkpower);
        unsigned long long new_exp=(unsigned long long) (thisclient->CharInfo->Exp*3*skill->atkpower/(100*100));
		CMap* map = GServer->MapList.Index[Position->Map];
        if(map->allowpvp!= 1)
        {
            thisclient->CharInfo->Exp+=new_exp;
        }
        thisclient->Stats->HP=thisclient->Stats->MaxHP*30/100;
	    if(GServer->ServerDebug)
            Log(MSG_INFO,"Revive, new HP %I64i, %I64i, Xp added %I64i, new %I64i",thisclient->Stats->HP,Target->Stats->HP,new_exp,thisclient->CharInfo->Exp);
        BEGINPACKET( pak, 0x79b );
        ADDDWORD   ( pak, thisclient->CharInfo->Exp );
        ADDWORD    ( pak, thisclient->CharInfo->stamina );
        ADDWORD    ( pak, 0 );
        thisclient->client->SendPacket( &pak );
	}
	//End of Patch.


	return;
}

// use Debuff skill
void CCharacter::UseDebuffSkill( CCharacter* Enemy, CSkills* skill )
{
    bool bflag = false;
    bflag = GServer->AddBuffs( skill, Enemy, GetInt( ) );
    if(GServer->ServerDebug)
        Log(MSG_INFO,"debufskill %i, %i",clientid,Enemy->clientid);
    if(skill->nbuffs>0 && bflag == true)
    {
        //Log(MSG_INFO,"debufskill %i, %i",clientid,Enemy->clientid);
        BEGINPACKET( pak, 0x7b5 );
        ADDWORD    ( pak, Enemy->clientid );
        ADDWORD    ( pak, clientid );
        ADDWORD    ( pak, Battle->skillid );
        ADDWORD    ( pak, GetInt( ) );
        ADDBYTE    ( pak, skill->nbuffs );
        GServer->SendToVisible( &pak, Enemy );
        //GServer->SendToAllInMap(&pak,this->Position->Map);
    }
    BEGINPACKET( pak, 0x7b9);
    ADDWORD    ( pak, clientid);
    ADDWORD    ( pak, Battle->skillid);
    //ADDWORD    ( pak, 1);
    GServer->SendToVisible( &pak, (CCharacter*)this );
}

// Use a skill (gm command)
bool CCharacter::UseSkill( CSkills* skill, CCharacter *Target )
{
  if (skill->atkpower > 0)
  {
    Log(MSG_INFO, "Need to do %i%s %s in range %i to target %i",
        ( skill->atkpower ),
        ( (skill->range > 0) ? " AOE" : "" ),
        ( (GServer->isSkillTargetFriendly(skill)) ? "healing" : "damage" ),
        ( skill->range ),
        ( skill->target ) );
  }
  for (int i = 0; i < 2; i++) {
    Log(MSG_INFO, "Status ID: %i", skill->status[i]);
    if (skill->status[i] == 0) continue;
    CStatus* status = GServer->GetStatusByID(skill->status[i]);
    if (status == NULL) continue;
    /************************
    We'll probably need to use status->decrease (Figure out whether buf is up/down
    status->repeat will tell us whether it's a one-time (Stat Boost [2]), repeat
    (Recovery, continueing damage [1]) or Special (Status Effect [3]).
    ************************/
    if (status->repeat == 1) // Continuous
    {
      Log(MSG_INFO, "Need to take stat %i and %s it by %i%s over %i seconds", skill->buff[i],
          ((status->decrease) ? "decrease" : "increase"),
          ((skill->value1[i] != 0) ? skill->value1[i] : skill->value2[i]),
          ((skill->value1[i] != 0) ? "" : "%"), skill->duration);

    } else if (status->repeat == 2) // Once (Stat Boost)
    {
      Log(MSG_INFO, "Need to take stat %i and %s it by %i%s for %i seconds", skill->buff[i],
          ((status->decrease) ? "decrease" : "increase"),
          ((skill->value1[i] != 0) ? skill->value1[i] : skill->value2[i]),
          ((skill->value1[i] != 0) ? "" : "%"), skill->duration);

    } else if (status->repeat == 3) // Status Effect (Poison,etc)
    {
      Log(MSG_INFO, "Need to give user status effect %i for %i seconds", skill->buff[i],
          ((skill->value1[i] != 0) ? skill->value1[i] : skill->value2[i]),
          ( skill->duration ) );

    }
  }
  return true;
}

//LMA: We take exp from a dead player.
bool CCharacter::TakeExp( CCharacter *Target )
{
    //LMA: We don't take exp from a player if the killer is a Player.
    if(!Target->IsPlayer()||(Target->IsPlayer()&&IsPlayer()))
    {
        return true;
    }

    //no need to take exp from UW.
    if(Position->Map==9)
    {
        return true;
    }

    //We take 3% of his xp.
    CPlayer* thisclient = GServer->GetClientByID(Target->clientid,Target->Position->Map);
    if (thisclient==NULL)
    {
        CPlayer* thisclient = GServer->GetClientByID(Target->clientid,Position->Map);
    }

    if (thisclient==NULL)
    {
        if(GServer->ServerDebug)
            Log(MSG_WARNING,"Can't find clientID %i to take his Exp...",Target->clientid);
        return true;
    }

    if(GServer->ServerDebug)
        Log(MSG_INFO,"Player %i died, Xp before %I64i",Target->clientid,thisclient->CharInfo->Exp);
    unsigned long long new_exp=(unsigned long long) (thisclient->CharInfo->Exp*3/100);
    thisclient->CharInfo->Exp-=new_exp;
    BEGINPACKET( pak, 0x79b );
    ADDDWORD   ( pak, thisclient->CharInfo->Exp );
    ADDWORD    ( pak, thisclient->CharInfo->stamina );
    ADDWORD    ( pak, 0 );
    thisclient->client->SendPacket( &pak );
    if(GServer->ServerDebug)
        Log(MSG_INFO,"Player %i died, Xp taken %I64i, new %I64i",Target->clientid,new_exp,thisclient->CharInfo->Exp);


    return true;
}

//LMA: Union war kill (and more generally qsd killing / death trigger).
void CCharacter::UWKill(CCharacter* Enemy)
{
    if(!IsPlayer()&&!Enemy->IsPlayer())
    {
        if(GServer->ServerDebug)
            Log(MSG_WARNING,"No player for UWKill");
        return;
    }

    CPlayer* plkiller=NULL;
    CPlayer* plkilled=NULL;

    if(IsPlayer())
    {
        plkiller=(CPlayer*) this;
    }

    if(Enemy->IsPlayer())
    {
        plkilled=(CPlayer*) Enemy;
    }

    int killer_level=0;
    int killed_level=0;

    dword hashkilling = GServer->MapList.Index[Position->Map]->QSDkilling;
    dword hashdeath = GServer->MapList.Index[Position->Map]->QSDDeath;

    //The killer.
    if(hashkilling>0&&plkiller!=NULL)
    {
        if(GServer->ServerDebug)
            Log(MSG_DEBUG,"Executing Quest Trigger for killer from UWKill");
        plkiller->ExecuteQuestTrigger(hashkilling,true);
        //Log(MSG_WARNING,"quest hash %u to the killer %s",hashkilling,plkiller->CharInfo->charname);
        killer_level=plkiller->Stats->Level;
    }

    //The killed one.
    if(hashkilling>0&&plkilled!=NULL)
    {
        if(GServer->ServerDebug)
            Log(MSG_DEBUG,"Executing Quest Trigger for killed from UWKill");
        plkilled->ExecuteQuestTrigger(hashdeath,true);
        //Log(MSG_WARNING,"quest hash %u to the killed %s",hashdeath,plkilled->CharInfo->charname);
        killed_level=plkilled->Stats->Level;
    }

    //Let's give some exp points to the killer...
    if(!IsPlayer()||!Enemy->IsPlayer())
    {
        //only if both are players.
        return;
    }

    if(plkiller==NULL)
    {
        return;
    }

    if(plkilled==NULL)
    {
        killed_level=killer_level;
    }

    UINT bonus_exp=GServer->GetColorExp(killer_level,killed_level,7000);
    plkiller->CharInfo->Exp += bonus_exp;

    //LMA: Only if not level up
    if(plkiller->CharInfo->Exp<plkiller->GetLevelEXP())
    {
        BEGINPACKET( pak, 0x79b );
        ADDDWORD   ( pak, plkiller->CharInfo->Exp );
        ADDWORD    ( pak, plkiller->CharInfo->stamina );

        if(plkilled!=NULL)
        {
            ADDWORD    ( pak, plkilled->clientid );
        }
        else
        {
            ADDWORD    ( pak, 0 );
        }

        plkiller->client->SendPacket( &pak );
        //Log(MSG_WARNING,"Giving %u exp to %s",bonus_exp,plkiller->CharInfo->charname);
    }


  return;
}


//LMA: test for quest hack (stackable).
#ifdef QHACK
//LMA: Adding a kill to the special quest kill list for a player.
void CCharacter::QuestKill(dword die_quest)
{
    CPlayer* plkiller;
    if(!IsPlayer()||die_quest==0)
    {
        if(GServer->ServerDebug)
        {
            if(die_quest == 0)
            {
                Log(MSG_INFO,"No Die Quest for this monster");
            }
        }
        if(IsSummon()&&die_quest!=0)
        {
            CMonster* questMonster = (CMonster*) this;
            plkiller= questMonster->GetOwner();
			if(GServer->ServerDebug)
                Log(MSG_INFO,"Summon got Quest");
        }
        else
        {
            return;
        }
    }
    else
    {
        plkiller = (CPlayer*) this;
        if(GServer->ServerDebug)
        {
            Log(MSG_INFO,"Die Quest for this monster is %i",die_quest);
        }
    }

    //looking for a "free" slot.
    clock_t mytime=clock();
    clock_t oldest_time=mytime;
    int oldest=0;

    for(int k=0;k<10;k++)
    {
        if(plkiller->arr_questid[k].questid==0)
        {
            oldest=k;
            break;
        }

        //looking for time (is it too old?)
        if(mytime>plkiller->arr_questid[k].die_time)
        {
            oldest=k;
            break;
        }

        //is it the oldest? if they are all too recent, it'll be set to 0.
        if(plkiller->arr_questid[k].die_time<oldest_time)
        {
            oldest_time=plkiller->arr_questid[k].die_time;
            oldest=k;
        }

    }

    plkiller->arr_questid[oldest].questid=die_quest;
    plkiller->arr_questid[oldest].die_time=mytime+(CLOCKS_PER_SEC/2);
    if(GServer->ServerDebug)
        Log(MSG_WARNING,"Killing time, offset %i time %u questid %u",oldest,plkiller->arr_questid[oldest].die_time,die_quest);


    return;
}
#endif



