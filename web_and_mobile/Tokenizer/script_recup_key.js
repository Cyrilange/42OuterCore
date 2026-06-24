

const { Wallet } = require("ethers");

const mnemonic = "your 12 words";

const wallet = Wallet.fromPhrase(mnemonic);

console.log("ADDRESS:", wallet.address);
console.log("PRIVATE KEY:", wallet.privateKey);
