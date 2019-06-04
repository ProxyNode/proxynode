// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Proxynode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("000002d5a967ee5a93d36c2de7dd0cf23d9cb5d1b265104e4a4bebfd0593ad15"))
	(10000, uint256("3dfd6295a24d18817db1604bb91d2c60519ca391407559cff0961f0a8e18aa17"))
	(30000, uint256("e1e112eb7617ed4041a22f63cf3e34d017144397c2b0679c417c3c10b359722e"))
	(50000, uint256("6d9bc743bf1385612dbd209bd3beee8b385bad318f6bbf68bce9513dbb8fbc3a"))
	(70000, uint256("13c6103f44b23b09087b15b3743cc6cb2fb4e1a3dd5923783c24103b1f90afad"))
	(100000, uint256("fa6eaeaec645c734926021e884a9791a1a0132ee179af8cae8aa7c7ba52d992f"))
	(120000, uint256("bcb36f03a7772327c7807d80f5142a9ce5843dc7b1deb05ed61bdd16b27407b4"))
	(140000, uint256("8a90b7e813cf5d4e178daa15a13063ab2cf339f49411f8655f0553b18a3e0d21"))
	(160000, uint256("bb389729575ddbf9d4e2ba29bef40746bb02a7eb180316a02f17257a98bc28a7"))
	(180000, uint256("5b38ea82cac03740eee023678e52a456fa9b819e72c5b0e6527133622dced1a0"))
	(200000, uint256("2fb43318372e887c541c25f6906f1c1782629fac3c3ccf980691bd7ec3dcbbaf"))
	(220000, uint256("1db555dc9495fb41dc6f63277b34854bdc9b4a1754fe12b549f77c389d6bbafc"))
	(240000, uint256("8564a14842b6abc39384ef75286137304f36b4c5547ef5c1d2ea31cee65264eb"))
	(260000, uint256("f3ef9191541d12057a1516b8b614e4972ef7a741788060c362fb3bc774b8ed54"))
	(280000, uint256("a9cfd5c05984886581039686526c0d55e17e6f2112571699674ef277f04ab6c2"))
	(282600, uint256("930f08a16095795a4ed3c2fe60a45812ce15c4a9ea4a70587f98d0feedb53d3d"))
	
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1558963366, // * UNIX timestamp of last checkpoint block
    788923,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1532008046,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1532008046,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0xd5;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0xd9;
		vAlertPubKey = ParseHex("0317dc37db1011c0a162fc11335812349817392cdad2a12b85a0f841c4c48346bd85f45ec5c1d");
		nDefaultPort = 12195;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Prx starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 2100000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Proxynode: 
        nTargetSpacing = 1 * 60;  // Proxynode:  
        nMaturity = 20;
        nMasternodeCountDrift = 20;
	nMaxMoneyOut = 500000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 615800;
        const char* pszTimestamp = "PROXYNODE new blockchain is here";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("042292b1f401860eea99e1a8aab3effbd7e1c013a59a1a3a0c91c9d1997a0bc6f338567278c11344802838c107055bf7c1641eaed61e879245c255a4f5be5746fc") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1536621253;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1634836;
		
		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000002d5a967ee5a93d36c2de7dd0cf23d9cb5d1b265104e4a4bebfd0593ad15"));
        assert(genesis.hashMerkleRoot == uint256("0xe658d8c00694e7a288d399ad881dc3fcd7629527aae7f5cd9aead0fddff982eb"));

    	vSeeds.push_back(CDNSSeedData("45.32.220.127", "45.32.220.127"));
        vSeeds.push_back(CDNSSeedData("165.22.69.13", "165.22.69.13"));
		vSeeds.push_back(CDNSSeedData("45.76.52.180", "45.76.52.180"));
		vSeeds.push_back(CDNSSeedData("95.179.239.251", "95.179.239.251"));
        vSeeds.push_back(CDNSSeedData("35.165.69.229", "35.165.69.229"));
		vSeeds.push_back(CDNSSeedData("85.255.0.59", "85.255.0.59"));
		vSeeds.push_back(CDNSSeedData("167.86.107.225", "167.86.107.225"));
		vSeeds.push_back(CDNSSeedData("51.158.78.150", "51.158.78.150"));
		vSeeds.push_back(CDNSSeedData("167.179.68.150", "167.179.68.150"));
		vSeeds.push_back(CDNSSeedData("178.128.99.157", "178.128.99.157"));
		vSeeds.push_back(CDNSSeedData("66.42.32.225", "66.42.32.225"));
		vSeeds.push_back(CDNSSeedData("207.148.102.76", "207.148.102.76"));
		vSeeds.push_back(CDNSSeedData("134.209.125.253", "134.209.125.253"));
		vSeeds.push_back(CDNSSeedData("185.235.129.189", "185.235.129.189"));
		vSeeds.push_back(CDNSSeedData("195.201.16.75", "195.201.16.75"));
		vSeeds.push_back(CDNSSeedData("68.183.190.43", "68.183.190.43"));
		

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55); // P
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 138); // x
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 98); // g
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 1135
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x04)(0x6f).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0476403992033dcc765108011d0e79ebe0b12560e909d08f9f1925a6cee00120a987221caf71adc868e95102ca779ea7f712e9e88977406435229ed7e145ecd762";
        strMasternodePoolDummyAddress = "PXdUCCL4XKGSPRYNTFkZzXwpvt6zTpaFWf";
        nStartMasternodePayments = 1532008046; 
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x4a;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        vAlertPubKey = ParseHex("041b2b4c86273359acac3522471911ed2b303eaab65e8a1de01c06e89f2eab1e55234a4b504f3ce20c6f661f007d0ca15623b4358d9855c7c8ba793a24fa315e22");
        nDefaultPort = 130229;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Proxynode: 1 day
        nTargetSpacing = 2 * 60;  // Proxynode: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1516926684;
        genesis.nNonce = 3097091;

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x00000ec1634e6ee176e84d803713f1dff191abbe0add7a59b817fe56db094b76"));

        vFixedSeeds.clear();
        vSeeds.clear();

      //  vSeeds.push_back(CDNSSeedData("159.89.119.230", "159.89.119.230"));
        
        // Testnet Proxynode addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 98);
        // Testnet Proxynode script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet Proxynode BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Proxynode BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04abb5e65280dda6a113fadfb9877f9c399532245fe1acb61de293ab298034d5084277fab3768774a3b68cbbe5021cc5049ec8c9997a13f64da1afa0bcfb156db1";
        strMasternodePoolDummyAddress = "pbJ4Qad4xc77PpLzMx6rUegAs6aUPWkcUq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Proxynode: 1 day
        nTargetSpacing = 2 * 60;        // Proxynode: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1516926684;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 230229;
        // assert(hashGenesisBlock == uint256("0x40d358c1e5dfd45b317f749c5aeeee6842c49fcb9db024e1a52b54ba7f7b1fff"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
