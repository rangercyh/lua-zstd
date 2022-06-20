# lua-zstd
lua binding for https://github.com/facebook/zstd

# useage
```lua
local ztsd = require "zstd"


local str = "asdf"
local s = ztsd.compress(str)
print(s, string.len(s))

assert(ztsd.decompress(s, string.len(str)) == str)
```

