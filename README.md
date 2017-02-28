# windows 下开发 electron /C++

安装 Node, VS/VS Code, Electron 等依赖

https://nodejs.org/dist/v6.10.0/node-v6.10.0-x86.msi

编译 C++ 需要 node-gyp, 最好安装 VS 2015

npm install -g cnpm --registry=https://registry.npm.taobao.org

cnpm install -g --production windows-build-tools

设置环境变量 PYTHON 指定到 python.exe

cnpm install -g electron electron-reload electron-prebuilt electron-rebuild electron-packager

cnpm install -g node-gyp


编写 hello.cc 和 binding.gyp
运行 node-gyp configure

index.js 添加调用
```
const addon = require('./build/Release/addon');

console.log(addon.hello());
```
或 index.html 添加
```
<script>
  var addon = require("./build/Release/addon");
  document.write(addon.hello());
</script>
```

(npm install 编译模块)

如果运行出现 Uncaught Error: The system cannot find message text for message number 0x%1 in the message file
%2.

node-gyp rebuild -target=1.4.13 -arch=ia32 -dist-url=https://atom.i
o/download/atom-shell

