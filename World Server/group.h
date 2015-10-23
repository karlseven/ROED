#ifndef __ROSE_PARY__
#define __ROSE_PARY__

#include "worldserver.h"
#include "datatypes.h"

class CGroup
{
    public:
        CGroup( );
        ~CGroup( );

        UINT GroupId;
        CPlayer* GetMember( UINT id );
        CPlayer* GetMemberByCharName( STRING name );
        void SendToMembers( CPacket* pak, CPlayer* exclient=NULL );
        void SendToVisible( CPacket* pak, CPlayer* thisclient );
        bool AddPlayer( CPlayer* player );
        bool RemovePlayer( CPlayer* player );

        UINT Option;
        vector<CPlayer*> Members;
};

#endif
