import React, { useState } from "react";
import { ethers } from "ethers";

const contractAddress = "0x88198937B1eC5338dAae2dFDb30E5B45Bd525c82";

const abi = [
  "function balanceOf(address) view returns (uint256)",
  "function transfer(address,uint256) returns (bool)",
  "function mint(address,uint256)",
  "function approve(address,uint256) returns (bool)",
  "function allowance(address,address) view returns (uint256)",
  "function transferFrom(address,address,uint256) returns (bool)",
];

const STATUS = { IDLE: "idle", LOADING: "loading", SUCCESS: "success", ERROR: "error" };

export default function Action() {
  const [account,   setAccount]   = useState("");
  const [balance,   setBalance]   = useState("");
  const [to,        setTo]        = useState("");
  const [amount,    setAmount]    = useState("");
  const [spender,   setSpender]   = useState("");
  const [allowance, setAllowance] = useState("");
  const [txStatus,  setTxStatus]  = useState(STATUS.IDLE);
  const [txMsg,     setTxMsg]     = useState("");

  function requireWallet() {
    if (!window.ethereum || !window.ethereum.isMetaMask)
      throw new Error("MetaMask not detected. Please install it first.");
    if (!account)
      throw new Error("Connect your wallet first.");
  }

  function setFeedback(status, msg) {
    setTxStatus(status);
    setTxMsg(msg);
  }

  async function connectWallet() {
    if (!window.ethereum || !window.ethereum.isMetaMask) {
      setFeedback(STATUS.ERROR, "MetaMask not detected.");
      return;
    }
    try {
      setFeedback(STATUS.LOADING, "Connecting…");
      const accounts = await window.ethereum.request({ method: "eth_requestAccounts" });
      setAccount(accounts[0]);
      setFeedback(STATUS.SUCCESS, "Wallet connected.");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.message || "Connection failed.");
    }
  }

  async function getBalance() {
    try {
      requireWallet();
      setFeedback(STATUS.LOADING, "Fetching balance…");
      const provider = new ethers.BrowserProvider(window.ethereum);
      const contract = new ethers.Contract(contractAddress, abi, provider);
      const bal = await contract.balanceOf(account);
      setBalance(ethers.formatEther(bal));
      setFeedback(STATUS.SUCCESS, "Balance updated.");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.reason || err?.message || "Failed to fetch balance.");
    }
  }

  async function transfer() {
    try {
      requireWallet();
      if (!to)     throw new Error("Enter a recipient address.");
      if (!amount) throw new Error("Enter an amount.");
      setFeedback(STATUS.LOADING, "Waiting for confirmation…");
      const provider = new ethers.BrowserProvider(window.ethereum);
      const signer   = await provider.getSigner();
      const contract = new ethers.Contract(contractAddress, abi, signer);
      const tx = await contract.transfer(to, ethers.parseEther(amount));
      setFeedback(STATUS.LOADING, `TX sent: ${tx.hash.slice(0, 10)}… Waiting for block…`);
      await tx.wait();
      setFeedback(STATUS.SUCCESS, "Transfer successful!");
      setTo(""); setAmount("");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.reason || err?.message || "Transfer failed.");
    }
  }

  async function mint() {
    try {
      requireWallet();
      if (!amount) throw new Error("Enter an amount to mint.");
      setFeedback(STATUS.LOADING, "Waiting for confirmation…");
      const provider = new ethers.BrowserProvider(window.ethereum);
      const signer   = await provider.getSigner();
      const contract = new ethers.Contract(contractAddress, abi, signer);
      const tx = await contract.mint(account, ethers.parseEther(amount));
      setFeedback(STATUS.LOADING, `TX sent: ${tx.hash.slice(0, 10)}… Waiting for block…`);
      await tx.wait();
      setFeedback(STATUS.SUCCESS, "Mint successful!");
      setAmount("");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.reason || err?.message || "Mint failed.");
    }
  }

  // Authorise `spender` to spend `amount` tokens on your behalf
  async function approve() {
    try {
      requireWallet();
      if (!spender) throw new Error("Enter a spender address.");
      if (!amount)  throw new Error("Enter an amount.");
      setFeedback(STATUS.LOADING, "Waiting for confirmation…");
      const provider = new ethers.BrowserProvider(window.ethereum);
      const signer   = await provider.getSigner();
      const contract = new ethers.Contract(contractAddress, abi, signer);
      const tx = await contract.approve(spender, ethers.parseEther(amount));
      setFeedback(STATUS.LOADING, `TX sent: ${tx.hash.slice(0, 10)}… Waiting for block…`);
      await tx.wait();
      setFeedback(STATUS.SUCCESS, `Approved ${amount} SF2 for ${spender.slice(0, 6)}…`);
      setSpender(""); setAmount("");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.reason || err?.message || "Approve failed.");
    }
  }

  // Check how much `spender` can spend on your behalf
  async function getAllowance() {
    try {
      requireWallet();
      if (!spender) throw new Error("Enter a spender address.");
      setFeedback(STATUS.LOADING, "Fetching allowance…");
      const provider = new ethers.BrowserProvider(window.ethereum);
      const contract = new ethers.Contract(contractAddress, abi, provider);
      const al = await contract.allowance(account, spender);
      setAllowance(ethers.formatEther(al));
      setFeedback(STATUS.SUCCESS, "Allowance updated.");
    } catch (err) {
      setFeedback(STATUS.ERROR, err?.reason || err?.message || "Failed to fetch allowance.");
    }
  }

  const isLoading = txStatus === STATUS.LOADING;
  const feedbackColor =
    txStatus === STATUS.SUCCESS ? "#4ade80"
    : txStatus === STATUS.ERROR ? "#f87171"
    : "#a0aec0";

  return (
    <div style={styles.page}>
      <div style={styles.card}>

        {/* Header */}
        <div style={styles.header}>
          <span style={styles.dot} />
          <h1 style={styles.title}>SocialFi</h1>
          <span style={styles.subtitle}>Token Interface</span>
        </div>

        {/* Wallet */}
        <section style={styles.section}>
          <button
            style={{ ...styles.btn, ...styles.btnPrimary, opacity: isLoading ? 0.6 : 1 }}
            onClick={connectWallet}
            disabled={isLoading}
          >
            {account ? "↻ Reconnect" : "⬡ Connect MetaMask"}
          </button>
          {account && (
            <div style={styles.addressBox}>
              <span style={styles.label}>Connected</span>
              <span style={styles.address}>{account.slice(0, 6)}…{account.slice(-4)}</span>
            </div>
          )}
        </section>

        <hr style={styles.divider} />

        {/* Balance */}
        <section style={styles.section}>
          <div style={styles.balanceRow}>
            <div>
              <div style={styles.label}>Token Balance</div>
              <div style={styles.balanceValue}>{balance ? `${balance} SF2` : "—"}</div>
            </div>
            <button
              style={{ ...styles.btn, ...styles.btnGhost, opacity: isLoading ? 0.6 : 1 }}
              onClick={getBalance}
              disabled={isLoading}
            >
              Refresh
            </button>
          </div>
        </section>

        <hr style={styles.divider} />

        {/* Transfer & Mint */}
        <section style={styles.section}>
          <div style={styles.label}>Transfer / Mint</div>
          <input
            style={styles.input}
            placeholder="Recipient address (0x…)"
            value={to}
            onChange={(e) => setTo(e.target.value)}
          />
          <input
            style={styles.input}
            placeholder="Amount"
            value={amount}
            onChange={(e) => setAmount(e.target.value)}
            type="number"
            min="0"
          />
          <div style={styles.btnRow}>
            <button
              style={{ ...styles.btn, ...styles.btnPrimary, flex: 1, opacity: isLoading ? 0.6 : 1 }}
              onClick={transfer}
              disabled={isLoading}
            >
              {isLoading ? "Processing…" : "Transfer →"}
            </button>
            <button
              style={{ ...styles.btn, ...styles.btnSecondary, flex: 1, opacity: isLoading ? 0.6 : 1 }}
              onClick={mint}
              disabled={isLoading}
            >
              {isLoading ? "Processing…" : "⬡ Mint"}
            </button>
          </div>
          <div style={styles.mintHint}>Mint sends tokens to your address (owner only).</div>
        </section>

        <hr style={styles.divider} />

        {/* Approve & Allowance */}
        <section style={styles.section}>
          <div style={styles.label}>Approve / Allowance</div>
          <input
            style={styles.input}
            placeholder="Spender address (0x…)"
            value={spender}
            onChange={(e) => setSpender(e.target.value)}
          />
          <input
            style={styles.input}
            placeholder="Amount to approve"
            value={amount}
            onChange={(e) => setAmount(e.target.value)}
            type="number"
            min="0"
          />
          {allowance && (
            <div style={styles.addressBox}>
              <span style={styles.label}>Allowance</span>
              <span style={styles.address}>{allowance} SF2</span>
            </div>
          )}
          <div style={styles.btnRow}>
            <button
              style={{ ...styles.btn, ...styles.btnPrimary, flex: 1, opacity: isLoading ? 0.6 : 1 }}
              onClick={approve}
              disabled={isLoading}
            >
              {isLoading ? "Processing…" : "Approve"}
            </button>
            <button
              style={{ ...styles.btn, ...styles.btnGhost, flex: 1, opacity: isLoading ? 0.6 : 1 }}
              onClick={getAllowance}
              disabled={isLoading}
            >
              Check Allowance
            </button>
          </div>
          <div style={styles.mintHint}>
            Approve lets a spender use your tokens on your behalf.
          </div>
        </section>

        {/* Feedback */}
        {txMsg && (
          <div style={{ ...styles.feedback, color: feedbackColor }}>
            {txStatus === STATUS.LOADING && <span style={styles.spinner}>⟳ </span>}
            {txMsg}
          </div>
        )}

      </div>
    </div>
  );
}

