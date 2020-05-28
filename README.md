# ConfigManager
a simple and light class for reading and parsing config files;
# file syntax
this is an example :
```
name = null 
[apple]
name = apple
weight = 1
[banana]
name = banana
weight = 0.8
# this is comment
```
# usage 
## class Config
Config is something you store all the keys an values , it was mananged by ConfigMgr. the Configs like the "[apple]" or "[banana]" in the file
### member functions:
#### at()
like some container ,at is the function which can get a value by it‘s key. if the key doesn't exist , it will throw a exception.
#### operator[]
[] is an operator overload. it works like at() but doesn't throw any exceptions. if the key does not exist , it will create ,and make the value equal to "";
#### to_string()
to_string is a function to convert to a string that like the file mentioned above.
#### remove()
to remove a key is to erase the key
#### insert()
to insert a key and a value.
####
## class ConfigMgr
the ConfigMgr manages all Configs.
