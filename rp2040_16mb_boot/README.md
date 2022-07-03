# rp2040_boot
---
## 준비
sudo python3 -m pip install pyserial

## CMake 설정 for Windows 
cmake -S . -B build -G "MinGW Makefiles" -DPICO_BOARD=rp2040_16mb

## CMake 설정 for macOS 
cmake -S . -B build -DPICO_BOARD=rp2040_16mb -DPICO_SDK_PATH="~/pico/pico-sdk"

## CMake 빌드
cmake --build build -j20

## 다운로드
python .\down.py
