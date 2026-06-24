// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import {Script} from "forge-std/Script.sol";
import {NeonBeach} from "../code/NeonBeach.sol";

contract NeonBeachScript is Script {
    NeonBeach public neonBeach;

    function setUp() public {}

    function run() public {
        // 1. private key
        uint256 deployerPrivateKey = vm.envUint("PRIVATE_KEY");
        
        // 2. cid
        string memory uri = vm.envString("MY_NFT_CID");

        // 3. start transaction with private key
        vm.startBroadcast(deployerPrivateKey);

        // 4. deploy
        neonBeach = new NeonBeach();

        // 5. minte first nft
        // vm.addr(deployerPrivateKey) find my public key 
        neonBeach.safeMint(vm.addr(deployerPrivateKey), uri);

        vm.stopBroadcast();
    }
}

//to deploy 
//1 into the terminal | source .env
//2 into the etrminal | forge script mint/NeonBeach.s.sol:NeonBeachScript --rpc-url $SEPOLIA_RPC_URL --broadcast --verify --etherscan-api-key $ETHERSCAN_API_KEY -vvvv 