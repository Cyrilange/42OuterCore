// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import {Test} from "forge-std/Test.sol";
import {NeonBeach} from "../code/NeonBeach.sol";

contract NeonBeachTest is Test {
    NeonBeach public neonBeach;
    address public owner = address(1);
    address public user1 = address(2);

    function setUp() public {
        
        vm.prank(owner);
        neonBeach = new NeonBeach();
    }

    function testContractNameAndSymbol() public  {
        
        assertEq(neonBeach.name(), "TokenizerArt");
        assertEq(neonBeach.symbol(), "neon beach");
    }

    function testMintSucces() public  {
        string memory sampleUri = "ipfs://bafybeiardzgyf3ifrcixf7ywmb2jvqzymyxipzyd55xsts5ueta3vt72fy";
        
        vm.prank(owner);
        neonBeach.safeMint(user1, sampleUri);

        // Assertions checking if state updated correctly
        assertEq(neonBeach.balanceOf(user1), 1);
        assertEq(neonBeach.ownerOf(0), user1);
        assertEq(neonBeach.tokenURI(0), sampleUri);
    }

}