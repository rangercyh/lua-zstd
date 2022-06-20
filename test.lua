local ztsd = require "zstd"


local str = "asdf"
local s = ztsd.compress(str)
print(s, string.len(s))

assert(ztsd.decompress(s, string.len(str)))

