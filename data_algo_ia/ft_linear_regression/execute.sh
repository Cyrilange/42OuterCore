#!/bin/bash
# setup_env_nosudo_v2.sh
# Checks for Python3 and matplotlib, installs matplotlib without sudo.
# Handles the case where "pip3" command doesn't exist at all.

set -e

echo "=== Checking Python3 ==="
if command -v python3 &> /dev/null; then
    echo "Python3 is already installed: $(python3 --version)"
else
    echo "Python3 not found, and installing it requires sudo/admin rights."
    echo "Ask your system admin to install python3."
    exit 1
fi

echo ""
echo "=== Checking pip ==="
if python3 -m pip --version &> /dev/null; then
    echo "pip is already available: $(python3 -m pip --version)"
else
    echo "pip not found. Trying ensurepip (no sudo needed)..."
    if python3 -m ensurepip --user &> /dev/null; then
        echo "pip installed via ensurepip."
    else
        echo "ensurepip not available. Downloading get-pip.py instead..."
        if command -v curl &> /dev/null; then
            curl -sS https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py
        elif command -v wget &> /dev/null; then
            wget -q -O /tmp/get-pip.py https://bootstrap.pypa.io/get-pip.py
        else
            echo "Neither curl nor wget is available. Cannot fetch get-pip.py."
            exit 1
        fi
        python3 /tmp/get-pip.py --user
    fi
fi

echo ""
echo "=== Checking matplotlib ==="
if python3 -c "import matplotlib" &> /dev/null; then
    echo "matplotlib is already installed."
else
    echo "matplotlib not found. Installing for current user only (no sudo)..."
    python3 -m pip install --user matplotlib --break-system-packages
fi

echo ""
echo "=== Final check ==="
python3 -c "import matplotlib; print('matplotlib version:', matplotlib.__version__)"

echo ""
echo "All set. You can now run: python3 train.py"