
const contractAddress = "0x0f63dc5a0ca0c91d28c01e84153f79eeb4a3e07f";
const contractABI = [
    
    "function safeMint(address to, string memory uri) public"
];

let provider;
let signer;
let contract;


const connectBtn = document.getElementById("connectBtn");
const walletAddressText = document.getElementById("walletAddress");
const mintSection = document.getElementById("mintSection");
const mintBtn = document.getElementById("mintBtn");
const tokenUriInput = document.getElementById("tokenUriInput");
const statusText = document.getElementById("statusText");


async function connectWallet() {
    if (typeof window.ethereum !== "undefined") {
        try {
           
            const accounts = await window.ethereum.request({ method: "eth_requestAccounts" });
            const userAddress = accounts[0];
            
         
            provider = new ethers.BrowserProvider(window.ethereum);
            signer = await provider.getSigner();
            contract = new ethers.Contract(contractAddress, contractABI, signer);
            walletAddressText.innerText = `Connecté : ${userAddress}`;
            connectBtn.style.display = "none";
            mintSection.style.display = "block";
        } catch (error) {
            console.error("Connexion refusée", error);
        }
    } else {
        alert("Installe MetaMask pour utiliser cette application !");
    }
}

async function mintNFT() {
    const uri = tokenUriInput.value;
    if (!uri) {
        alert("enter your IPFS link !");
        return;
    }

    try {
        statusText.innerText = "waiting validation MetaMask...";
        const userAddress = await signer.getAddress();
        const tx = await contract.safeMint(userAddress, uri);
        
        statusText.innerText = "Transaction send ! waiting for block...";
        await tx.wait();

        statusText.innerText = "NFT minted with succès !  Check on Etherscan !";
    } catch (error) {
        console.error(error);
        statusText.innerText = "Error during mint.";
    }
}


connectBtn.addEventListener("click", connectWallet);
mintBtn.addEventListener("click", mintNFT);