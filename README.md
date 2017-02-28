# windows 下开发 electron /C++

安装 Node, VS/VS Code, Electron 等依赖

https://nodejs.org/dist/v6.10.0/node-v6.10.0-x86.msi

编译 C++ 需要 node-gyp, 最好安装 VS 2015

npm install -g cnpm --registry=https://registry.npm.taobao.org

cnpm install -g --production windows-build-tools

设置环境变量 PYTHON 指定到 python.exe

cnpm install -g electron electron-reload electron-prebuilt electron-rebuild electron-packager

cnpm install -g node-gyp
