// SPDX-License-Identifier: MIT
pragma solidity ^0.8.27;

import {Script} from "forge-std/Script.sol";
import {SocialFii42} from "../code/sources/contract/SocialFii42.sol";

contract Deployment is Script {
    function run() external {
        vm.startBroadcast();
        new SocialFii42();
        vm.stopBroadcast();
    }
}

/*   
this command deploy the token , and create a new broadcast 
forge script deployment/Deploy.s.sol \

  --rpc-url $RPC_URL \

  --private-key $PRIVATE_KEY \

  --broadcast */