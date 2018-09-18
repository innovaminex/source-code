// Copyright (c) 2018 InnovaMinex www.innovaminex.com
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500; // we want moar

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // INX checkpoints
    // Double check before adding timestamp or a blockhash
    // Block 0 containts the genesis hash. It must match the rest with or without 0x
    // Do not remove. Must be validated and added by Hardline International LLC authorised developers only.
    // www.hardline.ltd
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (   0,     uint256("0x0000000223105f4bec915244592319dbe3e36b0c7ec6e1729ebdb8ac248ec070b") )
        (  10,     uint256("0x4c87b9cc5b61d40733d57efe850aa8c9aef7cab4af3232e3331550286e2e1262") )
        (  50,     uint256("0x26a2880f7b318ebbcec764454770cd6a9a13e1fc4a65ecc1d68926ed25770a9e") )
        ( 100,     uint256("0x82b9d4685e70d9c9ef30bd13e63cd1fd70b1a0396aa0a958df33eb24a81a3977") )
        ( 200,     uint256("0x7f86f6399efe15b09274ecf943340b512b20e34c71200d028c6832f6b2f61445") )
        ( 2018,    uint256("0x451918b13bf1eab2c5d42fab35c125bb9e449f49de75f92feb5a246b0dc24ff4") ) // year of INX checkpoint
        ( 4200,    uint256("0x7377e303e6fe18d93984b851205e9468495e4af122994a73c17b62ba548d5682") )
        ( 8300,    uint256("0x267f173084672a65d41d77ec16bd51aebffeb47110927a9f0309f8b6f4d9b267") ) // stable check
        ( 14100,   uint256("0x5a1dd71778fc7d88d2cfe379b2fcdcd3f81b2570c1eeaa006c76e819d8ab2f26") ) // ... goes on
        ( 95143,   uint256("0x961ab22fb1b66af9e9705d05fdb8c567e2511364fcb52770f37e99e32474bc45") ) // last good checkpoint
        ;

    // TestNet checkpoints
    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (  0,     uint256("0x0000097554d52f18dd8f60c9d7918590d202bb1f38f1a98c3d6f9ea7e4e97a8a") )
        ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
