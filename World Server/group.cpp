#include "worldserver.h"

// toxin:  Game Arena stuff
bool CWorldServer::RefreshGroups ( CPlayer* thisclient )
{
    if(thisclient==NULL) return true;
    if(thisclient->Groupga->Groupga != NULL)
    {
        GAGroup* group = thisclient->Groupga->Groupga;
        if(group == NULL) return true;
        for(UINT i=0;i<group->Members.size();i++)
            {
                CPlayer* thismember = group->Members.at(i);
                if(thismember==NULL) continue;
                BEGINPACKET ( pak, 0x854 );
                ADDDWORD    ( pak, thisclient->Groupga->id; );
                ADDWORD     ( pak, thismember->clientid );
                ADDDWORD    ( pak, thismember->Stats->MaxHP );
                ADDDWORD    ( pak, thismember->Stats->HP );
                ADDDWORD    ( pak, BuildBuffs(thismember) );
                ADDDWORD    ( pak, thismember->Stats->MaxMP );
                ADDDWORD    ( pak, thismember->Stats->MP );
                ADDDWORD    ( pak, BuildBuffs2(thismember) ); //build buffs 2
                thisclient->client->SendPacket(&pak);
            }
    }
    return true;
}

bool CWorldServer::Recv_pakGroupMemberList(CPlayer* thisplayer, CPacket* pak)
{
    if(thisplayer->Groupga->Groupga == NULL)
        return true;

    Send_pakGroupMemberList(thisplayer->Groupga->Groupga, 0x01);
    return true;
}

void CWorldServer::Send_pakGroupMemberList(GAGroup* thisgroup, BYTE btCommand, CPlayer* player)
{
    if(thisgroup == NULL)
        return;

    BEGINPACKET ( pak, 0x853 );
    ADDBYTE     ( pak, btCommand );

    switch(btCommand)
    {
    case 1: // List
        {
            ADDDWORD    ( pak, thisgroup->Members.size());

            for(int i = 0; i<thisgroup->Members.size(); i++)
            {
                CPlayer* member = thisgroup->Members.at(i);

                ADDDWORD    ( pak, member->CharInfo->charid );
                ADDBYTE     ( pak, member->Groupga->IsMaster );
                ADDDWORD    ( pak, member->Stats->Level );
                ADDDWORD    ( pak, member->CharInfo->Job );
                ADDDWORD    ( pak, member->Position->Map );
                ADDDWORD    ( pak, member->Stats->MaxHP );
                ADDDWORD    ( pak, member->Stats->HP );
                ADDDWORD    ( pak, BuildBuffs(member) );
                ADDDWORD    ( pak, BuildBuffs2(member) );
                ADDDWORD    ( pak, member->Stats->MaxMP );
                ADDDWORD    ( pak, member->Stats->MP );
                ADDDWORD    ( pak, 0 );//Passive MP Recovery
                ADDDWORD    ( pak, 0 );//Passive HP Recovery
                ADDWORD     ( pak, member->GetCon() );
                ADDWORD     ( pak, member->clientid );
                ADDDWORD    ( pak, 0 );
                ADDDWORD    ( pak, 0 );
                ADDSTRING   ( pak, member->CharInfo->charname );
                ADDBYTE     ( pak, 0 );
            }
        } break;
    case 4: // Join
        {
            ADDDWORD    ( pak, 1);
            ADDDWORD    ( pak, player->CharInfo->charid );
            ADDBYTE     ( pak, player->Groupga->IsMaster );
            ADDDWORD    ( pak, player->Stats->Level );
            ADDDWORD    ( pak, player->CharInfo->Job );
            ADDDWORD    ( pak, player->Position->Map );
            ADDDWORD    ( pak, player->Stats->MaxHP );
            ADDDWORD    ( pak, player->Stats->HP );
            ADDDWORD    ( pak, BuildBuffs(player) );
            ADDDWORD    ( pak, BuildBuffs2(player) );
            ADDDWORD    ( pak, player->Stats->MaxMP );
            ADDDWORD    ( pak, player->Stats->MP );
            ADDDWORD    ( pak, 0 );//Passive MP Recovery
            ADDDWORD    ( pak, 0 );//Passive HP Recovery
            ADDWORD     ( pak, player->GetCon() );
            ADDWORD     ( pak, player->clientid );
            ADDDWORD    ( pak, 0 );
            ADDDWORD    ( pak, 0 );
            ADDSTRING   ( pak, player->CharInfo->charname );
            ADDBYTE     ( pak, 0 );

        } break;
    }

    thisgroup->SendToMembers(&pak);
}

