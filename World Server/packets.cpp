#include "worldserver.h"

/*void CWorldServer::Send_pakAttack(CCharacter *pChar, CCharacter *pTarget)
{
    BEGINPACKET(pak, 0x798);

    ADDWORD(pak, pChar->clientid);
    ADDWORD(pak, pTarget->clientid);

    ADDWORD(pak, distance(pChar->Position->current, pTarget->Position->current)); //attackspeed

    ADDFLOAT(pak, pTarget->Position->current.x*100);
    ADDFLOAT(pak, pTarget->Position->current.y*100);

    this->SendToVisible(&pak, pChar);
}

void CWorldServer::Send_pakSkillSelf(CCharacter* pChar, char flag)
{
    BEGINPACKET( pak, 0x7b2);

    ADDWORD(pak, pChar->clientid);
    ADDWORD(pak, pChar->Battle->skillid);

	if(flag!=0)
    {
        ADDBYTE(pak, flag);
    }

    this->SendToVisible(&pak, pChar);
}

void CWorldServer::Send_pakSkillTarget(CCharacter *pChar, CCharacter *pTarget, char flag)
{
    BEGINPACKET(pak, 0x7b3 );
    ADDWORD(pak, pChar->clientid );
    ADDWORD(pak, pTarget->clientid );

    ADDWORD(pak, pChar->Battle->skillid);

    ADDWORD(pak, distance(pChar->Position->current, pTarget->Position->current));

    ADDFLOAT(pak, pTarget->Position->current.x*100 );
    ADDFLOAT(pak, pTarget->Position->current.y*100 );

    if(flag!=0)
    {
        ADDBYTE(pak, flag);
    }


    this->SendToVisible(&pak, pChar);
}

void CWorldServer::Send_pakSkillPosition(CCharacter* pChar)
{
    BEGINPACKET(pak, 0x7b4);

    ADDWORD(pak, pChar->clientid);
    ADDWORD(pak, pChar->Battle->skillid);
    ADDFLOAT(pak, pChar->Position->aoedestiny.x*100);
    ADDFLOAT(pak, pChar->Position->aoedestiny.y*100);
    ADDFLOAT(pak, pChar->Position->aoedestiny.z*100);

    SendToVisible(&pak, pChar);
}
*/
void CPlayer::Send_pakQuestReply(int result, int slot, int unk1, int quest)
{
	BEGINPACKET(pak, 0x730);

	ADDBYTE(pak, result);
	ADDBYTE(pak, slot);
	ADDDWORD(pak, unk1);
	ADDDWORD(pak, quest);

	client->SendPacket(&pak);
}
/*
void CWorldServer::Send_pakSkillStart(CCharacter* pChar)
{
    BEGINPACKET(pak, 0x7bb);
    ADDWORD(pak, pChar->clientid);
    this->SendToVisible(&pak, pChar);
}

void CWorldServer::Send_pakSkillResult(CCharacter *pChar)
{
    BEGINPACKET(pak, 0x7b9);

    ADDWORD(pak, pChar->clientid);
    ADDWORD(pak, pChar->Battle->skillid);

    SendToVisible(&pak, pChar);
}
void CWorldServer::Send_pakUsed(CCharacter *pChar, int id)
{
    CPlayer* thisclient2 = GServer->GetClientByID(pChar->clientid);
    if(thisclient2 == NULL) return ;
    if(thisclient2->IsMonster()) return ;
    BEGINPACKET(pak, 0x865);
    ADDWORD(pak, id);
    thisclient2->client->SendPacket(&pak);
}


void CWorldServer::Send_pakPartyReply(CPlayer* pPlayer, int source, int action)
{
    BEGINPACKET(pak, 0x7d1);
    ADDBYTE     (pak, action);
    ADDWORD     (pak, source);
    ADDBYTE     ( pak, 0x00 );
    pPlayer->client->SendPacket(&pak);
}

void CWorldServer::Send_pakPartyRequest(CPlayer* pPlayer, int source, int action)
{
    BEGINPACKET(pak, 0x7d0);
    ADDBYTE(pak, action );
    ADDDWORD(pak, source);
    pPlayer->client->SendPacket(&pak);
}

void CWorldServer::Send_pakPartyMembers(CParty* party, CPlayer* thisclient,int option)
{
    if(option=0)
    {
        BEGINPACKET( pak, 0x7d2 );
        ADDBYTE    (pak, party->Option );
        ADDBYTE    (pak, 0x01 );
        ADDDWORD   (pak, thisclient->CharInfo->charid );
        ADDWORD    (pak, thisclient->clientid );
        ADDDWORD   (pak, thisclient->Stats->MaxHP );
        ADDDWORD   (pak, thisclient->Stats->HP );
        ADDDWORD   (pak, BuildBuffs(thisclient));
        ADDDWORD   (pak, BuildBuffs2(thisclient) ); // Buffs
        ADDDWORD   (pak, 0x00000000 ); // ??
        ADDDWORD   (pak, 666 ); // Con
        ADDDWORD    (pak, 0x0000 ); //??
        ADDDWORD   (pak, thisclient->GetMPRegenAmount() );
        ADDDWORD   (pak, thisclient->GetHPRegenAmount() );
        ADDDWORD    (pak, thisclient->GetCon() );
        ADDSTRING  (pak, thisclient->CharInfo->charname );
        ADDBYTE    (pak, 0x00);
        party->SendToMembers(&pak);
        return;
    }
    else
    {
        BEGINPACKET( pak, 0x7d2 );
        ADDBYTE    ( pak, party->Option );
        ADDBYTE    ( pak, party->Members.size() );

        for(int i=0;i<party->Members.size();i++)
        {
            CPlayer* member= party->Members.at(i);
            ADDDWORD   ( pak, member->CharInfo->charid );
            ADDWORD    ( pak, member->clientid );
            ADDDWORD   ( pak, member->Stats->MaxHP );
            ADDDWORD   ( pak, member->Stats->HP );
            ADDDWORD   ( pak, BuildBuffs( member ));//Tomiz: Buff Data
            ADDDWORD   ( pak, BuildBuffs2( member ) ); //Buffs
            ADDDWORD   ( pak, 666 );// Buffs
            ADDDWORD    ( pak, 0x0000 );
            ADDDWORD   ( pak, member->GetMPRegenAmount() );
            ADDDWORD   ( pak, member->GetHPRegenAmount() );
            ADDDWORD    ( pak, 0 );
            ADDSTRING  ( pak, member->CharInfo->charname );
            ADDBYTE    ( pak, 0x00 );
        }
        thisclient->client->SendPacket(&pak);
        return;
    }
}

void CWorldServer::Send_pakEffectOfSkill(CCharacter* Source, CCharacter* Target, bool Failed)
{
	BEGINPACKET( pak, 0x7b5 );
	ADDWORD    ( pak, Target->clientid);
	ADDWORD    ( pak, Source->clientid );
	ADDWORD    ( pak, Source->Battle->skillid);
	ADDWORD    ( pak, Source->GetCha( ));
	ADDWORD    ( pak, Source->GetClassRequiredStatus());
	ADDBYTE    ( pak, !Failed );
	SendToVisible( &pak, Target );
}

void CWorldServer::Send_pakDamageOfSkill(CCharacter* Source, CCharacter* Target, bool Failed)
{
	BEGINPACKET( pak, 0x7b6 );
	ADDWORD    ( pak, Target->clientid);
	ADDWORD    ( pak, Source->clientid );
	ADDWORD    ( pak, Source->Battle->skillid);
	ADDWORD    ( pak, Source->GetCha( ));
	ADDWORD    ( pak, Source->GetClassRequiredStatus());
	ADDBYTE    ( pak, Failed );
	ADDDWORD   ( pak, 0x00000000);
	ADDDWORD   ( pak, 0x00000000)
	SendToVisible( &pak, Target );
}

void CWorldServer::Send_pakChangeSpeed(CCharacter* pChar, CCharacter* Enemy)
{
	BEGINPACKET( pak, 0x7b8 );
	ADDWORD    ( pak, pChar->Battle->skilltarget );
	ADDWORD	   ( pak, pChar->Stats->Base_Speed );
	ADDWORD	   ( pak, pChar->Stats->Move_Speed );
	ADDWORD	   ( pak, pChar->Stats->Base_Attack_Speed );
	ADDWORD	   ( pak, pChar->Stats->Attack_Speed );
	ADDBYTE	   ( pak, 0 ); // WeightRate
	SendToVisible( &pak, Enemy );
}

void CWorldServer::Send_pakPartyChangeMember(CPlayer* player)
{

}

void CWorldServer::Send_pakPartyChangeMember(CParty* party, CPlayer* player)
{

}

void CWorldServer::Send_pakHPMPRefresh(CCharacter *pChar)
{
    CPlayer* thisclient = GetClientByID(pChar->clientid);
    if(thisclient == NULL) return;
    if(thisclient->IsMonster())
    {
        BEGINPACKET( pak2, 0x7ec );

        ADDDWORD    (pak2, thisclient->Stats->HP );
        ADDDWORD    (pak2, thisclient->Stats->MP );
        ADDDWORD    (pak2, 0 );
        ADDDWORD    (pak2, 0 );

        thisclient->client->SendPacket( &pak2 );
        return;

    }
    BEGINPACKET( pak2, 0x7ec );

    if(thisclient->IsDead()) { ADDDWORD    (pak2,0xFFFFFFFF); }
    else { ADDDWORD    (pak2, thisclient->Stats->HP );}
    ADDDWORD    (pak2, thisclient->Stats->MP );
    ADDDWORD    (pak2, thisclient->CharInfo->stamina ); //??
    ADDDWORD    (pak2, thisclient->CharInfo->stamina ); //??

    thisclient->client->SendPacket( &pak2 );
}

void CWorldServer::Send_pakBuffRefresh(CCharacter* thisclient, int status)
{
    CPlayer* thisclient2 = GServer->GetClientByID(thisclient->clientid);
    if(thisclient2 == NULL) return ;
    if(thisclient2->IsMonster()) return ;
    BEGINPACKET( pak, 0x7b7 );
    ADDBYTE     (pak, 0x00 ); //changes every 2 send ????? >_ mean one xD isn't it the amount of buffs ? no its really random show me xD
    ADDWORD    ( pak, thisclient2->clientid );
    ADDDWORD    ( pak, GServer->GetBUFFPosition(status) ); //Buff position from the one who run out like 0x00040000 for ap buff
    ADDDWORD   ( pak, GServer->GetBUFFPosition2(status) ); //Buff position from the one who run out like 0x00040000 for int str dex buffs
    ADDDWORD   ( pak, 0 );
    ADDDWORD   ( pak, 0 );
    ADDDWORD   ( pak, GServer->BuildBuffs( thisclient2 ) );
    ADDDWORD   ( pak, GServer->BuildBuffs2( thisclient2 ) ); //second buildbuff str up
    ADDWORD    ( pak, thisclient->Stats->HP );
    thisclient2->client->SendPacket( &pak );

    RESETPACKET( pak, 0x7b7 );
    ADDBYTE     (pak, 0x00 ); //changes every 2 send ?????
    ADDWORD    ( pak, thisclient2->clientid );
    ADDDWORD    ( pak, GServer->GetBUFFPosition(status) ); //Buff position from the one who run out like 0x00040000 for ap buff
    ADDDWORD   ( pak, GServer->GetBUFFPosition2(status) );
    ADDDWORD   ( pak, 0 );
    ADDDWORD   ( pak, 0 );
    ADDDWORD   ( pak, GServer->BuildBuffs( thisclient2 ) );
    ADDDWORD   ( pak, GServer->BuildBuffs2( thisclient2 ) ); //second buildbuff str up
    ADDWORD    ( pak, thisclient->Stats->HP );
    GServer->SendToVisible( &pak, thisclient2 );

}
*/
