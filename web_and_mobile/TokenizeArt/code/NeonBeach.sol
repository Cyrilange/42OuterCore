// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts/access/Ownable.sol";



contract NeonBeach is ERC721,  ERC721URIStorage, Ownable {
  //no arg so we dont need them during the deployment 
    uint256 private _nextTokenId;  //because nft are non fungible they need a unique id
    constructor()  
    ERC721("TokenizerArt", "neon beach")  
    Ownable(msg.sender) 
    { }

    //this function is a variante of mint but safer
  function safeMint(address to, string memory uri) public onlyOwner {
        uint256 tokenId = _nextTokenId++;
        _safeMint(to, tokenId); //emit Transfer(address(0), to, tokenId);
        _setTokenURI(tokenId, uri); //when deploy uri will be set as the cid 
    }

    // this function is an override because it is a function to the parents , super will find the nearest parent
    function tokenURI(uint256 tokenId) public view override(ERC721, ERC721URIStorage) returns (string memory) {
        return super.tokenURI(tokenId);
    }

    //this function is for frontend so it let the front end interoge the contract
    function supportsInterface(bytes4 interfaceId) public view override(ERC721, ERC721URIStorage) returns (bool) {
            return super.supportsInterface(interfaceId);
        }


}
 