bool CWorldServer::pakGroup ( CPlayer* thisclient, CPacket* P )
{
    BYTE action = GETBYTE((*P), 0);

    BEGINPACKET ( pak, 0x850 );
    ADDBYTE     ( pak, action );
    thisclient->client->SendPacket(&pak);

    switch(action)
    {
    case 0: // create
        {
            GAGroup* thisgroup = NULL;
            if(thisclient->Groupga->Groupga == NULL)
            {
                thisgroup = new GAGroup;
                thisgroup->AddPlayer( thisclient );
                ADDGAGroup( thisgroup );
                thisclient->Groupga->id = GetNewGAId();
                thisclient->Groupga->IsMaster = true;
            }
            else
            {
                thisgroup = thisclient->Groupga->Groupga;
            }

            BEGINPACKET ( pak, 0x851 );
            ADDBYTE     ( pak, 1 );
            ADDDWORD    ( pak, thisclient->CharInfo->charid);
            ADDDWORD (pak, 0);
            thisclient->client->SendPacket(&pak);

            Send_pakGroupMemberList(thisgroup, 0x01); // List

        } break;
    case 1:
        {
            if(thisclient->Groupga->Groupga==NULL)
                return true;
            GAGroup* group = thisclient->Groupga->Groupga;
            bool pflag = false;
            if(!group->RemovePlayer( thisclient ))
                return true;

            BEGINPACKET(pak, 0x851);
            ADDBYTE(pak, 4);
            ADDDWORD(pak, thisclient->CharInfo->charid);
            ADDDWORD(pak, 0);

            group->SendToMembers(&pak, thisclient);

            if(group->Members.size()>1)
            {
                for(UINT i=0;i<group->Members.size();i++)
                {
                    CPlayer* thismember = group->Members.at(i);
                    if(!pflag)
                    {
                        if(thisclient->Groupga->IsMaster)
                            thismember->Groupga->IsMaster = true;
                        pflag = true;
                    }
                }
            }
            else
            {
                for(UINT i=0;i<group->Members.size();i++)
                {
                    CPlayer* thismember = group->Members.at(i);
                    thismember->Groupga->Groupga = NULL;
                    thismember->Groupga->IsMaster = false;
                }
                RemoveGroup( group );
                delete group;
            }

        } break;
    case 2: // disban
        {
            if(thisclient->Groupga->Groupga==NULL)
                return true;
            GAGroup* group = thisclient->Groupga->Groupga;

            if(!group->RemovePlayer( thisclient ))
                return true;

            ClearGAid(thisclient->Groupga->id);

            for(UINT i=0;i<group->Members.size();i++)
            {
                CPlayer* thismember = group->Members.at(i);
                group->RemovePlayer( thismember );
            }
            RemoveGroup( group );
            delete group;

        } break;
    }

    return true;
}

bool CWorldServer::pakGroupActions ( CPlayer* thisclient, CPacket* P )
{
    BYTE action = GETBYTE((*P), 0);
    BYTE lengh = GETBYTE((*P), 1);
    char name[lengh];
	memset( &name, '\0', lengh );
	strncpy( name, (char*)&(*P).Buffer[2],lengh);

    switch(action)
    {
        case 0: //invite xy player
        {
            CPlayer* otherclient = GServer->GetClientByCharName(name);
            if(otherclient==NULL)
            {
                BEGINPACKET     (pak, 0x852)
                ADDBYTE         (pak, 4);
                ADDBYTE         (pak, lengh);
                ADDSTRING       (pak, name);
                ADDBYTE         (pak, 0);
                otherclient->client->SendPacket(&pak);

            } else {
                thisclient->client->SendPacket(P);

                BEGINPACKET     (pak, 0x852)
                ADDBYTE         (pak, 1);
                ADDBYTE         (pak, strlen(thisclient->CharInfo->charname));
                ADDSTRING       (pak, thisclient->CharInfo->charname);
                ADDBYTE         (pak, 0);
                otherclient->client->SendPacket(&pak);
            }
        }
        break;
        case 1: //said yes to invite
        {
            CPlayer* otherclient = GServer->GetClientByCharName(name);
            if(otherclient==NULL) return true;

            BEGINPACKET     (pak, 0x852)
            ADDBYTE         (pak, 2);
            ADDBYTE         (pak, strlen(thisclient->CharInfo->charname));
            ADDSTRING       (pak, thisclient->CharInfo->charname);
            ADDBYTE         (pak, 0);
            otherclient->client->SendPacket(&pak);

            GAGroup* thisgroup = otherclient->Groupga->Groupga;

            thisclient->Groupga->id = GetNewGAId();
            thisclient->Groupga->IsMaster = false;

            thisgroup->AddPlayer( thisclient );

            Send_pakGroupMemberList(thisgroup, 4, thisclient);
            Send_pakGroupMemberList(thisgroup, 1);

        } break;
        case 2: //decline
        {
            CPlayer* otherclient = GServer->GetClientByCharName(name);
            BEGINPACKET     (pak, 0x852)
            ADDBYTE         (pak, 3);
            ADDBYTE         (pak, lengh);
            ADDSTRING       (pak, thisclient->CharInfo->charname);
            ADDBYTE         (pak, 0);
            otherclient->client->SendPacket(&pak);
        } break;
    }

    return true;
}
