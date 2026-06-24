// SPDX-License-Identifier: MIT
pragma solidity ^0.8.27;

//this contract is socialfi2, the contract using erc20 but with no zepellin , 
//well because it is not audit then , the zepellin version is better but this one 
//make you understand deep down how it is created


contract SocialFii42 {

	mapping(address => uint256) private balances;
	mapping(address => mapping(address => uint256)) private allowances; 
	uint256 public totalSupply;
	address public owner;
	string public name = "SocialFii42";
	string public  symbol = "SF2";
	uint8 public decimals = 18;
	constructor() {
		owner = msg.sender;
		uint256 initialSupply = 1_000_000 * 10**18;
    	balances[msg.sender] = initialSupply;
    	totalSupply = initialSupply;
    	emit Transfer(address(0), msg.sender, initialSupply); // mint 1 million of tokens when launch
	}

	//function to mint
	function mint(address recipient, uint256 amount) public {
		require(msg.sender == owner, "Only the owner can perform this action");
		balances[recipient] += amount;
        totalSupply += amount;
		emit Transfer(address(0), recipient, amount); //emit used to update the blockchain and the frontend  
	}

	  // function used to transfer
    function transfer(address recipient, uint256 amount) public returns (bool) {
        require(amount <= balances[msg.sender], "Not enough balance.");
        balances[msg.sender] -= amount;
        balances[recipient] += amount;
		emit Transfer(msg.sender, recipient, amount);
        return true;
    }
	// function to check balance
	function balanceOf(address acc) public view returns(uint256) {
		return balances[acc];
	}
	//event to transfert
	event Transfer(address indexed from, address indexed to, uint256 value);
	//event to approve
	event Approval(address indexed owner, address indexed spender, uint256 value);


	function transferFrom(address sender, address recipient, uint256 amount) public returns (bool success) {
		require(amount <= balances[sender], "Not enought tokens");
		require(amount <= allowances[sender][msg.sender], "Not enought tokens allowed");
		balances[sender] -= amount;
		allowances[sender][msg.sender] -= amount;
		balances[recipient] += amount;
		emit Transfer(sender, recipient, amount);
		return true;
	}

	function allowance(address _owner, address spender) public view returns (uint256 remaining) {
		 
		  return allowances[_owner][spender];

	}

	function approve(address _spender, uint256 _value) public returns (bool success) {
		allowances[msg.sender][_spender] = _value;
		emit Approval(msg.sender, _spender, _value);
    	return true;

	}

	function getOwner() public view returns (address) {
    	return owner;
}
}