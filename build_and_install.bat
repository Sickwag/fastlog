@echo off
echo Building FastLog Library...

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置项目（Debug模式）
cmake .. -DCMAKE_BUILD_TYPE=Debug

REM 编译项目
cmake --build . --config Debug

REM 安装库到指定位置
cmake --install . --config Debug

echo Build and installation completed!
echo Library files are installed in ./out/bin/lib
echo Header files are installed in ./out/bin/include
pause