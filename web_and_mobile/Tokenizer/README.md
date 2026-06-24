_this project is made by csalamit_

# SocialFii42 — ERC20 Token (No OpenZeppelin)

> A hand-crafted ERC20 implementation built to understand how the standard works under the hood, without relying on OpenZeppelin abstractions.

---

## Why these tools

- **Sepolia** — chosen as the deployment network because it is a stable Ethereum testnet, allowing real contract interaction without spending real ETH.
- **Foundry** — chosen as the development framework because it allows writing tests directly in Solidity, keeping the stack consistent and avoiding context-switching to JavaScript.
- **No OpenZeppelin** — intentional choice to understand how the ERC20 standard works under the hood, without relying on abstractions.

---

## Overview

**Token Name:** SocialFii42
**Symbol:** SF2
**Decimals:** 18
**Initial Supply:** 1,000,000 SF2 (minted to deployer on launch)
**Network:** EVM-compatible (deploy via Foundry)

---

## Contract Functions

### Read (view)

| Function | Description |
|---|---|
| `balanceOf(address acc)` | Returns the token balance of a given address |
| `allowance(address owner, address spender)` | Returns how many tokens `spender` is allowed to use on behalf of `owner` |
| `getOwner()` | Returns the address of the contract owner |

### Write (state-changing)

| Function | Access | Description |
|---|---|---|
| `mint(address recipient, uint256 amount)` | Owner only | Creates new tokens and assigns them to `recipient`. Increases `totalSupply`. |
| `transfer(address recipient, uint256 amount)` | Any user | Transfers tokens from the caller's wallet to `recipient` |
| `approve(address spender, uint256 value)` | Any user | Grants `spender` the right to spend up to `value` tokens on your behalf |
| `transferFrom(address sender, address recipient, uint256 amount)` | Any approved spender | Moves tokens from `sender` to `recipient` using a pre-approved allowance |

### Events

| Event | Emitted when |
|---|---|
| `Transfer(address from, address to, uint256 value)` | Tokens are transferred or minted |
| `Approval(address owner, address spender, uint256 value)` | An allowance is set via `approve` |

---

## Security

> ⚠️ This contract is **not audited**. It is intended for **educational purposes** to understand how ERC20 works from scratch. For production use, prefer the [OpenZeppelin ERC20 implementation](https://github.com/OpenZeppelin/openzeppelin-contracts).

### What is protected

- **`mint` is owner-only** — guarded by `require(msg.sender == owner)`, preventing arbitrary token creation
- **`transfer` checks balance** — `require(amount <= balances[msg.sender])` prevents spending more than owned
- **`transferFrom` double-checks** — verifies both the sender's balance and the approved allowance before moving funds

### Known limitations / missing features

| No pause/blacklist mechanism | Cannot freeze malicious activity once deployed |
| No overflow protection (pre-0.8) | Not an issue here since `pragma ^0.8.27` has built-in overflow checks |

### Best practices when interacting

- Never approve more than the amount you intend to spend
- Always verify the contract address before interacting
- Use a hardware wallet for the owner account in any real deployment

---

## Project Structure

```
Tokenizer/
├── code/
│   ├── sources/
│   │   ├── contract/
│   │   │   └── SocialFii42.sol       # Main ERC20 contract
│   │   └── test/
│   │       └── SocialFi.t.sol        # Foundry tests
│   ├── foundry.toml                  # Foundry config
│   └── lib/                          # Foundry dependencies 
├── deployment/
│   └── Deploy.s.sol                  # Deploy script
├── documentation/
│   └── Whitepaper.pdf
├── socialfi-frontend/                # React frontend (Vite)
├── script_recup_key.js               # Key utility script
├── .env                              # RPC_URL and PRIVATE_KEY
└── README.md
```

---

## Getting Started

### 1. Clone & enter the project

```bash
git clone <your_repo_url>
cd Tokenizer
```

### 2. Install Foundry dependencies

```bash
cd code
forge install foundry-rs/forge-std
forge install OpenZeppelin/openzeppelin-contracts
```

### 3. Compile

```bash
cd ~/Tokenizer/code
forge build
```

### 4. Run tests

```bash
cd ~/Tokenizer/code
forge test
```

Run with verbose output to see each test result:

```bash
forge test -vv
```

### 5. Deploy

Create a `.env` file at the root:

```bash
RPC_URL=https://sepolia.infura.io/v3/YOUR_KEY
PRIVATE_KEY=your_private_key_here
```

Then run:

```bash

cat > ~/Tokenizer/deploy.sh << 'EOF'
#!/bin/bash
source .env
forge script deployment/Deploy.s.sol \
  --rpc-url $RPC_URL \
  --private-key $PRIVATE_KEY \
  --broadcast
EOF
chmod +x ~/Tokenizer/deploy.sh


```

> ⚠️ Never commit your `.env` file or expose your private key.

### 6. Frontend

```bash
cd socialfi-frontend
npm install
npm run dev
```

---

## Interact with the contract from the terminal

Once deployed, you can call the contract directly with `cast` (included with Foundry):

```bash
# Check balance
cast call <CONTRACT_ADDRESS> "balanceOf(address)" <WALLET_ADDRESS> --rpc-url $RPC_URL

# Check total supply
cast call <CONTRACT_ADDRESS> "totalSupply()" --rpc-url $RPC_URL

# Check owner
cast call <CONTRACT_ADDRESS> "getOwner()" --rpc-url $RPC_URL

# Transfer tokens
cast send <CONTRACT_ADDRESS> "transfer(address,uint256)" <RECIPIENT> <AMOUNT> \
  --private-key $PRIVATE_KEY --rpc-url $RPC_URL

  exemple of address : 0x742d35Cc6634C0532925a3b844Bc454e4438f44e

# Approve a spender
cast send <CONTRACT_ADDRESS> "approve(address,uint256)" <SPENDER> <AMOUNT> \
  --private-key $PRIVATE_KEY --rpc-url $RPC_URL

# Mint tokens (owner only)
cast send <CONTRACT_ADDRESS> "mint(address,uint256)" <RECIPIENT> <AMOUNT> \
  --private-key $PRIVATE_KEY --rpc-url $RPC_URL
```

---

## Contract


https://sepolia.etherscan.io/token/0x88198937b1ec5338daae2dfdb30e5b45bd525c82

| Field | Value |
|-------|-------|
| **Network** | Ethereum Sepolia (testnet) |
| **Contract Address** | 0x88198937B1eC5338dAae2dFDb30E5B45Bd525c82 |
| **First transaction hash** | 0x711307afbf1bbe48a77ad4022ac872387c093f0869c9fa616496606985cc9443 |
| **Standard** | ERC-20 |
| **Symbol** | SF2 |
| **Decimals** | 18 |

---

## License

MIT