const styles = {
  page: {
    minHeight: "100vh",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    background: "#0d0f14",
    fontFamily: "'IBM Plex Mono', 'Courier New', monospace",
    padding: "24px",
  },
  card: {
    background: "#13161e",
    border: "1px solid #2a2d3a",
    borderRadius: "16px",
    padding: "32px",
    width: "100%",
    maxWidth: "420px",
    boxShadow: "0 0 60px rgba(99,102,241,0.08)",
  },
  header: {
    display: "flex",
    alignItems: "center",
    gap: "10px",
    marginBottom: "28px",
  },
  dot: {
    width: "10px",
    height: "10px",
    borderRadius: "50%",
    background: "#6366f1",
    boxShadow: "0 0 8px #6366f1",
    flexShrink: 0,
  },
  title: {
    margin: 0,
    fontSize: "20px",
    fontWeight: 700,
    color: "#e2e8f0",
    letterSpacing: "0.05em",
  },
  subtitle: {
    fontSize: "11px",
    color: "#4a5568",
    letterSpacing: "0.12em",
    textTransform: "uppercase",
    marginLeft: "auto",
  },
  section: {
    display: "flex",
    flexDirection: "column",
    gap: "12px",
    padding: "4px 0",
  },
  divider: {
    border: "none",
    borderTop: "1px solid #1e2130",
    margin: "20px 0",
  },
  label: {
    fontSize: "11px",
    color: "#4a5568",
    letterSpacing: "0.1em",
    textTransform: "uppercase",
    marginBottom: "2px",
  },
  addressBox: {
    background: "#0d0f14",
    border: "1px solid #2a2d3a",
    borderRadius: "8px",
    padding: "10px 14px",
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
  },
  address: {
    fontSize: "13px",
    color: "#6366f1",
    fontWeight: 600,
  },
  balanceRow: {
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
  },
  balanceValue: {
    fontSize: "22px",
    fontWeight: 700,
    color: "#e2e8f0",
    letterSpacing: "-0.02em",
    marginTop: "4px",
  },
  input: {
    background: "#0d0f14",
    border: "1px solid #2a2d3a",
    borderRadius: "8px",
    padding: "10px 14px",
    color: "#e2e8f0",
    fontSize: "13px",
    fontFamily: "inherit",
    outline: "none",
    transition: "border-color 0.2s",
    width: "100%",
    boxSizing: "border-box",
  },
  btnRow: {
    display: "flex",
    gap: "10px",
  },
  btn: {
    padding: "11px 18px",
    borderRadius: "8px",
    border: "none",
    cursor: "pointer",
    fontSize: "13px",
    fontFamily: "inherit",
    fontWeight: 600,
    letterSpacing: "0.03em",
    transition: "opacity 0.15s, transform 0.1s",
  },
  btnPrimary: {
    background: "#6366f1",
    color: "#fff",
  },
  btnSecondary: {
    background: "#1e2130",
    color: "#a78bfa",
    border: "1px solid #3730a3",
  },
  btnGhost: {
    background: "transparent",
    color: "#6366f1",
    border: "1px solid #2a2d3a",
    padding: "8px 14px",
  },
  mintHint: {
    fontSize: "11px",
    color: "#4a5568",
    fontStyle: "italic",
  },
  feedback: {
    marginTop: "16px",
    fontSize: "12px",
    padding: "10px 14px",
    background: "#0d0f14",
    border: "1px solid #2a2d3a",
    borderRadius: "8px",
    lineHeight: 1.5,
    wordBreak: "break-all",
  },
  spinner: {
    display: "inline-block",
    animation: "spin 1s linear infinite",
  },
};