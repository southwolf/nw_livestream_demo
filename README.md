Some documentation: http://www.jianshu.com/p/5a4c7ce2be54

# Developing "hybrid" electron /C++ app in windows

First, install Node, VS/VS Code, Electron, etc.

https://nodejs.org/dist/v6.10.0/node-v6.10.0-x86.msi

`node-gyp` for building C++, Python and Visual Studio

```
npm install -g cnpm --registry=https://registry.npm.taobao.org

cnpm install -g --production windows-build-tools

cnpm install -g electron electron-reload electron-prebuilt electron-rebuild electron-packager

cnpm install -g node-gyp
```

Create hello.cc and binding.gyp

`node-gyp configure`

Add require modules in `index.js`

```
const addon = require('./build/Release/addon');

console.log(addon.hello());
```
or in `index.html`
```
<script>
  var addon = require("./build/Release/addon");
  document.write(addon.hello());
</script>
```

Then `npm install` to compile everything

If you get `Uncaught Error: The system cannot find message text for message number 0x%1 in the message file
%2.`

Run

`node-gyp rebuild -target=1.4.13 -arch=ia32 -dist-url=https://atom.i
o/download/atom-shell`

