# pico_lcd
---
## CMake 설정
cmake -S . -B build -G "Unix Makefiles" -DPICO_BOARD=pico

## CMake 빌드
cmake --build build -j4

## 다운로드
python .\down.py
