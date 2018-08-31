// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2018 InnovaMinex
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

int64_t genTime = 1526392294;

void MineGenesis(CBlock genesis){
    // This will figure out a valid hash and Nonce if you're creating a different genesis block:
    uint256 hashTarget = CBigNum().SetCompact(Params().ProofOfWorkLimit().GetCompact()).getuint256();
    printf("Target: %s\n", hashTarget.GetHex().c_str());
    uint256 newhash = genesis.GetHash();
    uint256 besthash;
    memset(&besthash,0xFF,32);
    while (newhash > hashTarget) {
    	++genesis.nNonce;
        if (genesis.nNonce == 0){
            printf("NONCE WRAPPED, incrementing time");
            ++genesis.nTime;
        }
	newhash = genesis.GetHash();
	if(newhash < besthash){
	    besthash=newhash;
	    printf("New best: %s\n", newhash.GetHex().c_str());
	}
    }
    printf("Found Genesis, Nonce: %ld, Hash: %s\n", genesis.nNonce, genesis.GetHash().GetHex().c_str());
    printf("Gensis Hash Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
}

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe1;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0x7a;
        vAlertPubKey = ParseHex("0486cce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 9115;
        nRPCPort = 9114;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "BBC News, 15-May-2018: China Sichuan Airlines pilot 'half sucked out of plane' survives";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, genTime, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = genTime;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 2515652;

        hashGenesisBlock = genesis.GetHash();
//      MineGenesis(genesis); // mine the genesis block only, disable after solved
        assert(hashGenesisBlock == uint256("0x000000223105f4bec915244592319dbe3e36b0c7ec6e1729ebdb8ac248ec070b"));
        assert(genesis.hashMerkleRoot == uint256("0xb8a05de531407626736cbec7777060c198216924cb41fd810f28a0ad62e75a01"));


        vSeeds.push_back(CDNSSeedData("node1.hardline.ltd", "node1.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node2.hardline.ltd", "node2.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node3.hardline.ltd", "node3.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node4.hardline.ltd", "node4.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node5.hardline.ltd", "node5.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node6.hardline.ltd", "node6.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node7.hardline.ltd", "node7.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node8.hardline.ltd", "node8.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node9.hardline.ltd", "node9.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node10.hardline.ltd", "node10.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node11.hardline.ltd", "node11.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node12.hardline.ltd", "node12.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node13.hardline.ltd", "node13.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("node14.hardline.ltd", "node14.hardline.ltd"));
	vSeeds.push_back(CDNSSeedData("tn0.innovaminex.com", "tn0.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn1.innovaminex.com", "tn1.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn2.innovaminex.com", "tn2.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn3.innovaminex.com", "tn3.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn4.innovaminex.com", "tn4.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn5.innovaminex.com", "tn5.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn6.innovaminex.com", "tn6.innovaminex.com"));
	vSeeds.push_back(CDNSSeedData("tn7.innovaminex.com", "tn7.innovaminex.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,102);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 1000;
        nPOSStartBlock = 700;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x72;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x24;
        pchMessageStart[3] = 0x15;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 19115;
        nRPCPort = 19114;

        strDataDir = "testnet";
        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 5473935;
//        MineGenesis(genesis); // mine the genesis block only, disable after solved
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000097554d52f18dd8f60c9d7918590d202bb1f38f1a98c3d6f9ea7e4e97a8a"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet1.hardline.ltd", "testnet1.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("testnet2.hardline.ltd", "testnet2.hardline.ltd"));
        vSeeds.push_back(CDNSSeedData("testnet3.hardline.ltd", "testnet3.hardline.ltd"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 8); // Testnet tele addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 65 + 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0x2f;
        pchMessageStart[2] = 0x35;
        pchMessageStart[3] = 0x4a;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        nDefaultPort = 29115;
        strDataDir = "regtest";
        genesis.nTime = genTime;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2811523;
        hashGenesisBlock = genesis.GetHash();
//        MineGenesis(genesis);
        assert(hashGenesisBlock == uint256("0x00000eb4356c4574aea33a90b1ccfd66fee166dd6c637a878494b4a65699da94"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
