rapngasm [![Gem Version](https://badge.fury.io/rb/rapngasm.svg)](http://badge.fury.io/rb/rapngasm)
========
Ruby interface for apngasm

Requirements
------------
rapngasm requires libapngasm and SWIG.  
APNGAsm install instructions can be found in the "Installing" section 
[here](https://github.com/apngasm/apngasm).  
SWIG can be found [here](https://github.com/swig/swig).  
  
If you are using rapngasm on Heroku you will need the rapngasm build pack to enable 
native compilation of the extension during bundling. You can find the buildpack 
[here](https://github.com/Kagetsuki/heroku-rapngasm-buildpack).

Building
--------
```
rake compile
```

Specs!
------
```
rspec
```

License
-------
libpng

Support
-------
File a github issue

Expediated Support
------------------
Submit an issue and put up a bounty on it [here](https://www.bountysource.com/teams/apngasm/issues?tracker_ids=255971).

Copyright
---------
Genshin Souzou Kabushiki Kaisha  
apngasm is copyright Max Stepin and is maintained by Max Stepin & Genshin Souzou K.K.
