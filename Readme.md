CuteFanficBGM
=============

An implementation of [FanficBGM](http://) using Qt.
The original idea, playlist and implementation was developed by and is the 
intellectual property of user *Guest Poster*.

Some [screenshots](https://imgur.com/a/wqUOq).

**Note**: while CuteFanficBGM technically works on Windows too, I advise using
the original implementation as Windows user since I can't test nor support this
platform in any way.


Requirements
------------

 * C++11 must be supported by your compiler/stdlib
 * Qt 5 with `multimedia` support  
**Note**: some package managers seperate the multimedia part into an additional package.


Functionality
-------------

The goal was to provide the functionality Windows users experience with 
[FanficBGM](http://) for people using unix compliant systems, therefore, 
CuteFanficBGM should behave pretty similar.

However, there are minor differences:

   * no simple view
   * no options view  
     Instead the whole state of CuteFanficBGM is restored whenever you launch 
     it again. You don't have to deal with preserving properties yourself, the program is smart enough.
   * additional display of song title and a volume change bar


Building
--------

### Linux

After you statisfied the Qt5 requirement there's not much left to do.
Fire up a terminal and within the CuteFanficBGM directory execute:

    qmake
    make

Done!


### OS X

There is a precompiled binary in [Releases](https://github.com/Argon-/CuteFanficBGM/releases), 
compiled using 10.10. In theory it should work on 10.9, 10.8 and 10.7 too but I have
no way to verify this.

Technically, you can just do the same Linux users do. Use your favorite 
package manager (e.g. [homebrew](http://brew.sh)) and install the dependency:

    brew install qt5

One minor difference though: `qt5`'s `qmake` is not in your `PATH` by default. 
Homebrew does this deliberately because of compatibility issues with `qt4`.
However, just use the full path to `qmake` or do it like this:

    $(brew --prefix qt5)/bin/qmake
    make

